#include "stdafx.h"

extern Portrait getGameChangerPortrait(GAME_CHANGER);
extern const char* getGameChangerDescription(GAME_CHANGER);

constexpr int IW_width = 640;
constexpr int IW_height = 462;
bool IsInfoWindowVisible = false;
bool IsLeftButtonDown = false;
bool IsAdmItemWindow = false;
int AdmItemJumpId = 0;
char AdmItemSearch[64] = {};
bool AdmItemSearchMode = false;

DisplayObject InfoWindowRect;
constexpr const char* IW_headTexts[] = {
	 /*left*/ "Info do Modificador",
	/*right*/ "Lista de Modificadores"
};

DisplayObject closeButton;
char closeButtonState = 0;
DisplayObject admSpawnButton;
DisplayObject admSpawnSetButton;
DisplayObject admPrevPageButton;
DisplayObject admNextPageButton;
DisplayObject admGoIdButton;

constexpr size_t rowInList = 20;
DisplayObject textlist[rowInList];
char textliststates[20];
size_t lastSelectedInListIndex = 0;

DisplayObject gc_icon;

DisplayObject longTextMidPos;

size_t listStartFromIndex = 0;
size_t listStartLastIndex = 0;

char* IW_IMG_background;
char* IW_IMG_icons;
char* IW_IMG_buttons;

vector<int> gc_listIndexes;

// ---- th2 -------------------------------------------------------------------------------
void RecalculateRectRightDown(DisplayObject & obj)
{
	obj.Right = obj.Left + obj.Width;
	obj.Down = obj.Top + obj.Heigth;
}

// ---- th2 -------------------------------------------------------------------------------
static void InfoWindow_ResetListSelection()
{
	listStartFromIndex = 0;
	listStartLastIndex = gc_listIndexes.size() <= rowInList ? 0 : gc_listIndexes.size() - rowInList;
	lastSelectedInListIndex = 0;
	memset(textliststates, 0, sizeof(textliststates));
	textliststates[0] = 1;
}

static void InfoWindow_LoadGameChangerList()
{
	gc_listIndexes.clear();
	for (int i = 1; i < GC_COUNT; ++i)
		if (Players[CurrentPlayerIndex].gameChanger & BIT(i))
			gc_listIndexes.emplace_back(i);
	InfoWindow_ResetListSelection();
}

void InfoWindow_Init()
{
	gc_listIndexes.clear();
	gc_listIndexes.reserve(128);

	InfoWindowRect.Left = ScreenWidth / 2 - IW_width / 2;
	InfoWindowRect.Top = (ScreenHeight - 132) / 2 - IW_height / 2;
	InfoWindowRect.Width = IW_width;
	InfoWindowRect.Heigth = IW_height;
	RecalculateRectRightDown(InfoWindowRect);

	closeButton.Left = InfoWindowRect.Left + InfoWindowRect.Width - 20 - 33;
	closeButton.Top = InfoWindowRect.Top + InfoWindowRect.Heigth - 20 - 32;
	closeButton.Width = 33;
	closeButton.Heigth = 32;
	RecalculateRectRightDown(closeButton);

	admSpawnButton.Left = InfoWindowRect.Left + 45;
	admSpawnButton.Top = InfoWindowRect.Top + 345;
	admSpawnButton.Width = 110;
	admSpawnButton.Heigth = 24;
	RecalculateRectRightDown(admSpawnButton);
	admSpawnSetButton.Left = InfoWindowRect.Left + 170;
	admSpawnSetButton.Top = InfoWindowRect.Top + 345;
	admSpawnSetButton.Width = 110;
	admSpawnSetButton.Heigth = 24;
	RecalculateRectRightDown(admSpawnSetButton);
	admPrevPageButton.Left = InfoWindowRect.Left + 350;
	admPrevPageButton.Top = InfoWindowRect.Top + 405;
	admPrevPageButton.Width = 100;
	admPrevPageButton.Heigth = 22;
	RecalculateRectRightDown(admPrevPageButton);
	admNextPageButton.Left = InfoWindowRect.Left + 500;
	admNextPageButton.Top = InfoWindowRect.Top + 405;
	admNextPageButton.Width = 100;
	admNextPageButton.Heigth = 22;
	RecalculateRectRightDown(admNextPageButton);
	admGoIdButton.Left = InfoWindowRect.Left + 45;
	admGoIdButton.Top = InfoWindowRect.Top + 385;
	admGoIdButton.Width = 235;
	admGoIdButton.Heigth = 24;
	RecalculateRectRightDown(admGoIdButton);

	gc_icon.Width = 120;
	gc_icon.Heigth = 76;
	gc_icon.Left = InfoWindowRect.Left - gc_icon.Width / 2 + (315 - 15) / 2 + 15;
	gc_icon.Top = InfoWindowRect.Top + 54;
	RecalculateRectRightDown(gc_icon);

	longTextMidPos.Left = InfoWindowRect.Left + (315 - 15) / 2 + 15;
	longTextMidPos.Top = InfoWindowRect.Top + 150;

	for (size_t i = 0; i < countof(textlist); ++i) {
		textlist[i].Left = InfoWindowRect.Left + 335;
		textlist[i].Top = InfoWindowRect.Top + 56 + 17 * i;
		textlist[i].Width = 280;
		textlist[i].Heigth = 16;
		RecalculateRectRightDown(textlist[i]);
		textliststates[i] = 0;
	}
	textliststates[lastSelectedInListIndex] = 1;

	InfoWindow_LoadGameChangerList();

	IW_IMG_background = (char*)LoadFile("data\\gc_info\\gc_background.cel");
	IW_IMG_icons = (char*)LoadFile("data\\gc_info\\gc_icons.cel");
	IW_IMG_buttons = (char*)LoadFile("data\\stash_21\\tradewindowbutn.cel");
};

// ---- th2 -------------------------------------------------------------------------------
void InfoWindow_Free()
{
	gc_listIndexes.clear();
	FreeMemZero(IW_IMG_background);
	FreeMemZero(IW_IMG_icons);
	FreeMemZero(IW_IMG_buttons);
	listStartFromIndex = 0;
	listStartLastIndex = 0;
	lastSelectedInListIndex = 0;
};

// ---- th2 -------------------------------------------------------------------------------
void __fastcall IW_DrawRegularCel(int Xpos, int Ypos, const char* image, int frame, int width)
{
	if (!WorkingSurface || !image) return;
	char* dst = (char*)&WorkingSurface[Xpos] + YOffsetHashTable[Ypos];
	const int* img = reinterpret_cast<const int*>(image);
	int size = img[frame + 1] - img[frame];
	const char* src = image + img[frame];

	// skip header
	if (src[0] == 10 && src[1] == 0) {
		size -= 11;
		src += 11;
	}
	// decode RLE
	for (int i = 0, j = 0, k; i < size; ++i) {
		if( (size_t)dst < (size_t)WorkingSurfaceDrawBegin ){ return; }
		if (j >= width) {
			dst -= WorkingWidth;
			j = 0;
		}
		if (src[i] == 127) {
			for (k = 0; k < 127; ++k) dst[j + k] = src[i + k + 1];
			i += 127;
			j += 127;
		}
		else if (src[i] == -128) j += 128;
		else if (src[i] >= 0) {
			for (k = 0; k < src[i]; ++k) dst[j + k] = src[i + k + 1];
			j += src[i];
			i += src[i];
		}
		else if (src[i] < 0) j += -src[i];
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall IW_TransparentBackground(int xPosition, int yPosition, int width, int height)
{
	size_t position = 0;
	uchar cutColors = 0;
	uchar clrVal = 0;

	struct color {
		inline static void town(const int& position) { WorkingSurface[position] = 252 + (WorkingSurface[position] >> 5); };
		inline static void dungeon(const int& position) { WorkingSurface[position] = 0; };
	};

	void (*redrawColor)(const int&) = nullptr;

	switch( Dungeon->graphType ){
	case DT_0_TOWN: cutColors = 128u; redrawColor = color::town;    break;
	case DT_4_HELL: cutColors = 16u;  redrawColor = color::dungeon; break;
	case DT_3_CAVE
	  or DT_5_CRYPT
	  or DT_6_ABYSS: cutColors = 32u; redrawColor = color::dungeon; break;
	case DT_1_CHURCH: break;
	};

	for (int i = 0, j; i < height; ++i) {
		position = WorkingWidth * (yPosition + i) + xPosition;
		for (j = 0; j < width; ++j) {
			clrVal = WorkingSurface[position];
			if (clrVal) {
				if (clrVal < cutColors)
					redrawColor(position);
				else if ((clrVal >= 128 && clrVal <= 135) || (clrVal >= 144 && clrVal <= 151) || (clrVal >= 136 && clrVal <= 143) || (clrVal > 152 && clrVal < 159))
					WorkingSurface[position] = (clrVal & 0b11111000) + ((clrVal & 0b00000111) >> 2) + 6;
				else
					WorkingSurface[position] = (clrVal & 0b11110000) + ((clrVal & 0b00001111) >> 2) + 12;
			}
			++position;
		}
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_DrawLongText(int xPos, int yPos, const char* stringPtr, int fontColor)
{
	auto InfoWindow_CropText = [](const char* text, int textSize = 22) {
		const char* last = text;
		for (int i = 0; i < textSize; ++i) {
			if (*text == ' ') {
				last = text;
			}
			else if (*text == '\0' || *text == '\n') {
				last = text;
				break;
			}
			++text;
		}
		return last;
	};

	int textWidth;
	char LetterID;
	int SurfaceOffset;

	const char* firstInLine = stringPtr;
	const char* lastInLine = nullptr;

	for (int i = 0; i < 24; ++i) {
		if (lastInLine) firstInLine = ++lastInLine;
		lastInLine = InfoWindow_CropText(firstInLine, 30);
		if (firstInLine == lastInLine) continue;
		textWidth = 0;

		const char* tmp = firstInLine;
		while (tmp != lastInLine){
			LetterID = FontIndexSmall[Codepage[*tmp]];
			textWidth += FontWidthSmall[LetterID] + 1;;
			++tmp;
		}

		SurfaceOffset = YOffsetHashTable[yPos + Screen_TopBorder + 14 * i] + xPos + Screen_LeftBorder - textWidth / 2;
		do {
			LetterID = FontIndexSmall[Codepage[*firstInLine]];
			if (LetterID)
				DrawLetter(SurfaceOffset, (uint8_t)LetterID, fontColor);
			SurfaceOffset += FontWidthSmall[LetterID] + 1;;
			++firstInLine;
		} while (firstInLine != lastInLine && *firstInLine);

		if (*firstInLine == '\0') break;
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_DrawRect(int xPosition, int yPosition, int width, int height, uint8_t color)
{
	uchar* dst = &WorkingSurface[WorkingWidth * yPosition + xPosition];
	for (int i = 0; i < height; ++i) {
		memset(dst, color, width);
		dst += WorkingWidth;
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_Draw()
{
	if( IsAdmItemWindow ){
		IW_TransparentBackground(InfoWindowRect.Left + Screen_LeftBorder + 16, InfoWindowRect.Top + Screen_TopBorder + 16, IW_width - 32, IW_height - 32);
		IW_DrawRegularCel(Screen_LeftBorder + InfoWindowRect.Left, Screen_TopBorder + InfoWindowRect.Top + IW_height, IW_IMG_background, 1, 640);
		DrawLevelInfoText(InfoWindowRect.Left + 70, InfoWindowRect.Top + 44, "Ferramentas ADM", C_3_Gold);
		DrawLevelInfoText(InfoWindowRect.Left + 365, InfoWindowRect.Top + 44, "Lista de Itens Unicos", C_3_Gold);
		IW_DrawRegularCel(Screen_LeftBorder + closeButton.Left, Screen_TopBorder + closeButton.Top + closeButton.Heigth, IW_IMG_buttons, closeButtonState ? 20 : 19, closeButton.Width);
		if( gc_listIndexes.empty() ) return;
		size_t selected = lastSelectedInListIndex + listStartFromIndex;
		if( selected >= gc_listIndexes.size() ) selected = gc_listIndexes.size() - 1;
		int selectedId = gc_listIndexes[selected];
		const UniqueItem& selectedItem = UniqueItems[selectedId];
		char admText[512];
		sprintf(admText, "ID: %d\nNome: %s\nQualidade: %d\nSet: %s\n\nClique em um item da lista e use GERAR ITEM ou GERAR SET.", selectedId, selectedItem.Name ? selectedItem.Name : "(sem nome)", selectedItem.qualityLevel, selectedItem.uniqueSetIndex >= 0 && selectedItem.uniqueSetIndex < int(count_UniqueSet) ? UniqueSets[selectedItem.uniqueSetIndex].Name : "Nenhum");
		InfoWindow_DrawLongText(longTextMidPos.Left, longTextMidPos.Top - 70, admText, C_0_White);
		InfoWindow_DrawRect(Screen_LeftBorder + admSpawnButton.Left, Screen_TopBorder + admSpawnButton.Top, admSpawnButton.Width, admSpawnButton.Heigth, CursorIntoDisplayObject(admSpawnButton) ? 241 : 197);
		InfoWindow_DrawRect(Screen_LeftBorder + admSpawnSetButton.Left, Screen_TopBorder + admSpawnSetButton.Top, admSpawnSetButton.Width, admSpawnSetButton.Heigth, CursorIntoDisplayObject(admSpawnSetButton) ? 241 : 197);
		DrawLevelInfoText(admSpawnButton.Left + 18, admSpawnButton.Top + 17, "GERAR ITEM", C_0_White);
		DrawLevelInfoText(admSpawnSetButton.Left + 24, admSpawnSetButton.Top + 17, "GERAR SET", selectedItem.uniqueSetIndex >= 0 && selectedItem.uniqueSetIndex < int(count_UniqueSet) ? C_0_White : C_7_Grey);
		InfoWindow_DrawRect(Screen_LeftBorder + admPrevPageButton.Left, Screen_TopBorder + admPrevPageButton.Top, admPrevPageButton.Width, admPrevPageButton.Heigth, CursorIntoDisplayObject(admPrevPageButton) ? 241 : 197);
		InfoWindow_DrawRect(Screen_LeftBorder + admNextPageButton.Left, Screen_TopBorder + admNextPageButton.Top, admNextPageButton.Width, admNextPageButton.Heigth, CursorIntoDisplayObject(admNextPageButton) ? 241 : 197);
		DrawLevelInfoText(admPrevPageButton.Left + 15, admPrevPageButton.Top + 16, "< ANTERIOR", C_0_White);
		DrawLevelInfoText(admNextPageButton.Left + 17, admNextPageButton.Top + 16, "PROXIMA >", C_0_White);
		InfoWindow_DrawRect(Screen_LeftBorder + admGoIdButton.Left, Screen_TopBorder + admGoIdButton.Top, admGoIdButton.Width, admGoIdButton.Heigth, CursorIntoDisplayObject(admGoIdButton) ? 241 : 197);
		char goIdText[96];
		if( AdmItemSearchMode ) sprintf(goIdText, "BUSCAR: %s_", AdmItemSearch);
		else sprintf(goIdText, "ID: %d | / BUSCAR", AdmItemJumpId);
		DrawLevelInfoText(admGoIdButton.Left + 35, admGoIdButton.Top + 17, goIdText, C_0_White);
		char pageText[64];
		sprintf(pageText, "%u-%u / %u", (unsigned)(listStartFromIndex + 1), (unsigned)min(listStartFromIndex + rowInList, gc_listIndexes.size()), (unsigned)gc_listIndexes.size());
		DrawLevelInfoText(InfoWindowRect.Left + 458, InfoWindowRect.Top + 395, pageText, C_3_Gold);
		for( size_t i = 0; i < countof(textlist) && listStartFromIndex + i < gc_listIndexes.size(); ++i ){
			int id = gc_listIndexes[listStartFromIndex + i];
			char row[256];
			sprintf(row, "%d | %s%s", id, UniqueItems[id].Name ? UniqueItems[id].Name : "(sem nome)", UniqueItems[id].uniqueSetIndex >= 0 ? " [SET]" : "");
			DrawLevelInfoText(-GetTextWidth(row) / 2 + textlist[i].Left + textlist[i].Width / 2, textlist[i].Top + 12, row, textliststates[i] ? textliststates[i] == 1 ? C_1_Blue : C_4_Orange : C_0_White);
		}
		return;
	}
	// Background (transparent)
	IW_TransparentBackground(
		InfoWindowRect.Left + Screen_LeftBorder + 16,
		InfoWindowRect.Top + Screen_TopBorder + 16,
		IW_width - 32,
		IW_height - 32
	);
	// Window board (image)
	IW_DrawRegularCel(
		InfoWindowRect.Left + Screen_LeftBorder,
		InfoWindowRect.Top + Screen_TopBorder + IW_height,
		IW_IMG_background,
		1,
		640
	);

	// Left main text
	DrawLevelInfoText(-GetTextWidth(IW_headTexts[0]) / 2 + InfoWindowRect.Left + 165, InfoWindowRect.Top + 44, IW_headTexts[0], C_3_Gold);
	// Right main text
	DrawLevelInfoText(-GetTextWidth(IW_headTexts[1]) / 2 + InfoWindowRect.Left + 475, InfoWindowRect.Top + 44, IW_headTexts[1], C_3_Gold);

	// Close button (image)
	IW_DrawRegularCel(
		Screen_LeftBorder + closeButton.Left,
		Screen_TopBorder + closeButton.Top + closeButton.Heigth,
		IW_IMG_buttons,
		closeButtonState ? 20 : 19,
		closeButton.Width
	);

	if(gc_listIndexes.size() == 0) return;

	// Icon (Game Changer)
	IW_DrawRegularCel(
		Screen_LeftBorder + gc_icon.Left,
		Screen_TopBorder + gc_icon.Top + gc_icon.Heigth,
		IW_IMG_icons,
		getGameChangerPortrait((GAME_CHANGER)gc_listIndexes[lastSelectedInListIndex + listStartFromIndex]).id + 1,
		gc_icon.Width
	);


	const char* textptr = nullptr;
	// Long text
	textptr = getGameChangerDescription((GAME_CHANGER)gc_listIndexes[lastSelectedInListIndex + listStartFromIndex]);
	InfoWindow_DrawLongText(
		longTextMidPos.Left,
		longTextMidPos.Top,
		textptr,
		C_0_White
	);

	textptr = nullptr;
	// List
	size_t index;
	for (size_t i = 0; i < countof(textlist) && listStartFromIndex + i < gc_listIndexes.size(); ++i) {
		index = listStartFromIndex + i;
		textptr = GC_Names_InfoWindow[gc_listIndexes[index]];
		DrawLevelInfoText(
			-GetTextWidth(textptr) / 2 + textlist[i].Left + textlist[i].Width / 2,
			textlist[i].Top + 12,
			textptr,
			textliststates[i] ? textliststates[i] == 1 ? C_1_Blue : C_4_Orange : C_0_White
		);
	}

	// Scroll list indicator
	if (true /* && listStartLastIndex*/) {
		InfoWindow_DrawRect(
			Screen_LeftBorder + InfoWindowRect.Left + IW_width - 24,
			Screen_TopBorder + InfoWindowRect.Top + 55,
			1,
			340,
			197
		);
		InfoWindow_DrawRect(
			Screen_LeftBorder + InfoWindowRect.Left + IW_width - 26,
			Screen_TopBorder + InfoWindowRect.Top + 55 + ((listStartFromIndex + lastSelectedInListIndex) * 340 / (gc_listIndexes.size() > 1 ? gc_listIndexes.size() - 1 : 1)), /*division by zero*/
			5,
			1,
			241
		);
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_MouseMove()
{
	// Close button
	if (CursorIntoDisplayObject(closeButton) && IsLeftButtonDown)
		closeButtonState = 1;
	else if (closeButtonState)
		closeButtonState = 0;

	// List
	for (size_t i = 0; i < countof(textlist) && listStartFromIndex + i < gc_listIndexes.size(); ++i) {
		if (CursorIntoDisplayObject(textlist[i])) {
			if (textliststates[i] == 0) textliststates[i] = 2;
		}
		else if (textliststates[i] == 2) textliststates[i] = 0;
	}
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_MouseDown()
{
	IsLeftButtonDown = true;
}

// ---- th2 -------------------------------------------------------------------------------
void __fastcall InfoWindow_MouseUp()
{
	if( IsAdmItemWindow && !gc_listIndexes.empty() ){
		if( CursorIntoDisplayObject(admGoIdButton) ){
			int id = AdmItemJumpId;
			if( id < 0 ) id = 0;
			if( id >= int(gc_listIndexes.size()) ) id = int(gc_listIndexes.size()) - 1;
			AdmItemJumpId = id;
			listStartFromIndex = (size_t(id) / rowInList) * rowInList;
			if( listStartFromIndex > listStartLastIndex ) listStartFromIndex = listStartLastIndex;
			lastSelectedInListIndex = size_t(id) - listStartFromIndex;
			if( lastSelectedInListIndex >= rowInList ) lastSelectedInListIndex = rowInList - 1;
			memset(textliststates, 0, sizeof(textliststates));
			textliststates[lastSelectedInListIndex] = 1;
			PlayGlobalSound(S_75_I_TITLEMOV); IsLeftButtonDown = false; return;
		}
		if( CursorIntoDisplayObject(admPrevPageButton) ){
			listStartFromIndex = listStartFromIndex >= rowInList ? listStartFromIndex - rowInList : 0;
			lastSelectedInListIndex = 0;
			memset(textliststates, 0, sizeof(textliststates)); textliststates[0] = 1;
			PlayGlobalSound(S_75_I_TITLEMOV); IsLeftButtonDown = false; return;
		}
		if( CursorIntoDisplayObject(admNextPageButton) ){
			listStartFromIndex = min(listStartFromIndex + rowInList, listStartLastIndex);
			lastSelectedInListIndex = 0;
			memset(textliststates, 0, sizeof(textliststates)); textliststates[0] = 1;
			PlayGlobalSound(S_75_I_TITLEMOV); IsLeftButtonDown = false; return;
		}
		size_t selected = lastSelectedInListIndex + listStartFromIndex;
		if( selected < gc_listIndexes.size() ){
			int selectedId = gc_listIndexes[selected];
			if( CursorIntoDisplayObject(admSpawnButton) ){
				int itemIndex = -1;
				UniqueItem& uniq = UniqueItems[selectedId];
				for( size_t i = 0; i < count_BaseItems; ++i ){
					if( uniq.uniqLine == BaseItems[i].uniqLine ){
						itemIndex = SpawnUnique(selectedId, Players[CurrentPlayerIndex].Row + 1, Players[CurrentPlayerIndex].Col, false, i);
						if( itemIndex != -1 ) Items[itemIndex].Identified = 1;
					}
				}
				if( itemIndex == -1 ){
					itemIndex = SpawnUnique(selectedId, Players[CurrentPlayerIndex].Row + 1, Players[CurrentPlayerIndex].Col);
					if( itemIndex != -1 ) Items[itemIndex].Identified = 1;
				}
				PlayGlobalSound(S_75_I_TITLEMOV);
				IsLeftButtonDown = false;
				return;
			}
			if( CursorIntoDisplayObject(admSpawnSetButton) && UniqueItems[selectedId].uniqueSetIndex >= 0 && UniqueItems[selectedId].uniqueSetIndex < int(count_UniqueSet) ){
				int setId = UniqueItems[selectedId].uniqueSetIndex;
				for( size_t id = 0; id < count_UniqueItems; ++id ){
					if( UniqueItems[id].uniqueSetIndex == setId ){
						int itemIndex = SpawnUnique((int)id, Players[CurrentPlayerIndex].Row + 1, Players[CurrentPlayerIndex].Col);
						if( itemIndex != -1 ) Items[itemIndex].Identified = 1;
					}
				}
				PlayGlobalSound(S_75_I_TITLEMOV);
				IsLeftButtonDown = false;
				return;
			}
		}
	}
	// Close button
	if (CursorIntoDisplayObject(closeButton)) {
		closeButtonState = 0;
		InfoWindow_Close();
		PlayGlobalSound(S_75_I_TITLEMOV);
	}

	// List
	for (size_t i = 0; i < countof(textlist) && listStartFromIndex + i < gc_listIndexes.size(); ++i)
		if (CursorIntoDisplayObject(textlist[i])) {
			if (i == lastSelectedInListIndex) break;
			textliststates[lastSelectedInListIndex] = 0;
			textliststates[i] = 1;
			lastSelectedInListIndex = i;
			PlayGlobalSound(S_75_I_TITLEMOV);
			break;
		}

	if (IsLeftButtonDown) IsLeftButtonDown = false;
}

// ---- th2 -------------------------------------------------------------------------------
void InfoWindow_Open()
{
	InfoWindow_LoadGameChangerList();
	IsAdmItemWindow = false;
	IsInfoWindowVisible = true;
}

void AdmItemWindow_Open()
{
	if( !DevelopMode || count_UniqueItems == 0 ) return;
	AdmItemSearchMode = false;
	AdmItemSearch[0] = 0;
	AdmItemJumpId = 0;
	IsLeftButtonDown = false;
	closeButtonState = 0;
	IsAdmItemWindow = true;
	gc_listIndexes.clear();
	gc_listIndexes.reserve(count_UniqueItems);
	for( size_t i = 0; i < count_UniqueItems; ++i ) gc_listIndexes.emplace_back((int)i);
	InfoWindow_ResetListSelection();
	IsInfoWindowVisible = true;
}

// ---- th2 -------------------------------------------------------------------------------
void InfoWindow_Close()
{
	IsInfoWindowVisible = false;
	IsAdmItemWindow = false;
	AdmItemSearchMode = false;
	AdmItemSearch[0] = 0;
	AdmItemJumpId = 0;
	IsLeftButtonDown = false;
	closeButtonState = 0;
}

// ---- th2 -------------------------------------------------------------------------------
static char AdmAsciiLower(char c)
{
	return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

static bool AdmNameContains(const char* name, const char* query)
{
	if( !name || !query || !query[0] ) return false;
	for( const char* start = name; *start; ++start ){
		const char* a = start;
		const char* b = query;
		while( *a && *b && AdmAsciiLower(*a) == AdmAsciiLower(*b) ){ ++a; ++b; }
		if( !*b ) return true;
	}
	return false;
}

static void AdmSelectUniqueId(int id)
{
	if( gc_listIndexes.empty() ) return;
	if( id < 0 ) id = 0;
	if( id >= int(gc_listIndexes.size()) ) id = int(gc_listIndexes.size()) - 1;
	AdmItemJumpId = id;
	listStartFromIndex = (size_t(id) / rowInList) * rowInList;
	if( listStartFromIndex > listStartLastIndex ) listStartFromIndex = listStartLastIndex;
	lastSelectedInListIndex = size_t(id) - listStartFromIndex;
	memset(textliststates, 0, sizeof(textliststates));
	textliststates[lastSelectedInListIndex] = 1;
}

bool AdmItemWindow_HandleKey(int key)
{
	if( !IsAdmItemWindow || !IsInfoWindowVisible ) return false;
	if( key == 191 ){
		AdmItemSearchMode = true;
		AdmItemSearch[0] = 0;
		return true;
	}
	if( AdmItemSearchMode ){
		size_t len = strlen(AdmItemSearch);
		if( key == VK_27_ESC_KEY ){
			AdmItemSearchMode = false;
			AdmItemSearch[0] = 0;
			return true;
		}
		if( key == VK_8_BACKSPACE_KEY ){
			if( len ) AdmItemSearch[len - 1] = 0;
			return true;
		}
		if( key == VK_13_RETURN_KEY ){
			if( AdmItemSearch[0] ){
				int selected = int(listStartFromIndex + lastSelectedInListIndex);
				int startId = selected + 1;
				int found = -1;
				for( int pass = 0; pass < 2 && found < 0; ++pass ){
					int from = pass == 0 ? startId : 0;
					int to = pass == 0 ? int(count_UniqueItems) : startId;
					for( int id = from; id < to; ++id ){
						if( AdmNameContains(UniqueItems[id].Name, AdmItemSearch) ){
							found = id;
							break;
						}
					}
				}
				if( found >= 0 ) AdmSelectUniqueId(found);
			}
			AdmItemSearchMode = false;
			PlayGlobalSound(S_75_I_TITLEMOV);
			return true;
		}
		if( len + 1 < sizeof(AdmItemSearch) && ((key >= VK_65_A_KEY && key <= VK_90_Z_KEY) || (key >= VK_48_0_KEY && key <= VK_57_9_KEY) || key == VK_32_SPACE_KEY || key == VK_189_OEM_MINUS_KEY) ){
			AdmItemSearch[len] = key == VK_189_OEM_MINUS_KEY ? '-' : char(key);
			AdmItemSearch[len + 1] = 0;
		}
		return true;
	}
	if( key >= VK_48_0_KEY && key <= VK_57_9_KEY ){
		int digit = key - VK_48_0_KEY;
		if( AdmItemJumpId > 99999 ) AdmItemJumpId = 0;
		AdmItemJumpId = AdmItemJumpId * 10 + digit;
		return true;
	}
	if( key == VK_8_BACKSPACE_KEY ){
		AdmItemJumpId /= 10;
		return true;
	}
	if( key == VK_13_RETURN_KEY ){
		AdmSelectUniqueId(AdmItemJumpId);
		PlayGlobalSound(S_75_I_TITLEMOV);
		return true;
	}
	return false;
}

// ---- th2 -------------------------------------------------------------------------------
void InfoWindow_Prev()
{
	if (lastSelectedInListIndex > 0) {
		textliststates[lastSelectedInListIndex] = 0;
		textliststates[--lastSelectedInListIndex] = 1;
		PlayGlobalSound(S_75_I_TITLEMOV);
	}
	else if (lastSelectedInListIndex == 0 && listStartFromIndex > 0) {
		--listStartFromIndex;
		PlayGlobalSound(S_75_I_TITLEMOV);
	}
}void InfoWindow_Next()
{
	if( gc_listIndexes.empty() ) return;
	size_t selected = listStartFromIndex + lastSelectedInListIndex;
	if( selected + 1 >= gc_listIndexes.size() ) return;
	++selected;
	if( selected >= listStartFromIndex + rowInList ) ++listStartFromIndex;
	lastSelectedInListIndex = selected - listStartFromIndex;
	memset(textliststates, 0, sizeof(textliststates));
	textliststates[lastSelectedInListIndex] = 1;
	PlayGlobalSound(S_75_I_TITLEMOV);
}

// ---- th2 -------------------------------------------------------------------------------
void InfoWindow_Prev()
{
	if( gc_listIndexes.empty() ) return;
	size_t selected = listStartFromIndex + lastSelectedInListIndex;
	if( selected == 0 ) return;
	--selected;
	if( selected < listStartFromIndex ) --listStartFromIndex;
	lastSelectedInListIndex = selected - listStartFromIndex;
	memset(textliststates, 0, sizeof(textliststates));
	textliststates[lastSelectedInListIndex] = 1;
	PlayGlobalSound(S_75_I_TITLEMOV);
}
