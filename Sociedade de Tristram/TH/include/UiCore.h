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

// Backpack grid. InventoryPanel.cpp static_asserts these against the engine's InvCols/InvRows.
constexpr int UiInvCols = 10, UiInvRows = 7, UiCellPitch = 29, UiCellSize = 28;

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

// ---------------------------------------------------------------------------
// Hit list: ONE ordered list of rectangles per window. Draw code reads the rectangles to
// paint, input code reads the same list to decide who gets a click. Priority is explicit
// (z); a click is delivered to exactly one entry.
// ---------------------------------------------------------------------------
constexpr int UiMaxHits = 32;

struct UiHit
{
    int    id;
    UiRect rect;
    int    z;
    bool   enabled;
};

struct UiHitList
{
    UiHit hits[UiMaxHits];
    int   count = 0;

    void Clear() { count = 0; }
    bool Add(int id, const UiRect& r, int z, bool enabled = true)
    {
        if (count >= UiMaxHits || !r.Valid()) return false;
        hits[count].id = id; hits[count].rect = r; hits[count].z = z; hits[count].enabled = enabled;
        ++count;
        return true;
    }
    // Topmost entry under the point. Highest z wins; with equal z the entry added LAST wins.
    const UiHit* Pick(int px, int py) const
    {
        const UiHit* best = nullptr;
        for (int i = 0; i < count; ++i) {
            if (!hits[i].rect.Contains(px, py)) continue;
            if (!best || hits[i].z >= best->z) best = &hits[i];
        }
        return best;
    }
};

// ---------------------------------------------------------------------------
// Inventory window layout (panel space). Built from the panel rectangle and three flags,
// rebuilt whenever one of them (or the panel position) changes.
// ---------------------------------------------------------------------------
enum UiInvId : int
{
    UiInv_None        = 0,
    UiInv_TabInventory,
    UiInv_TabSigils,
    UiInv_Organize,
    UiInv_Companions,
    UiInv_Summon,
    UiInv_StoreFilter,
    UiInv_StoreAll,
    UiInv_ControlsEnd,              // every id below this one is a button or a tab
    UiInv_SigilPage   = 20,         // blocker: keeps clicks away from the backpack cells under the page
    UiInv_SigilRow0   = 30          // + 0..4
};

struct UiInvFlags
{
    bool stash           = false;
    bool sigilsPage      = false;
    bool companionActive = false;
    bool operator==(const UiInvFlags& o) const
    {
        return stash == o.stash && sigilsPage == o.sigilsPage && companionActive == o.companionActive;
    }
    bool operator!=(const UiInvFlags& o) const { return !(*this == o); }
};

struct UiInventoryLayout
{
    UiRect panel;
    UiRect rowA, rowB;               // the two rows of the bottom bar
    UiRect tabInventory, tabSigils, gold;
    UiRect organize, companions, summon, storeFilter, storeAll;
    UiRect backpackArea;             // 10 x 7 cells + the page that replaces them
    UiRect sigilRows[UiSigilCount];
    UiRect sigilIcons[UiSigilCount];
    UiHitList hits;

    static UiInventoryLayout Build(int left, int top, int width, int height, const UiInvFlags& f)
    {
        UiInventoryLayout L;
        L.panel = UiRect(left, top, width, height);
        const int padX = 9;
        const int barW = width - 2 * padX;
        // The bar is anchored to the bottom edge: 2px frame, row B, 2px gap, row A.
        const int rowBy = top + height - 17;
        const int rowAy = rowBy - 17;
        L.rowA = UiRect(left + padX, rowAy, barW, 15);
        L.rowB = UiRect(left + padX, rowBy, barW, 15);
        L.backpackArea = UiRect(left + 17, top + 222, width - 17, 204);

        L.organize = UiRect(L.rowB.x, L.rowB.y, 92, 15);
        if (!f.stash) {
            L.tabInventory = UiRect(L.rowA.x, L.rowA.y, 105, 15);
            L.tabSigils    = UiRect(L.tabInventory.Right() + 2, L.rowA.y, 66, 15);
            const int gx   = L.tabSigils.Right() + 6;
            L.gold         = UiRect(gx, L.rowA.y, L.rowA.Right() - gx, 15);
            L.companions   = UiRect(L.rowB.x + 95, L.rowB.y, 118, 15);
            if (f.companionActive)
                L.summon   = UiRect(L.companions.Right() + 3, L.rowB.y, L.rowB.Right() - (L.companions.Right() + 3), 15);
        } else {
            L.storeFilter  = UiRect(L.rowA.x, L.rowA.y, 134, 15);
            L.storeAll     = UiRect(L.storeFilter.Right() + 3, L.rowA.y, 84, 15);
            L.gold         = UiRect(L.rowB.x + 95, L.rowB.y, L.rowB.Right() - (L.rowB.x + 95), 15);
        }
        for (int i = 0; i < UiSigilCount; ++i) {
            L.sigilRows[i]  = UiRect(left + 18, top + 224 + i * 40, 288, 38);
            L.sigilIcons[i] = UiRect(L.sigilRows[i].x + 3, L.sigilRows[i].y + 2, 34, 34);
        }

        // Registration order does not matter; z does. Controls always beat the page.
        const int zControl = 20, zRow = 10, zPage = 5;
        L.hits.Add(UiInv_Organize, L.organize, zControl);
        if (!f.stash) {
            L.hits.Add(UiInv_TabInventory, L.tabInventory, zControl);
            L.hits.Add(UiInv_TabSigils,    L.tabSigils,    zControl);
            L.hits.Add(UiInv_Companions,   L.companions,   zControl);
            if (f.companionActive) L.hits.Add(UiInv_Summon, L.summon, zControl);
            if (f.sigilsPage) {
                L.hits.Add(UiInv_SigilPage, L.backpackArea, zPage);
                for (int i = 0; i < UiSigilCount; ++i) L.hits.Add(UiInv_SigilRow0 + i, L.sigilRows[i], zRow);
            }
        } else {
            L.hits.Add(UiInv_StoreFilter, L.storeFilter, zControl);
            L.hits.Add(UiInv_StoreAll,    L.storeAll,    zControl);
        }
        return L;
    }

    int Pick(int px, int py) const
    {
        const UiHit* h = hits.Pick(px, py);
        return h ? h->id : (int)UiInv_None;
    }
    // Buttons and tabs only (what InventoryPanel_CursorOnControls() reports).
    static bool IsControl(int id) { return id > UiInv_None && id < UiInv_ControlsEnd; }
    static int  SigilRowOf(int id) { return id >= UiInv_SigilRow0 && id < UiInv_SigilRow0 + UiSigilCount ? id - UiInv_SigilRow0 : -1; }
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

// ---------------------------------------------------------------------------
// Word wrap (pure). Every produced line is GUARANTEED to be <= maxWidth wide. Breaks at
// spaces when possible, hard-cuts a single word that does not fit, and truncates the last
// allowed line with ".." when text remains. Returns the number of lines written (0..maxLines).
// ---------------------------------------------------------------------------
#include <cstring>

template <class WidthFn>
inline int UiWrapLines(const char* s, int maxWidth, WidthFn widthOf, char (*out)[160], int maxLines)
{
    if (!s || !out || maxLines <= 0 || maxWidth <= 0) return 0;
    int lines = 0;
    const char* p = s;
    while (*p && lines < maxLines) {
        while (*p == ' ') ++p;
        if (!*p) break;
        if (lines == maxLines - 1) {                      // last allowed line: fit or truncate
            UiTruncateToFit(p, maxWidth, widthOf, out[lines], 160);
            ++lines;
            break;
        }
        const int total = (int)std::strlen(p);
        const int fit = UiFitChars(p, maxWidth, widthOf);
        if (fit <= 0) break;                              // not even one glyph fits
        int cut = fit;
        if (fit < total) {
            while (cut > 0 && p[cut] != ' ') --cut;       // back up to a space
            if (cut == 0) cut = fit;                      // a single long word
        }
        int len = cut > 159 ? 159 : cut;
        while (len > 0 && p[len - 1] == ' ') --len;       // no trailing spaces
        std::memcpy(out[lines], p, (size_t)len);
        out[lines][len] = '\0';
        ++lines;
        p += cut;
    }
    return lines;
}

// ---------------------------------------------------------------------------
// Notifications (pure). Collects what should be on screen from a ring of messages.
//   - chronological order (oldest first) starting at ringNext, NOT slot order;
//   - empty and expired entries take no space;
//   - consecutive identical messages merge into one line with a counter;
//   - at most maxLines lines, keeping the newest;
//   - 'fading' is set during the last fadeMs of a line's life.
// The message texts keep their meaning; only what is shown changes.
// ---------------------------------------------------------------------------
struct UiNotifyLine
{
    char      text[160];
    int       count;
    long long timeMs;
    bool      fading;
};

inline int UiNotifyCollect(const char* const* texts, const long long* times, const bool* isSystem,
                           int n, int ringNext, long long now, long long ttlMs, long long fadeMs,
                           int maxLines, UiNotifyLine* out)
{
    if (!texts || !times || !isSystem || !out || n <= 0 || maxLines <= 0) return 0;
    int m = 0;
    for (int k = 0; k < n; ++k) {
        const int idx = ((ringNext % n) + n + k) % n;
        if (!isSystem[idx] || !texts[idx] || !texts[idx][0]) continue;
        if (now - times[idx] > ttlMs) continue;
        if (m > 0 && std::strncmp(out[m - 1].text, texts[idx], 159) == 0) {
            ++out[m - 1].count;
            if (times[idx] > out[m - 1].timeMs) out[m - 1].timeMs = times[idx];
            continue;
        }
        std::strncpy(out[m].text, texts[idx], 159);
        out[m].text[159] = '\0';
        out[m].count = 1;
        out[m].timeMs = times[idx];
        ++m;
    }
    if (m > maxLines) {
        for (int i = 0; i < maxLines; ++i) out[i] = out[m - maxLines + i];
        m = maxLines;
    }
    for (int i = 0; i < m; ++i) out[i].fading = (now - out[i].timeMs) > (ttlMs - fadeMs);
    return m;
}

// ---------------------------------------------------------------------------
// Gold amount that is GUARANTEED to fit maxWidth: full digits when they fit, otherwise thousands
// ("2147483K") or millions ("2147M"). Display only; the real amount is never touched.
// ---------------------------------------------------------------------------
#include <cstdio>

template <class WidthFn>
inline void UiFormatGold(long long gold, int maxWidth, WidthFn widthOf, char* out, int cap)
{
    if (!out || cap <= 0) return;
    char buf[32];
    std::snprintf(buf, sizeof buf, "%lld", gold);
    auto width = [&](const char* s) { int w = 0; for (const unsigned char* p = (const unsigned char*)s; *p; ++p) w += widthOf(*p); return w; };
    if (width(buf) > maxWidth) std::snprintf(buf, sizeof buf, "%lldK", gold / 1000);
    if (width(buf) > maxWidth) std::snprintf(buf, sizeof buf, "%lldM", gold / 1000000);
    std::strncpy(out, buf, (size_t)cap - 1);
    out[cap - 1] = '\0';
}
