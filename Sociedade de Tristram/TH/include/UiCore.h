#pragma once
// UiCore.h - Sociedade de Tristram UI layer (pure logic, NO engine dependencies).
//
// Coordinate space: "panel space" = the same space as CursorX/CursorY and
// DisplayObject (0,0 = top-left of the visible screen, WITHOUT Screen_LeftBorder /
// Screen_TopBorder). Only UiKit.cpp adds the borders when it touches the surface.
//
// Rule of this layer: every widget owns exactly ONE UiRect. Drawing and hit-testing
// both read that same rectangle, so they cannot drift apart.
#include <cstdint>

// Half-open rectangle: contains x in [x, x+w) and y in [y, y+h).
struct UiRect
{
    int x, y, w, h;
    constexpr UiRect() : x(0), y(0), w(0), h(0) {}
    constexpr UiRect(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}
    constexpr int  Right()  const { return x + w; }   // exclusive
    constexpr int  Bottom() const { return y + h; }   // exclusive
    constexpr bool Valid()  const { return w > 0 && h > 0; }
    constexpr bool Contains(int px, int py) const
    {
        return Valid() && px >= x && px < x + w && py >= y && py < y + h;
    }
    constexpr UiRect Inset(int d) const { return UiRect(x + d, y + d, w - 2 * d, h - 2 * d); }
};

enum class UiButtonState { Normal, Hover, Pressed, Disabled };

struct UiButton
{
    UiRect rect;
    bool   visible = true;
    bool   enabled = true;

    // True when the click belongs to this button (even if disabled), so it never
    // falls through to whatever is drawn underneath.
    bool Consumes(int px, int py) const { return visible && rect.Contains(px, py); }
    // True when the click should actually run the button's action.
    bool Activates(int px, int py) const { return Consumes(px, py) && enabled; }

    UiButtonState StateAt(int px, int py, bool mouseDown) const
    {
        if (!enabled) return UiButtonState::Disabled;
        if (!Consumes(px, py)) return UiButtonState::Normal;
        return mouseDown ? UiButtonState::Pressed : UiButtonState::Hover;
    }
};

// ---------------------------------------------------------------------------
// Sigils page
// ---------------------------------------------------------------------------
constexpr int UiSigilCount = 5; // Veu, Ferro, Arcano, Pacto, Brasas

enum class UiSigilState
{
    Empty,           // slot is the empty sentinel
    Bound,           // slot holds the Sigil that belongs to this row
    UnknownContent,  // slot holds something else (old/unexpected data): never touched
    Unavailable      // row cannot be used right now (multiplayer)
};

// Read-only classification. Mirrors the validation used by the bind click, so the
// page can never say "empty" while the bind click says "already bound".
//   itemCodeIsNone   : item.ItemCode == IC_M1_NONE
//   isZeroSentinel   : the legacy all-zero reserved slot (treated as empty)
//   baseIndexOffset  : item.baseItemIndex - BI_2504_SIGIL_VEIL
inline UiSigilState UiClassifySigilSlot(int slot, bool itemCodeIsNone, bool isZeroSentinel,
                                        int baseIndexOffset, bool singlePlayer)
{
    if (!itemCodeIsNone && baseIndexOffset == slot) return UiSigilState::Bound;
    if (itemCodeIsNone || isZeroSentinel) return singlePlayer ? UiSigilState::Empty
                                                              : UiSigilState::Unavailable;
    return UiSigilState::UnknownContent;
}

struct UiSigilPageLayout
{
    UiRect tabInventory;
    UiRect tabSigils;
    UiRect area;                 // whole page: consumes clicks so they never reach the backpack
    UiRect rows[UiSigilCount];
    UiRect footer;

    // panelLeft/panelTop/panelWidth come from InventoryPanelRect.
    static UiSigilPageLayout Build(int panelLeft, int panelTop, int panelWidth)
    {
        UiSigilPageLayout L;
        L.tabInventory = UiRect(panelLeft + 18,  panelTop + 211, 140, 11);
        L.tabSigils    = UiRect(panelLeft + 160, panelTop + 211, 143, 11);
        L.area         = UiRect(panelLeft + 17,  panelTop + 222, panelWidth - 17, 204);
        for (int i = 0; i < UiSigilCount; ++i)
            L.rows[i]  = UiRect(panelLeft + 18, panelTop + 235 + i * 36, 285, 34);
        L.footer       = UiRect(panelLeft + 18,  panelTop + 414, 285, 12);
        return L;
    }

    int RowAt(int px, int py) const
    {
        for (int i = 0; i < UiSigilCount; ++i)
            if (rows[i].Contains(px, py)) return i;
        return -1;
    }
};

// ---------------------------------------------------------------------------
// Text helpers (pure)
// ---------------------------------------------------------------------------
// The bitmap font has no accented glyphs (its codepage folds them to base letters).
// Source text may arrive as UTF-8 (C3 xx) OR as single Latin-1/CP1252 bytes, depending on
// the build machine's execution charset, so both are accepted and folded to ASCII.
// Returns the ASCII letter for a Latin-1 code point 0xC0..0xFF, or '?' if there is none.
inline char UiLatin1ToAscii(unsigned cp)
{
    if (cp >= 0xC0 && cp <= 0xC5) return 'A';
    if (cp == 0xC7) return 'C';
    if (cp >= 0xC8 && cp <= 0xCB) return 'E';
    if (cp >= 0xCC && cp <= 0xCF) return 'I';
    if (cp == 0xD1) return 'N';
    if ((cp >= 0xD2 && cp <= 0xD6) || cp == 0xD8) return 'O';
    if (cp >= 0xD9 && cp <= 0xDC) return 'U';
    if (cp == 0xDD) return 'Y';
    if (cp >= 0xE0 && cp <= 0xE5) return 'a';
    if (cp == 0xE7) return 'c';
    if (cp >= 0xE8 && cp <= 0xEB) return 'e';
    if (cp >= 0xEC && cp <= 0xEF) return 'i';
    if (cp == 0xF1) return 'n';
    if ((cp >= 0xF2 && cp <= 0xF6) || cp == 0xF8) return 'o';
    if (cp >= 0xF9 && cp <= 0xFC) return 'u';
    if (cp == 0xFD || cp == 0xFF) return 'y';
    return '?';
}

// Returns the output length. Output is always NUL-terminated when cap > 0.
inline int UiFoldPtBr(const char* in, char* out, int cap)
{
    if (!out || cap <= 0) return 0;
    int n = 0;
    auto put = [&](char c) { if (n < cap - 1) out[n++] = c; };
    if (in) {
        const unsigned char* p = (const unsigned char*)in;
        while (*p) {
            const unsigned char c = *p;
            if (c < 0x20) { ++p; continue; }
            if (c < 0x80) { put((char)c); ++p; continue; }
            // Valid UTF-8 two-byte sequence for U+0080..U+07FF
            if ((c & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80) {
                put(UiLatin1ToAscii(((unsigned)(c & 0x1F) << 6) | (p[1] & 0x3F)));
                p += 2;
                continue;
            }
            // Valid UTF-8 three/four-byte sequence (punctuation, emoji...): one '?'
            int len = (c & 0xF0) == 0xE0 ? 3 : (c & 0xF8) == 0xF0 ? 4 : 1;
            bool ok = len > 1;
            for (int k = 1; ok && k < len; ++k) if ((p[k] & 0xC0) != 0x80) ok = false;
            if (ok) { put('?'); p += len; continue; }
            // Not UTF-8: a lone Latin-1/CP1252 byte
            put(UiLatin1ToAscii(c));
            ++p;
        }
    }
    out[n] = '\0';
    return n;
}

// Largest number of leading characters of s whose total width is <= maxWidth.
// widthOf(unsigned char) must return the advance of one glyph.
template <class WidthFn>
inline int UiFitChars(const char* s, int maxWidth, WidthFn widthOf)
{
    if (!s || maxWidth <= 0) return 0;
    int used = 0, count = 0;
    for (const unsigned char* p = (const unsigned char*)s; *p; ++p) {
        const int w = widthOf(*p);
        if (used + w > maxWidth) break;
        used += w;
        ++count;
    }
    return count;
}

// Writes into 'out' the longest text that fits in maxWidth, GUARANTEEING that the width
// of 'out' is <= maxWidth (an empty string when nothing fits).
//   - the whole text, when it fits;
//   - otherwise leading characters followed by "..", but only when ".." itself fits;
//   - otherwise leading characters alone (never an ellipsis that would overflow).
// Returns the length written. 'out' is always NUL-terminated when cap > 0.
template <class WidthFn>
inline int UiTruncateToFit(const char* s, int maxWidth, WidthFn widthOf, char* out, int cap)
{
    if (!out || cap <= 0) return 0;
    out[0] = '\0';
    if (!s || maxWidth <= 0) return 0;

    int total = 0;
    for (const unsigned char* p = (const unsigned char*)s; *p; ++p) total += widthOf(*p);

    int n = 0;
    if (total <= maxWidth) {
        while (s[n] && n < cap - 1) { out[n] = s[n]; ++n; }
    } else {
        const int dots = widthOf((unsigned char)'.') * 2;
        const bool useDots = dots <= maxWidth && cap >= 3;
        int keep = UiFitChars(s, useDots ? maxWidth - dots : maxWidth, widthOf);
        const int room = useDots ? cap - 3 : cap - 1;
        if (keep > room) keep = room;
        for (; n < keep; ++n) out[n] = s[n];
        if (useDots) { out[n++] = '.'; out[n++] = '.'; }
    }
    out[n] = '\0';
    return n;
}
