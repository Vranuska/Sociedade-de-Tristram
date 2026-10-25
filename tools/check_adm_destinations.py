"""Compile and test the real ADM destination UI logic against engine stubs."""
from pathlib import Path
import subprocess
import tempfile
root=Path(__file__).resolve().parents[1]
s=(root / 'Sociedade de Tristram/TH/src/InfoWindow.cpp').read_text(encoding='utf-8-sig')
def function(name):
 import re
 a=re.search(r'^.*(?:void|bool) '+re.escape(name)+r'\s*\n\{',s,re.M).start();b=s.index('{',a);depth=1;i=b+1
 while depth:
  depth+=(s[i]=='{')-(s[i]=='}');i+=1
 return s[a:i]+'\n'
table=s[s.index('static const char* const AdmDungeonNames'):s.index('DisplayObject InfoWindowRect;')]
pre=r'''
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using std::size_t; using std::min; using std::vector;
#define countof(a) (sizeof(a)/sizeof((a)[0]))
enum DUNGEON { DUN_0_TOWN=0, DUN_24_CRYPT_4=24, DungeonCount=116 };
struct CurDungeon {DUNGEON value; operator DUNGEON()const{return value;} operator int()const=delete;}; CurDungeon Dungeon{DUN_0_TOWN};
const int WM_1029_GOTO_QUEST_DUNGEON=1029,WM_1031_GOTO_DUNGEON=1031, PCA_10_NEW_LEVEL=10, S_75_I_TITLEMOV=75;
const int VK_27_ESC_KEY=27,VK_13_RETURN_KEY=13,VK_38_UP_ARROW_KEY=38,VK_40_DOWN_ARROW_KEY=40;
const int C_0_White=0,C_1_Blue=1,C_3_Gold=3,C_4_Orange=4,C_7_Grey=7;
struct DisplayObject {int Left=0,Top=0,Width=100,Heigth=20;};
DisplayObject InfoWindowRect,closeButton,longTextMidPos,admSpawnButton,admPrevPageButton,admNextPageButton,textlist[20];
char textliststates[20]={};
size_t listStartFromIndex=0,lastSelectedInListIndex=0,listStartLastIndex=0;
constexpr size_t rowInList=20; constexpr int IW_width=640,IW_height=462;
int Screen_LeftBorder=0,Screen_TopBorder=0,closeButtonState=0;
char *IW_IMG_background=nullptr,*IW_IMG_buttons=nullptr;
vector<int> gc_listIndexes;
bool IsAdmDungeonWindow=false,IsInfoWindowVisible=false,IsAdmItemWindow=false,AdmItemSearchMode=false,IsLeftButtonDown=false,IsPlayerDead=false;
int MaxCountOfPlayersInGame=1,CurrentPlayerIndex=0;
struct Player{int CurAction=0;};Player Players[1];
bool travelAllowed=true;int travelCount=0,lastDestination=-1;
bool StartNewLvl(int,int msg,DUNGEON d){assert(msg==(int(d)>24?1029:1031));++travelCount;lastDestination=d;return travelAllowed;}
void InfoWindow_Close(){IsAdmDungeonWindow=false;IsInfoWindowVisible=false;}
void InfoWindow_Prev(); void InfoWindow_Next();
const DisplayObject* hovered=nullptr;
bool CursorIntoDisplayObject(const DisplayObject& obj){return &obj==hovered;}
template<class... A>void PlayGlobalSound(A...){}
template<class... A>void IW_TransparentBackground(A...){}
template<class... A>void IW_DrawRegularCel(A...){}
template<class... A>void DrawLevelInfoText(A...){}
template<class... A>void InfoWindow_DrawLongText(A...){}
template<class... A>void InfoWindow_DrawRect(A...){}
'''
out=pre+table+function('InfoWindow_ResetListSelection()')+function('AdmDungeonWindow_Travel()')+function('AdmDungeonWindow_Draw()')+function('AdmDungeonWindow_Open()')+function('InfoWindow_Next()')+function('InfoWindow_Prev()')
# Compile and exercise the exact destination-specific mouse and key branches.
a=s.index('void __fastcall InfoWindow_MouseUp()');b=s.index('\tif( IsAdmItemWindow &&',a)
out+=s[a:b].replace('__fastcall ','')+'}\n'
a=s.index('bool AdmItemWindow_HandleKey(int key)');b=s.index('\tif( !IsAdmItemWindow',a)
out+=s[a:b]+'return false;\n}\n'
out+=r'''
int main(){
assert(countof(AdmDungeonNames)==116);
for(int d=0;d<116;++d){
 Dungeon.value=(DUNGEON)d;AdmDungeonWindow_Open();
 assert(IsInfoWindowVisible && !IsAdmItemWindow && gc_listIndexes.size()==116);
 assert(listStartFromIndex+lastSelectedInListIndex==size_t(d));
 assert(lastSelectedInListIndex<20);AdmDungeonWindow_Draw();
 int before=travelCount;AdmDungeonWindow_Travel();assert(travelCount==before);
 Dungeon.value=(DUNGEON)(d==0?1:0);assert(AdmItemWindow_HandleKey(13));
 assert(lastDestination==d && !IsInfoWindowVisible);
}
Dungeon.value=DUN_0_TOWN;AdmDungeonWindow_Open();
for(int i=0;i<140;++i) AdmItemWindow_HandleKey(40);
assert(listStartFromIndex+lastSelectedInListIndex==115);
for(int i=0;i<140;++i) AdmItemWindow_HandleKey(38);
assert(listStartFromIndex+lastSelectedInListIndex==0);
hovered=&admNextPageButton;IsLeftButtonDown=true;InfoWindow_MouseUp();assert(listStartFromIndex==20);
hovered=&admPrevPageButton;IsLeftButtonDown=true;InfoWindow_MouseUp();assert(listStartFromIndex==0);
InfoWindow_Next();travelAllowed=false;assert(AdmItemWindow_HandleKey(13));assert(IsInfoWindowVisible);
travelAllowed=true;hovered=&admSpawnButton;IsLeftButtonDown=true;InfoWindow_MouseUp();assert(!IsInfoWindowVisible && lastDestination==1);
AdmDungeonWindow_Open();int before=travelCount;
gc_listIndexes[0]=999;AdmDungeonWindow_Travel();assert(travelCount==before);
AdmDungeonWindow_Open();MaxCountOfPlayersInGame=2;AdmDungeonWindow_Travel();assert(travelCount==before);MaxCountOfPlayersInGame=1;
IsPlayerDead=true;AdmDungeonWindow_Travel();assert(travelCount==before);IsPlayerDead=false;
Players[0].CurAction=10;AdmDungeonWindow_Travel();assert(travelCount==before);Players[0].CurAction=0;
assert(AdmItemWindow_HandleKey(27));assert(!IsInfoWindowVisible);
printf("Destination menu: 116 destinations, navigation, mouse, Enter, Esc and travel guards passed.\n");
}
'''
with tempfile.TemporaryDirectory() as tmp:
 cpp=Path(tmp)/'destinations.cpp'
 exe=Path(tmp)/'destinations'
 cpp.write_text(out)
 subprocess.run(['g++','-std=c++11','-Wall','-Wextra','-Werror',str(cpp),'-o',str(exe)],check=True)
 subprocess.run([str(exe)],check=True)
