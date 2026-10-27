#include "stdafx.h"
#include "UiKit.h"

// Sociedade de Tristram UI layer - engine side.
// Surface facts verified in the source: WorkingSurface is a byte-per-pixel buffer of
// WorkingWidth x WorkingHeight that INCLUDES the Screen_*Border margins, and row y
// starts at y * WorkingWidth (YOffsetHashTable[y] is built that way in dx.cpp).

namespace {

constexpr int kFontLetters = 68;   // FontWidthSmall[68]
constexpr int kFontCodes   = 128;  // FontIndexSmall[128]

bool SurfaceReady()
{
    return WorkingSurface && WorkingWidth > 0 && WorkingHeight > 0;
}

// Clip a panel-space rect to the surface; returns false when nothing is visible.
bool ClipToSurface(const UiRect& r, int& x0, int& y0, int& x1, int& y1)
{
    if (!SurfaceReady() || !r.Valid()) return false;
    x0 = r.x + Screen_LeftBorder;  y0 = r.y + Screen_TopBorder;
    x1 = r.Right() + Screen_LeftBorder;  y1 = r.Bottom() + Screen_TopBorder;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > WorkingWidth)  x1 = WorkingWidth;
    if (y1 > WorkingHeight) y1 = WorkingHeight;
    return x1 > x0 && y1 > y0;
}

// Letter index for a source byte, or -1 when the byte has no valid glyph slot.
// 'c' is treated as UNSIGNED: the old DrawText indexed Codepage[] with a signed char,
// which reads before the array for any byte >= 0x80.
int GlyphIndex(unsigned char c)
{
    const unsigned code = Codepage[c];
    if (code >= (unsigned)kFontCodes) return -1;
    const unsigned letter = FontIndexSmall[code];
    if (letter >= (unsigned)kFontLetters) return -1;
    return (int)letter;
}

int GlyphAdvance(unsigned char c)
{
    const int letter = GlyphIndex(c);
    return letter < 0 ? 0 : FontWidthSmall[letter] + 1;
}

} // namespace

uint8_t UiToneColor(UiTone tone, bool hot)
{
    // THEME: ramp base + shade nibble. Tune the nibbles in game.
    switch (tone) {
    case UiTone::Gold:   return (uint8_t)(BLC_YELLOW + (hot ? 3 : 6));
    case UiTone::Danger: return (uint8_t)(BLC_RED    + (hot ? 3 : 6));
    case UiTone::Dim:    return (uint8_t)(BLC_GREY   + 12);
    case UiTone::Neutral:
    default:             return (uint8_t)(BLC_GREY   + (hot ? 4 : 8));
    }
}

void UiFillRect(const UiRect& r, uint8_t color)
{
    int x0, y0, x1, y1;
    if (!ClipToSurface(r, x0, y0, x1, y1)) return;
    for (int y = y0; y < y1; ++y)
        memset(WorkingSurface + (size_t)y * WorkingWidth + x0, color, (size_t)(x1 - x0));
}

void UiFrameRect(const UiRect& r, uint8_t color)
{
    if (!r.Valid()) return;
    UiFillRect(UiRect(r.x, r.y, r.w, 1), color);
    UiFillRect(UiRect(r.x, r.Bottom() - 1, r.w, 1), color);
    UiFillRect(UiRect(r.x, r.y, 1, r.h), color);
    UiFillRect(UiRect(r.Right() - 1, r.y, 1, r.h), color);
}

int UiTextWidth(const char* utf8)
{
    char folded[200];
    UiFoldPtBr(utf8, folded, (int)sizeof(folded));
    int width = 0;
    for (const unsigned char* p = (const unsigned char*)folded; *p; ++p) width += GlyphAdvance(*p);
    return width;
}

void UiDrawText(const UiRect& area, int baseline, const char* utf8, int fontColor, UiAlign align)
{
    if (!utf8 || !*utf8 || !SurfaceReady() || !area.Valid()) return;

    char folded[200];
    UiFoldPtBr(utf8, folded, (int)sizeof(folded));

    // Guaranteed to fit: UiTruncateToFit never returns text wider than area.w, and drops
    // the ".." when even the dots do not fit (very narrow rectangles).
    char fitted[204];
    UiTruncateToFit(folded, area.w, GlyphAdvance, fitted, (int)sizeof(fitted));
    if (!fitted[0]) return;

    int width = 0;
    for (const unsigned char* p = (const unsigned char*)fitted; *p; ++p) width += GlyphAdvance(*p);
    int x = area.x;
    if (align == UiAlign::Center) x += (area.w - width) / 2;
    else if (align == UiAlign::Right) x += area.w - width;

    const int surfaceY = area.y + baseline + Screen_TopBorder;
    const int surfaceX = x + Screen_LeftBorder;
    const int rows = (int)(sizeof(YOffsetHashTable) / sizeof(YOffsetHashTable[0]));
    // Keep a margin above the baseline for the glyph body and a little below it.
    if (surfaceY < 20 || surfaceY >= WorkingHeight - 2 || surfaceY >= rows) return;
    if (surfaceX < 0 || surfaceX + width > WorkingWidth) return;

    int offset = YOffsetHashTable[surfaceY] + surfaceX;
    for (const unsigned char* p = (const unsigned char*)fitted; *p; ++p) {
        const int letter = GlyphIndex(*p);
        if (letter > 0) DrawLetter(offset, letter, (char)fontColor);
        offset += letter < 0 ? 0 : FontWidthSmall[letter] + 1;
    }
}

void UiDrawButton(const UiButton& button, const char* label, int fontColor, bool selected)
{
    if (!button.visible || !button.rect.Valid()) return;
    const bool down = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    const UiButtonState state = button.StateAt(CursorX, CursorY, down);

    UiTone tone = UiTone::Neutral;
    bool hot = false;
    if (state == UiButtonState::Disabled) tone = UiTone::Dim;
    else if (selected || state == UiButtonState::Hover || state == UiButtonState::Pressed) {
        tone = UiTone::Gold; hot = (state != UiButtonState::Normal);
    }

    UiFillRect(button.rect, 0);                         // opaque: hides whatever art is underneath
    if (state == UiButtonState::Pressed) UiFillRect(button.rect.Inset(1), UiToneColor(UiTone::Dim, false));
    UiFrameRect(button.rect, UiToneColor(tone, hot));

    // Baseline kept at +13 inside an 18px button (the value the old labels used);
    // scaled down proportionally for shorter buttons so the label stays inside.
    const int baseline = button.rect.h >= 18 ? 13 : button.rect.h - 2;
    UiDrawText(button.rect.Inset(2), baseline - 2, label,
               state == UiButtonState::Disabled ? C_0_White : fontColor, UiAlign::Center);
}
