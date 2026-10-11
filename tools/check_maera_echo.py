"""Compile isolated real training/casting functions against simulated engine APIs.
Requires Python 3 and g++; does not replace the Windows/gameplay checks.
"""
from pathlib import Path
import subprocess
import tempfile
import re

source = (Path(__file__).resolve().parents[1] / 'Sociedade de Tristram/TH/src/PlayerTrade.cpp').read_text(encoding='utf-8-sig')
def section(start, end):
    return source[source.index(start):source.index(end, source.index(start))]

learned = section('// Maera\'s first bond quest:', 'static bool CompanionPanelStandalone')
training = section('static int CompanionTraining(', 'static int CompanionLevel(unsigned char companionId);')
delay = section('static int CompanionAbilityDelay(', 'void CompanionOpenPanel()')
missile = section('static int CompanionCastPureMissile(', 'bool CompanionIsSummoned()')
abilities = section('void CompanionProcessAbilities()', '//----- (0046C43D)')
menu = section('static bool MaeraConvergenceEligible(', 'void MaeraMenu()')
guide = section('static void BuildCompanionJourneyLines(', 'void CompanionMenu()')
bond_target = section('static unsigned char MaeraBondTarget()\n', 'static bool MaeraBondCompanionPresent()')
prefix = r'''
#include <cassert>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <string>
using i64=long long;
enum {COMPANION_NONE,COMPANION_JASON,COMPANION_KUROKO,COMPANION_MIZUKI,COMPANION_THOR,COMPANION_LORD,COMPANION_PITTY,COMPANION_COUNT};
const int MEMORY_CLUES=83,COMPANION_SAVE_GEMS=40,COMPANION_MAX_LEVEL=50,DUN_0_TOWN=0;
const int PD_0_None=0,PD_32_Maera=32,PD_34_MaeraTraining=34,PD_35_MaeraConvergence=35;
const int PT_DialogRows_NoIndent=0,PT_DialogRows_20_SmallDialog_RowsCount=20,C_3_Gold=3,C_1_Blue=1,C_0_White=0;
const int CT_0_PLAYER=0,MSF_COMPANION=16,MF_6_FRIENDLY=64,MF_15_KILLED=32768,CF_2_VISIBLE_BY_PLAYER=2;
const int SummonMonsters_Count=16;
struct {char unused[412]={};} AdditionalStateData;
struct Player {int CharLevel=20,CurMana=100,BaseMana=100,MaxCurMana=100,MaxBaseMana=100,TotalGold=10000;} Players[4];
struct Monster {int Row=20,Col=20,NextRow=20,NextCol=20,CurrentLife=100,flag=0;void* SpritePtr=(void*)1;} Monsters[200];
struct Missile {int flag=0,Damage=0;} Missiles[200];
int FlagMap[112][112]={},MonstersCount=1,MonsterIndexes[200]={20};
int MaxCountOfPlayersInGame=1,Dungeon=0,CurrentPlayerIndex=0,CurrentDialogIndex=0,SelectedDialogRow=14,DialogRowsCount=0;
int levels[7]={1,15,15,15,15,15,15},affinities[7]={},stage=1;unsigned char active=1;
i64 CompanionPrimaryReadyAt[4]={},CompanionUltimateReadyAt[4]={},clockNow=10000;
bool CompanionAiUseSkills=true,CompanionAiShowSkillMessages=true,IsBigMenuBox=false,DialogHasScroolBox=false,rescued=true;
int castCount=0,castLimit=200,castsByType[200]={},charges=0,recalcs=0;
std::string error;bool selectable[32]={};
static int CompanionLevel(unsigned char id){return levels[id];}
static int CompanionEvolutionStage(unsigned char){return stage;}
unsigned char ActiveCompanion(){return active;}
int CompanionAffinity(unsigned char id){return affinities[id];}
const char* CompanionName(unsigned char){return "Jason";}
bool MemoryCaretakerRescued(){return rescued;}
bool MemoryAvailable(){return true;}
unsigned char MemoryState(){return (unsigned char)AdditionalStateData.unused[80];}
unsigned char MemoryTestimonies(){return (unsigned char)AdditionalStateData.unused[81]&7;}
bool CompanionUnlocked(unsigned char id){return id>0&&id<7;}
int CompanionExperience(unsigned char){return 25;}
int CompanionExperienceForNextLevel(int){return 135;}
void CompanionOpenPanel(){CurrentDialogIndex=30;}
int CompanionMonsterSlot(int){return 0;}
void CompanionEnsureSummoned(){}
i64 GetTickCountTh(){return clockNow;}
bool In112(int r,int c){return r>=0&&r<112&&c>=0&&c<112;}
bool CheckCastInSight(int,int,int,int){return true;}
int OrientationToTarget(int,int,int,int){return 0;}
struct CompanionFreeCastScope {explicit CompanionFreeCastScope(Player&){} };
int CastMissile(int,int,int,int,int,int type,int caster,int,int damageMarker,int,int){
 assert(caster==CT_0_PLAYER&&damageMarker==1);
 if(castCount>=castLimit)return -1;
 castsByType[castCount]=type;Missiles[castCount]={};return castCount++;
}
void ErrorPlrMsg(const char* s){error=s;}
void ClearGoldByInventoryAsPrice(int n){Players[0].TotalGold-=n;++charges;}
void RecalcPlayer(int,bool){++recalcs;}
void ChangeTownerDialog(int p){CurrentDialogIndex=p;}
void MemoryLines(const char* const(&lines)[7]){for(auto s:lines)assert(strlen(s)<128);}
void SetDialogRow(int,int row,int,const char* s,char,int select){assert(row>=0&&row<32);assert(strlen(s)<128);selectable[row]=select;}
template<size_t N> void strcpy_s(char(&s)[N],const char* t){assert(strlen(t)<N);strcpy(s,t);}
template<size_t N,class... T> void sprintf_s(char(&s)[N],const char* fmt,T... a){snprintf(s,N,fmt,a...);}
void resetCasting(){castCount=0;castLimit=200;CompanionPrimaryReadyAt[0]=0;CompanionUltimateReadyAt[0]=0;FlagMap[20][20]=CF_2_VISIBLE_BY_PLAYER;}
'''
constants = sorted(set(re.findall(r'\b(?:MI|PS)_\d+_[A-Z0-9_]+\b', abilities)))
prefix += '\nenum {' + ','.join(f'{name}={i+1}' for i,name in enumerate(constants)) + '};\n'
tests=r'''
int main(){
 // Gates and one-time charge, including independent companions and no gold loss on failure.
 rescued=false;HandleMaeraTraining();assert(charges==0);rescued=true;
 active=1;levels[1]=14;HandleMaeraTraining();assert(charges==0);
 levels[1]=15;HandleMaeraTraining();assert(charges==0);
 AdditionalStateData.unused[104]=1;Players[0].TotalGold=4999;HandleMaeraTraining();assert(charges==0);
 Players[0].TotalGold=10000;HandleMaeraTraining();assert(charges==1&&Players[0].TotalGold==5000);
 assert(MaeraEchoLearned(1)&&CompanionTraining(1,0)==2);
 HandleMaeraTraining();assert(charges==1&&Players[0].TotalGold==5000);
 assert(!MaeraEchoLearned(2));
 AdditionalStateData.unused[43]=2;assert(CompanionTraining(2,0)==0); // Forged equipped value is not an unlock.
 assert(!MaeraEchoLearned(0)&&!MaeraEchoLearned(7));
 Players[0].TotalGold=50000;
 for(unsigned char id=2;id<7;id++){
  active=id;AdditionalStateData.unused[104+id-1]=1;HandleMaeraTraining();assert(MaeraEchoLearned(id));
  HandleMaeraTraining();
 }
 assert(charges==6&&Players[0].TotalGold==25000);active=1;


 // Advanced special: all prerequisites, insufficient gold and one-time charge per companion.
 active=1;levels[1]=24;affinities[1]=50;HandleMaeraConvergence();assert(!MaeraConvergenceLearned(1));
 levels[1]=25;affinities[1]=49;HandleMaeraConvergence();assert(!MaeraConvergenceLearned(1));
 affinities[1]=50;Players[0].TotalGold=14999;HandleMaeraConvergence();assert(!MaeraConvergenceLearned(1));
 Players[0].TotalGold=90000;
 for(unsigned char id=1;id<7;id++){
  active=id;levels[id]=25;affinities[id]=50;HandleMaeraConvergence();assert(MaeraConvergenceLearned(id));HandleMaeraConvergence();
 }
 assert(Players[0].TotalGold==0&&charges==12);active=1;
 resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1);assert(Missiles[0].Damage==250*2*64*140/100);
 resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1,true);assert(Missiles[0].Damage==250*2*64&&castCount==2);
 AdditionalStateData.unused[41]=1;resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1);assert(Missiles[0].Damage==250*2*64);
 AdditionalStateData.unused[41]=2;levels[1]=15;
 // Primary echo uses player authority, has 60% damage, and is not recursive.
 resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1,true);
 assert(castCount==2&&Missiles[1].Damage==Missiles[0].Damage*60/100);
 assert((Missiles[0].flag&MSF_COMPANION)&&(Missiles[1].flag&MSF_COMPANION));
 resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1);assert(castCount==1);
 resetCasting();castLimit=1;CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1,true);assert(castCount==1);
 resetCasting();castLimit=0;CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1,true);assert(castCount==0);
 AdditionalStateData.unused[40]=1;resetCasting();CompanionCastPureMissile(20,20,21,21,0,1,0,2,1,1,true);assert(castCount==1);
 // Jason starts with a basic skill; special unlocks at 15, and respects independent timers.
 Dungeon=115;active=1;AdditionalStateData.unused[40]=0;levels[1]=1;resetCasting();CompanionProcessAbilities();
 assert(castCount==1&&castsByType[0]==MI_24_ARCANE_STAR&&CompanionUltimateReadyAt[0]==0);
 CompanionProcessAbilities();assert(castCount==1);
 levels[1]=15;resetCasting();CompanionProcessAbilities();assert(castCount==2&&castsByType[1]==MI_15_ARCANE_NOVA);
 resetCasting();CompanionPrimaryReadyAt[0]=clockNow+1000;CompanionProcessAbilities();assert(castCount==1&&castsByType[0]==MI_15_ARCANE_NOVA);
 AdditionalStateData.unused[40]=2;resetCasting();CompanionProcessAbilities();assert(castCount==3&&castsByType[2]==MI_15_ARCANE_NOVA);
 // Friendly/unseen targets and disabled AI never trigger a basic skill.
 Monsters[20].flag=MF_6_FRIENDLY;resetCasting();CompanionProcessAbilities();assert(castCount==0);Monsters[20].flag=0;
 resetCasting();FlagMap[20][20]=0;CompanionProcessAbilities();assert(castCount==0);
 resetCasting();CompanionAiUseSkills=false;CompanionProcessAbilities();assert(castCount==0);CompanionAiUseSkills=true;
 // All six basic paths cast an echo after training. Specials are held on cooldown here.
 for(unsigned char id=1;id<7;id++){
  active=id;levels[id]=15;AdditionalStateData.unused[110+id-1]=1;AdditionalStateData.unused[40+(id-1)*3]=2;
  resetCasting();CompanionUltimateReadyAt[0]=clockNow+1000;CompanionProcessAbilities();assert(castCount==2);
 }

 // Each actual special path receives the boost; primary echoes are not multiplied by it.
 const int specialScales[7]={0,4,5,4,3,4,5};
 for(unsigned char id=1;id<7;id++){
  active=id;levels[id]=25;AdditionalStateData.unused[40+(id-1)*3]=0;AdditionalStateData.unused[41+(id-1)*3]=2;
  resetCasting();CompanionPrimaryReadyAt[0]=clockNow+1000;CompanionProcessAbilities();assert(castCount>0);
  assert(Missiles[castCount-1].Damage==250*specialScales[id]*64*140/100);
 }

 // Guide reads all quest stages and memory combinations without changing saved data or gold.
 char lines[10][128],snapshot[412];const int goldBeforeGuide=Players[0].TotalGold;
 for(int state=0;state<=4;state++)for(unsigned char pet=0;pet<7;pet++)for(int mask=0;mask<8;mask++){
  AdditionalStateData.unused[80]=(char)state;AdditionalStateData.unused[81]=(char)mask;
  AdditionalStateData.unused[83]=(char)mask;AdditionalStateData.unused[102]=2;AdditionalStateData.unused[103]=(char)mask;
  memcpy(snapshot,AdditionalStateData.unused,412);BuildCompanionJourneyLines(lines,pet);
  assert(memcmp(snapshot,AdditionalStateData.unused,412)==0&&Players[0].TotalGold==goldBeforeGuide);
  for(auto& line:lines){assert(strlen(line)<128);}assert(lines[0][0]);
  if(state==4&&mask==7)assert(std::string(lines[4]).find("Volte a Maera")!=std::string::npos);
  if(state==4&&mask!=7&&pet!=2)assert(std::string(lines[4]).find("Selecione")!=std::string::npos);
 }
 assert(Players[0].CurMana==100&&Players[0].BaseMana==100);
 active=1;Dungeon=0;MaeraTrainingMenu();assert(selectable[14]);
 puts("PASS: training gates/price, independent unlocks, equipment validation, echo damage/authority/capacity, Jason level/timers, target gates, six basic/special paths, Convergence prerequisites/price/damage, read-only journey guide");
}
'''
with tempfile.TemporaryDirectory() as tmp:
    cpp=Path(tmp)/'maera_echo_test.cpp';binary=Path(tmp)/'maera_echo_test'
    cpp.write_text(prefix+learned+training+delay+missile+abilities+menu+bond_target+guide+tests)
    subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror','-Wno-unused-function',str(cpp),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
