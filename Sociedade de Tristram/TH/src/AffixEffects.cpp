#include "stdafx.h"

template<typename... T> __forceinline int I( const char* s, T... a ) { return sprintf_s( InfoPanelBuffer, sizeof(InfoPanelBuffer), s, a ... ); }
template<typename... T> __forceinline int I( int l, T... a ) { return sprintf_s( InfoPanelBuffer + l, sizeof(InfoPanelBuffer) - l, a ... ); }
char* par( int v1, int v2 ){ static char buf[64]; if( v2 && v1 != v2 ){ sprintf( buf, "%c(%i-%i)", v1 < 0 ? '-' : '+', abs(v1), abs(v2) ); }else{ sprintf( buf, "%+i", v1 ); } return buf; }
#define F [](Item& i, Effect& e, Player& p) // TODO: remove all player dependency from item generation data

const AffixEffect AffixEffect::Table[255] = { // AFFIX_EFFECT Effect.id is short (Item_TH2.PrefixEffect и Item_TH2.PostfixEffect - uchar - максимум 254 эффекта + 1 end marker)
	{	AE_TO_HIT,	                               Chance, F{ I( "precisao: %+i", e.chance ); }	},
	{	AE_PERCENT_DAMAGE,	               Min           , F{ I( "%+i%% de dano da arma", e.minVal ); }	},
	{	AE_TO_HIT_DAMAGE,	               Min    |Chance, F{ I( "%+i de precisao, %+i%% de dano da arma", e.chance, e.minVal ); }	},
	{	AE_PERCENT_AC,	                   Min           , F{ I( "%+i%% de armadura", e.minVal ); }	},
	{	AE_SPECIAL_AC,	                   Min           , F{ I( "armadura: %i", e.minVal ); }	},
	{	AE_AC,	                           Min           , F{ I( "%+i de armadura", e.minVal ); }	},
	{	AE_RESIST_All,	                   Min           , F{ I( "%+i para todas as resistencias", e.minVal ); }	},
	{	AE_SPELLS_LEVEL,	               Min           , F{ I( e.minVal >= 0 ? "magias aumentadas em %i niveis" : "magias reduzidas em %i niveis", abs(e.minVal) ); }	},
	{	AE_EXTRA_CHARGES,	               Min           , F{ I( "Cargas extras" ); }	},
	{	AE_SPELL,	                       Min           , F{ I( "%i / %i cargas de %s", i.CurCharges, e.minVal, getSpellName( e.type ) ); }	},
	{	AE_ELEM_HIT,	                   Min|Max       , F{ I( "%s de dano de %s", par(e.minVal, e.maxVal), BaseActions[e.type].name(i,e,p) ); }	},
	{	AE_STAT,	                       Min           , F{ I( "%+i de %s", e.minVal, Stats[e.type] ); }	},
	{	AE_ALL_STAT,	                   Min           , F{ I( "%+i para todos os atributos", e.minVal ); }	},
	{	AE_DFE,	                           Min           , F{ I( "%+i de dano dos inimigos", e.minVal ); }	},
	{	AE_HIT_POINTS,	                   Min           , F{ I( "%+i de vida", e.minVal ); }	},
	{	AE_MANA,	                       Min           , F{ I( "%+i de mana", e.minVal ); }	},
	{	AE_HIGH_DURABILITY,	               Min           , F{ I( "alta durabilidade" ); }	},
	{	AE_DECREASED_DURABILITY,	       Min           , F{ I( "durabilidade reduzida" ); }	},
	{	AE_INDESTRUCTIBLE_DIS,	           0             , F{ I( "indestrutivel" ); }	},
	{	AE_PLUS_LIGHT_RADIUS,	           Min           , F{ I( "+%i%% de raio de luz", 10 * e.minVal ); }	},
	{	AE_MINUS_LIGHT_RADIUS,	           Min           , F{ I( "-%i%% de raio de luz", 10 * e.minVal ); }	},
	{	AE_FLAG,	                       0             , F{ I( "%s"/*" (flag)"*/, BaseActions[e.type].name(i,e,p) ); }	}, // flag effect, does not sum values
	{	AE_SPICIES_DAMAGE_TOTAL,	       Min           , F{ I( "%+i%% de dano corpo a corpo total contra %s"/*" (max)"*/, e.minVal, Spicies[e.type]); }	},
	{	AE_MANA_STEAL_PERCENT,             0/*Min*/      , F{ I( "golpes corpo a corpo roubam %i%% de mana"/*" (max)"*/, e.minVal ); }	},
	{	AE_LIFE_STEAL_PERCENT,             0/*Min*/      , F{ I( "golpes corpo a corpo roubam %i%% de vida"/*" (max)"*/, e.minVal ); }	},
	{	AE_ARMOR_PIERCING,	               Min           , F{ I( "perfuracao de armadura: %+i%%", (e.minVal*100)/16 ); }	},
	{	AE_ATTACK_SPEED,                   0/*Min*/      , F{ I( "ataque %s"/*" (max)"*/, by(e.minVal-1, "rapido", "muito rapido", "veloz", "velocissimo") ); }	},
	{	AE_HIT_RECOVERY,                   0/*Min*/      , F{ I( "recuperacao de golpe %s"/*" (max)"*/, by(e.minVal-1, "rapida", "muito rapida", "velocissima") ); }	},
	{	AE_DAMAGE,	                       Min           , F{ I( "adiciona %i de dano fisico", e.minVal ); }	},
	{   AE_UNUSUAL_ITEM_DAMAGE,            Min|Max       , F{ I("dano base incomum: %s", par(i.MinDamage, i.MaxDamage)); }	},
	{	AE_UNUSUAL_DURABILITY,	           0             , F{ I( "durabilidade incomum" ); }	},
	{	AE_ONE_HANDED_STAFF,	           0             , F{ I( "item de uma mao" ); }	},
	{	AE_NO_STR_REQ,	                   0             , F{ I( "sem requisito de forca" ); }	},
	{	AE_UNIQUE_GRAPHIC,                 0             , 0	},
	{	AE_LOW_DUR_ADD_DAMAGE,	           Min           , F{ I( "baixa durabilidade, %+i%% de dano", 2 * e.minVal + 140 ); }	},
	{	AE_MANA_MOVED_TO_HEALTH,	       0             , F{ I( "50%% da mana convertida em vida" ); }	}, // TODO: looks like it should be flag effect
	{	AE_HEALTH_MOVED_TO_MANA,	       0             , F{ I( "40%% da vida convertida em mana" ); }	}, // TODO: looks like it should be flag effect
	{	AE_GOLD_FIND,	                   Min           , F{ I( "%+i%% de ouro encontrado", e.minVal ); }	},
	{	AE_GOLD_ABS_FIND,	               Min|Max       , F{ I( "%s de ouro encontrado", par(e.minVal, e.maxVal) ); }	},
	{	AE_MAGIC_FIND,	                   Min           , F{ I( "%+i%% de chance de encontrar itens magicos", e.minVal ); }	},
	{	AE_SPELL_LEVEL,	                   Min           , F{ I( "%s: %+i niveis de magia", getSpellName( e.type ), e.minVal ); }	},
	{	AE_SPELL_PERCENT,	               Min           , F{ I( "dano de %s: %+i%%", getSpellName( e.type ), e.minVal ); }	},
	{	AE_SPELL_DAMAGE,	               Min|Max|Chance, F{ if (!(e.minVal && e.maxVal)) I("%s: %+i de precisao da magia", getSpellName(e.type), e.chance); else I(e.chance ? "%s de dano de %s, %+i de precisao" : "%s de dano de %s", par(e.minVal, e.maxVal), getSpellName(e.type), e.chance); }	},
	{	AE_ELEMENT_PERCENT,	               Min           , F{ I( "elemento %s: %+i%% de dano", Elements[e.type], e.minVal); }	},
	{	AE_ELEMENT_DAMAGE,	               Min|Max|Chance, F{ if( !(e.minVal && e.maxVal) ) I( "elemento %s: %+i de precisao", Elements[e.type], e.chance ); else I( e.chance ? "%s de dano de elemento %s, %+i de precisao" : "%s de dano de elemento %s", par(e.minVal, e.maxVal), Elements[e.type], e.chance ); }	},
	{	AE_ACTION,	                       Min|Max|Chance, F{ I( e.chance < 100 ? "%s %s, chance: %i%%" : "%s %s", BaseActions[e.type].name(i,e,p), par(e.minVal, e.maxVal), e.chance ); }	},
	{	AE_ACTION_PERCENT,	               Min    |Chance, F{ I( e.chance ? "%s %+i%%, %+i de precisao" : "%s %+i%%", BaseActions[e.type].name(i,e,p), e.minVal, e.chance ); }	},
	{	AE_ACTION_VALUE,	               Min|Max|Chance, F{ I( e.chance ? "%s %s, %+i de precisao" : "%s %s", BaseActions[e.type].name(i,e,p), par(e.minVal, e.maxVal), e.chance ); }	},
	{	AE_CAST_SPEED,	                   0/*Min*/      , F{ I( "velocidade de conjuracao %s"/*" (max)"*/, by(e.minVal-1, "fast", "faster", "fastest" ) ); }	},
	{	AE_ALL_STAT_PERCENT,	           Min           , F{ I( "%+i%% para todos os atributos", e.minVal ); }	},
	{	AE_STAT_PERCENT,	               Min           , F{ I( "%+i%% para %s", e.minVal, Stats[e.type] ); }	},
	{	AE_LIFE_REGEN,	                   Min           , F{ I( "%+i de regeneracao de vida", e.minVal ); }	},
	{	AE_MANA_REGEN,	                   Min           , F{ I( "%+i de regeneracao de mana", e.minVal ); }	},
	{	AE_LIFE_REGEN_PERCENT,	           Min           , F{ I( "%+i%% de regeneracao de vida", e.minVal ); }	},
	{	AE_MANA_REGEN_PERCENT,	           Min           , F{ I( "%+i%% de regeneracao de mana", e.minVal ); }	},
	{	AE_XP_GAIN,	                       Min|Max       , F{ I( "%s de experiencia obtida", par(e.minVal, e.maxVal) ); }	},
	{	AE_XP_GAIN_PERCENT,	               Min           , F{ I( "%+i%% de experiencia obtida", e.minVal ); }	},
	{	AE_ABSORB_MELEE_DAMAGE,	           Min           , F{ I( "%+i de resistencia a dano corpo a corpo", e.minVal ); }	},
	{	AE_ABSORB_RANGED_DAMAGE,	       Min           , F{ I( "%+i de resistencia a dano de projeteis", e.minVal ); }	},
	{	AE_SUMMON_HP_PERCENT,	           Min           , F{ I( "%+i%% de vida das invocacoes", e.minVal ); }	},
	{	AE_SUMMON_DAMAGE_PERCENT,	       Min           , F{ I( "%+i%% de dano das invocacoes", e.minVal ); }	},
	{	AE_SUMMON_AC_PERCENT,	           Min           , F{ I( "%+i%% de armadura das invocacoes", e.minVal ); }	},
	{	AE_SUMMON_TO_HIT,	                       Chance, F{ I( "%+i de precisao das invocacoes", e.chance ); }	},
	{	AE_SUMMON_HP,	                   Min           , F{ I( "%+i de vida das invocacoes", e.minVal ); }	},
	{	AE_SUMMON_DAMAGE,	               Min|Max       , F{ I( "%s de dano das invocacoes", par(e.minVal, e.maxVal) ); }	},
	{	AE_SUMMON_AC,	                   Min           , F{ I( "%+i de armadura das invocacoes", e.minVal ); }	},
	{	AE_BLOCK_CHANCE,	                       Chance, F{ I( "%+i de bloqueio", e.chance ); }	},
	{	AE_CRIT_CHANCE,	                           Chance, F{ I( "%+i%% de chance de critico", e.chance ); }	},
	{	AE_CRIT_DAMAGE_PERCENT,	           Min           , F{ I( "%+i%% de dano critico", e.minVal ); }	},
	{	AE_CRIT_PERCENT,	               Min    |Chance, F{ I( "%+i%% de dano critico, %+i%% de chance de critico", e.minVal, e.chance ); }	},
	{	AE_CRIT_DAMAGE,	                   Min|Max       , F{ I( "%s de dano critico", par(e.minVal, e.maxVal) ); }	},
	{	AE_SPICIES_DAMAGE,	               Min|Max       , F{ I( "%s de dano contra %s", par(e.minVal, e.maxVal), Spicies[e.type] ); }	},
	{	AE_SPICIES_DAMAGE_PERCENT,	       Min           , F{ I( "%+i%% de dano da arma contra %s", e.minVal, Spicies[e.type] ); }	},
	{	AE_SPICIES_TO_HIT,	                       Chance, F{ I( "%+i de precisao contra %s", e.chance, Spicies[e.type] ); }	},
	{	AE_SPICIES_AC,	                   Min           , F{ I( "%+i de armadura contra %s", e.minVal, Spicies[e.type] ); }	},
	{	AE_SPICIES_AC_PERCENT,	           Min           , F{ I( "%+i%% de armadura contra %s", e.minVal, Spicies[e.type] ); }	},
	{	AE_SPICIES_DFE,	                   Min           , F{ I( "%+i de dano recebido de %s", e.minVal, Spicies[e.type] ); }	},
	{	AE_LIFE_PERCENT,	               Min           , F{ I( "vida: %+i%%", e.minVal ); }	},
	{	AE_MANA_PERCENT,	               Min           , F{ I( "mana: %+i%%", e.minVal ); }	},
	{	AE_WEAPON_PERCENT,	               Min           , F{ I( "%+i%% de dano de %s ", e.minVal, Weapons[e.type] ); }	},
	{	AE_RESIST,	                       Min           , F{ I( "%+i de resistencia a %s", e.minVal, Elements[e.type]  ); }	},
	{	AE_THORNS_PERCENT,	               Min           , F{ I( "%+i%% de dano de espinhos", e.minVal ); }	},
	{	AE_STUN_RESIST,                    Min           , F{ I( "%+i de resistencia a atordoamento", e.minVal ); } },
	{	AE_REQUIRED_CLVL,                  Min           , 0	}, // F{ I( "requires character level %i", e.minVal ); }	},
	{	AE_SOCKET,                         Min           , 0	},
	{	AE_CLVL_AC,	                       Min|Max       , F{ int l = 0; l += I(l,"AC: ");                              l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_HIT,	                   Min|Max       , F{ int l = 0; l += I(l,"Precisao: ");                        l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_DAMAGE,	                   Min|Max       , F{ int l = 0; l += I(l,"Dano: ");                          l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_DAMAGE_PERCENT,	           Min|Max       , F{ int l = 0; l += I(l,Dano da arma: ");                   l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_DFE,	                   Min|Max       , F{ int l = 0; l += I(l,"DFE: ");                             l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_RESIST_ALL,	               Min|Max       , F{ int l = 0; l += I(l,"Todas as resistencias: ");                      l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_STAT_ALL,	               Min|Max       , F{ int l = 0; l += I(l,"Todos os atributos: ");                  l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_HP,	                       Min|Max       , F{ int l = 0; l += I(l,"Vida: ");                            l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_MANA,	                   Min|Max       , F{ int l = 0; l += I(l,"Mana: ");                            l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_MELEE_RES,	               Min|Max       , F{ int l = 0; l += I(l,"Resistencia a dano corpo a corpo: ");             l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_ARROW_RES,	               Min|Max       , F{ int l = 0; l += I(l,"Resistencia a dano de projeteis: ");             l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_STUN_RES,	               Min|Max       , F{ int l = 0; l += I(l,"Resistencia a atordoamento: ");                  l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_GOLD,	                   Min|Max       , F{ int l = 0; l += I(l,"Ouro encontrado: ");                      l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_XP,	                       Min|Max       , F{ int l = 0; l += I(l,"Experiencia obtida: ");               l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SPELL_ALL,	               Min|Max       , F{ int l = 0; l += I(l,"Poder magico: ");                     l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_RESIST,	                   Min|Max       , F{ int l = 0; l += I(l,Resistencia a %s: ", Elements[e.type]);		l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_STAT,	                   Min|Max       , F{ int l = 0; l += I(l,"%s: ", Stats[e.type]);				l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SPELL_LVL,	               Min|Max       , F{ int l = 0; l += I(l,Nivel de %s: ", getSpellName(e.type));	l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_ELEM_PERCENT,	           Min|Max       , F{ int l = 0; l += I(l,"%s Dano: ", Elements[e.type]);		l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SPELL_PERCENT,	           Min|Max       , F{ int l = 0; l += I(l,Dano de %s: ", getSpellName(e.type));	l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_CRIT_CHANCE,               Min|Max       , F{ int l = 0; l += I(l,"Chance de critico: ");                     l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_CRIT_DAMAGE_PERCENT,	   Min|Max       , F{ int l = 0; l += I(l,"Dano critico: ");                     l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_DAMAGE,			   Min|Max       , F{ int l = 0; l += I(l,"Dano das invocacoes: ");                   l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_DAMAGE_PERCENT,	   Min|Max       , F{ int l = 0; l += I(l,"Dano das invocacoes: ");                   l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_TO_HIT,			   Min|Max       , F{ int l = 0; l += I(l,Precisao das invocacoes: ");                 l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_AC,				   Min|Max       , F{ int l = 0; l += I(l,"Armadura das invocacoes: ");                       l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_HP,				   Min|Max       , F{ int l = 0; l += I(l,"Vida das invocacoes: ");                   l += I(l,"%+i (",   e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_CLVL_SUMMON_HP_PERCENT,		   Min|Max       , F{ int l = 0; l += I(l,"Vida das invocacoes: ");                   l += I(l,"%+i%% (", e.minVal + p.CharLevel * e.maxVal / 100); if( e.minVal ) l += I(l,"%i + ", e.minVal); I(l,"CLVL x %g)", double(e.maxVal)/100); } },
	{	AE_NO	}
	 
};

int	ActThorns( uint playerIndex, int type, int minVal, int maxVal, int row, int col );
int ApplyWineFromTearsPerk(uint playerIndex, int type, int minVal, int maxVal, int row, int col);

void EffectAction::operator= (Effect& e){ id = (EFFECT_ACTION)e.type; minVal = e.minVal; maxVal = e.maxVal; chance = e.chance; }
void EffectAction::operator+=(Effect& e){ id = (EFFECT_ACTION)e.type; minVal+= e.minVal; maxVal+= e.maxVal; chance+= e.chance; }
template<typename... T> __forceinline char* N( const char* s, T... a ) { sprintf_s( ErrorTextBuffer, sizeof(ErrorTextBuffer), s, a ... ); return ErrorTextBuffer; }
#define R return

BaseAction BaseActions[] = {
	{ EA_NO,                    F{R N("Sem efeito");},                          T_NO,          0 },

	{ EA_MELEE_FIRE,            F{R N("Fogo corpo a corpo");},                          T_ATTACK,      0 }, // ET_1_FIRE
	{ EA_MELEE_LIGHTNING,       F{R N("Raio corpo a corpo");},                     T_ATTACK,      0 }, // ET_2_LIGHTNING
	{ EA_MELEE_ARCAN,           F{R N("Arcano corpo a corpo");},                        T_ATTACK,      0 }, // ET_3_ARCAN
	{ EA_MELEE_ACID,            F{R N("Acido corpo a corpo");},                          T_ATTACK,      0 }, // ET_4_ACID
	{ EA_MELEE_HOLY,            F{R N("Sagrado corpo a corpo");},                          T_ATTACK,      0 }, // ET_5_HOLY
	{ EA_MELEE_COLD,            F{R N("Gelo corpo a corpo");},                          T_ATTACK,      0 }, // ET_6_COLD

	{ EA_ARROW_FIRE,            F{R N("Fogo a distancia");},                          T_ATTACK,      0 }, // ET_1_FIRE
	{ EA_ARROW_LIGHTNING,       F{R N("Raio a distancia");},                     T_ATTACK,      0 }, // ET_2_LIGHTNING
	{ EA_ARROW_ARCAN,           F{R N("Arcano a distancia");},                        T_ATTACK,      0 }, // ET_3_ARCAN
	{ EA_ARROW_ACID,            F{R N("Acido a distancia");},                          T_ATTACK,      0 }, // ET_4_ACID
	{ EA_ARROW_HOLY,            F{R N("Sagrado a distancia");},                          T_ATTACK,      0 }, // ET_5_HOLY
	{ EA_ARROW_COLD,            F{R N("Gelo a distancia");},                          T_ATTACK,      0 }, // ET_6_COLD

	{ EA_LIFE_STEAL,            F{R N("Roubo de vida em golpe corpo a corpo:");},            T_DAMAGE,      0 },
	{ EA_MANA_STEAL,            F{R N("Roubo de mana em golpe corpo a corpo:");},            T_DAMAGE,      0 },
	{ EA_TAKEN_TO_MANA,         F{R N("Dano recebido convertido em mana");},                T_TAKE_DAMAGE, 0 },
	{ EA_THORNS,                F{R N("Dano de espinhos");},                       T_TAKE_MELEE,  ActThorns },
	{ EA_WINE_FROM_TEARS,       F{R N("Cura por vinho");},                           T_TAKE_HIT,    ApplyWineFromTearsPerk },

	{ EA_QUENCH_DAMAGE,         F{R N("Dano");},                              T_DAMAGE,      0 },
	{ EA_QUENCH_ARMOR,          F{R N("Armadura");},                               T_DAMAGE,      0 },
	{ EA_QUENCH_SPELL_DAMAGE,   F{R N("Dano de magia");},                        T_DAMAGE,      0 },
	{ EA_QUENCH_SUMMON_DAMAGE,  F{R N("Dano das invocacoes");},                       T_DAMAGE,      0 },

	{ EA_KNOCK_BACK,            F{R N("Empurra o alvo");},                  T_HIT,         0 },
	{ EA_MULTISHOT,             F{R N("Tiro multiplo");},                           T_ATTACK,      0 },
	{ EA_INFRAVISION,           F{R N("Infravisao");},							T_PASSIVE,     0 },
	{ EA_LOSE_REGENERATION,     F{R N("Perde toda a regeneracao");},               T_PASSIVE,     0 },
	{ EA_LOSE_RESISTANCE,       F{R N("Perde todas as resistencias");},                T_PASSIVE,     0 },
	{ EA_FURY_DURATION,         F{R N((p.ClassID == PC_2_MAGE ? "+%i seconds to duration of Concentration" : (p.fullClassId == PFC_KENSEI && MaxCountOfPlayersInGame == 1) ? "+%i seconds to duration of Battle Trance" : "+%i seconds to Fury duration"), p.CharLevel / 6 + 10);}, T_PASSIVE, 0 },
	{ EA_FAST_BLOCK,            F{R N("velocidade de bloqueio rapida");},                 T_PASSIVE,     0 },
	{ EA_RANDOM_SPEED_ARROW,    F{R N("dispara flechas com velocidade aleatoria");},           T_PASSIVE,     0 },
	{ EA_LIFE_REGEN_DOUBLE,     F{R N("duplica a regeneracao basica de vida");},     T_PASSIVE,     0 },
	{ EA_MANA_REGEN_DOUBLE,     F{R N("duplica a regeneracao basica de mana");},     T_PASSIVE,     0 },
	{ EA_AC_DEMON_MELEE,        F{R N("+20 de armadura contra demonios");},            T_PASSIVE,     0 },
	{ EA_AC_UNDEAD_MELEE,       F{R N("+15 de armadura contra mortos-vivos");},            T_PASSIVE,     0 },
	{ EA_MANACOST,              F{R N("-25%% de custo de mana");},                     T_PASSIVE,     0 },
	{ EA_MORE_DAMAGE_CHANCE,    F{R N("30%% de chance de causar +50%% de dano");}, T_PASSIVE,     0 },
	{ EA_RANDOM_DAMAGE,         F{R N("Dano aleatorio: 80-150%%");},         T_PASSIVE,     0 },
	{ EA_LIFE_STEAL_RND,	    F{R N("Roubo de vida aumentado aleatoriamente" );},	T_HIT_MELEE,   0 },

	//{ EA_THORNS_FIRE, "Thorns", T_TAKE_MELEE, 0 },  // тут можно будет добавить это:

	{ EA_END_MARKER }
};

//----- (th2) -------------------------------------------------------------
void __fastcall ActGoldFind( int& gold )
{
    const Player& player = Players[CurrentPlayerIndex];
    int newGoldValue = gold
        + gold * player.goldFind / 100
        + RngFromRange( player.goldAbsFindMin, player.goldAbsFindMax );
    LimitToMin(newGoldValue, 1);
	gold = newGoldValue;
}
	
BaseCrit BaseCrits[CR_COUNT][PFC_COUNT] = {
	// base_chance,	+%damage,	+damageMin,	+damageMax,	CLVL_Div,	func?
	{ // melee
	{  5, 200, 0, 0, 0, 0 }, // WARRIOR, +10% DPS
	{  5, 200, 0, 0, 0, 0 }, // INQUISITOR, +10%
	{ 10, 100, 5, 10, 0, 0 }, // GUARDIAN, +10%
	{  5, 150, 0, 0, 0, 0 }, // TEMPLAR, +7,5%
	{ 0, 0, 0, 0, 0, 0 }, // ARCHER
	{ 0, 0, 0, 0, 0, 0 }, // SCOUT
	{ 0, 0, 0, 0, 0, 0 }, // SHARPSHOOTER
	{ 0, 0, 0, 0, 0, 0 }, // TRAPPER
	{ 0, 0, 0, 0, 0, 0 }, // MAGE
	{ 0, 0, 0, 0, 0, 0 }, // ELEMENTALIST
	{ 0, 0, 0, 0, 0, 0 }, // DEMONOLOGIST?
	{ 0, 0, 0, 0, 0, 0 }, // NECROMANCER?
	{ 0, 0, 0, 0, 0, 0 }, // BEASTMASTER?
	{ 0, 0, 0, 0, 0, 0 }, // WARLOCK?
	{ 10, 200, 0, 0, 0, 0 }, // MONK, +20%
	{  8, 125, 0, 0, 0, 0 }, // KENSEI, +10%
	{  6, 100, 0, 0, 0, 0 }, // SHUGOKI, +6%
	{  8, 150, 0, 0, 0, 0 }, // SHINOBI, +12%
	{  7, 100, 3, 5, 0, 0 }, // ROGUE, +7%
	{ 12, 250, 10, 15, 0, 0 }, // ASSASSIN, +30%
	{  8, 125, 0, 0, 0, 0 }, // IRON MAIDEN, +10%
	{ 0, 0, 0, 0, 0, 0 }, // BOMBARDIER
	{ 0, 0, 0, 0, 0, 0 }, // SAVAGE, NO CRITS
	{  6, 150, 0, 0, 0, 0 }, // BERSERKER, +9%
	{  5, 200, 0, 0, 0, 0 }, // EXECUTIONER, +10%
	{  5, 150, 0, 0, 0, 0 }, // THRAEX, +7.5%
	{  3, 130, 10, 20, 0, 0 }, // MURMILLO, +4%
	{  3, 100, 0, 0, 0, 0 }, // DIMACHAERUS, +3%
	{ 11, 100, 1, 2, 0, 0 }, // SECUTOR, +11%
	{ 9, 50, 10, 50, 0, 0 }, // DRUID
	},
	{ // arrow
	{ 8, 45, 0, 0, 0, 0 }, // WARRIOR, +3,6% 
	{ 3, 40, 0, 0, 0, 0 }, // INQUISITOR, +1,2% 
	{ 7, 90, 10, 20, 0, 0 }, // GUARDIAN, +6,3%
	{ 9, 60, 0, 0, 0, 0 }, // TEMPLAR, +5,4%
	{ 10, 140, 0, 0, 0, 0 }, // ARCHER, +14%
	{ 0, 0, 0, 0, 0, 0 }, // SCOUT
	{ 12, 160, 10, 20, 0, 0 }, // SHARPSHOOTER, +19,2%
	{ 8, 80, 0, 0, 0, 0 }, // TRAPPER, +6,4%
	{ 0, 0, 0, 0, 0, 0 }, // MAGE
	{ 0, 0, 0, 0, 0, 0 }, // ELM
	{ 0, 0, 0, 0, 0, 0 }, // DMN
	{ 0, 0, 0, 0, 0, 0 }, // NCR
	{ 0, 0, 0, 0, 0, 0 }, // BST
	{ 0, 0, 0, 0, 0, 0 }, // WRLK
	{ 4, 90, 0, 0, 0, 0 }, // MONK, +3,6%
	{ 3, 135, 0, 0, 0, 0 }, // KNS, +3,6%
	{ 6, 60, 0, 0, 0, 0 }, // SHG, +3,6%
	{ 10, 36, 0, 0, 0, 0 }, // SHN, +3,6%
	{ 0, 0, 0, 0, 0, 0 }, // ROGUE, no crits
	{ 7, 250, 7, 9, 0, 0 }, // ASN, +17,5%
	{ 9, 75, 0, 0, 0, 0 }, // IM, +6,75%
	{ 0, 0, 0, 0, 0, 0 }, // BMB 0
	{ 0, 0, 0, 0, 0, 0 }, // SAVAGE 0
	{ 7, 50, 0, 0, 0, 0 }, // BRS, +3,6%
	{ 4, 90, 0, 0, 0, 0 }, // EXE, +3,6%
	{ 5, 72, 0, 0, 0, 0 }, // TRX, +3,6%
	{ 2, 100, 0, 0, 0, 0 }, // MRM, +2%
	{ 8, 45, 0, 0, 0, 0 }, // DMC, +3,6%
	{ 3, 120, 0, 0, 0, 0 }, // SCT, +3,6%
	{ 0, 40, 0, 0, 0, 0 }, // DRUID
	},
	{ // magic missile
	{ 0, 0, 0, 0, 0, 0 }, // WARRIOR
	{ 1, 10, 0, 0, 85, 0 }, // INQUISITOR
	{ 0, 0, 0, 0, 0, 0 }, // GUARDIAN
	{ 0, 0, 0, 0, 0, 0 }, // TEMPLAR
	{ 0, 0, 0, 0, 0, 0 }, // ARCHER
	{ 1, 50, 0, 0, 30, 0 }, // SCOUT, +3% DPS on clvl 150 (6% for +50% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // SHARPSHOOTER
	{ 0, 50, 0, 0, 0, 0 }, // TRAPPER
	{ 5, 50, 0, 0, 0, 0 }, // MAGE, +2,5% DPS on clvl 150 (5% for +50% dmg)
	{ 5, 60, 0, 0, 0, 0 }, // ELEMENTALIST, +3% DPS on clvl 150 (5% for +60% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // DEMONOLOGIST
	{ 0, 50, 0, 0, 0, 0 }, // NECROMANCER
	{ 0, 50, 0, 0, 0, 0 }, // BEASTMASTER
	{ 5, 40, 0, 0, 0, 0 }, // WARLOCK, +2% DPS on clvl 150 (5% for +40% dmg)
	{ 0, 10, 0, 0, 0, 0 }, // MONK
	{ 0, 10, 0, 0, 0, 0 }, // KENSEI
	{ 0, 10, 0, 0, 0, 0 }, // SHUGOKI
	{ 0, 20, 0, 0, 0, 0 }, // SHINOBI
	{ 5, 75, 0, 0, 14, 0 }, // ROGUE, +11,25% DPS on clvl 150 (15% for +75% dmg)
	{ 0, 50, 0, 0, 14, 0 }, // ASSASSIN, +5% DPS on clvl 150 (10% for +50% dmg)
	{ 0, 30, 0, 0, 0, 0 }, // IRON MAIDEN
	{ 5, 85, 0, 0, 5, 0 }, // BOMBARDIER
	{ 0, 10, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 10, 0, 0, 0, 0 }, // BERSERKER
	{ 0, 10, 0, 0, 0, 0 }, // EXECUTIONER
	{ 0, 10, 0, 0, 0, 0 }, // THRAEX
	{ 0, 10, 0, 0, 0, 0 }, // MURMILLO
	{ 0, 10, 0, 0, 0, 0 }, // DIMACHAERUS
	{ 0, 40, 0, 0, 0, 0 }, // SECUTOR
	{ 2, 40, 0, 0, 0, 0 }, // DRUID
	},
	{ // reflect
	{ 0, 50, 0, 0, 0, 0 }, // WARRIOR
	{ 0, 50, 0, 0, 0, 0 }, // WARRIOR
	{ 0, 50, 0, 0, 0, 0 }, // WARRIOR
	{ 0, 50, 0, 0, 0, 0 }, // WARRIOR
	{ 0, 50, 0, 0, 0, 0 }, // ARCHER
	{ 0, 50, 0, 0, 0, 0 }, // ARCHER
	{ 0, 50, 0, 0, 0, 0 }, // ARCHER
	{ 0, 50, 0, 0, 0, 0 }, // ARCHER
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 50, 0, 0, 0, 0 }, // MAGE
	{ 0, 150, 0, 0, 0, 0 }, // MONK
	{ 0, 150, 0, 0, 0, 0 }, // MONK
	{ 0, 150, 0, 0, 0, 0 }, // MONK
	{ 0, 150, 0, 0, 0, 0 }, // MONK
	{ 0, 50, 0, 0, 0, 0 }, // ROGUE
	{ 0, 50, 0, 0, 0, 0 }, // ROGUE
	{ 20, 200, 0, 0, 0, 0 }, // im, +40% DPS on clvl 150 (20% for +200% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // ROGUE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 200, 0, 0, 0, 0 }, // DRUID
	},
	{ // elemental arrow/weapon explosion
	{ 0, 50, 0, 0, 0, 0 }, // WARRIOR
	{ 10, 100, 0, 0, 29, 0 }, // INQUISITOR, +15% DPS on clvl 150 (15% for +100% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // GUARDIAN
	{ 0, 50, 0, 0, 0, 0 }, // TEMPLAR
	{ 0, 50, 0, 0, 0, 0 }, // ARCHER
	{ 10, 100, 0, 0, 29, 0 }, // SCOUT, +15% DPS on clvl 150 (15% for +100% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // SHARPSHOOTER
	{ 0, 50, 0, 0, 0, 0 }, // TRAPPER
	{ 0, 50, 0, 0, 0, 0 }, // MAGE, 
	{ 0, 50, 0, 0, 0, 0 }, // ELEMENTALIST,
	{ 0, 50, 0, 0, 0, 0 }, // DEMONOLOGIST
	{ 0, 50, 0, 0, 0, 0 }, // NECROMANCER
	{ 0, 50, 0, 0, 0, 0 }, // BEASTMASTER
	{ 0, 50, 0, 0, 0, 0 }, // WARLOCK,
	{ 0, 50, 0, 0, 0, 0 }, // MONK
	{ 0, 50, 0, 0, 0, 0 }, // KENSEI
	{ 0, 50, 0, 0, 0, 0 }, // SHUGOKI
	{ 0, 50, 0, 0, 0, 0 }, // SHINOBI
	{ 5, 30, 0, 0, 29, 0 }, // ROGUE, +3% DPS on clvl 150 (10% for +30% dmg)
	{ 1, 60, 0, 0, 26, 0 }, // ASSASSIN, +3,6% DPS on clvl 150 (6% for +60% dmg)
	{ 0, 50, 0, 0, 0, 0 }, // IRON MAIDEN
	{ 0, 50, 0, 0, 0, 0 }, // BOMBARDIER
	{ 0, 50, 0, 0, 0, 0 }, // SAVAGE
	{ 0, 50, 0, 0, 0, 0 }, // BERSERKER
	{ 0, 50, 0, 0, 0, 0 }, // EXECUTIONER
	{ 0, 50, 0, 0, 0, 0 }, // THRAEX
	{ 0, 50, 0, 0, 0, 0 }, // MURMILLO
	{ 0, 50, 0, 0, 0, 0 }, // DIMACHAERUS
	{ 0, 50, 0, 0, 0, 0 }, // SECUTOR
	{ 0, 50, 0, 0, 0, 0 }, // DRUID
	},
};


BaseCrit GetBaseCrits(int critType, int playerIndex)
{
	Player& player = Players[playerIndex];
	BaseCrit bc = BaseCrits[critType][player.fullClassId];
	if (critType == CR_ARROW && HasTrait(playerIndex, TraitId::Ranger)) {
		bc.chance += 2 + player.CharLevel / 18;
	}
	else if (critType == CR_MELEE && HasTrait(playerIndex, TraitId::Fechtmeister)) {// else because these traits are incompatible
		bc.chance += 4;
		bc.percent += 50;
	}
	else if (player.fullClassId == PFC_DIMACHAERUS && critType == CR_MELEE && (is(GameMode, GM_IRONMAN, GM_NIGHTMARE, GM_SURVIVAL))) {
		bc.chance += 3;
	}
	else if (HasTrait(playerIndex, TraitId::Crupellarius) && (critType == CR_MELEE || critType == CR_ARROW)) {
		bc.chance -= 1;
	}
	//------------------------ trait specials ----------
	if (HasTrait(playerIndex, TraitId::Mamluk)) {
		if (critType == CR_ARROW) {
			bc.chance += 5 + player.CharLevel / 29;
		}
		else if (critType == CR_MELEE) {
			bc.chance += 5 + player.CharLevel / 29;
		}
		else if (critType == CR_MAGIC) {
			bc.chance = 0;
		}
		else if (critType == CR_ELEMENTAL) {
			bc.chance = 10; bc.percent = 200;
		}
	}
	else if (HasTrait(playerIndex, TraitId::Paladin)) {
		if (critType == CR_MAGIC) {
			bc.chance = 5 + player.CharLevel / 10;
			bc.percent = 200;
		}
	}
	else if (HasTrait(playerIndex, TraitId::Pistoleer)) {
		if (critType == CR_MELEE) {
			bc.chance = 0;
			bc.percent = 0;
		}
	}
	if (GameMode == GM_CLASSIC) {
		if (critType == CR_MELEE) {
			if (player.fullClassId == PFC_WARRIOR) {
				bc.chance = player.CharLevel;
				bc.percent = 100;
			}
			else {
				bc.chance = 0;
				bc.percent = 0;
			}
		}
		else {
			bc.chance = 0;
			bc.percent = 0;
		}
	}
	return bc;
}

//----- (th2) -------------------------------------------------------------
void __fastcall ActCriticalHit( int& damage, int playerIndex, int row, int col, bool playSound,int damageType, int baseMissileIndex )
{
	Player& player = Players[playerIndex];
	BaseMissile& bm = BaseMissiles[baseMissileIndex];
	int critType = CR_MAGIC;
	if (baseMissileIndex == -1) { 
		critType = CR_MELEE; 
	}
	else if (baseMissileIndex == -2) { 
		critType = CR_REFLECT; 
	}
	else if (bm.EffectType == MT_0_ARROW) {
		if (bm.DamageType == ET_0_PHYSICAL) {
			critType = CR_ARROW;
		}
		else {
			critType = CR_ELEMENTAL;
		}
	}
	BaseCrit bc = GetBaseCrits(critType, playerIndex);

	int chance = bc.chance + (bc.levelDiv ? player.CharLevel / bc.levelDiv : 0);
	int percent = bc.percent;
	int damageMin = bc.damageMin;
	int damageMax = bc.damageMax;

	// Additional crits from items and perks now work only for melee damage and phisical part of arrows
	if (critType == CR_MELEE || (critType == CR_ARROW && damageType == ET_0_PHYSICAL)) {
		chance += player.critChance;
		percent += player.critPercent;
		if (player.fullClassId != PFC_TRAPPER) {
			damageMin += player.critDamageMin;
			damageMax += player.critDamageMax;
		}
	}
	if ((damageMin || damageMax || percent) && chance > 0) {
		if (RNG(100) < chance) {
			if (playSound && damageType == 0) {
				PlayLocalSound(S_972_CRIT_SOUND_01, row, col);
			}
			damage += damage * percent / 100;
			if (damageMax || damageMin) damage += RngFromRange(damageMin, damageMax);
		}
	}
}

//----- (th2) -------------------------------------------------------------
int ApplyWineFromTearsPerk(uint playerIndex, int /*type*/, int minVal, int maxVal, int row, int col) {
	Player& player = Players[playerIndex];
	player.CurLife += minVal << 6;
	player.BaseLife += minVal << 6;
	LimitToMax(player.CurLife, player.MaxCurLife);
	LimitToMax(player.BaseLife, player.MaxBaseLife);
	return 1;
}

//----- (th2) -------------------------------------------------------------
int	ActThorns( uint playerIndex, int /*type*/, int minVal, int maxVal, int row, int col )
{
    int monsterNumber = MonsterMap[ row ][ col ];
    if( monsterNumber ){
        PvM_Melee(playerIndex, abs(monsterNumber) - 1, false, true, minVal, maxVal);
    }
    return 1;
}

//----- (th2) -------------------------------------------------------------
void OnTakeMeleeTrigger( int monsterIndex, int playerIndex )
{
    Player& player = Players[playerIndex];
    for( size_t i = 0; player.effectAction[i].id != EA_NO; ++i ){
        EffectAction& action = player.effectAction[i];
        BaseAction& baseAction = BaseActions[action.id];
        if( (baseAction.trigger & T_TAKE_MELEE) != 0 && baseAction.act != nullptr ){
            int toProcRandFactor = RNG(100);
            if( toProcRandFactor < action.chance ){
            	Monster& monster = Monsters[monsterIndex];
            	
				int result = baseAction.act( playerIndex, action.id, action.minVal, action.maxVal, monster.Row, monster.Col );
            }
        }
    }
}

// TODO: as CurAffixes(droptype) can be reused to unify Item_AddAffixes/Prefix funcs for magic and rare
//----- (th3) -------------------------------------------------------------
Affix* CurAffixesMagic()
{
	switch(GameMode){
	case GM_COLISEUM: return AffixesColiseum;
	case GM_CLASSIC : return AffixesClassic;
	default         : return Affixes;
	}
}
