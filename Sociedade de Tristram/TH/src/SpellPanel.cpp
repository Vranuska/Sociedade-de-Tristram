#include "stdafx.h"


DisplayObject SpellBookRect;
DisplayObject SpellBookTextRect;
DisplayObject SpellBookPageButtonsRect;
DisplayObject SpellBookSpellButtonsRect;


//----- (th2) -------------------------------------------------------------
PLAYER_SPELL LearnedSpells(int page, int line)
{
	static PLAYER_SPELL BasePages[GUI_SpellBook_PagesAmount * GUI_SpellBook_SpellsPerPageAmount] = {
		// page 1
		PS_0_NONE,
		PS_22_FURY,
		PS_7_TOWN_PORTAL,
		PS_16_REFLECT,
		PS_33_TELEKINES,
		PS_11_MANA_SHIELD,
		PS_23_TELEPORT,
		PS_2_HEALING,
		PS_34_HEAL_OTHER,

		// page 2
		PS_1_FIREBOLT,
		PS_20_INCINERATE,
		PS_6_FIRE_WALL,
		PS_12_FIREBLAST,
		PS_19_FLAME_RING,
		PS_41_FIERY_NOVA,
		PS_13_HYDRA,
		PS_M1_NONE,
		PS_M1_NONE,

		// page 3
		PS_30_CHARGED_BOLT,
		PS_3_LIGHTNING,
		PS_40_LIGHTING_WALL,
		PS_14_BALL_LIGHTNING,
		PS_17_LIGHTING_RING,
		PS_18_LIGHTNING_NOVA,
		PS_35_ARCANE_STAR,
		PS_4_FLASH,
		PS_43_ARCANE_NOVA,

		// page 4
		PS_31_HOLY_BOLT,
		PS_39_HOLY_NOVA,
		PS_36_BONE_SPIRIT,
		PS_15_FORCE_WAVE,
		PS_21_GOLEM,
		PS_8_STONE_CURSE,
		PS_29_ELEMENTAL,
		PS_M1_NONE,
		PS_M1_NONE,

		// page 5
		PS_56_ICE_BOLT,
		PS_57_FREEZING_BALL,
		PS_58_FROST_NOVA,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_52_LESSER_SUMMON,
		PS_53_COMMON_SUMMON,
		PS_54_GREATER_SUMMON,

		// page 6
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
		PS_M1_NONE,
	};
	constexpr auto pos = [](int page, int line){ return page * GUI_SpellBook_SpellsPerPageAmount + line; };
	int index = pos(page, line);
	PLAYER_SPELL spell = BasePages[index];
	Player& player = Players[CurrentPlayerIndex];
	switch( index ){
	case pos(0, 0):
		switch( player.ClassID ){
		case PC_0_WARRIOR: spell = PS_26_ITEM_REPAIR; break;
		case PC_1_ARCHER : spell = PS_9_INFRAVISION; break;
		case PC_2_MAGE   : spell = PS_27_STAFF_RECHARGE; break;
		case PC_3_MONK   : spell = PS_33_TELEKINES; break;
		case PC_4_ROGUE  : spell = PS_5_IDENTIFY; break;
		case PC_5_SAVAGE : spell = PS_16_REFLECT; break;
		}
		if( player.fullClassId == PFC_IRON_MAIDEN || HasTrait(CurrentPlayerIndex, TraitId::Mamluk)) spell = PS_26_ITEM_REPAIR;
		else if( player.gameChanger & BIT(GC_9_NIGHT_KIN) ) spell = PS_9_INFRAVISION;
		else if ( HasTrait(CurrentPlayerIndex, TraitId::Hydramancer)) spell = PS_13_HYDRA;
		else if (HasTrait(CurrentPlayerIndex, TraitId::Paladin)) spell = PS_11_MANA_SHIELD;
		//else if (player.fullClassId == PFC_WARLOCK) spell = PS_13_HYDRA;
		break;
	case pos(4, 0): if( player.fullClassId == PFC_WARLOCK ) spell = PS_59_RANCID_BOLT; break;
	case pos(4, 1): if( player.fullClassId == PFC_WARLOCK ) spell = PS_60_TOXIC_BALL; break;
	case pos(4, 2): if( player.fullClassId == PFC_WARLOCK ) spell = PS_61_ACID_NOVA; break;
	case pos(1, 6): if( player.fullClassId == PFC_ELEMENTALIST ) spell = PS_M1_NONE; break;
	case pos(4, 3): if( player.fullClassId == PFC_ELEMENTALIST ) spell = PS_13_HYDRA; break;
	}
	return spell;
}

//----- (th2) -------------------------------------------------------------
void WriteSummonSpellBookInfo(PLAYER_SPELL minionTypeSpell, int LINE_HEIGHT, int& lineIndex) {
	
	auto drawLine = [&](const char* text, int baseFontColor = C_0_White)
	{
		DrawTextColored(SpellBookTextRect.Left, SpellBookTextRect.Top + 11 + 8 + lineIndex * LINE_HEIGHT, SpellBookTextRect.Right, text, baseFontColor);
		++lineIndex;
	};

	int minAccuracyFirst, maxAccuracyFirst, minAccuracySecond, maxAccuracySecond, minMinDamageFirst, maxMinDamageFirst, minMaxDamageFirst, maxMaxDamageFirst, minMinDamgeSecond, maxMinDamageSecond, minMaxDamageSecond, maxMaxDamageSecond, minArmor, maxArmor, minLife, maxLife;
	Player& owner = Players[CurrentPlayerIndex];
	int clvl = owner.CharLevel;
	int slvl = PlayerSpellLevel(CurrentPlayerIndex, minionTypeSpell);

	if (minionTypeSpell == PS_21_GOLEM) {
		if (GameMode == GM_CLASSIC) {
			minLife = 2 * owner.MaxCurMana / 3 + ((10 * slvl) << 6);
			maxLife = minLife;
			minArmor = 25;
			maxArmor = minArmor;
			minAccuracyFirst = 40 + 2 * clvl + 5 * slvl;
			maxAccuracyFirst = minAccuracyFirst;
			minMinDamageFirst = 8 + 2 * slvl;
			maxMinDamageFirst = minMinDamageFirst;
			minMaxDamageFirst = 16 + 2 * slvl;
			maxMaxDamageFirst = minMaxDamageFirst;
				// the rest is not used but i'll leave it here just because
			//toHitSecond = slvl + 2 * clvl;
			//minDamageSecond = 2 * (slvl + 1);
			//maxDamageSecond = 4 * (slvl + 10); 
		}
		else {
			minLife = (((owner.CurMagic * clvl) / 10) << 6) + ((clvl * clvl) << 6) + 6400 + owner.MaxCurMana;
			maxLife = minLife + ((10 * clvl) << 6);
			minAccuracyFirst = slvl + 2 * clvl;
			maxAccuracyFirst = minAccuracyFirst;
			minAccuracySecond = slvl + 2 * clvl;
			maxAccuracySecond = minAccuracySecond;
			minMinDamageFirst = owner.CurMagic * clvl / 1000 + clvl / 2 + 1 + slvl;
			maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 2;
			minMaxDamageFirst = owner.CurMagic * clvl / 500 + 3 + clvl / 2 + slvl;
			maxMaxDamageFirst = minMaxDamageFirst + (clvl / 3) + 2;
			minMinDamgeSecond = 2 * (slvl + 1);
			maxMinDamageSecond = minMinDamgeSecond;
			minMaxDamageSecond = 4 * (slvl + 10);
			maxMaxDamageSecond = minMaxDamageSecond;
			minArmor = owner.CurMagic * clvl / 500 + (clvl / 2) + slvl;
			maxArmor = minArmor + (clvl / 10) + 2;
		}

		sprintf(InfoPanelBuffer, "cria um golem");
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, "para servir voce");
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, "(causa dano fisico)");
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);
	}
	int fclass = owner.fullClassId;
	if (is(fclass, PFC_DEMONOLOGIST, PFC_MAGE, PFC_NECROMANCER, PFC_BEASTMASTER)) {
		int summontype = 0;
		switch (minionTypeSpell) {
		case PS_21_GOLEM: summontype = SUM_GOLEM;			break;
		case PS_52_LESSER_SUMMON: summontype = SUM_LESSER;	break;
		case PS_53_COMMON_SUMMON: summontype = SUM_COMMON;	break;
		case PS_54_GREATER_SUMMON: summontype = SUM_GREATER; break;
		}
		sprintf(InfoPanelBuffer, "Quantidade maxima: %i", CalculateSummonsMaxAmount(summontype, slvl, CurrentPlayerIndex));
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);
	}
	else if (is(fclass, PFC_ARCHER, PFC_SHARPSHOOTER, PFC_SCOUT)){
		sprintf(InfoPanelBuffer, "Resistencia extra a");
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, "dano elemental: %i%%", PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 0));
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);
	}

	switch (owner.fullClassId) {
		case PFC_DEMONOLOGIST:
			switch (minionTypeSpell) {
				case PS_52_LESSER_SUMMON: {
					minLife = (((owner.CurMagic * clvl) / 22) << 6) + ((3 * clvl) << 6) + (owner.MaxCurMana / 3);
					maxLife = minLife + ((clvl + 15) << 6);
					minAccuracyFirst = owner.CurMagic * clvl / 666 + clvl / 2 + slvl / 2 + 12;
					maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
					minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
					maxAccuracySecond = minAccuracySecond;
					minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 8) : (clvl / 4)) + slvl / 2 + 2;
					maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 2;
					minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 8) : (clvl / 4)) + slvl / 2 + (is(GameMode, GM_EASY, GM_CLASSIC) ? 7 : 6);
					maxMaxDamageFirst = minMaxDamageFirst + (clvl / 4) + 3;
					minMinDamgeSecond = owner.CurMagic * clvl / 337 + clvl / 2 + slvl;
					maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2; 
					minMaxDamageSecond = owner.CurMagic * clvl / 250 + clvl / 2 + slvl + 2;
					maxMaxDamageSecond = minMaxDamageSecond + (clvl / 3) + 2;
					minArmor = owner.CurMagic * clvl / 2000 + clvl / 2 + slvl;
					maxArmor = minArmor + (clvl / 10) + 5;

					sprintf(InfoPanelBuffer, "invoca um diabrete voador");
					drawLine(InfoPanelBuffer);
					break;
				}
				case PS_53_COMMON_SUMMON: {
						minLife = (((owner.CurMagic * clvl) / 13) << 6) + (owner.MaxCurMana / 3);
						maxLife = minLife + (((2 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 666 + clvl / 3 + slvl;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 3 + 4;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 3;
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 3 + (is(GameMode, GM_EASY, GM_CLASSIC) ? 15 : 13);
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 260 + clvl / 2 + slvl;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2;
						minMaxDamageSecond = owner.CurMagic * clvl / 208 + clvl / 2 + slvl + 2;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 3) + 2;
						minArmor = owner.CurMagic * clvl / 2000 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um arqueiro bode");
						drawLine(InfoPanelBuffer);
						break;
				}
				case PS_54_GREATER_SUMMON: {
					minLife = ((owner.CurMagic * clvl / 5) << 6) + (owner.MaxCurMana * 2);
						maxLife = minLife + (((10 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 400 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 2 + 4;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 7) + 3;
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 2 + 9;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 260 + clvl / 2 + slvl;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2;
						minMaxDamageSecond = owner.CurMagic * clvl / 208 + clvl / 2 + slvl + 2;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 10) + 5;
						minArmor = owner.CurMagic * clvl / 300 + clvl / 2 + 2 * slvl + 1;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um senhor satiro");
						drawLine(InfoPanelBuffer);
						break;
				}
			}	break;
		case PFC_NECROMANCER:
			switch (minionTypeSpell) {
				case PS_52_LESSER_SUMMON: {
						minLife = (((owner.CurMagic * clvl) / 16) << 6) + (owner.MaxCurMana / 5);
						maxLife = minLife + ((clvl + 5) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 500 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 6) : (clvl / 3)) + (slvl / 2) + (is(GameMode, GM_EASY, GM_CLASSIC) ? 6 : 5);
						maxMinDamageFirst = minMinDamageFirst + ((clvl / 10) + 1);
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 6) : (clvl / 3)) + (slvl / 2) + 8;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 7) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 337 + clvl / 2 + slvl;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2;
						minMaxDamageSecond = owner.CurMagic * clvl / 250 + clvl / 2 + slvl + 2;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 3) + 2;
						minArmor = owner.CurMagic * clvl / 2000 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um arqueiro esqueletico");
						drawLine(InfoPanelBuffer);
						break;
				}
				case PS_53_COMMON_SUMMON: {
						minLife = (((owner.CurMagic * clvl) / 7) << 6) + (owner.MaxCurMana / 2);
						maxLife = minLife + (((2 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 333 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 666 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 2)) + slvl / 2 + (is(GameMode, GM_EASY, GM_CLASSIC) ? 8 : 7);
						maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 5;
						minMaxDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 2)) + slvl / 2 + (is(GameMode, GM_EASY, GM_CLASSIC) ? 16 : 14);
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 260 + clvl / 2 + slvl;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2;
						minMaxDamageSecond = owner.CurMagic * clvl / 208 + clvl / 2 + slvl + 2;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 3) + 2;
						minArmor = owner.CurMagic * clvl / 500 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um guerreiro esqueletico");
						drawLine(InfoPanelBuffer);
						break;
				}
				case PS_54_GREATER_SUMMON: {
						minLife = ((owner.CurMagic * clvl / 5) << 6) + (owner.MaxCurMana * 2);
						maxLife = minLife + (((10 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 300 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 2) : (clvl / 2)) + slvl / 2 + 5;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 7) + 5;
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 2) : (clvl / 2)) + slvl / 2 + 20;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 400 + clvl + slvl / 2 + 14;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 10) + 5;
						minMaxDamageSecond = owner.CurMagic * clvl / 300 + clvl + slvl / 2 + 23;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 8) + 5;
						minArmor = owner.CurMagic * clvl / 500 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um senhor esqueletico");
						drawLine(InfoPanelBuffer);
						break;
				}
			} break;
		case PFC_BEASTMASTER:
			switch (minionTypeSpell) {
				case PS_52_LESSER_SUMMON: {
						minLife = (((owner.CurMagic * clvl) / 17) << 6) + ((5 * clvl) << 6) + (owner.MaxCurMana / 3);
						maxLife = minLife + ((clvl + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 666 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 3)) + slvl / 2 + 5;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 2;
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 3)) + slvl / 2 + 8;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 3) + 3;
						minMinDamgeSecond = owner.CurMagic * clvl / 337 + clvl / 2 + slvl;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 2;
						minMaxDamageSecond = owner.CurMagic * clvl / 250 + clvl / 2 + slvl + 2;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 3) + 2;
						minArmor = owner.CurMagic * clvl / 800 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um ferrador");
						drawLine(InfoPanelBuffer);
						break;
				}
				case PS_53_COMMON_SUMMON: {
						minLife = (((owner.CurMagic * clvl) / 6) << 6) + (owner.MaxCurMana / 2);
						maxLife = minLife + (((2 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 500 + clvl / 2 + slvl / 2 + 12;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 500 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 2)) + slvl / 2 + 5;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 4;
						minMaxDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 5) : (clvl / 2)) + slvl / 2 + 14;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 500 + clvl + slvl / 2 + 5;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 5) + 5;
						minMaxDamageSecond = owner.CurMagic * clvl / 400 + clvl + slvl / 2 + 14;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 8) + 5;
						minArmor = owner.CurMagic * clvl / 500 + clvl / 2 + slvl;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca um javali gigante");
						drawLine(InfoPanelBuffer);
						break;
				}
				case PS_54_GREATER_SUMMON: {
						minLife = ((owner.CurMagic * clvl / 2) << 6) + (owner.MaxCurMana * 2);
						maxLife = minLife + (((10 * clvl) + 15) << 6);
						minAccuracyFirst = owner.CurMagic * clvl / 266 + clvl / 2 + slvl / 2 + 15;
						maxAccuracyFirst = minAccuracyFirst + (clvl / 10) + 6;
						minAccuracySecond = (3 * slvl / 2) + 3 * clvl / 2;;
						maxAccuracySecond = minAccuracySecond;
						minMinDamageFirst = owner.CurMagic * clvl / 400 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 2 + 7;
						maxMinDamageFirst = minMinDamageFirst + (clvl / 5) + 4;
						minMaxDamageFirst = owner.CurMagic * clvl / 333 + (GameMode == GM_HARD ? (clvl / 4) : (clvl / 2)) + slvl / 2 + 18;
						maxMaxDamageFirst = minMaxDamageFirst + (clvl / 8) + 4;
						minMinDamgeSecond = owner.CurMagic * clvl / 400 + clvl + slvl / 2 + 14;
						maxMinDamageSecond = minMinDamgeSecond + (clvl / 10) + 5;
						minMaxDamageSecond = owner.CurMagic * clvl / 300 + clvl + slvl / 2 + 23;
						maxMaxDamageSecond = minMaxDamageSecond + (clvl / 8) + 5;
						minArmor = owner.CurMagic * clvl / 400 + clvl / 2 + slvl + 1;
						maxArmor = minArmor + (clvl / 10) + 5;

						sprintf(InfoPanelBuffer, "invoca uma fera superior");
						drawLine(InfoPanelBuffer);
						break;
				}
			}
	}
	if (minionTypeSpell != PS_21_GOLEM) {
		sprintf(InfoPanelBuffer, "para lutar por voce");
		drawLine(InfoPanelBuffer);
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);
	}

	int best_defense_trait_penalty = HasTrait(CurrentPlayerIndex, TraitId::BestDefense) ? +(25 + (owner.CharLevel / 15)) : 0;
	minLife += minLife * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	minLife += ((minLife * owner.summonHpPercent) / 100 + (owner.summonHp << 6)); // hp increase from affixes
	minLife += PerkValue(PERK_TOUGH_MINIONS, CurrentPlayerIndex) << 6; // +hp from perks
	minLife = minLife * (100 - best_defense_trait_penalty) / 100; //added here because it changes TOTAL hit points. including affix and perk buffs
	maxLife += maxLife * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	maxLife += ((maxLife * owner.summonHpPercent) / 100 + (owner.summonHp << 6)); // hp increase from affixes
	maxLife += PerkValue(PERK_TOUGH_MINIONS, CurrentPlayerIndex) << 6; // +hp from perks
	maxLife = maxLife * (100 - best_defense_trait_penalty) / 100; //added here because it changes TOTAL hit points. including affix and perk buffs

	minAccuracyFirst += owner.summonToHit;
	minAccuracyFirst += minAccuracyFirst * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	minAccuracyFirst += PerkValue(PERK_ACCURATE_MINIONS, CurrentPlayerIndex); // +accuracy from perks
	maxAccuracyFirst += owner.summonToHit;
	maxAccuracyFirst += maxAccuracyFirst * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	maxAccuracyFirst += PerkValue(PERK_ACCURATE_MINIONS, CurrentPlayerIndex); // +accuracy from perks

	int best_defense_benefit = HasTrait(CurrentPlayerIndex, TraitId::BestDefense) ? (25 + owner.CharLevel / 15) : 0;
	minMinDamageFirst += minMinDamageFirst * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	minMinDamageFirst += minMinDamageFirst * (owner.summonDamagePercent + best_defense_benefit) / 100 + owner.summonDamageMin;
	minMinDamageFirst += PerkValue(PERK_STRONG_MINIONS, CurrentPlayerIndex) + PerkValue(SYNERGY_MINION_OFFENSE, CurrentPlayerIndex); // +damage from perks
	
	maxMaxDamageFirst += maxMaxDamageFirst * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	maxMaxDamageFirst += maxMaxDamageFirst * (owner.summonDamagePercent + best_defense_benefit) / 100 + owner.summonDamageMax;
	maxMaxDamageFirst += PerkValue(PERK_STRONG_MINIONS, CurrentPlayerIndex) + PerkValue(SYNERGY_MINION_OFFENSE, CurrentPlayerIndex); // +damage from perks
	
	if (minionTypeSpell == PS_54_GREATER_SUMMON) {
		switch (owner.fullClassId) {
		case PFC_DEMONOLOGIST: minMinDamageFirst *= 2; maxMaxDamageFirst *= 2; break;
		case PFC_NECROMANCER: minMinDamageFirst *= 2; maxMaxDamageFirst *= 2; break;
		case PFC_BEASTMASTER: minMinDamageFirst = minMinDamageFirst * 5 / 2; maxMaxDamageFirst = maxMaxDamageFirst * 5 / 2;
		}
	}

	minArmor += minArmor * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100; 
	minArmor += (minArmor * owner.summonAcPercent) / 100 + owner.summonAc;
	minArmor += PerkValue(PERK_ARMORED_MINIONS, CurrentPlayerIndex); // +armor from perks
	maxArmor += maxArmor * PerkValue(PERK_GOLEM_MASTERY, CurrentPlayerIndex, 1) / 100;
	maxArmor += (maxArmor * owner.summonAcPercent) / 100 + owner.summonAc;
	maxArmor += PerkValue(PERK_ARMORED_MINIONS, CurrentPlayerIndex); // +armor from perks


	if (minAccuracyFirst == maxAccuracyFirst)
		sprintf(InfoPanelBuffer, "Precisao: %i", minAccuracyFirst);
	else 
		sprintf(InfoPanelBuffer, "Precisao: %i - %i", minAccuracyFirst, maxAccuracyFirst);
	drawLine(InfoPanelBuffer);
	sprintf(InfoPanelBuffer, "Dano: %i - %i", minMinDamageFirst, maxMaxDamageFirst);
	drawLine(InfoPanelBuffer);
	sprintf(InfoPanelBuffer, "Classe de armadura: %i - %i", minArmor, maxArmor);
	drawLine(InfoPanelBuffer);
	sprintf(InfoPanelBuffer, "Pontos de vida: %i - %i", minLife>>6, maxLife>>6);
	drawLine(InfoPanelBuffer);

}

//----- (00406C24) -------------------------------------------------------- interface
void DrawSpellBook()
{
    static constexpr int LINE_HEIGHT = 22;

	const int offsetX = SpellBookRect.Left;
	const int offsetY = SpellBookRect.Top;
 
	const int spellBookTextOffset = 66 + Screen_LeftBorder;
	
	// Собственно рисуем картинку
	Surface_DrawCEL(SpellBookRect.Left + Screen_LeftBorder, SpellBookRect.Down + Screen_TopBorder, Data_SpellBkCEL, 1, SpellBookRect.Width);
	// Прорисовка 5 кнопок перехода между страницами
	if( CurrentSpellBookPage < GUI_SpellBook_PagesAmount ){
		Surface_DrawCEL(SpellBookPageButtonsRect.Left + Screen_LeftBorder + GUI_SpellBook_PageButtonWidth * CurrentSpellBookPage, SpellBookPageButtonsRect.Down + Screen_TopBorder, Data_SpellBkBCEL, CurrentSpellBookPage + 1, GUI_SpellBook_PageButtonWidth);// Отрисовка нажатого состояния кнопки номера текущей страницы заклинания
	}
    
    int lineIndex = 0;
    
    auto drawLine = [&]( const char* text, int baseFontColor = C_0_White )
        {
            DrawTextColored( SpellBookTextRect.Left, SpellBookTextRect.Top + 11 + 8 + lineIndex*LINE_HEIGHT, SpellBookTextRect.Right, text, baseFontColor );
            ++lineIndex;
        };
    
	Player& player = Players[CurrentPlayerIndex];
	int surfaceY = 215 + offsetY; // TODO: change 215 to Screen_TopBorder + 55
	const __int64 spellMask = player.AvailableSpellMask | player.AvailableSkillMask | player.AvailableChargesMask;
	
	for( int spellOnPage = 0; spellOnPage < GUI_SpellBook_SpellsPerPageAmount; spellOnPage++, surfaceY += 43){
		const int spellIndex = LearnedSpells(CurrentSpellBookPage, spellOnPage);
		if( spellIndex == -1 || !(spellMask & (1i64 << (spellIndex - 1)) ) ){
			continue;
		}
		// Изображение заклинания
		int spellType = GetColorNumberWithSpellBook(spellIndex, 1);
		DrawSpellColor(spellType);
		DrawSpellIcon(11 + Screen_LeftBorder + offsetX, surfaceY, Data_SpellI2CEL, getSpellIcon( spellIndex ), 37, spellType);
		// Вот то что нам нужно. Отрисовка выделения
		if( spellIndex == player.CurrentSpellIndex && spellType == player.SpellType ){
			DrawSpellColor(0);
			DrawSpellIcon(11 + Screen_LeftBorder + offsetX, surfaceY, Data_SpellI2CEL, 52, 37, 0);
		}
	}
	
	if( player.CurrentSpellIndex == PS_M1_NONE ){
	    drawLine( "Nenhuma magia selecionada" );
	}
	else {
		const auto spellIndex = player.CurrentSpellIndex;
		const auto spellType = player.SpellType;

		// 1. Spell name
		drawLine(getSpellName(spellIndex), C_3_Gold);

		// 2. Spell origin
		if (spellType == SO_0_SKILL) {
			drawLine("Habilidade");
		}
		else if (spellType == SO_1_SPELL) {
			int spellLevel = PlayerSpellLevel(CurrentPlayerIndex, spellIndex);
			if( spellLevel == 0 ){
				drawLine("Nivel de magia 0 - Indisponivel", C_2_Red);
			}else{
				sprintf(InfoPanelBuffer, "Nivel de magia %i", spellLevel);
				drawLine(InfoPanelBuffer);
			}
		}
		else if (spellType == SO_2_RELIC) {
			const int numberOfRelicWithCurrentSpell = GetNumberOfRelicWithCurrentSpell(spellIndex);
			if (numberOfRelicWithCurrentSpell == 1) {
				drawLine("1 Reliquia");
			}
			else {
				sprintf(InfoPanelBuffer, "%i Reliquias", numberOfRelicWithCurrentSpell);
				drawLine(InfoPanelBuffer);
			}
		}
		else if (spellType == SO_3_EQUIPED_ITEM) {
			int sumCharges = SumBodySlotSpellCharges( CurrentPlayerIndex, spellIndex );
			if( sumCharges > 0 ){
				sprintf(InfoPanelBuffer, "%s cargas: %i", getSpellName(spellIndex), sumCharges);
				drawLine(InfoPanelBuffer);
			}
			else {
				drawLine("Item equipado");
			}
		}

		// 3. description
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);
		if (spellIndex == PS_22_FURY && player.fullClassId == PFC_KENSEI && MaxCountOfPlayersInGame == 1) {
			sprintf(InfoPanelBuffer, "Slows time and"); drawLine(InfoPanelBuffer);
		}
		if (spellIndex == PS_22_FURY) { // page 1
			sprintf(InfoPanelBuffer, "improves battle prowess"); drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "for a short time"); drawLine(InfoPanelBuffer);
			//sprintf(InfoPanelBuffer, " "); drawLine(InfoPanelBuffer);
			//sprintf(InfoPanelBuffer, "spell power grows"); drawLine(InfoPanelBuffer);
			//sprintf(InfoPanelBuffer, "with character level"); drawLine(InfoPanelBuffer);
			//sprintf(InfoPanelBuffer, " "); drawLine(InfoPanelBuffer); 
			sprintf(InfoPanelBuffer, " "); drawLine(InfoPanelBuffer);
			int CLVL = player.CharLevel;
			switch (player.fullClassId){
					// WARRIORS
			case PFC_WARRIOR:
				if(HasTrait(CurrentPlayerIndex, TraitId::Ranger)){
					sprintf(InfoPanelBuffer, "triple shot"); drawLine(InfoPanelBuffer);
				}
				else if (HasTrait(CurrentPlayerIndex, TraitId::Fechtmeister)) {
					// show nothing
				}
				else {
					sprintf(InfoPanelBuffer, "chance de bloqueio: +%i", (CLVL / 10) + 5); drawLine(InfoPanelBuffer);
				}
				sprintf(InfoPanelBuffer, "precisao: +%i", (CLVL / 3) + 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", (CLVL / 4) + 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", 7 * CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_INQUISITOR:
				sprintf(InfoPanelBuffer, "precisao: +%i", (CLVL / 2) - 3); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", (CLVL / 3) - 1); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", (2 * CLVL) - 1); drawLine(InfoPanelBuffer);
				break;
			case PFC_GUARDIAN:
				sprintf(InfoPanelBuffer, "precisao: +%i", CLVL / 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", (4 * CLVL / 5) + 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 10); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resistencia a projeteis: +%i", CLVL / 5); drawLine(InfoPanelBuffer);
				break;
			case PFC_TEMPLAR:
				sprintf(InfoPanelBuffer, "precisao: +%i", (CLVL / 5) + 10); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", (CLVL / 9) + 15); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", (2 * CLVL) + 1); drawLine(InfoPanelBuffer);
				break;
					//ARCHERS
			case PFC_ARCHER:
				sprintf(InfoPanelBuffer, "dano: +%i", CLVL + 5); drawLine(InfoPanelBuffer);
				break;
			case PFC_SCOUT:
				sprintf(InfoPanelBuffer, "dano: +%i", (3 * CLVL / 2) + 3); drawLine(InfoPanelBuffer);
				break;
			case PFC_SHARPSHOOTER:
				sprintf(InfoPanelBuffer, "precisao: +%i", (CLVL / 3) + 7); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", (2 * CLVL) - 2); drawLine(InfoPanelBuffer);
				break;
			case PFC_TRAPPER:
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", 2 * CLVL / 3); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", 2 * CLVL / 9); drawLine(InfoPanelBuffer);
				break;
					// SUMMONERS
			case PFC_DEMONOLOGIST:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "armadura das invocacoes: +%i", CLVL / 5); drawLine(InfoPanelBuffer);
				break;
			case PFC_NECROMANCER:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "summon hp %%: +%i", (CLVL / 10) + 5); drawLine(InfoPanelBuffer);
				break;
			case PFC_BEASTMASTER:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano das invocacoes: +%i", CLVL / 5); drawLine(InfoPanelBuffer);
				break;
					// CASTERS
			case PFC_MAGE:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", (CLVL / 15) + 2); drawLine(InfoPanelBuffer);
				break;
			case PFC_ELEMENTALIST:
				if (HasTrait(CurrentPlayerIndex, TraitId::Mamluk)) {
					sprintf(InfoPanelBuffer, "precisao: +%i", (CLVL / 5) + 10); drawLine(InfoPanelBuffer);
					sprintf(InfoPanelBuffer, "classe de armadura: +%i", (CLVL / 9) + 15); drawLine(InfoPanelBuffer);
					sprintf(InfoPanelBuffer, "dano: +%i", (2 * CLVL) + 1); drawLine(InfoPanelBuffer);
				}				
				else {
					sprintf(InfoPanelBuffer, "niveis de magia: +%i", (CLVL / 10) + 2); drawLine(InfoPanelBuffer);
				}
				break;
			case PFC_WARLOCK:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "regeneracao de mana: +%i", (CLVL / 2) + 1); drawLine(InfoPanelBuffer);
				break;
					// MONKS
			case PFC_MONK:
				sprintf(InfoPanelBuffer, "DANO: +%i", 2 * CLVL); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_KENSEI:
			{ if (MaxCountOfPlayersInGame != 1)
				sprintf(InfoPanelBuffer, "DANO: +%i", 3 * CLVL / 2); drawLine(InfoPanelBuffer);
			}
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_SHUGOKI:
				sprintf(InfoPanelBuffer, "DANO: +%i", 2 * CLVL); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_SHINOBI:
				sprintf(InfoPanelBuffer, "DANO: +%i", 5 * CLVL / 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
					// ROGUES
			case PFC_ROGUE:
				sprintf(InfoPanelBuffer, "DANO: +%i", 3 * CLVL / 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", 3 * CLVL / 8); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_ASSASSIN:
				sprintf(InfoPanelBuffer, "chance de critico: +%i", (CLVL / 10) + 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano critico: +%i", CLVL * 7); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", (CLVL / 5) + 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_IRON_MAIDEN:
				sprintf(InfoPanelBuffer, "chance de critico: +%i", (CLVL / 25) + 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resistencia a dano corpo a corpo: +%i", CLVL / 5 + 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 11 + 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_BOMBARDIER:
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", CLVL / 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "resist all: +%i", CLVL / 3); drawLine(InfoPanelBuffer);
				break;
					// SAVAGES
			case PFC_SAVAGE:
				sprintf(InfoPanelBuffer, "dano: +%i", 5 * CLVL / 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", CLVL / 3); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "precisao: +%i", CLVL / 3); drawLine(InfoPanelBuffer);
				break;
			case PFC_BERSERKER:
				sprintf(InfoPanelBuffer, "accuracy: +%i", 10 + 3 * CLVL / 5 + PerkValue(PERK_BASHING_HITS, CurrentPlayerIndex)); drawLine(InfoPanelBuffer); 
				sprintf(InfoPanelBuffer, "dano: +%i", CLVL * player.BaseStrength / 357 + CLVL / 2 + PerkValue(PERK_BLOODTHIRST, CurrentPlayerIndex)); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", 1 + CLVL / 3 + PerkValue(PERK_LIKE_A_ROCK, CurrentPlayerIndex)); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dfe: -%i", 1 + CLVL / 5 + PerkValue(PERK_FEEL_NO_PAIN, CurrentPlayerIndex)); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "stun threshold: +%i", 1 + CLVL / 5 + PerkValue(PERK_UNBREAKABLE, CurrentPlayerIndex)); drawLine(InfoPanelBuffer);
				//sprintf(InfoPanelBuffer, "resistencia a dano corpo a corpo: +%i", 10 + (CLVL / 5)); drawLine(InfoPanelBuffer);
				//sprintf(InfoPanelBuffer, "+(%s)", "perk improvements"); drawLine(InfoPanelBuffer);
				break;
			case PFC_EXECUTIONER:
				sprintf(InfoPanelBuffer, "dano: +%i", 10 + (5 * CLVL / 2)); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", (3 * CLVL / 7) + 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "precisao: +%i", CLVL / 3); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "regeneracao de vida: +%i", CLVL + 10); drawLine(InfoPanelBuffer);
				break;
					// GLADIATORS
			case PFC_THRAEX:
				sprintf(InfoPanelBuffer, "dano: +%i", 2 * CLVL); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", 2 * CLVL / 9); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "precisao: +%i", 5 * CLVL / 4); drawLine(InfoPanelBuffer);
				break;
			case PFC_DIMACHAERUS:
				sprintf(InfoPanelBuffer, "velocidade de ataque: -%i %s", 1, "quadro"); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "precisao: +%i", CLVL / 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", CLVL / 2); drawLine(InfoPanelBuffer);
				break;
			case PFC_MURMILLO:
				sprintf(InfoPanelBuffer, "dano: +%i", 7 * CLVL / 4); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", 2 * CLVL / 5); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", 3 * CLVL / 4); drawLine(InfoPanelBuffer);
				break;			
			case PFC_SECUTOR:
				sprintf(InfoPanelBuffer, "niveis de magia: +%i", 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano: +%i", CLVL * 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", (3 * CLVL / 10) - 2); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", CLVL / 10); drawLine(InfoPanelBuffer);
				break;
			case PFC_DRUID:
				sprintf(InfoPanelBuffer, "dano: +%i", 5 + CLVL * 3); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "dano dos inimigos: -%i", 3 * CLVL / 21 + 1); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "precisao: +%i", CLVL / 2 + 10); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "classe de armadura: +%i", 5 + CLVL / 10); drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "stun threshold: +%i", 3 + CLVL / 15); drawLine(InfoPanelBuffer);
				break;
			}
			// Fury duration:
			int additionalFuryDuration = player.effectFlag[EA_FURY_DURATION] ? (player.CharLevel / 6 + 10) : 0;
			int durf = 30 + (CLVL / 5) + /*10 * missile.SpellLevel*/ + additionalFuryDuration + PerkValue(PERK_RAMPAGE, CurrentPlayerIndex);
			sprintf(InfoPanelBuffer, " "); drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "duracao: %i segundos", durf); drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_7_TOWN_PORTAL) {
			sprintf(InfoPanelBuffer, "cria um portal magico");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que teleporta o conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para a cidade e de volta");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_33_TELEKINES) {
			sprintf(InfoPanelBuffer, "o conjurador usa poderes cineticos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para manipular objetos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "from a distance");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_16_REFLECT) {
			sprintf(InfoPanelBuffer, "gives invulnerability");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "contra ataques corpo a corpo de monstros");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_23_TELEPORT) {
			sprintf(InfoPanelBuffer, "move o conjurador instantaneamente");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para o local selecionado");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_11_MANA_SHIELD) {
			sprintf(InfoPanelBuffer, "o dano e descontado");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "da mana em vez da vida");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_2_HEALING) {
			drawLine ("restaura parte da vida");
			drawLine("");			
		}
		else if (spellIndex == PS_34_HEAL_OTHER) {
			sprintf(InfoPanelBuffer, "o conjurador recupera vida");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "for selected player");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_1_FIREBOLT) { // page 2
			sprintf(InfoPanelBuffer, "casts a fiery missile");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_20_INCINERATE) {
			sprintf(InfoPanelBuffer, "lanca um jato de chamas");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que incinera os inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_12_FIREBLAST) {
			sprintf(InfoPanelBuffer, "lanca uma poderosa bola de fogo");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que explode ao atingir");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "e causa dano aos inimigos proximos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_6_FIRE_WALL) {
			sprintf(InfoPanelBuffer, "cria uma parede de chamas");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que impede os inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "sem imunidade a fogo");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "from crossing it");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_19_FLAME_RING) {
			sprintf(InfoPanelBuffer, "cria um circulo em chamas");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que impede os inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "sem imunidade a fogo");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "from crossing it");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_41_FIERY_NOVA) {
			sprintf(InfoPanelBuffer, "cria um circulo em expansao");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de bolas de fogo ao redor do conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_13_HYDRA) {
			sprintf(InfoPanelBuffer, "summons a multi-headed");
			drawLine(InfoPanelBuffer);
			if (player.fullClassId == PFC_ELEMENTALIST) {
				sprintf(InfoPanelBuffer, "fera que cospe setas de gelo");
				drawLine(InfoPanelBuffer);
			}
			else if (HasTrait(CurrentPlayerIndex, TraitId::Hydramancer)) {
				sprintf(InfoPanelBuffer, "fera que arremessa fogo,");
				drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "electric, arcane");
				drawLine(InfoPanelBuffer);
				sprintf(InfoPanelBuffer, "or acid bolts");
				drawLine(InfoPanelBuffer);
			}
			else {
			sprintf(InfoPanelBuffer, "fera que arremessa fogo");
			drawLine(InfoPanelBuffer);
			}
			sprintf(InfoPanelBuffer, "em inimigos nao imunes");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "Quantidade maxima: %i", MaxCountOfHydrasForPlayer(CurrentPlayerIndex));
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_40_LIGHTING_WALL) { // page 3
			sprintf(InfoPanelBuffer, "cria uma parede eletrica");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que impede os inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "sem imunidade a raios");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "from crossing it");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_17_LIGHTING_RING) {
			sprintf(InfoPanelBuffer, "cria um circulo eletrico");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que impede os inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "sem imunidade a raios");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "from crossing it");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_30_CHARGED_BOLT) {
			sprintf(InfoPanelBuffer, "cria varios raios");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de energia eletrica");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_3_LIGHTNING) {
			sprintf(InfoPanelBuffer, "dispara uma corrente de raios");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que atinge os alvos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_14_BALL_LIGHTNING) {
			sprintf(InfoPanelBuffer, "lanca uma grande esfera");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de energia eletrica");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_18_LIGHTNING_NOVA) {
			sprintf(InfoPanelBuffer, "lanca um anel expansivo");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de descargas eletricas");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_35_ARCANE_STAR) {
			sprintf(InfoPanelBuffer, "cria uma estrela magica");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que causa dano arcano");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_4_FLASH) {
			sprintf(InfoPanelBuffer, "cria um anel magico");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de energia ao redor do conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para ferir alvos proximos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_43_ARCANE_NOVA) {
			sprintf(InfoPanelBuffer, "cria um anel em expansao");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de estrelas ao redor do conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_31_HOLY_BOLT) { // page 4
			sprintf(InfoPanelBuffer, "um raio de energia sagrada");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que causa dano a mortos-vivos");
			drawLine(InfoPanelBuffer);
			if (GameMode != GM_CLASSIC) {
				sprintf(InfoPanelBuffer, "and knocks them back");
				drawLine(InfoPanelBuffer);
			}
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_39_HOLY_NOVA) {
			sprintf(InfoPanelBuffer, "cria um grande anel");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de raios sagrados expansivos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir mortos-vivos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_8_STONE_CURSE) {
			sprintf(InfoPanelBuffer, "transforma inimigos nao imunes");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "em pedra");
			drawLine(InfoPanelBuffer);
			if (GameMode != GM_CLASSIC) {
				sprintf(InfoPanelBuffer, "making them invulnerable");
				drawLine(InfoPanelBuffer);			
			}
			sprintf(InfoPanelBuffer, "for some time");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_36_BONE_SPIRIT) {
			sprintf(InfoPanelBuffer, "liberta uma alma inquieta");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "que devora os vivos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "causando dano proporcional a vida");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_15_FORCE_WAVE) {
			sprintf(InfoPanelBuffer, "sends a moving wall");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de energia de forca");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para repelir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "(causa dano fisico)");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_21_GOLEM) {
			WriteSummonSpellBookInfo(PS_21_GOLEM, LINE_HEIGHT, lineIndex);
		}
		else if (spellIndex == PS_29_ELEMENTAL) {
			sprintf(InfoPanelBuffer, "releases a chaos being");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "that seeks and destroys");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "live creatures");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "(causa dano fisico)");
			drawLine(InfoPanelBuffer);
			if (GameMode != GM_CLASSIC) {
				sprintf(InfoPanelBuffer, "(knocks target back)");
				drawLine(InfoPanelBuffer);
			}
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_56_ICE_BOLT) { // page 5
			sprintf(InfoPanelBuffer, "lanca um fragmento de gelo");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_57_FREEZING_BALL) {
			sprintf(InfoPanelBuffer, "launches a powerful");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "esfera de gelo que causa dano");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_58_FROST_NOVA) {
			sprintf(InfoPanelBuffer, "cria um anel em expansao");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de gelo ao redor do conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_59_RANCID_BOLT) {
			sprintf(InfoPanelBuffer, "casts an acid bolt");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para queimar inimigos lentamente");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_60_TOXIC_BALL) {
			sprintf(InfoPanelBuffer, "launches a powerful");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "esfera de acido que causa dano");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_61_ACID_NOVA) {
			sprintf(InfoPanelBuffer, "cria um anel em expansao");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "de acido ao redor do conjurador");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, "para destruir inimigos");
			drawLine(InfoPanelBuffer);
			sprintf(InfoPanelBuffer, " ");
			drawLine(InfoPanelBuffer);
		}
		else if (spellIndex == PS_52_LESSER_SUMMON) {
			WriteSummonSpellBookInfo(PS_52_LESSER_SUMMON, LINE_HEIGHT, lineIndex);
		}
		else if (spellIndex == PS_53_COMMON_SUMMON) {
			WriteSummonSpellBookInfo(PS_53_COMMON_SUMMON, LINE_HEIGHT, lineIndex);
		}
		else if (spellIndex == PS_54_GREATER_SUMMON) {
			WriteSummonSpellBookInfo(PS_54_GREATER_SUMMON, LINE_HEIGHT, lineIndex);
		}
		else if (spellIndex == PS_10_PHASING) {
			drawLine("teleporta rapidamente o conjurador");
			drawLine("para um local aleatorio proximo");
		}
		else if(spellIndex == PS_42_WARP) {
			drawLine("teleporta o conjurador");
			drawLine("para a escada mais proxima");
		}
		else if (spellIndex == PS_24_APOCALYPSE) {
			drawLine("envolve os inimigos visiveis");
			drawLine("in infernal flames");
			drawLine("obliterating everything");
			drawLine("(causa dano fisico)");
		}
		else if (spellIndex == PS_25_ETHEREAL) {
			drawLine("torna o conjurador invulneravel");
			drawLine("a todo dano magico");
			drawLine("for 20 seconds");
		}
		else if (spellIndex == PS_26_ITEM_REPAIR) {
			drawLine("fully repairs item");
			drawLine("but reduces maximum");
			drawLine("durability by 1 point");
		}
		else if (spellIndex == PS_27_STAFF_RECHARGE) {
			drawLine("restaura cargas de magia");
			drawLine("reduzindo a durabilidade");			
			drawLine("atual do item");
		}
		else if (spellIndex == PS_28_TRAP_DISARM) {
			drawLine("disarms trapped objects");			
		}
		else if (spellIndex == PS_37_MANA_RECHARGE) { 
			drawLine("restaura parte da mana");	
			drawLine("");
		}
		else if (spellIndex == PS_38_MAGI) {
			drawLine("restaura toda a mana");			
		}
		//else if (spellIndex == PS_42_WARP) { // somehow this didn't work !!
		//	drawLine("quickly teleport");
		//	drawLine("para a escada mais proxima");
		//}
		else if (spellIndex == PS_5_IDENTIFY) {
			drawLine("identify selected item");			
		}
		else if (spellIndex == PS_9_INFRAVISION) {
			drawLine("monstros fora da");
			drawLine("linha de visao do conjurador");
			drawLine("and light radius");
			drawLine("are highlighted red");
		}

        // 4. damage, healing or kind of
        int minDamage = 0;
        int maxDamage = 0;
        GetDamageOfPlayerSpell(CurrentPlayerIndex, spellIndex, PlayerSpellLevel(CurrentPlayerIndex, spellIndex), SpellElement(player, spellIndex), &minDamage, &maxDamage);
        
        if( spellIndex == PS_36_BONE_SPIRIT ){
            const int atrophyLevel = PerkValue(PERK_ATROPHY, CurrentPlayerIndex);
            int numerator;
            int denominator;
			if (atrophyLevel >= 3) {
				numerator = 1;
				denominator = 5;
			}else if( atrophyLevel == 2 ){
                numerator =     1;
                denominator =   6;
            }else if( atrophyLevel == 1 ){
                numerator =     1;
                denominator =   7;
            }else{
                numerator =     1;
                denominator =   8;
            }
			denominator += Difficulty;
            sprintf( InfoPanelBuffer, "Dano: %i/%i da vida do alvo", numerator, denominator );
            drawLine( InfoPanelBuffer );
        }else if( spellIndex == PS_2_HEALING || spellIndex == PS_34_HEAL_OTHER ){   //
            const POINT p = InfoPanelManaHeal( spellIndex );
            sprintf( InfoPanelBuffer, "Healing: %i-%i", p.x, p.y ); // TODO: write new function. And use it here and in healing code
            drawLine( InfoPanelBuffer );
		}else if (spellIndex == PS_37_MANA_RECHARGE) {   //  Реликт маны
			const POINT p = InfoPanelManaHeal(spellIndex);
			sprintf(InfoPanelBuffer, "mana restaurada: %i-%i",p.x, p.y );
			drawLine(InfoPanelBuffer);
        }else if( spellIndex == PS_11_MANA_SHIELD ){
            sprintf( InfoPanelBuffer, "Dano recebido: %i%%", minDamage );
            drawLine( InfoPanelBuffer );
        }else if (spellIndex == PS_16_REFLECT) {
			int reflect_layers = player.BaseVitality / 50 + 1; // that's basic level of Reflect layers
			if (HasTrait(CurrentPlayerIndex, TraitId::Armadillo)) {
				reflect_layers += player.CharLevel / 13 + 2;
			}
			reflect_layers += PerkValue(SYNERGY_IRON_BULWARK, CurrentPlayerIndex);
			if( reflect_layers == 1 ){
                drawLine( "Absorve 1 golpe" );
            }else{
                sprintf( InfoPanelBuffer, "Absorbs %i hits", reflect_layers);
                drawLine( InfoPanelBuffer );
            }
		}else if (spellIndex == PS_6_FIRE_WALL || spellIndex == PS_19_FLAME_RING) {
			sprintf(InfoPanelBuffer, "Dano por segundo: %i", minDamage);
			drawLine(InfoPanelBuffer, 4);
		}else if (spellIndex == PS_17_LIGHTING_RING || spellIndex == PS_40_LIGHTING_WALL) {
			sprintf(InfoPanelBuffer, "Dano por segundo: %i", minDamage);
			drawLine(InfoPanelBuffer, 1);
		}else if (spellIndex == PS_4_FLASH) {
			sprintf(InfoPanelBuffer, "Dano por segundo: %i", minDamage);
			drawLine(InfoPanelBuffer, 8);
		}else if (spellIndex == PS_20_INCINERATE) {
			sprintf(InfoPanelBuffer, "Dano por segundo: %i", minDamage);
			drawLine(InfoPanelBuffer, 4);
		}else if( minDamage != -1 && !( minDamage == 0 && maxDamage == 0 ) && !is(spellIndex, PS_21_GOLEM, PS_52_LESSER_SUMMON, PS_53_COMMON_SUMMON, PS_54_GREATER_SUMMON)){
            sprintf( InfoPanelBuffer, "Dano: %i-%i", minDamage, maxDamage );
			int le_color;
			//ELEMENTAL_TYPE damageType;
			switch (spellIndex) {
			case PS_13_HYDRA: player.fullClassId == PFC_ELEMENTALIST ? le_color = 7 /*grey*/ : le_color = 4/*orng*/; break; 
			case PS_12_FIREBLAST:
			//case PS_19_FLAME_RING:
			case PS_1_FIREBOLT:
			//case PS_20_INCINERATE:
			case PS_41_FIERY_NOVA:
			//case PS_6_FIRE_WALL:
			//case PS_45_RING_OF_FIRE:	
										le_color = 4; break; // orange
			//case PS_17_LIGHTING_RING:
			case PS_14_BALL_LIGHTNING:
			case PS_18_LIGHTNING_NOVA:
			case PS_30_CHARGED_BOLT:
			case PS_3_LIGHTNING:
			//case PS_40_LIGHTING_WALL:	
										le_color = 1; break; // blue
			case PS_31_HOLY_BOLT:
			case PS_39_HOLY_NOVA:		le_color = 6; break; // goldish
			case PS_43_ARCANE_NOVA:
			case PS_35_ARCANE_STAR:
			//case PS_4_FLASH:			
										le_color = 8; break; // brownish
			case PS_56_ICE_BOLT:
			case PS_57_FREEZING_BALL:
			case PS_58_FROST_NOVA:		le_color = 7; break; // grey
			case PS_59_RANCID_BOLT:
			case PS_60_TOXIC_BALL:
			case PS_61_ACID_NOVA:		le_color = 5; break; // yellow
			default:					le_color = 0; break; // white - physical
			}

			if( HasTrait(CurrentPlayerIndex, TraitId::Hydramancer) && spellIndex == PS_13_HYDRA ){
				if (PlayerSpellLevel(CurrentPlayerIndex, PS_1_FIREBOLT) > 0) {
					GetDamageOfPlayerSpell(CurrentPlayerIndex, spellIndex, PlayerSpellLevel(CurrentPlayerIndex, spellIndex), ET_1_FIRE, &minDamage, &maxDamage);
					sprintf(InfoPanelBuffer, "Dano de fogo: %i-%i", minDamage, maxDamage);
					drawLine(InfoPanelBuffer, C_4_Orange);
				}

				if (PlayerSpellLevel(CurrentPlayerIndex, PS_30_CHARGED_BOLT) > 0) {
					GetDamageOfPlayerSpell(CurrentPlayerIndex, spellIndex, PlayerSpellLevel(CurrentPlayerIndex, spellIndex), ET_2_LIGHTNING, &minDamage, &maxDamage);
					sprintf(InfoPanelBuffer, "Dano eletrico: %i-%i", minDamage, maxDamage);
					drawLine(InfoPanelBuffer, C_1_Blue);
				}

				if (PlayerSpellLevel(CurrentPlayerIndex, PS_35_ARCANE_STAR) > 0) {
					GetDamageOfPlayerSpell(CurrentPlayerIndex, spellIndex, PlayerSpellLevel(CurrentPlayerIndex, spellIndex), ET_3_ARCAN, &minDamage, &maxDamage);
					sprintf(InfoPanelBuffer, "Arcane Dano: %i-%i", minDamage, maxDamage);
					drawLine(InfoPanelBuffer, C_8_Pink);
				}

				if (PlayerSpellLevel(CurrentPlayerIndex, PS_59_RANCID_BOLT) > 0) {
					GetDamageOfPlayerSpell(CurrentPlayerIndex, spellIndex, PlayerSpellLevel(CurrentPlayerIndex, spellIndex), ET_4_ACID, &minDamage, &maxDamage);
					sprintf(InfoPanelBuffer, "Acid Dano: %i-%i", minDamage, maxDamage);
					drawLine(InfoPanelBuffer, C_5_Yellow);
				}
			}
			else {
				drawLine(InfoPanelBuffer, le_color);
			}
        }

		// empty line
		sprintf(InfoPanelBuffer, " ");
		drawLine(InfoPanelBuffer);

		// 5. Range
		if (spellIndex == PS_20_INCINERATE) {
			drawLine("range: 3 tiles");
			drawLine("");
		}
		else if (is(spellIndex, PS_23_TELEPORT, PS_33_TELEKINES)) {
			drawLine("range: 10 tiles");
			drawLine("");
		}

		

        // 7. Mana cost
        if( spellType == SO_1_SPELL ){
            int manaCost = CalculateManaRequiredToCastSpell(CurrentPlayerIndex, spellIndex) / 64;
            sprintf( InfoPanelBuffer, "Custo de mana: %i", manaCost ); // TODO: red or blue depending on bonuses and penalties
            drawLine( InfoPanelBuffer );
        }

		const auto [cdType, cooldown] = GetSpellCooldownValue(CurrentPlayerIndex, spellIndex);
		if (cooldown > 0) {
			if (cooldown == 1) {				
				sprintf(InfoPanelBuffer, "Recarga: 1 segundo");
			}
			else {				
				sprintf(InfoPanelBuffer, "Recarga: %i segundos", cooldown);
			}
			drawLine("");
			drawLine(InfoPanelBuffer);
		}
        
    }
}

//----- (00406F90) -------------------------------------------------------- interface
void BookPanel_CkeckLButtonClick()
{
	Player& player = Players[CurrentPlayerIndex];

    if( CursorIntoDisplayObject(SpellBookPageButtonsRect) ){
        CurrentSpellBookPage = (CursorX - SpellBookPageButtonsRect.Left) / GUI_SpellBook_PageButtonWidth;
        LimitToRange( CurrentSpellBookPage, 0, GUI_SpellBook_PagesAmount - 1 );
		PlayGlobalSound(S_75_I_TITLEMOV);
        return;
    }
    
    if( CursorIntoDisplayObject(SpellBookSpellButtonsRect) ){
        i64 spellMask;
        unsigned& maskHi = *((unsigned*)&spellMask + 1);
        unsigned& maskLo = *(unsigned*)&spellMask;
        int spellBookLine = (CursorY - SpellBookSpellButtonsRect.Top) / GUI_SpellBook_SpellButtonHeight;
        int spellNumber = LearnedSpells(CurrentSpellBookPage, spellBookLine);
		spellMask = player.AvailableSkillMask | player.AvailableChargesMask | player.AvailableSpellMask;
        if( spellNumber == -1 ){
            return;
        }
        __int64 spellSelector = 1i64 << (spellNumber - 1);
        if( !( spellSelector & spellMask )){
            return;
        }
        int spellType = SO_1_SPELL;
        if( player.AvailableChargesMask & spellSelector ){
            spellType = SO_3_EQUIPED_ITEM;
        }
        if( player.AvailableSkillMask & spellSelector ){
            spellType = SO_0_SKILL;
        }
        player.CurrentSpellIndex = spellNumber;
        player.SpellType = spellType;
		PlayGlobalSound(S_75_I_TITLEMOV);
    }
}

void ToggleSpellBook()
{
    // Conflicts with
    {
        CloseInventoryPanel();
        IsPerksPanelVisible = false;
        IsInfoWindowVisible = false;
    }

    IsSpellBookVisible = !IsSpellBookVisible;
	PlayGlobalSound(75);
}
