#include "stdafx.h"

Perk SymptomPerks[] = {

	{ SYMP_MALAISE, {"voce se sente doente::    vida: -%i%%"}, "Mal-Estar", {
		{  2, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  5 },
		{  4, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
		{  7, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
		{ 10, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 20 },
		{ 13, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 25 },
	} },

	{ SYMP_PALLOR, {"fluxo sanguineo reduzido::deixa sua aparencia palida::    mana: -%i%%"}, "Palidez", {
		{  2, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  5 },
		{  5, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
		{  8, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
		{ 11, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 20 },
		{ 14, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 25 },
	} },

	{ SYMP_FEVER_AND_CHILLS, {"febre e desidratacao severa::    armadura: -%i"}, "Febre e Calafrios", {
		{  3, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,   5 },
		{  6, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  10 },
		{  9, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  20 },
		{ 12, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  35 },
		{ 15, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  50 },
	} },

	{ SYMP_COUGHING, {"tosse intensa::    regeneracao de mana: -%i"}, "Tosse", {
		{  4, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  1 },
		{  7, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  2 },
		{ 10, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  3 },
		{ 13, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  4 },
		{ 16, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  5 },
		{ 20, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  7 },
		{ 24, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  9 },
		{ 27, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 11 },
		{ 30, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 13 },
		{ 33, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
	} },

	{ SYMP_BLOODY_SPUTUM, {"tosse com sangue::    regeneracao de vida: -%i"}, "Escarro com Sangue", {
		{  5, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  1 },
		{  8, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  2 },
		{ 11, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  3 },
		{ 14, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  4 },
		{ 17, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  5 },
		{ 20, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  7 },
		{ 22, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  9 },
		{ 24, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 11 },
		{ 26, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 13 },
		{ 28, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
		{ 30, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 17 },
		{ 31, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 19 },
		{ 32, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 21 },
		{ 33, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 23 },
		{ 34, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 25 },

	} },

	{ SYMP_FIBROSIS, {"pulmoes se enchem de sangue::e causam falta de ar::regeneracao de vida e mana::    reduzida em %i%%"}, "Fibrose", {
		{ 17, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
		{ 20, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
		{ 23, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 20 },
		{ 26, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 30 },
		{ 29, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 35 },
		{ 32, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 40 },
		{ 35, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 45 },
		{ 38, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 50 },
		{ 41, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 55 },
		{ 44, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 60 },
		{ 47, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 65 },
		{ 50, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 70 },
	} },

	{ SYMP_CYSTS, {"carocos dolorosos aparecem::em seu pescoco::    dano recebido: +%i"}, "Cistos", {
		{  3, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 1 },
		{  6, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 2 },
		{  9, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 3 },
		{ 12, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 4 },
		{ 15, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 5 },
	} },

	{ SYMP_DARK_PUSTULES, {"cistos escurecem::e se enchem de pus::    dano recebido: +%i"}, "Pustulas Escuras", {
		{ 16, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  2 },
		{ 19, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  4 },
		{ 22, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  6 },
		{ 25, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  8 },
		{ 28, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
	} },
	
	{ SYMP_BUBOES, {"ganglios incham::causando dor e sofrimento::    dano recebido: +%i"}, "Buboes", {
		{ 29, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  3 },
		{ 32, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  6 },
		{ 35, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  9 },
		{ 38, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 12 },
		{ 41, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
	} },

	{ SYMP_SEPSIS, {"infeccao alcanca os orgaos::e envenena o sangue::    regeneracao de vida: -%i"}, "Sepse", {
		{ 35, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  5 },
		{ 37, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
		{ 39, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 15 },
		{ 41, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 20 },
		{ 43, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 25 },
	} },

	{ SYMP_INTERNAL_BLEEDING, {"coagulacao reduzida::e hemorragia interna severa::    regeneracao de vida: -%i"}, "Hemorragia Interna", {
		{ 44, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 10 },
		{ 45, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 20 },
		{ 46, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 30 },
		{ 47, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 40 },
		{ 48, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 50 },
	} },

	{ SYMP_NECROSIS, {"tecido infectado perde sangue::e se torna foco de gangrena::    regeneracao de vida: -%i"}, "Necrose", {
		{  50, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  10 },
		{  60, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  20 },
		{  70, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  30 },
		{  80, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  40 },
		{  90, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  50 },
		{ 100, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  60 },
		{ 110, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  70 },
		{ 120, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  80 },
		{ 130, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/,  90 },
		{ 140, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 100 },
		{ 150, IPCM_ALL_CLASSES, {}/*perk*/, {}/*spell*/, 0,0,0,0/*sdmv*/, 110 },
	} },

};
