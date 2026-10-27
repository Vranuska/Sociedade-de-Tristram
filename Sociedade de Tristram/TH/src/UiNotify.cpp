#include "stdafx.h"
#include "UiKit.h"

// Engine glue for the notification stack. READ-ONLY: PlayerStatusMessages is never modified, so the
// meaning and the lifetime rules of the messages (10s clear in CheckPlayerStatusMessagesTimeout) stay
// exactly as they were. Only what is drawn on screen changes. Tune the constants here.
namespace {
constexpr long long kLifetimeMs = 5000;   // how long a system notice stays visible
constexpr long long kFadeMs     = 1200;   // the last stretch is drawn dimmed
constexpr int       kMaxLines   = 3;      // never more than this many notices at once
constexpr int       kAnchorX    = 10;
constexpr int       kAboveHud   = 170;    // distance above the main HUD where the stack starts (room for 3 notices of 3 lines)
}

void UiNotifyDrawSystemMessages()
{
	const char* texts[MaxMessages_8];
	long long   times[MaxMessages_8];
	bool        isSystem[MaxMessages_8];
	for( int i = 0; i < MaxMessages_8; ++i ){
		texts[i]    = PlayerStatusMessages[i].str;
		times[i]    = PlayerStatusMessages[i].messageTime;
		isSystem[i] = PlayerStatusMessages[i].playerIndex == PlayersMax_4;   // chat lines are not ours
	}
	UiNotifyLine lines[MaxMessages_8];
	const int count = UiNotifyCollect(texts, times, isSystem, MaxMessages_8, PlayerStatusMessageIndex,
		GetTickCountTh(), kLifetimeMs, kFadeMs, kMaxLines, lines);
	if( count <= 0 ) return;
	int y = ScreenHeight - GUI_MainPanelHeight - kAboveHud;
	if( y < 20 ) y = 20;
	UiDrawNotifications(kAnchorX, y, lines, count);
}
