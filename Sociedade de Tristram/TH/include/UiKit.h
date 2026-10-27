#pragma once
// UiKit.h - engine-facing drawing for the Sociedade de Tristram UI layer.
// All rectangles are in panel space (see UiCore.h). Every function is safe to call
// with a null surface, an empty rectangle or text that does not fit: it clips or
// does nothing, it never writes outside WorkingSurface.
#include "UiCore.h"

enum class UiAlign { Left, Center, Right };
enum class UiTone  { Neutral, Gold, Danger, Dim };

// Palette helper. Ramps are the engine's 16-entry blocks (BLC_*). The shade nibble is
// a theme constant that must be tuned in game against the real palette.
uint8_t UiToneColor(UiTone tone, bool hot);

void UiFillRect (const UiRect& r, uint8_t color);   // clipped solid fill
void UiFrameRect(const UiRect& r, uint8_t color);   // clipped 1px outline

// Width of the text as it will be drawn (after accent folding).
int  UiTextWidth(const char* utf8);

// Draws text with the small bitmap font, inside 'area', never wider than area.w
// (truncates with ".."). 'baseline' is measured from area.y, same convention the
// old DrawText calls used for yPos.
void UiDrawText(const UiRect& area, int baseline, const char* utf8, int fontColor,
                UiAlign align = UiAlign::Left);

// Opaque button: fill + frame + centered label. State is derived from the SAME
// rectangle used by UiButton::Consumes()/Activates().
void UiDrawButton(const UiButton& button, const char* label, int fontColor, bool selected = false);
