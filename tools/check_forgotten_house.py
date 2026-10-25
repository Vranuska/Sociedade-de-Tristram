"""Exercise real Forgotten House encounter code with simulated engine APIs.
Requires g++; full Windows compilation and in-game visual/collision QA remain required.
"""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
source = (root / 'Sociedade de Tristram/TH/src/PlayerTrade.cpp').read_text(encoding='utf-8-sig')
start = source.index('static constexpr int MEMORY_STATE = 80;')
end = source.index('static void MemoryTopic(', start)
code = source[start:end]
prefix = r'''
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
using PLAYER_DIALOG=int;
const int PD_5_WitchMain=5,PD_0_None=0,PD_31_ForgottenHouse=31;
const int GM_COLISEUM=1,GM_IRONMAN=2,GM_SURVIVAL=3,GM_SPEEDRUN=4,GM_NIGHTMARE=5;
const int DUN_0_TOWN=0,DUN_115_FORGOTTEN_HOUSE=115;
const int BM_9_SKELETON_WARRIOR=9,BM_29_HIDDEN=29,BM_50_SKELETON_LORD=50,BM_169_ZOMBIE=169;
const int MF_15_KILLED=32768,MF_1_INVISIBLE=1,MPF_2_DONT=2;
const int BO_52_BOOK1=52,BO_9_CANDLE2=9,MaxObjects_127=127;
const int WM_1028_RETURN_FROM_QUEST_DUNGEON=1028,S_76_I_TITLSLCT=76;
const int MI_1_FIREBOLT=1,CT_1_MONSTER_AND_TRAP=1,BI_0_GOLD=0;
struct {char unused[412]={};} AdditionalStateData;
int Dungeon=115,MaxCountOfPlayersInGame=1,GameMode=0,CurrentPlayerIndex=0,MonstersCount=0;
int CurrentDialogIndex=0,Difficulty=0,MonsterIndexes[200]={},blockedRow=-1,castCount=0,castLimit=200;
int gold=0,objectCount=0,warpCount=0;
struct Sprite{int baseMonsterIndex=0;};Sprite sprites[200];
struct Monster{Sprite* SpritePtr=nullptr;int CurrentLife=0,BaseLife=0,flag=0,Row=0,Col=0,Orientation=0;const char* Name=nullptr;};Monster Monsters[200];
struct Player{int Row=40,Col=34,CurLife=100;};Player Players[4];
struct Object{int Row=0,Col=0,BaseObjectIndex=0;};Object Objects[127];
struct Missile{int Damage=0;};Missile Missiles[200];
std::string message;
template<class... T> bool is(int v,T... args){int values[]={args...};for(int x:values)if(v==x)return true;return false;}
int AddMonsterTypeToDungeon(int base,int){return base;}
bool IsCellFreeForMonster(int r,int c){if(r==blockedRow)return false;for(int i=0;i<MonstersCount;++i)if(Monsters[i].CurrentLife>0&&Monsters[i].Row==r&&Monsters[i].Col==c)return false;return true;}
int AddMonster(int r,int c,int,int sprite,int){int n=MonstersCount++;MonsterIndexes[n]=n;sprites[n].baseMonsterIndex=sprite;Monsters[n].SpritePtr=&sprites[n];Monsters[n].Row=r;Monsters[n].Col=c;Monsters[n].CurrentLife=Monsters[n].BaseLife=100;return n;}
void LoadQuestDungeonMainMapChurch(const char*,int,int){}
void LoadPalette(const char*){}
void AddObject(int base,int r,int c){auto& o=Objects[objectCount++];o.Row=r;o.Col=c;o.BaseObjectIndex=base;}
void AddWarp(int,int,int,int){++warpCount;}
void PlayGlobalSound(int){}
void ErrorPlrMsg(const char* s){message=s;}
int CastMissile(int,int,int,int,int,int,int,int,int,int,int){if(castCount>=castLimit)return -1;return castCount++;}
int SpawnSomething(int,int,int,bool,int,int,char,int amount){gold+=amount;return 0;}
bool MaeraBondOperateObject(int,int){return false;}
void ChangeTownerDialog(int d){CurrentDialogIndex=d;}
'''
tests = r'''
void reset(){
 AdditionalStateData={};MonstersCount=0;objectCount=0;warpCount=0;castCount=0;gold=0;CurrentDialogIndex=0;blockedRow=-1;
 MaxCountOfPlayersInGame=1;GameMode=0;Dungeon=115;Difficulty=0;Players[0]={};MemoryCombatTicks=0;castLimit=200;
 for(auto& m:Monsters)m=Monster{};
}
int findBase(int base){for(int i=0;i<MonstersCount;++i)if(sprites[i].baseMonsterIndex==base)return i;return -1;}
int main(){
 reset();assert(MemoryTestimonies()==0);MemoryGenerateHouse();assert(MonstersCount==0&&objectCount==13&&warpCount==1);
 reset();AdditionalStateData.unused[80]=2;MemoryGenerateHouse();assert(MonstersCount==12&&FindMemoryGuardian()<0);
 for(int i=0;i<10;++i)assert(MemoryObjectLabel(i)!=nullptr);
 assert(MemoryObjectLabel(-1)==nullptr&&MemoryObjectLabel(127)==nullptr);
 AdditionalStateData.unused[83]=7;SpawnMemoryGuardian();int boss=FindMemoryGuardian();assert(boss>=0&&Monsters[boss].BaseLife==500);
 SpawnMemoryGuardian();assert(MonstersCount==13);
 int scribe=findBase(BM_50_SKELETON_LORD),nurse=findBase(BM_169_ZOMBIE);
 MemoryGuardianKilled(scribe);assert(AdditionalStateData.unused[86]==1&&gold==500&&MemoryState()==2);
 MemoryGuardianKilled(scribe);assert(gold==500);
 MemoryGuardianKilled(nurse);assert(AdditionalStateData.unused[86]==3&&gold==1000);
 for(int phase=0;phase<3;++phase){
  Monsters[boss].CurrentLife=phase==0?500:phase==1?300:100;
  castCount=0;MemoryCombatTicks=0;Players[0].Row=70;Players[0].Col=44;
  for(int tick=0;tick<(20-phase*4)*4;++tick)MemoryUpdateGuardian();
  assert(castCount==phase+1);
  castCount=0;MemoryCombatTicks=0;Players[0].Row=50;Players[0].Col=38;
  for(int tick=0;tick<(20-phase*4)*4;++tick)MemoryUpdateGuardian();
  assert(castCount==0);
 }
 castCount=0;MemoryCombatTicks=0;Players[0].Row=82;Players[0].Col=38;
 for(int i=0;i<48;++i){MemoryUpdateGuardian();}
 assert(castCount==0);
 Monsters[boss].flag|=MF_1_INVISIBLE;Players[0].Row=68;Players[0].Col=38;MemoryUpdateGuardian();assert(!(Monsters[boss].flag&MF_1_INVISIBLE));
 Monsters[boss].flag|=MF_1_INVISIBLE;Players[0].Row=36;Players[0].Col=38;MemoryUpdateGuardian();assert(!(Monsters[boss].flag&MF_1_INVISIBLE));
 Monsters[scribe].Name=nullptr;MemoryUpdateGuardian();assert(std::string(Monsters[scribe].Name)=="O Escrivao das Tres Mortes");
 CurrentDialogIndex=31;int ticks=MemoryCombatTicks;MemoryUpdateGuardian();assert(MemoryCombatTicks==ticks);CurrentDialogIndex=0;
 MemoryGuardianKilled(boss);assert(MemoryState()==3&&gold==2500);MemoryGuardianKilled(boss);assert(gold==2500);
 reset();AdditionalStateData.unused[80]=2;AdditionalStateData.unused[86]=3;MemoryGenerateHouse();assert(MonstersCount==10);
 reset();AdditionalStateData.unused[80]=4;MemoryGenerateHouse();assert(MonstersCount==0);
 reset();AdditionalStateData.unused[80]=2;AdditionalStateData.unused[83]=7;blockedRow=78;SpawnMemoryGuardian();assert(FindMemoryGuardian()<0);
 reset();AdditionalStateData.unused[80]=2;AdditionalStateData.unused[83]=7;SpawnMemoryGuardian();boss=FindMemoryGuardian();castLimit=0;Players[0].Row=70;for(int i=0;i<80;++i)MemoryUpdateGuardian();assert(castCount==0);
 puts("PASS: house encounters, clue labels, two minibosses, one-time rewards, three combat phases, bowl, mirror, safe return visits and spawn/missile capacity");
}
'''
with tempfile.TemporaryDirectory() as tmp:
    cpp = Path(tmp) / 'house.cpp'
    exe = Path(tmp) / 'house'
    cpp.write_text(prefix + code + tests)
    subprocess.run(['g++', '-std=c++11', '-Wall', '-Wextra', '-Werror', '-Wno-unused-variable', str(cpp), '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
