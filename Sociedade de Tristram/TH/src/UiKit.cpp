#include "stdafx.h"
#include "UiKit.h"

// Sociedade de Tristram UI layer - engine side.
// Surface facts verified in the source: WorkingSurface is a byte-per-pixel buffer of
// WorkingWidth x WorkingHeight that INCLUDES the Screen_*Border margins, and row y starts at
// y * WorkingWidth (YOffsetHashTable[y] is built that way in dx.cpp).

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
// 'c' is treated as UNSIGNED: the old DrawText indexed Codepage[] with a signed char, which
// reads before the array for any byte >= 0x80.
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

uint32_t Hash(int x, int y, uint32_t seed)
{
    uint32_t h = (uint32_t)x * 374761393u + (uint32_t)y * 668265263u + seed * 2246822519u;
    h = (h ^ (h >> 13)) * 1274126177u;
    return h ^ (h >> 16);
}

// ---- theme --------------------------------------------------------------------------
UiPalette g_pal;
bool      g_palReady = false;

int Luma(const PALETTEENTRY& e) { return (e.peRed * 30 + e.peGreen * 59 + e.peBlue * 11) / 100; }

// Nearest palette entry (redmean distance) among index 0 and 32..239.
uint8_t MatchRGB(int r, int g, int b)
{
    int best = 0;
    long bestD = 0x7fffffff;
    for (int i = 0; i < 240; ++i) {
        if (i > 0 && i < 32) continue;
        const int dr = r - BasePalette[i].peRed;
        const int dg = g - BasePalette[i].peGreen;
        const int db = b - BasePalette[i].peBlue;
        const int rm = (r + BasePalette[i].peRed) / 2;
        const long d = (((512 + rm) * dr * dr) >> 8) + 4L * dg * dg + (((767 - rm) * db * db) >> 8);
        if (d < bestD) { bestD = d; best = i; }
    }
    return (uint8_t)best;
}

void PutPx(int sx, int sy, uint8_t c)   // surface coordinates, clipped
{
    if (sx < 0 || sy < 0 || sx >= WorkingWidth || sy >= WorkingHeight) return;
    WorkingSurface[(size_t)sy * WorkingWidth + sx] = c;
}

} // namespace

void UiThemeRefresh()
{
    UiPalette& p = g_pal;
    p.black = 0;
    static const int stone[4][3]  = { {17,16,18}, {26,25,28}, {37,35,39}, {50,47,53} };
    static const int iron[5][3]   = { {8,8,10}, {42,42,48}, {68,68,76}, {104,104,114}, {150,150,162} };
    static const int gold[4][3]   = { {74,56,20}, {128,100,36}, {176,142,58}, {222,190,100} };
    static const int wine[3][3]   = { {34,9,15}, {64,16,26}, {112,28,42} };
    static const int arcane[2][3] = { {22,32,62}, {44,70,128} };
    for (int i = 0; i < 4; ++i) p.stone[i]  = MatchRGB(stone[i][0],  stone[i][1],  stone[i][2]);
    for (int i = 0; i < 5; ++i) p.iron[i]   = MatchRGB(iron[i][0],   iron[i][1],   iron[i][2]);
    for (int i = 0; i < 4; ++i) p.gold[i]   = MatchRGB(gold[i][0],   gold[i][1],   gold[i][2]);
    for (int i = 0; i < 3; ++i) p.wine[i]   = MatchRGB(wine[i][0],   wine[i][1],   wine[i][2]);
    for (int i = 0; i < 2; ++i) p.arcane[i] = MatchRGB(arcane[i][0], arcane[i][1], arcane[i][2]);

    // Wells: the engine re-tints pixels >= 160 and keeps the low nibble, so these three come
    // from the 240..255 ramp, picked by brightness (a dark-ish, low-chroma subset).
    int idx[16], n = 0;
    for (int i = 240; i < 256; ++i) {
        const PALETTEENTRY& e = BasePalette[i];
        const int hi = e.peRed > e.peGreen ? (e.peRed > e.peBlue ? e.peRed : e.peBlue) : (e.peGreen > e.peBlue ? e.peGreen : e.peBlue);
        const int lo = e.peRed < e.peGreen ? (e.peRed < e.peBlue ? e.peRed : e.peBlue) : (e.peGreen < e.peBlue ? e.peGreen : e.peBlue);
        if (hi - lo <= 40) idx[n++] = i;
    }
    if (n < 7) { n = 0; for (int i = 240; i < 256; ++i) idx[n++] = i; }
    for (int a = 1; a < n; ++a) {                    // insertion sort by luma, dark -> light
        const int v = idx[a]; int b = a - 1;
        while (b >= 0 && Luma(BasePalette[idx[b]]) > Luma(BasePalette[v])) { idx[b + 1] = idx[b]; --b; }
        idx[b + 1] = v;
    }
    p.well[0] = (uint8_t)idx[n > 2 ? 2 : 0];
    p.well[1] = (uint8_t)idx[n > 4 ? 4 : n - 1];
    p.well[2] = (uint8_t)idx[n > 6 ? 6 : n - 1];
    g_palReady = true;
}

const UiPalette& UiPal()
{
    if (!g_palReady) UiThemeRefresh();
    return g_pal;
}

// ---- primitives ---------------------------------------------------------------------
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

void UiPutPixel(int x, int y, uint8_t color)
{
    if (!SurfaceReady()) return;
    PutPx(x + Screen_LeftBorder, y + Screen_TopBorder, color);
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

    // Guaranteed to fit: UiTruncateToFit never returns text wider than area.w, and drops the
    // ".." when even the dots do not fit (very narrow rectangles).
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

// ---- building blocks -----------------------------------------------------------------
namespace {

// Dark masonry: staggered blocks, mortar, a lit upper edge, light grain.
void DrawStone(const UiRect& r, uint32_t seed)
{
    const UiPalette& P = UiPal();
    int x0, y0, x1, y1;
    if (!ClipToSurface(r, x0, y0, x1, y1)) return;
    for (int sy = y0; sy < y1; ++sy) {
        const int ry = sy - Screen_TopBorder - r.y;
        const int row = ry / 16, ly = ry % 16;
        const int offs = (row & 1) ? 20 : 0;
        uint8_t* dst = WorkingSurface + (size_t)sy * WorkingWidth;
        for (int sx = x0; sx < x1; ++sx) {
            const int rx = sx - Screen_LeftBorder - r.x;
            uint8_t c;
            if (ly == 0 || ((rx + offs) % 40) == 0) c = P.stone[0];          // mortar
            else if (ly == 1) c = P.stone[2];                                 // lit edge under the mortar
            else {
                const uint32_t n = Hash(rx, ry, seed) & 31;
                c = n < 5 ? P.stone[0] : n < 27 ? P.stone[1] : n < 31 ? P.stone[2] : P.stone[3];
            }
            dst[sx] = c;
        }
    }
}

void Rivet(int cx, int cy)   // 3x3 aged-gold stud
{
    const UiPalette& P = UiPal();
    UiFillRect(UiRect(cx - 1, cy - 1, 3, 3), P.gold[1]);
    UiPutPixel(cx - 1, cy - 1, P.gold[3]);
    UiPutPixel(cx + 1, cy + 1, P.gold[0]);
}

void Circle(int cx, int cy, int r, uint8_t c, int skipEvery)
{
    int x = r, y = 0, err = 1 - r, n = 0;
    while (x >= y) {
        if (skipEvery <= 0 || (n % skipEvery) != skipEvery - 1) {
            UiPutPixel(cx + x, cy + y, c); UiPutPixel(cx - x, cy + y, c);
            UiPutPixel(cx + x, cy - y, c); UiPutPixel(cx - x, cy - y, c);
            UiPutPixel(cx + y, cy + x, c); UiPutPixel(cx - y, cy + x, c);
            UiPutPixel(cx + y, cy - x, c); UiPutPixel(cx - y, cy - x, c);
        }
        ++y; ++n;
        if (err < 0) err += 2 * y + 1; else { --x; err += 2 * (y - x) + 1; }
    }
}

// The outer frame: iron bands with a gold inlay, riveted corners. Sides are 7px, top and
// bottom 2px because the head slot and the bottom bar sit right against those edges.
void DrawFrame(const UiRect& r)
{
    const UiPalette& P = UiPal();
    const uint8_t side[7] = { P.black, P.iron[1], P.iron[3], P.iron[2], P.gold[1], P.iron[0], P.black };
    for (int i = 0; i < 7; ++i) {
        UiFillRect(UiRect(r.x + i, r.y, 1, r.h), side[i]);
        UiFillRect(UiRect(r.Right() - 1 - i, r.y, 1, r.h), side[i]);
    }
    UiFillRect(UiRect(r.x, r.y, r.w, 1), P.black);
    UiFillRect(UiRect(r.x + 1, r.y + 1, r.w - 2, 1), P.iron[3]);
    UiFillRect(UiRect(r.x, r.Bottom() - 1, r.w, 1), P.black);
    UiFillRect(UiRect(r.x + 1, r.Bottom() - 2, r.w - 2, 1), P.iron[2]);
    // corner blocks 9x9
    const int cs = 9;
    const UiRect corners[4] = { UiRect(r.x, r.y, cs, cs), UiRect(r.Right() - cs, r.y, cs, cs),
                                UiRect(r.x, r.Bottom() - cs, cs, cs), UiRect(r.Right() - cs, r.Bottom() - cs, cs, cs) };
    for (int i = 0; i < 4; ++i) {
        UiFillRect(corners[i], P.iron[1]);
        UiFrameRect(corners[i], P.black);
        UiFrameRect(corners[i].Inset(1), P.iron[3]);
        Rivet(corners[i].x + cs / 2, corners[i].y + cs / 2);
    }
    // studs along the side bands
    for (int y = r.y + 64; y < r.Bottom() - 20; y += 96) { Rivet(r.x + 3, y); Rivet(r.Right() - 4, y); }
}

// A slot well. Everything decorative stays OUTSIDE 'r': the interior is exactly the rectangle
// the engine highlights, and it uses the tint-compatible ramp.
void DrawWell(const UiRect& r, bool ticks)
{
    const UiPalette& P = UiPal();
    UiFillRect(UiRect(r.x - 1, r.y - 1, r.w + 2, 1), P.iron[0]);
    UiFillRect(UiRect(r.x - 1, r.y - 1, 1, r.h + 2), P.iron[0]);
    UiFillRect(UiRect(r.x - 1, r.Bottom(), r.w + 2, 1), P.iron[3]);
    UiFillRect(UiRect(r.Right(), r.y - 1, 1, r.h + 2), P.iron[3]);
    int x0, y0, x1, y1;
    if (ClipToSurface(r, x0, y0, x1, y1)) {
        for (int sy = y0; sy < y1; ++sy) {
            uint8_t* dst = WorkingSurface + (size_t)sy * WorkingWidth;
            for (int sx = x0; sx < x1; ++sx) {
                const uint32_t n = Hash(sx, sy, 7) & 15;
                dst[sx] = n < 11 ? P.well[0] : n < 15 ? P.well[1] : P.well[2];
            }
        }
    }
    if (ticks) {   // gold corner ticks, drawn on the row/column just outside the well
        const uint8_t g = P.gold[1];
        for (int k = 0; k < 5; ++k) {
            UiPutPixel(r.x - 2 + k, r.y - 2, g);           UiPutPixel(r.x - 2, r.y - 2 + k, g);
            UiPutPixel(r.Right() + 1 - k, r.y - 2, g);     UiPutPixel(r.Right() + 1, r.y - 2 + k, g);
            UiPutPixel(r.x - 2 + k, r.Bottom() + 1, g);    UiPutPixel(r.x - 2, r.Bottom() + 1 - k, g);
            UiPutPixel(r.Right() + 1 - k, r.Bottom() + 1, g); UiPutPixel(r.Right() + 1, r.Bottom() + 1 - k, g);
        }
    }
}

void DrawPlate(const UiRect& r, uint8_t fill, uint8_t edge)
{
    UiFillRect(r, fill);
    UiFrameRect(r, edge);
}

void DrawCoin(int x, int y)   // 9x9 aged-gold coin
{
    const UiPalette& P = UiPal();
    for (int dy = 0; dy < 9; ++dy) for (int dx = 0; dx < 9; ++dx) {
        const int ox = dx - 4, oy = dy - 4, d2 = ox * ox + oy * oy;
        if (d2 > 20) continue;
        uint8_t c = d2 > 14 ? P.gold[0] : (ox + oy < -1 ? P.gold[3] : P.gold[2]);
        if (d2 <= 5 && d2 >= 2) c = P.gold[1];
        UiPutPixel(x + dx, y + dy, c);
    }
}

int ButtonBaseline(const UiRect& r) { return r.h - 2; }

} // namespace

// ---- components ----------------------------------------------------------------------
void UiDrawButton(const UiBtnView& v)
{
    if (!v.rect.Valid()) return;
    const UiPalette& P = UiPal();
    const UiRect& r = v.rect;

    uint8_t top, bottom, textTone;
    int font;
    switch (v.tone) {
    case UiBtnTone::Wine: top = P.wine[1]; bottom = P.wine[0]; font = C_3_Gold; break;
    case UiBtnTone::Gold: top = P.iron[1]; bottom = P.stone[1]; font = C_3_Gold; break;
    default:              top = P.iron[1]; bottom = P.stone[1]; font = C_0_White; break;
    }
    (void)textTone;
    if (v.hover && !v.disabled)  { top = v.tone == UiBtnTone::Wine ? P.wine[2] : P.iron[2]; }
    if (v.pressed && !v.disabled) { const uint8_t t = top; top = bottom; bottom = t; }
    if (v.disabled)              { top = P.stone[1]; bottom = P.stone[0]; font = C_7_Grey; }

    UiFillRect(UiRect(r.x, r.y, r.w, r.h / 2), top);
    UiFillRect(UiRect(r.x, r.y + r.h / 2, r.w, r.h - r.h / 2), bottom);

    const bool lit = (v.hover || v.selected) && !v.disabled;
    UiFrameRect(r, v.disabled ? P.iron[0] : (lit ? P.gold[2] : P.black));
    const UiRect in = r.Inset(1);
    if (in.Valid() && !v.disabled) {
        const uint8_t hi = v.pressed ? P.iron[0] : P.iron[3];
        const uint8_t lo = v.pressed ? P.iron[2] : P.iron[0];
        UiFillRect(UiRect(in.x, in.y, in.w, 1), hi);
        UiFillRect(UiRect(in.x, in.y, 1, in.h), hi);
        UiFillRect(UiRect(in.x, in.Bottom() - 1, in.w, 1), lo);
        UiFillRect(UiRect(in.Right() - 1, in.y, 1, in.h), lo);
    }
    if (v.tone == UiBtnTone::Gold && !v.disabled)
        UiFillRect(UiRect(r.x + 2, r.Bottom() - 3, r.w - 4, 1), P.gold[0]);

    UiDrawText(UiRect(r.x + 2, r.y, r.w - 4, r.h), ButtonBaseline(r) + (v.pressed ? 1 : 0),
               v.label, v.disabled ? C_7_Grey : (lit && v.tone == UiBtnTone::Neutral ? C_3_Gold : font),
               UiAlign::Center);
}

void UiDrawTab(const UiBtnView& v)
{
    if (!v.rect.Valid()) return;
    const UiPalette& P = UiPal();
    const UiRect& r = v.rect;
    if (v.selected) {
        UiFillRect(r, P.stone[1]);
        UiFillRect(UiRect(r.x, r.y, r.w, 1), P.gold[2]);               // lit top edge
        UiFillRect(UiRect(r.x, r.y, 1, r.h), P.iron[3]);
        UiFillRect(UiRect(r.Right() - 1, r.y, 1, r.h), P.iron[0]);
        UiFillRect(UiRect(r.x + 1, r.y + 1, r.w - 2, 1), P.gold[0]);
    } else {
        UiFillRect(UiRect(r.x, r.y, r.w, r.h / 2), v.hover ? P.iron[2] : P.iron[1]);
        UiFillRect(UiRect(r.x, r.y + r.h / 2, r.w, r.h - r.h / 2), P.stone[0]);
        UiFrameRect(r, v.hover ? P.gold[1] : P.black);
    }
    UiPutPixel(r.x, r.y, P.stone[0]);                                   // chamfered top corners
    UiPutPixel(r.Right() - 1, r.y, P.stone[0]);
    UiDrawText(UiRect(r.x + 2, r.y, r.w - 4, r.h), ButtonBaseline(r) + (v.pressed ? 1 : 0), v.label,
               v.selected ? C_3_Gold : (v.hover ? C_0_White : C_7_Grey), UiAlign::Center);
}

void UiDrawInventoryBackdrop(const UiInventoryLayout& L, const UiSlotWell* wells, int wellCount, bool backpackGrid)
{
    UiThemeRefresh();
    const UiPalette& P = UiPal();
    const UiRect& pn = L.panel;
    DrawStone(pn, 11);

    // Faint arcane circle behind the paper-doll.
    const int cx = pn.x + pn.w / 2, cy = pn.y + 112;
    Circle(cx, cy, 66, P.arcane[0], 0);
    Circle(cx, cy, 62, P.arcane[0], 3);
    Circle(cx, cy, 44, P.arcane[0], 0);
    for (int i = 0; i < 12; ++i) {
        static const int dx[12] = {0,33,57,66,57,33,0,-33,-57,-66,-57,-33};
        static const int dy[12] = {-66,-57,-33,0,33,57,66,57,33,0,-33,-57};
        Rivet(cx + dx[i], cy + dy[i]);   // reads as small runic studs at this scale
    }

    DrawFrame(pn);

    for (int i = 0; i < wellCount; ++i) {
        if (!wells[i].rect.Valid()) continue;
        if (wells[i].plate) {
            DrawPlate(wells[i].rect, P.stone[0], P.iron[1]);
            UiFillRect(UiRect(wells[i].rect.x + 1, wells[i].rect.y + 1, wells[i].rect.w - 2, 1), P.iron[0]);
        } else {
            DrawWell(wells[i].rect, wells[i].rect.w * wells[i].rect.h >= 28 * 56);
        }
    }

    // Backpack: recess + 10 x 7 cells (1px gap = the engine's pitch of 29).
    const UiRect grid(pn.x + 17, pn.y + 222, UiInvCols * UiCellPitch, UiInvRows * UiCellPitch);
    const UiRect recess(grid.x - 2, grid.y - 2, grid.w + 3, grid.h + 3);
    UiFillRect(recess, P.iron[0]);
    UiFillRect(UiRect(recess.x - 1, recess.y - 1, recess.w + 2, 1), P.gold[0]);
    UiFillRect(UiRect(recess.x - 1, recess.Bottom(), recess.w + 2, 1), P.gold[0]);
    UiFillRect(UiRect(recess.x - 1, recess.y - 1, 1, recess.h + 2), P.gold[0]);
    UiFillRect(UiRect(recess.Right(), recess.y - 1, 1, recess.h + 2), P.gold[0]);
    if (backpackGrid) {
        for (int row = 0; row < UiInvRows; ++row) for (int col = 0; col < UiInvCols; ++col) {
            const UiRect cell(grid.x + col * UiCellPitch, grid.y + row * UiCellPitch, UiCellSize, UiCellSize);
            int x0, y0, x1, y1;
            if (!ClipToSurface(cell, x0, y0, x1, y1)) continue;
            for (int sy = y0; sy < y1; ++sy) {
                uint8_t* dst = WorkingSurface + (size_t)sy * WorkingWidth;
                for (int sx = x0; sx < x1; ++sx) {
                    const uint32_t n = Hash(sx, sy, 7) & 15;
                    dst[sx] = n < 11 ? P.well[0] : n < 15 ? P.well[1] : P.well[2];
                }
            }
        }
    } else {
        UiFillRect(UiRect(grid.x, grid.y, grid.w - 1, grid.h - 1), P.stone[0]);
    }
}

void UiDrawInventoryBar(const UiInventoryLayout& L, const UiBarView& v)
{
    UiThemeRefresh();
    const UiPalette& P = UiPal();
    const UiRect plate(L.rowA.x - 3, L.rowA.y - 2, L.rowA.w + 6, (L.rowB.Bottom() - L.rowA.y) + 2);
    DrawPlate(plate, P.stone[0], P.iron[1]);
    UiFillRect(UiRect(plate.x + 1, plate.y + 1, plate.w - 2, 1), P.iron[0]);

    auto view = [&](const UiRect& r, const char* label, UiBtnTone tone, int id) {
        UiBtnView b; b.rect = r; b.label = label; b.tone = tone;
        b.hover = v.hoverId == id; b.pressed = b.hover && v.mouseDown;
        return b;
    };

    if (!v.stash) {
        UiBtnView ti = view(L.tabInventory, "INVENTÁRIO", UiBtnTone::Neutral, UiInv_TabInventory);
        UiBtnView ts = view(L.tabSigils,    "SIGILOS",    UiBtnTone::Neutral, UiInv_TabSigils);
        ti.selected = !v.sigilsPage; ts.selected = v.sigilsPage;
        UiDrawTab(ti);
        UiDrawTab(ts);
        UiDrawButton(view(L.companions, "COMPANHEIROS", UiBtnTone::Wine, UiInv_Companions));
        if (v.companionActive)
            UiDrawButton(view(L.summon, v.companionSummoned ? "DISPENSAR" : "CHAMAR", UiBtnTone::Gold, UiInv_Summon));
    } else {
        UiDrawButton(view(L.storeFilter, v.filterLabel, UiBtnTone::Neutral, UiInv_StoreFilter));
        UiDrawButton(view(L.storeAll,    "GUARDAR",     UiBtnTone::Gold,    UiInv_StoreAll));
    }
    UiDrawButton(view(L.organize, "ORGANIZAR", UiBtnTone::Neutral, UiInv_Organize));

    // Gold counter: a coin and the amount, right-aligned inside its own plate.
    if (L.gold.Valid()) {
        DrawPlate(L.gold, P.stone[0], P.iron[1]);
        DrawCoin(L.gold.x + 4, L.gold.y + (L.gold.h - 9) / 2);
        char num[32];
        const UiRect numArea(L.gold.x + 16, L.gold.y, L.gold.w - 20, L.gold.h);
        UiFormatGold(v.gold, numArea.w, GlyphAdvance, num, (int)sizeof(num));   // always fits; full value shown when it does
        UiDrawText(numArea, L.gold.h - 2, num, C_3_Gold, UiAlign::Right);
    }
}

void UiDrawSigilPage(const UiInventoryLayout& L, const UiSigilRowView* rows, int hoverId)
{
    if (!rows) return;
    UiThemeRefresh();
    const UiPalette& P = UiPal();
    const UiRect page(L.backpackArea.x - 1, L.backpackArea.y - 1, UiInvCols * UiCellPitch + 2, UiInvRows * UiCellPitch + 2);
    DrawPlate(page, P.stone[0], P.iron[0]);

    for (int i = 0; i < UiSigilCount; ++i) {
        const UiRect& row = L.sigilRows[i];
        const UiRect& icon = L.sigilIcons[i];
        const UiSigilRowView& v = rows[i];
        const bool hover = hoverId == UiInv_SigilRow0 + i;

        uint8_t fill = P.stone[1], edge = P.iron[1], accent = P.iron[2];
        int nameFont = C_0_White, statusFont = C_7_Grey, descFont = C_7_Grey;
        const char* status = "VAZIO";
        switch (v.state) {
        case UiSigilState::Bound:
            fill = P.stone[1]; edge = P.gold[1]; accent = P.gold[2];
            nameFont = C_3_Gold; statusFont = C_3_Gold; descFont = C_0_White; status = "VINCULADO"; break;
        case UiSigilState::UnknownContent:
            fill = P.wine[0]; edge = P.wine[2]; accent = P.wine[2];
            nameFont = C_0_White; statusFont = C_2_Red; descFont = C_7_Grey; status = "DESCONHECIDO"; break;
        case UiSigilState::Unavailable:
            fill = P.stone[0]; edge = P.iron[0]; accent = P.iron[1];
            nameFont = C_7_Grey; statusFont = C_7_Grey; descFont = C_7_Grey; status = "INDISPONÍVEL"; break;
        default: break;
        }
        UiFillRect(row, hover ? (v.state == UiSigilState::UnknownContent ? P.wine[1] : P.stone[2]) : fill);
        UiFrameRect(row, hover && v.state != UiSigilState::Unavailable ? P.gold[3] : edge);
        UiFillRect(UiRect(row.x + 1, row.y + 1, 3, row.h - 2), accent);

        // icon well + placeholder per state
        DrawWell(icon, false);
        const int icx = icon.x + icon.w / 2, icy = icon.y + icon.h / 2;
        if (v.state == UiSigilState::Empty) {
            Circle(icx, icy, 9, P.arcane[1], 0);
            Circle(icx, icy, 5, P.arcane[0], 0);
        } else if (v.state == UiSigilState::UnknownContent) {
            UiDrawText(icon, icon.h / 2 + 6, "?", C_2_Red, UiAlign::Center);
        } else if (v.state == UiSigilState::Unavailable) {
            for (int k = -7; k <= 7; ++k) { UiPutPixel(icx + k, icy + k, P.iron[2]); UiPutPixel(icx + k, icy - k, P.iron[2]); }
        }

        // texts
        const int tx = icon.Right() + 7;
        const int tw = row.Right() - 6 - tx;
        const UiRect area(tx, row.y, tw, row.h);
        const int statusW = UiTextWidth(status);
        UiDrawText(area, 16, status, statusFont, UiAlign::Right);
        const int nameAreaW = tw - statusW - 8;
        UiDrawText(UiRect(tx, row.y, nameAreaW, row.h), 16, v.name, nameFont, UiAlign::Left);
        const int nameW = UiTextWidth(v.name);
        const int affW = UiTextWidth(v.affinity);
        if (nameW + 10 + affW <= nameAreaW)
            UiDrawText(UiRect(tx + nameW + 10, row.y, affW, row.h), 16, v.affinity, C_7_Grey, UiAlign::Left);
        UiDrawText(area, 32, v.description, descFont, UiAlign::Left);
    }
}

void UiDrawNotifications(int x, int y, const UiNotifyLine* lines, int count)
{
    if (!lines || count <= 0 || !SurfaceReady()) return;
    UiThemeRefresh();
    const UiPalette& P = UiPal();
    const int maxTextW = 520;
    int cy = y;
    for (int i = 0; i < count; ++i) {
        char msg[200];
        if (lines[i].count > 1) sprintf(msg, "%s x%d", lines[i].text, lines[i].count);
        else { strncpy(msg, lines[i].text, sizeof(msg) - 1); msg[sizeof(msg) - 1] = '\0'; }
        char folded[200];
        UiFoldPtBr(msg, folded, (int)sizeof(folded));
        char wrapped[3][160];   // up to 3 lines: long NPC lines in PlayerTrade.cpp are ~1000px wide
        const int n = UiWrapLines(folded, maxTextW, GlyphAdvance, wrapped, 3);
        if (n <= 0) continue;
        int w = 0;
        for (int j = 0; j < n; ++j) {
            int lw = 0;
            for (const unsigned char* p = (const unsigned char*)wrapped[j]; *p; ++p) lw += GlyphAdvance(*p);
            if (lw > w) w = lw;
        }
        const UiRect plate(x, cy, w + 16, 6 + 14 * n);
        const bool fade = lines[i].fading;
        DrawPlate(plate, P.stone[0], fade ? P.iron[1] : P.gold[0]);
        UiFillRect(UiRect(plate.x + 1, plate.y + 1, 3, plate.h - 2), fade ? P.iron[2] : P.gold[2]);
        for (int j = 0; j < n; ++j)
            UiDrawText(UiRect(plate.x + 8, plate.y, plate.w - 10, plate.h), 15 + 14 * j, wrapped[j],
                       fade ? C_7_Grey : C_0_White, UiAlign::Left);
        cy += plate.h + 4;
    }
}


// Character sheet: palette-safe Gothic metalwork with a restrained crimson accent.
// Drawn under the original live text; no change to gameplay hitboxes or stat logic.
void UiDrawCharacterBackdrop(const UiRect& panel)
{
    if (!panel.Valid()) return;
    UiThemeRefresh();
    const UiPalette& P = UiPal();

    UiFillRect(panel, P.stone[0]);
    UiFrameRect(panel, P.iron[3]);
    UiFrameRect(UiRect(panel.x + 2, panel.y + 2, panel.w - 4, panel.h - 4), P.gold[1]);

    // Upper identity band and the section dividers respect the existing 320px sheet.
    UiFillRect(UiRect(panel.x + 5, panel.y + 5, panel.w - 10, 46), P.stone[1]);
    UiFillRect(UiRect(panel.x + 5, panel.y + 50, panel.w - 10, 2), P.wine[2]);
    UiFillRect(UiRect(panel.x + 5, panel.y + 117, panel.w - 10, 1), P.gold[1]);

    // Two inset stat columns. These deliberately stay behind all existing text.
    const int leftX = panel.x + 12;
    const int rightX = panel.x + 181;
    const int leftW = 163;
    const int rightW = panel.w - 193;
    if (leftW > 0 && rightW > 0 && panel.h > 135) {
        UiFillRect(UiRect(leftX, panel.y + 124, leftW, panel.h - 132), P.stone[1]);
        UiFillRect(UiRect(rightX, panel.y + 124, rightW, panel.h - 132), P.stone[1]);
        UiFrameRect(UiRect(leftX, panel.y + 124, leftW, panel.h - 132), P.iron[2]);
        UiFrameRect(UiRect(rightX, panel.y + 124, rightW, panel.h - 132), P.iron[2]);
        UiFillRect(UiRect(leftX + 1, panel.y + 125, 2, panel.h - 134), P.wine[1]);
        UiFillRect(UiRect(rightX + 1, panel.y + 125, 2, panel.h - 134), P.gold[1]);
    }

    // Small ornamental corner pins.
    const int inset = 7;
    for (int i = 0; i < 4; ++i) {
        const int x = panel.x + (i & 1 ? panel.w - inset - 1 : inset);
        const int y = panel.y + (i & 2 ? panel.h - inset - 1 : inset);
        UiFillRect(UiRect(x - 2, y - 2, 5, 5), P.iron[4]);
        UiFillRect(UiRect(x - 1, y - 1, 3, 3), P.gold[2]);
    }
}
