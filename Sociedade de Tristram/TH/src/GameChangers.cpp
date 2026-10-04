#include "stdafx.h"

GAME_CHANGER SelectedGameChanger = GC_0_CONTINUE;

int GameChangerTitleList[2] = { ID_CAPTION, 0 };
int GameChangerOkCancelList[3] = { ID_OK_BUTTON, ID_CANCEL_BUTTON, 0 };

int GameChangerButtonList[] = {
    ID_GAME_CHANGER_1,
    ID_GAME_CHANGER_2,
    ID_GAME_CHANGER_3,
    ID_GAME_CHANGER_4,
    ID_GAME_CHANGER_5,
    ID_GAME_CHANGER_6,
    0 };

constexpr std::array nextGameChangerOrder = {
    ID_GAME_CHANGER_2,
    ID_GAME_CHANGER_3,
    ID_GAME_CHANGER_4,
    ID_GAME_CHANGER_5,
    ID_GAME_CHANGER_6,
    ID_GAME_CHANGER_1,
};
constexpr std::array prevGameChangerOrder = {
    ID_GAME_CHANGER_6,
    ID_GAME_CHANGER_1,
    ID_GAME_CHANGER_2,
    ID_GAME_CHANGER_3,
    ID_GAME_CHANGER_4,
    ID_GAME_CHANGER_5, 
};

const char* GC_Names_InfoWindow[GC_COUNT] = {
    /*GC_0_CONTINUE*/
    "Nenhum",
    /*GC_1_AUTO_SAVE*/
    "Save Automatico",
    /*GC_2_BT_STRIP*/
    "Equipamento Preso",
    /*GC_3_DROP_ITMS*/
    "Derrubar Itens",
    /*GC_4_EFFORTLESS*/
    "Sem Esforco",
    /*GC_5*/
    "Vida da Terra",
    /*GC_6*/
    "Impossivel",
    /*GC_7*/
    "Proibicao",
    /*GC_8*/
    "Contato Total",
    /*GC_9*/
    "Filho da Noite",
    /*GC_10*/
    "Hack & Slash",
    /*GC_11*/
    "Vacinado",
    /*GC_12*/
    "Meu Segredo",
    /*GC_13*/
    "Sem Regeneracao",
    /*GC_14*/
    "Maos Limpas",
    /*GC_15*/
    "Era do Gelo",
    /*GC_16*/
    "Dia da Marmota",
    /*GC_17*/
    "Monstros Fortes",
    /*GC_18*/
    "Itens Indestrutiveis",
    /*GC_19*/
    "Sem Mapa",
    /*GC_20*/
    "Dano Duplo",
    /*GC_21*/
    "Nao Veja o Mal",
    /*GC_22*/
    "Peste Negra",
    /*GC_23*/
    "Ma Sorte",
    /*GC_24*/
    "Ferro Implacavel",
    /*GC_25*/
    "Aceleracao",
    /*GC_26*/
    "Ascetismo"
};

const char* GC_Descriptions_InfoWindow[GC_COUNT] = {
    "Nenhum modificador. Continue com as regras normais.",
    "SAVE AUTOMATICO\n\nO jogo salva sozinho, como no modo multijogador.",
    "EQUIPAMENTO PRESO\n\nDurante batalhas, voce so pode trocar os itens das maos.",
    "DERRUBAR ITENS\n\nAo morrer, os equipamentos caem. Recupere-os na mesma sessao.",
    "SEM ESFORCO\n\nOs monstros causam metade do dano normal.",
    "VIDA DA TERRA\n\nMoradores nao vendem itens, mas mantem seus outros servicos.",
    "IMPOSSIVEL\n\nOs monstros causam o dobro de dano.",
    "PROIBICAO\n\nMonstros nao derrubam elixires de atributos aleatoriamente.",
    "CONTATO TOTAL\n\nMonstros de ataque a distancia nao recuam.",
    "FILHO DA NOITE\n\nVoce vive de sangue, nao usa itens e depende de poderes inatos.",
    "HACK & SLASH\n\nTodas as armas causam dano neutro contra qualquer monstro.",
    "VACINADO\n\nMonstros perdem imunidades. Algumas magias especiais nao mudam.",
    "MEU SEGREDO\n\nFuria nao possui recarga e pode ser usada ao terminar.",
    "SEM REGENERACAO\n\nO personagem nao regenera vida nem mana naturalmente.",
    "MAOS LIMPAS\n\nMonstros nao derrubam equipamentos utilizaveis pelo personagem.",
    "ERA DO GELO\n\nAs masmorras recebem uma aparencia congelada.",
    "DIA DA MARMOTA\n\nA mesma masmorra e os mesmos monstros surgem a cada partida.",
    "MONSTROS FORTES\n\nOs monstros recebem +200% de pontos de vida.",
    "ITENS INDESTRUTIVEIS\n\nDurabilidade zero inutiliza o item ate o reparo, sem destrui-lo.",
    "SEM MAPA\n\nO automapa fica indisponivel durante a exploracao.",
    "DANO DUPLO\n\nSeus ataques causam o dobro de dano aos monstros.",
    "NAO VEJA O MAL\n\nA habilidade de visao nao destaca monstros na escuridao.",
    "PESTE NEGRA\n\nUma doenca incuravel piora com o tempo e pode levar a morte.",
    "MA SORTE\n\nAtributos 5, +2 por nivel e -75% de MF, GF e experiencia.",
    "FERRO IMPLACAVEL\n\nRegras Ironman classicas, sem bonus de progressao ou saques extras.",
    "ACELERACAO\n\nA experiencia recebida e multiplicada por cinco.",
    "ASCETISMO\n\nSave automatico, sem renascer na cidade e perda dos itens ao morrer."

};

std::vector<GAME_CHANGER> GameChangersAvailableList;

Portrait getGameChangerPortrait(GAME_CHANGER gameChanger)
{
    Portrait portrait;
    switch (gameChanger)
    {
    case GC_0_CONTINUE:     portrait = PcxGcs[50]; break;
    case GC_1_AUTO_SAVE:    portrait = PcxGcs[ 0]; break;
    case GC_2_BT_STRIP:     portrait = PcxGcs[ 1]; break;
    case GC_3_DROP_ITMS:    portrait = PcxGcs[ 2]; break;
    case GC_4_EFFORTLESS:   portrait = PcxGcs[14]; break;
    case GC_5_LOTL:         portrait = PcxGcs[ 4]; break;
    case GC_6_IMPOSSIBLE:   portrait = PcxGcs[13]; break;
    case GC_7_PROHIBITION:  portrait = PcxGcs[17]; break;
    case GC_8_FULL_CONTACT: portrait = PcxGcs[ 3]; break;
    case GC_9_NIGHT_KIN:    portrait = PcxGcs[ 5]; break;
    case GC_10_HACKNSLASH:  portrait = PcxGcs[19]; break;
    case GC_11_VACCINATED:  portrait = PcxGcs[12]; break;
    case GC_12_MY_SECRET:   portrait = PcxGcs[ 7]; break;
    case GC_13_NO_REGENS:   portrait = PcxGcs[ 8]; break;
    case GC_14_CLEAN_HANDS: portrait = PcxGcs[ 9]; break;
    case GC_15_ICE_AGE:     portrait = PcxGcs[16]; break;
    case GC_16_GROUNDHOG:   portrait = PcxGcs[15]; break;
    case GC_17_TOUGH_MNSTR: portrait = PcxGcs[10]; break;
    case GC_18_INDESTR_ITM: portrait = PcxGcs[11]; break;
    case GC_19_NO_MAP:      portrait = PcxGcs[22]; break;
    case GC_20_2X_DAMAGE:   portrait = PcxGcs[21]; break; // unused: 18
    case GC_21_C_NO_EVIL:   portrait = PcxGcs[20]; break;
    case GC_22_BLACK_DEATH: portrait = PcxGcs[ 6]; break;
    case GC_23_TOUGH_LUCK:  portrait = PcxGcs[18]; break;
    case GC_24_RUTHLESS:    portrait = PcxGcs[18]; break;
    case GC_25_ACCELERATION:portrait = PcxGcs[15]; break;
    case GC_26_ASCETICISM:  portrait = PcxGcs[15]; break;
    default:                portrait = PcxGcs[50]; break;
	}
    return portrait;
}

const char* getGameChangerDescription(const GAME_CHANGER gameChanger)
{
    switch (gameChanger)
    {
    case GC_0_CONTINUE:     return "Modificadores sao opcionais e permanentes. Podem adicionar ou remover vantagens e sinergias do personagem.";
    case GC_1_AUTO_SAVE:    return "O jogo salva automaticamente, como no modo multijogador. Voce nao precisa salvar manualmente.";
    case GC_2_BT_STRIP:     return "Durante batalhas, nao e possivel equipar ou remover itens, exceto nos espacos das maos.";
    case GC_3_DROP_ITMS:    return "Ao morrer, voce derruba os itens equipados. Se nao recupera-los na mesma sessao, eles desaparecem.";
    case GC_4_EFFORTLESS:   return "Facilita o jogo: monstros causam apenas metade do dano normal.";
    case GC_5_LOTL:         return "Moradores nao vendem itens, mas continuam oferecendo reparo, identificacao, encantamento e outros servicos.";
    case GC_6_IMPOSSIBLE:   return "Aumenta muito a dificuldade: monstros causam o dobro de dano.";
    case GC_7_PROHIBITION:  return "Monstros deixam de derrubar elixires de atributos aleatoriamente. Algumas vantagens ainda podem conceder elixires.";
    case GC_8_FULL_CONTACT: return "Facilita o jogo: monstros que atacam a distancia nao recuam de voce.";
    case GC_9_NIGHT_KIN:    return "Muda completamente o estilo de jogo. Voce nao usa itens e depende apenas de seus poderes inatos.";
    case GC_10_HACKNSLASH:  return "Todas as armas causam dano neutro. Nao e preciso trocar o tipo de arma para enfrentar monstros diferentes.";
    case GC_11_VACCINATED:  return "Monstros perdem imunidades, reduzindo a necessidade de trocar feiticos. Algumas magias nao sao afetadas.";
    case GC_12_MY_SECRET:   return "Furia nao possui tempo de recarga e pode ser usada novamente assim que terminar.";
    case GC_13_NO_REGENS:   return "Adiciona desafio: o personagem nao possui regeneracao basica de vida nem de mana.";
    case GC_14_CLEAN_HANDS: return "Monstros nao derrubam equipamentos utilizaveis. Voce deve consegui-los comprando ou encantando.";
    case GC_15_ICE_AGE:     return "Mudanca visual: as masmorras ficam congeladas, como se um inverno profundo tivesse tomado o Inferno.";
    case GC_16_GROUNDHOG:   return "A mesma masmorra e os mesmos monstros sao gerados em todas as partidas, permitindo aperfeicoar sua rota.";
    case GC_17_TOUGH_MNSTR: return "Aumenta a dificuldade: monstros possuem +200% de pontos de vida.";
    case GC_18_INDESTR_ITM: return "Itens nao sao destruidos com durabilidade zero. Ficam inutilizaveis ate serem reparados.";
    case GC_19_NO_MAP:      return "Adiciona desafio: o automapa fica indisponivel. Voce tera que explorar as masmorras sem mapa.";
    case GC_20_2X_DAMAGE:   return "Facilita o jogo: seus ataques causam o dobro de dano aos monstros.";
    case GC_21_C_NO_EVIL:   return "Adiciona desafio: a habilidade de visao nao destaca monstros na escuridao.";
    case GC_22_BLACK_DEATH: return "Voce esta infectado pela Peste Negra, uma maldicao que progride sem controle. Quanto tempo conseguira sobreviver?";
    case GC_23_TOUGH_LUCK:  return "Atributos iniciais = 5, +2 pontos por nivel e -75% de MF/GF/XP. Varias vantagens de progressao ficam indisponiveis.";
    case GC_24_RUTHLESS:    return "Regras Ironman classicas: sem bonus de XP, MF ou atributos e sem oleos ou identificadores dos chefes.";
    case GC_25_ACCELERATION:return "Facilita o jogo: experiencia aumentada em 5x para acelerar bastante a progressao.";
    case GC_26_ASCETICISM:  return "Save automatico, sem ressuscitar na cidade e todos os itens derrubados sao perdidos ao morrer.";
    default:                return "Modificador desconhecido";
    }
}

const char* returnONorOFF(const GAME_CHANGER gameChanger) {
    return NewSaveInfo.GameChanger & BIT(gameChanger) ? "SIM" : "NAO";
}

const char* getGameChangerName(const GAME_CHANGER gameChanger)
{
	static char text[256];

	switch (gameChanger)
    {
    case GC_0_CONTINUE:     sprintf(text, "Continuar"); break;
    case GC_1_AUTO_SAVE:    sprintf(text, "Save Automatico: %s", returnONorOFF(gameChanger)); break;
    case GC_2_BT_STRIP:     sprintf(text, "Equipamento Preso: %s", returnONorOFF(gameChanger)); break;
    case GC_3_DROP_ITMS:    sprintf(text, "Derrubar Itens: %s", returnONorOFF(gameChanger)); break;
    case GC_4_EFFORTLESS:   sprintf(text, "Sem Esforco: %s", returnONorOFF(gameChanger)); break;
    case GC_5_LOTL:         sprintf(text, "Vida da Terra: %s", returnONorOFF(gameChanger)); break;
    case GC_6_IMPOSSIBLE:   sprintf(text, "Impossivel: %s", returnONorOFF(gameChanger)); break;
    case GC_7_PROHIBITION:  sprintf(text, "Proibicao: %s", returnONorOFF(gameChanger)); break;
    case GC_8_FULL_CONTACT: sprintf(text, "Contato Total: %s", returnONorOFF(gameChanger)); break;
    case GC_9_NIGHT_KIN:    sprintf(text, "Filho da Noite: %s", returnONorOFF(gameChanger)); break;
    case GC_10_HACKNSLASH:  sprintf(text, "Hack & Slash: %s", returnONorOFF(gameChanger)); break;
    case GC_11_VACCINATED:  sprintf(text, "Vacinado: %s", returnONorOFF(gameChanger)); break;
    case GC_12_MY_SECRET:   sprintf(text, "Meu Segredo: %s", returnONorOFF(gameChanger)); break;
    case GC_13_NO_REGENS:   sprintf(text, "Sem Regeneracao: %s", returnONorOFF(gameChanger)); break;
    case GC_14_CLEAN_HANDS: sprintf(text, "Maos Limpas: %s", returnONorOFF(gameChanger)); break;
    case GC_15_ICE_AGE:     sprintf(text, "Era do Gelo: %s", returnONorOFF(gameChanger)); break;
    case GC_16_GROUNDHOG:   sprintf(text, "Dia da Marmota: %s", returnONorOFF(gameChanger)); break;
    case GC_17_TOUGH_MNSTR: sprintf(text, "Monstros Fortes: %s", returnONorOFF(gameChanger)); break;
    case GC_18_INDESTR_ITM: sprintf(text, "Itens Indestrutiveis: %s", returnONorOFF(gameChanger)); break;
    case GC_19_NO_MAP:      sprintf(text, "Sem Mapa: %s", returnONorOFF(gameChanger)); break;
    case GC_20_2X_DAMAGE:   sprintf(text, "Dano Duplo: %s", returnONorOFF(gameChanger)); break;
    case GC_21_C_NO_EVIL:   sprintf(text, "Nao Veja o Mal: %s", returnONorOFF(gameChanger)); break;
    case GC_22_BLACK_DEATH: sprintf(text, "Peste Negra: %s", returnONorOFF(gameChanger)); break;
    case GC_23_TOUGH_LUCK:  sprintf(text, "Ma Sorte: %s", returnONorOFF(gameChanger)); break;
    case GC_24_RUTHLESS:    sprintf(text, "Ferro Implacavel: %s", returnONorOFF(gameChanger)); break;
    case GC_25_ACCELERATION:sprintf(text, "Aceleracao: %s", returnONorOFF(gameChanger)); break;
    case GC_26_ASCETICISM:  sprintf(text, "Ascetismo: %s", returnONorOFF(gameChanger)); break;
    default:                sprintf(text, "Modificador desconhecido"); break;
	}
    return text;
}

int GetSuperGameChanger(char*) //?
{
    return GC_0_CONTINUE;
}

void __fastcall SetGameChangerInfoText(HWND parent, const GAME_CHANGER gameChanger)
{
    ShowWindowList(parent, CharParamNameList, SW_HIDE);
    ShowWindowList(parent, CharParamValueList, SW_HIDE);
    ShowWindowList(parent, ClassDescriptionList, SW_SHOW);

    Portrait portrait = getGameChangerPortrait(gameChanger);
    const char* description = getGameChangerDescription(gameChanger);

    DrawReadableTextToElem(parent, ID_CLASS_DESCRIPTION, description);

    const HWND portraitWin = GetDlgItem(parent, ID_PLAYER_PORTRAIT);
    RECT rect;
    InvalidateRect(portraitWin, 0, 0);
    GetClientRect(portraitWin, &rect);
    AdjustScrollRect(&rect, 0, rect.bottom * portrait.id);
	SDlgSetBitmap(portraitWin, 0, "Static", -1, 1, portrait.pcx->data, &rect, portrait.pcx->size.cx, portrait.pcx->size.cy, -1);
}

void __fastcall ResetGameChangerButtons(HWND hdlg, const int topIndex)
{
    GameChangersAvailableList.clear();
    GameChangersAvailableList.emplace_back(GC_0_CONTINUE);
    if (MaxCountOfPlayersInGame == 1
        && (!(NewSaveInfo.GameChanger & BIT(GC_26_ASCETICISM)))
        && is(NewSaveInfo.GameMode, GM_EASY, GM_NORMAL, GM_HARD, GM_HARDCORE)) {
        GameChangersAvailableList.emplace_back(GC_1_AUTO_SAVE);
    }

    GameChangersAvailableList.emplace_back(GC_2_BT_STRIP); // always available

    if ((MaxCountOfPlayersInGame > 1 || NewSaveInfo.GameChanger & BIT(GC_1_AUTO_SAVE)) 
        && is(NewSaveInfo.GameMode, GM_EASY, GM_NORMAL, GM_HARD)) {
        GameChangersAvailableList.emplace_back(GC_3_DROP_ITMS);
    }

    if (MaxCountOfPlayersInGame == 1 && NewSaveInfo.GameMode == GM_EASY) {
        GameChangersAvailableList.emplace_back(GC_4_EFFORTLESS);
    }

    if (!has(NewSaveInfo.Traits, TraitId::Leper)
        && (!(NewSaveInfo.GameChanger & BIT(GC_14_CLEAN_HANDS)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_26_ASCETICISM)))
        ) {
        GameChangersAvailableList.emplace_back(GC_5_LOTL);
    }

    if (MaxCountOfPlayersInGame == 1 
        && NewSaveInfo.GameMode == GM_HARD) {
        GameChangersAvailableList.emplace_back(GC_6_IMPOSSIBLE);
    }

    GameChangersAvailableList.emplace_back(GC_7_PROHIBITION); // always available

    if (MaxCountOfPlayersInGame == 1 
        && NewSaveInfo.GameMode != GM_HARD) {
        GameChangersAvailableList.emplace_back(GC_8_FULL_CONTACT);
    }

    if (MaxCountOfPlayersInGame == 1 && (NewSaveInfo.Class == PC_5_SAVAGE && NewSaveInfo.SubClass == PSC_SAVAGE_EXECUTIONER)) {
        if (
            (!has(NewSaveInfo.Traits, TraitId::Leper))
            && (!has(NewSaveInfo.Traits, TraitId::Barbarism))
            && (!has(NewSaveInfo.Traits, TraitId::Weird))
            && (!has(NewSaveInfo.Traits, TraitId::Scrounger))
            && (!has(NewSaveInfo.Traits, TraitId::TreasureHunter))
            && (!has(NewSaveInfo.Traits, TraitId::NastyDisposition))
            && (!has(NewSaveInfo.Traits, TraitId::CrowdSeeker))
            && (!has(NewSaveInfo.Traits, TraitId::LitheBuild))
            //&& (is(NewSaveInfo.GameMode, GM_EASY, GM_NORMAL, GM_HARD, GM_HARDCORE))
            ) {
            GameChangersAvailableList.emplace_back(GC_9_NIGHT_KIN);
        }
    }

    if (MaxCountOfPlayersInGame == 1 // SP
        && NewSaveInfo.GameMode == GM_EASY // EASY
        && (!is(NewSaveInfo.Class, PC_1_ARCHER, PC_2_MAGE)) // not archers or magi
        && (!has(NewSaveInfo.Traits, TraitId::Axepertise)) // Axe Rogue doesn't need it (axe is neutral damage)
        && (!has(NewSaveInfo.Traits, TraitId::Bestiarius)) // Bestiarius can't have it..
        && (!has(NewSaveInfo.Traits, TraitId::TwoTowers)) // Maiden with 2 shields does not use weapons
        && (!(NewSaveInfo.Class == PC_0_WARRIOR && NewSaveInfo.SubClass == PSC_WARRIOR_INQUISITOR)) // not Inquisitor
        && (!(NewSaveInfo.Class == PC_3_MONK && NewSaveInfo.SubClass == PSC_MONK_SHUGOKI)) // not Shugoki
        && (!(NewSaveInfo.Class == PC_4_ROGUE && NewSaveInfo.SubClass == PSC_ROGUE_BOMBARDIER)) // not Bombardier
        && (!(NewSaveInfo.Class == PC_5_SAVAGE && NewSaveInfo.SubClass == PSC_SAVAGE_BERSERKER)) // not Berserker
        ) {
        GameChangersAvailableList.emplace_back(GC_10_HACKNSLASH);
    }

    if (MaxCountOfPlayersInGame == 1 // SP
        && NewSaveInfo.GameMode == GM_EASY
        && ((NewSaveInfo.Class == PC_2_MAGE && NewSaveInfo.SubClass == PSC_MAGE_MAGE)
            || (NewSaveInfo.Class == PC_2_MAGE && NewSaveInfo.SubClass == PSC_MAGE_ELEMENTALIST)// mor: Mamluk still has it, might want to remove it from him
            || (NewSaveInfo.Class == PC_2_MAGE && NewSaveInfo.SubClass == PSC_MAGE_WARLOCK)
            //|| (NewSaveInfo.Class == PC_1_ARCHER && NewSaveInfo.SubClass == PSC_ARCHER_SCOUT)
            //|| (NewSaveInfo.Class == PC_0_WARRIOR && NewSaveInfo.SubClass == PSC_WARRIOR_INQUISITOR)
            || (NewSaveInfo.Class == PC_4_ROGUE && NewSaveInfo.SubClass == PSC_ROGUE_BOMBARDIER))
        ) {
        GameChangersAvailableList.emplace_back(GC_11_VACCINATED);
    }

    if (MaxCountOfPlayersInGame == 1 
        && NewSaveInfo.GameMode == GM_EASY) {
        GameChangersAvailableList.emplace_back(GC_12_MY_SECRET);
    }

    if (
        (!has(NewSaveInfo.Traits, TraitId::Adrenaline))
        && (!has(NewSaveInfo.Traits, TraitId::Necropathy))
        && (!has(NewSaveInfo.Traits, TraitId::GrimDeal))
        && (!has(NewSaveInfo.Traits, TraitId::DarkPact))
        && (!has(NewSaveInfo.Traits, TraitId::Barbarism))
        && (!has(NewSaveInfo.Traits, TraitId::Survivor))
        && (!has(NewSaveInfo.Traits, TraitId::FastMetabolism))
        && (!has(NewSaveInfo.Traits, TraitId::BlisteredSkin))
        && (!has(NewSaveInfo.Traits, TraitId::Black_Witchery))
        && (!has(NewSaveInfo.Traits, TraitId::Psion)) 
        && (!has(NewSaveInfo.Traits, TraitId::Paladin))
        && (!has(NewSaveInfo.Traits, TraitId::Insensitive))
        && (!has(NewSaveInfo.Traits, TraitId::BloodOath))
        ) {
        GameChangersAvailableList.emplace_back(GC_13_NO_REGENS);
    }

    if (
        (!has(NewSaveInfo.Traits, TraitId::Scrounger))
        && (!has(NewSaveInfo.Traits, TraitId::TreasureHunter))
        && (!has(NewSaveInfo.Traits, TraitId::Barbarian))
        && (!has(NewSaveInfo.Traits, TraitId::NastyDisposition))
        && (!(NewSaveInfo.Class == PC_5_SAVAGE && NewSaveInfo.SubClass == PSC_SAVAGE_EXECUTIONER)) // executioner cannot have clean hands
        && (!(NewSaveInfo.GameChanger & BIT( GC_5_LOTL )))
        && (is(NewSaveInfo.GameMode, GM_EASY, GM_NORMAL, GM_HARD, GM_HARDCORE))
        ) {
        GameChangersAvailableList.emplace_back(GC_14_CLEAN_HANDS);
    }

    if (MaxCountOfPlayersInGame == 1) {
        GameChangersAvailableList.emplace_back(GC_15_ICE_AGE);
    }

    if (MaxCountOfPlayersInGame == 1 
        && NewSaveInfo.GameMode == GM_SPEEDRUN) {
        GameChangersAvailableList.emplace_back(GC_16_GROUNDHOG);
    }

    if (MaxCountOfPlayersInGame == 1 
         && NewSaveInfo.GameMode != GM_EASY) {
        GameChangersAvailableList.emplace_back(GC_17_TOUGH_MNSTR);
    }

    if (
        (is(NewSaveInfo.GameMode, GM_EASY, GM_NORMAL, GM_SURVIVAL))
        && (!(NewSaveInfo.GameChanger & BIT(GC_9_NIGHT_KIN)))
        ) {
        GameChangersAvailableList.emplace_back(GC_18_INDESTR_ITM);
    }

    GameChangersAvailableList.emplace_back(GC_19_NO_MAP);

    if (
        MaxCountOfPlayersInGame == 1
        && NewSaveInfo.GameMode == GM_EASY
        && (!has(NewSaveInfo.Traits, TraitId::Psion))
        && (!has(NewSaveInfo.Traits, TraitId::Devastator))
        && (!has(NewSaveInfo.Traits, TraitId::HolyAura))
        ) {
        GameChangersAvailableList.emplace_back(GC_20_2X_DAMAGE);
    }

    if (NewSaveInfo.GameMode != GM_EASY) {
        GameChangersAvailableList.emplace_back(GC_21_C_NO_EVIL);
    }

    if (
        NewSaveInfo.GameMode != GM_EASY
        && (!has(NewSaveInfo.Traits, TraitId::Sisyphean))
        && (!has(NewSaveInfo.Traits, TraitId::Forgetful))
        && (!has(NewSaveInfo.Traits, TraitId::Adrenaline))
        && (!has(NewSaveInfo.Traits, TraitId::Prodigy)) 
        && (!has(NewSaveInfo.Traits, TraitId::Insensitive))
        && (!has(NewSaveInfo.Traits, TraitId::FearTheReaper))
        && (!(NewSaveInfo.Class == PC_5_SAVAGE && NewSaveInfo.SubClass == PSC_SAVAGE_EXECUTIONER)) // not executioner
        && (!(NewSaveInfo.Class == PC_2_MAGE && NewSaveInfo.SubClass == PSC_MAGE_WARLOCK)) // not warlock
        && (!(NewSaveInfo.GameChanger & BIT(GC_23_TOUGH_LUCK)))
        ) {
        GameChangersAvailableList.emplace_back(GC_22_BLACK_DEATH);
    }

    if (
        (is(NewSaveInfo.GameMode, GM_NORMAL, GM_HARD))
        && (!has(NewSaveInfo.Traits, TraitId::GrimDeal))
        && (!has(NewSaveInfo.Traits, TraitId::Gifted))
        && (!has(NewSaveInfo.Traits, TraitId::Adventurer))
        && (!has(NewSaveInfo.Traits, TraitId::Forgetful))
        && (!has(NewSaveInfo.Traits, TraitId::BlueBlood))
        && (!has(NewSaveInfo.Traits, TraitId::Domesticated))
        && (!has(NewSaveInfo.Traits, TraitId::Rudiarius))
        && (!has(NewSaveInfo.Traits, TraitId::Sisyphean))
        && (!has(NewSaveInfo.Traits, TraitId::FearTheReaper))
        && (!(NewSaveInfo.GameChanger & BIT(GC_22_BLACK_DEATH)))
        ) {
        GameChangersAvailableList.emplace_back(GC_23_TOUGH_LUCK);
    }

    if (
        MaxCountOfPlayersInGame == 1
        && NewSaveInfo.GameMode == GM_IRONMAN
        ) {
        GameChangersAvailableList.emplace_back(GC_24_RUTHLESS);
    }

    if (
        MaxCountOfPlayersInGame == 1
        && (!has(NewSaveInfo.Traits, TraitId::Sisyphean))
        ) {
        GameChangersAvailableList.emplace_back(GC_25_ACCELERATION);
    }

    if (
        MaxCountOfPlayersInGame == 1
        && is(NewSaveInfo.GameMode, GM_NORMAL, GM_HARD)
        && (!has(NewSaveInfo.Traits, TraitId::Sisyphean))
        && (!(NewSaveInfo.GameChanger & BIT(GC_22_BLACK_DEATH)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_23_TOUGH_LUCK)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_9_NIGHT_KIN)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_1_AUTO_SAVE)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_3_DROP_ITMS)))
        && (!(NewSaveInfo.GameChanger & BIT(GC_5_LOTL)))
        ) {
        GameChangersAvailableList.emplace_back(GC_26_ASCETICISM);
    }
    // ----- END OF DATA -----

	for (int i = 0; GameChangerButtonList[i] != 0; ++i) {
        int saveButtonId = GameChangerButtonList[i];
        HWND saveButton = GetDlgItem(hdlg, saveButtonId);
        if (saveButton) {
            const uint currentGameChangerIndex = topIndex + i;
            if( currentGameChangerIndex < GameChangersAvailableList.size() ){
                EnableWindow(saveButton, true);
                if (auto gameChangerWin = (GameChangerWin*)GetWindowLongA(saveButton, GWL_USERDATA); gameChangerWin) { //todo
                    WriteTextToElemData((TextWin*)gameChangerWin, getGameChangerName(GameChangersAvailableList[currentGameChangerIndex]));
                    gameChangerWin->gameChangerIndex = currentGameChangerIndex;
                }
            }
            else {
                EnableWindow(saveButton, false);
            }
        }
    }
    ResetButtonText(hdlg, GameChangerButtonList, 2, 1);
}

void GameChangerRefreshCurrentGameChangerInfo(HWND hdlg, int button)
{
    if (const HWND activeElem = GetDlgItem(hdlg, button); activeElem) {
        if (const auto gameChangerWin = (GameChangerWin*)GetWindowLongA(activeElem, GWL_USERDATA); gameChangerWin) { //todo
            SelectedGameChanger = GameChangersAvailableList[gameChangerWin->gameChangerIndex];
            SetGameChangerInfoText(GetParent(hdlg), SelectedGameChanger);
        }
    }
}

int __fastcall GetGameChangerElemIndex(HWND elem)
{
    int result = 0;
    if (elem) {
        if (auto* gameChangerWin = (GameChangerWin*)GetWindowLongA(elem, GWL_USERDATA); gameChangerWin) { //todo
            return gameChangerWin->gameChangerIndex;
        }
    }
    return result;
}

void GameChangerRefreshScrollState(const HWND hdlg)
{
    SetScrollOnElem(hdlg, ID_SCROLL, GameChangersAvailableList.size(), GetGameChangerElemIndex(GetFocus()));
}

void GameChangerSelectNextGameChanger(const HWND hdlg, const HWND button, int order)
{
    const auto& buttonsOrder = (order > 0) ? nextGameChangerOrder : prevGameChangerOrder;
    HWND currentButton = button;
    for (auto i{ 0u }, ie{ buttonsOrder.size() }; i < ie; ++i) {
        currentButton = GetDlgItem(hdlg, buttonsOrder[GetWindowLongA(currentButton, GWL_ID) - ID_GAME_CHANGER_1]);
        if (IsWindowEnabled(currentButton)) {
            SetFocus(currentButton);
            break;
        }
    }
}

void __fastcall GameChangerPageDown(const HWND button)
{
    const HWND hdlg = GetParent(button);
    if (!hdlg) {
        return;
    }

    const HWND firstBut = GetDlgItem(hdlg, ID_GAME_CHANGER_1);
    if (!firstBut) {
        return;
    }

    auto gameChangerWin = (GameChangerWin*)GetWindowLongA(GetDlgItem(hdlg, ID_GAME_CHANGER_6), GWL_USERDATA); //todo
    if (!gameChangerWin) {
        return;
    }

    if (uint gameChangerIndex = gameChangerWin->gameChangerIndex; gameChangerIndex + 1 < GameChangersAvailableList.size()) { //todo
        const int topSaveIndex = GetGameChangerElemIndex(firstBut);
        const int nextTopGameChangerIndex = std::min(topSaveIndex + 6, (int)GameChangersAvailableList.size() - 6);
        PlaySoundTitleMove();
        ResetGameChangerButtons(hdlg, nextTopGameChangerIndex);
        GameChangerRefreshCurrentGameChangerInfo(hdlg, GetWindowLongA(button, GWL_ID));
        GameChangerRefreshScrollState(hdlg);
    }
    else {
        GameChangerSelectNextGameChanger(hdlg, firstBut, -1);
    }
}

void __fastcall GameChangerPageUp(const HWND button)
{
    const auto hdlg = GetParent(button);
    if (!hdlg) {
        return;
    }

    const HWND firstBut = GetDlgItem(hdlg, ID_GAME_CHANGER_1);
    if (!firstBut) {
        return;
    }

    const auto gameChangerWin = (const GameChangerWin*)GetWindowLongA(firstBut, GWL_USERDATA); //todo
    if (!gameChangerWin) {
        return;
    }

    if (const auto gameChangerIndex = gameChangerWin->gameChangerIndex; gameChangerIndex == 0) { //todo
        const auto lastBut = GetDlgItem(hdlg, ID_GAME_CHANGER_6);
        GameChangerSelectNextGameChanger(hdlg, lastBut, 1);
    }
    else {
        const int topSaveIndex = GetGameChangerElemIndex(firstBut);
        const int nextTopGameChangerIndex = std::max(topSaveIndex - 6, 0);
        PlaySoundTitleMove();
        ResetGameChangerButtons(hdlg, nextTopGameChangerIndex);
        GameChangerRefreshCurrentGameChangerInfo(hdlg, GetWindowLongA(button, GWL_ID));
        GameChangerRefreshScrollState(hdlg);
    }
}

void __fastcall GameChangerDown(const HWND button)
{
    const auto hdlg = GetParent(button);

    if (auto gameChangerWin = (GameChangerWin*)GetWindowLongA(button, GWL_USERDATA); gameChangerWin) { //todo
        if (auto gameChangerIndex = gameChangerWin->gameChangerIndex; gameChangerIndex + 1 < GameChangersAvailableList.size()) {
            if (GetWindowLongA(button, GWL_ID) < ID_GAME_CHANGER_6) {
                GameChangerSelectNextGameChanger(hdlg, button, 1);
            }
            else {
                if (auto newBut = GetDlgItem(hdlg, ID_GAME_CHANGER_2); newBut) {
                    if (auto newWin = (GameChangerWin*)GetWindowLongA(newBut, GWL_USERDATA); newWin) {//todo
                        const auto nextTopGameChangerIndex = newWin->gameChangerIndex;
                        PlaySoundTitleMove();
                        ResetGameChangerButtons(hdlg, nextTopGameChangerIndex);
                        GameChangerRefreshCurrentGameChangerInfo(hdlg, GetWindowLongA(button, GWL_ID));
                        GameChangerRefreshScrollState(hdlg);
                    }
                }
            }
        }
    }
}

void __fastcall GameChangerUp(const HWND button)
{
    const auto hdlg = GetParent(button);

    if (GetWindowLongA(button, GWL_ID) > ID_GAME_CHANGER_1) {
        GameChangerSelectNextGameChanger(hdlg, button, -1);
        return;
    }
    else {
        if (auto gameChangerWin = (GameChangerWin*)GetWindowLongA(button, GWL_USERDATA); gameChangerWin) {//todo
            if (auto gameChangerIndex = gameChangerWin->gameChangerIndex; gameChangerIndex > 0) {
                const auto nextTopGameChangerIndex = gameChangerIndex - 1;
                PlaySoundTitleMove();
                ResetGameChangerButtons(hdlg, nextTopGameChangerIndex);
                GameChangerRefreshCurrentGameChangerInfo(hdlg, GetWindowLongA(button, GWL_ID));
                GameChangerRefreshScrollState(hdlg);
            }
        }
    }
}

LRESULT __stdcall GameChangerSelectButtonProc(const HWND button, unsigned int Msg, WPARAM wParam, LPARAM lParam)
{
    XinputVirtualKeyboard();

    LRESULT result = 0;
    auto oldProc = (WNDPROC)GetPropA(button, "UIOLDPROC");
    const auto hdlg = GetParent(button);

    switch (Msg) {
    case WM_GETDLGCODE:
        result = 4;
        break;
    case WM_KEYFIRST:
        switch (wParam) {
        case VK_RETURN:
        case VK_SPACE:
            SendMessageA(hdlg, 273, 1, 0);
            break;
        case VK_ESCAPE:
            SendMessageA(hdlg, 273, 2, 0);
            break;
        case VK_TAB:
            GameChangerSelectNextGameChanger(hdlg, button, (GetKeyState(VK_SHIFT) >= 0) ? 1 : -1);
            break;
        case VK_LEFT:
        case VK_UP:
            GameChangerUp(button);
            break;
        case VK_RIGHT:
        case VK_DOWN:
            GameChangerDown(button);
            break;
        case VK_PRIOR:
            GameChangerPageUp(button);
            break;
        case VK_NEXT:
            GameChangerPageDown(button);
            break;
        case VK_DELETE:
            SendMessageA(hdlg, Msg, wParam, lParam);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        RemovePropA(button, "UIOLDPROC");
        if (oldProc) {
            SetWindowLongA(button, GWL_WNDPROC, (LONG)oldProc);
        }
        [[fallthrough]];
    default:
        if (oldProc) {
            result = CallWindowProcA_(oldProc, button, Msg, wParam, lParam);
        }
        else {
            result = DefWindowProcA_(button, Msg, wParam, lParam);
        }
        break;
    case WM_PAINT:
        PaintElem(button);
        break;
    }
    return result;
}

int __stdcall DialogSelectGameChangers(HWND hdlg, unsigned int Msg, WPARAM wParam, LPARAM lParam)
{
    int result;
    bool needToCallDefDialogProc = true;

    XinputVirtualKeyboard();

    switch (Msg) {
    case WM_INITDIALOG:
    {
		if( GameMode == GM_COLISEUM || GameMode == GM_CLASSIC ){
            SelectedGameChanger = GAME_CHANGER::GC_0_CONTINUE;
            SDlgEndDialog(hdlg, lParam == 1 ? -1 : 0);
            return SDlgDefDialogProc_(hdlg, Msg, wParam, lParam);
        }
        SelectedGameChanger = GAME_CHANGER::GC_0_CONTINUE;

        for (int i = 0; GameChangerButtonList[i] != 0; ++i) {
            int saveButtonId = GameChangerButtonList[i];
            HWND saveButton = GetDlgItem(hdlg, saveButtonId);
            if (saveButton) {
                SetPropA(saveButton, "UIOLDPROC", (HANDLE)GetWindowLongA(saveButton, GWL_WNDPROC));
                SetWindowLongA(saveButton, GWL_WNDPROC, (LONG)GameChangerSelectButtonProc);
            }
        }

        char tempBuf[32];
        LoadStringA(HInstance, NewHeroTitle(), tempBuf, 31);
        WriteAndDrawDialogTitle(GetParent(hdlg), tempBuf);
        SetWindowLongA(hdlg, GWL_USERDATA, GetWindowLongA(GetParent(hdlg), GWL_USERDATA));
        InitTextElemList(hdlg, GameChangerTitleList, 5);
        InitButtonListText(hdlg, GameChangerOkCancelList, 4, 0);
        InitButtonListText(hdlg, GameChangerButtonList, 2, 1);
        ResetGameChangerButtons(hdlg, 0);
        InitSelectionAndLoadPentagram("ui_art\\focus16.pcx");
        SDlgSetTimer(hdlg, 1, 55, 0);
        InitScroll(hdlg, ID_SCROLL);
        if( GameChangersAvailableList.size() <= 6 ){
            ShowWindow(GetDlgItem(hdlg, ID_SCROLL), 0);
        }
        needToCallDefDialogProc = false;
        result = 0;
        break;
    }
    case WM_DESTROY:
    {
        DeleteScroll(hdlg, ID_SCROLL);
        DeletePentagram();
        DeleteElementListData(hdlg, GameChangerButtonList);
        DeleteElementListData(hdlg, GameChangerOkCancelList);
        DeleteElementListData(hdlg, GameChangerTitleList);
        WriteAndDrawDialogTitle(GetParent(hdlg), 0);
        break;
    }
    case WM_COMMAND:
    {
        if (HIWORD_IDA(wParam) == BN_KILLFOCUS) {
            LeaveButton(hdlg, (HWND)lParam);
        }
        else if (HIWORD_IDA(wParam) == BN_SETFOCUS) {
            InvalidateRect(GetParent(hdlg), NULL, NULL); //removes menu freezes // character selection menu
            UpdateWindow(GetParent(hdlg)); //removes menu freezes // character selection menu
            SelectButton((HWND)lParam);
            AnimateSelectionPentagram(hdlg, (HWND)lParam);
            GameChangerRefreshCurrentGameChangerInfo(hdlg, (unsigned __int16)wParam);
            GameChangerRefreshScrollState(hdlg);
        }
        else if (HIWORD_IDA(wParam) == BN_DOUBLECLICKED || (ushort)wParam == 1) { // Enter
            PlaySoundTitleSelect();
            SDlgKillTimer(hdlg, 1);
            SDlgEndDialog(hdlg, 1);
        }
        else if ((ushort)wParam == 2) {
            PlaySoundTitleSelect();
            SDlgKillTimer(hdlg, 1);
            SDlgEndDialog(hdlg, 2);
        }
        break;
    }
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
    {
        int cursorX = (unsigned __int16)lParam;
        int cursorY = (unsigned int)lParam >> 16;
        if (CheckCursorOnButton(hdlg, GetDlgItem(hdlg, ID_OK_BUTTON), cursorX, cursorY)) {
            PlaySoundTitleSelect();
            SDlgKillTimer(hdlg, 1);
            SDlgEndDialog(hdlg, 1);
        }
        else if (CheckCursorOnButton(hdlg, GetDlgItem(hdlg, ID_CANCEL_BUTTON), cursorX, cursorY)) {
            PlaySoundTitleSelect();
            SDlgKillTimer(hdlg, 1);
            SDlgEndDialog(hdlg, 2);
        }
        else if (CheckCursorOnButton(hdlg, GetDlgItem(hdlg, ID_SCROLL), cursorX, cursorY)) {
            switch (GetScrollAction(GetDlgItem(hdlg, ID_SCROLL), cursorX, cursorY)) {
            case 1:
                GameChangerUp(GetFocus());
                break;
            case 2:
                GameChangerDown(GetFocus());
                break;
            case 3:
                GameChangerPageUp(GetFocus());
                break;
            case 4:
                GameChangerPageDown(GetFocus());
                break;
            default:
                break;
            }
        }
        break;
    }
    case WM_LBUTTONUP:
    {
        if (CheckScrollPressAndRelease(GetDlgItem(hdlg, ID_SCROLL))) {
            GameChangerRefreshScrollState(hdlg);
        }
        break;
    }
    case WM_TIMER:
        AnimateSelectionPentagram(hdlg, GetFocus());
        needToCallDefDialogProc = false;
        result = 0;
        break;
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
        SendMessageA(SDrawGetFrameWindow(nullptr), Msg, wParam, lParam);
        break;
    }

    if (needToCallDefDialogProc) {
        result = SDlgDefDialogProc_(hdlg, Msg, wParam, lParam);
    }

    return result;
}
