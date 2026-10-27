#pragma once
// UiKit.h - engine-facing drawing for the Sociedade de Tristram UI layer.
// All rectangles are in panel space (see UiCore.h). Every function is safe to call with a
// null surface, an empty rectangle or text that does not fit: it clips or does nothing, it
// never writes outside WorkingSurface.
#include "UiCore.h"

enum class UiAlign { Left, Center, Right };

// ---------------------------------------------------------------------------
// Theme. Colors are described in RGB and matched at run time against the CURRENT level
// palette (BasePalette), searching only index 0 and 32..239: 1..31 are cycled by some
// levels and 240..255 may be reserved by the system palette (same rule the companion
// sprite loader already follows). Only the slot "wells" use 240..255, because the
// engine's own highlight code (ShadowItemSlot) re-tints pixels >= 160 and keeps the low
// nibble as shade.
// ---------------------------------------------------------------------------
struct UiPalette
{
    uint8_t black;
    uint8_t stone[4];   // dark -> light
    uint8_t iron[5];    // shadow -> highlight
    uint8_t gold[4];    // shadow -> highlight
    uint8_t wine[3];
    uint8_t arcane[2];
    uint8_t well[3];    // 240..255 ramp, dark -> lighter (tint-compatible)
};
void UiThemeRefresh();
const UiPalette& UiPal();

// ---------------------------------------------------------------------------
// Primitives
// ---------------------------------------------------------------------------
void UiFillRect (const UiRect& r, uint8_t color);   // clipped solid fill
void UiFrameRect(const UiRect& r, uint8_t color);   // clipped 1px outline
void UiPutPixel (int x, int y, uint8_t color);      // clipped

int  UiTextWidth(const char* utf8);                 // width as drawn (after accent folding)
// Text with the small bitmap font inside 'area', never wider than area.w (truncates with
// ".." only when the dots fit). 'baseline' is measured from area.y.
void UiDrawText(const UiRect& area, int baseline, const char* utf8, int fontColor,
                UiAlign align = UiAlign::Left);

// ---------------------------------------------------------------------------
// Components
// ---------------------------------------------------------------------------
enum class UiBtnTone { Neutral, Wine, Gold };

struct UiBtnView
{
    UiRect      rect;
    const char* label    = "";
    UiBtnTone   tone     = UiBtnTone::Neutral;
    bool        hover    = false;
    bool        pressed  = false;
    bool        selected = false;
    bool        disabled = false;
};
void UiDrawButton(const UiBtnView& v);   // 4 states: normal / hover / pressed / disabled
void UiDrawTab   (const UiBtnView& v);   // selected tab opens into the content below it

struct UiSlotWell
{
    UiRect rect;
    bool   plate = false;   // plain dark plate (weapon swap buttons): no slot texture
};

// Stone, frame, rune circle, equipment wells and (optionally) the 10 x 7 backpack grid.
void UiDrawInventoryBackdrop(const UiInventoryLayout& L, const UiSlotWell* wells, int wellCount,
                             bool backpackGrid);

struct UiBarView
{
    int         hoverId          = 0;   // the id UiInventoryLayout::Pick() returned for the cursor
    bool        mouseDown        = false;
    bool        sigilsPage       = false;
    bool        stash            = false;
    bool        companionActive  = false;
    bool        companionSummoned = false;
    const char* filterLabel      = "";
    int         gold             = 0;
};
void UiDrawInventoryBar(const UiInventoryLayout& L, const UiBarView& v);

struct UiSigilRowView
{
    const char*  name        = "";
    const char*  affinity    = "";
    const char*  description = "";
    UiSigilState state       = UiSigilState::Empty;
};
// Draws the chrome of the five rows (plate, icon well, texts). The caller draws the item
// sprite of a Bound sigil on top of L.sigilIcons[i].
void UiDrawSigilPage(const UiInventoryLayout& L, const UiSigilRowView* rows, int hoverId);

// Stack of system notices anchored at (x, y), newest at the bottom.
void UiDrawNotifications(int x, int y, const UiNotifyLine* lines, int count);
