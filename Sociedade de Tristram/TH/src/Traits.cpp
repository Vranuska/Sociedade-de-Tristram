#include "stdafx.h"

int TraitIndexToSelect = 0;
TraitId SelectedTraitId = TraitId::NoTrait;
int TraitTitleList[ 2 ] = { ID_CAPTION, 0 };
int TraitOkCancelList[ 3 ] = { ID_OK_BUTTON, ID_CANCEL_BUTTON, 0 };

int TraitButtonList[] = {
    ID_TRAIT_1,
    ID_TRAIT_2,
    ID_TRAIT_3,
    ID_TRAIT_4,
    ID_TRAIT_5,
    ID_TRAIT_6,
    0 };

constexpr std::array nextTraitOrder = {
    ID_TRAIT_2,
    ID_TRAIT_3,
    ID_TRAIT_4,
    ID_TRAIT_5,
    ID_TRAIT_6,
    ID_TRAIT_1,
};
constexpr std::array prevTraitOrder = {
    ID_TRAIT_6,
    ID_TRAIT_1,
    ID_TRAIT_2,
    ID_TRAIT_3,
    ID_TRAIT_4,
    ID_TRAIT_5,
};

enum TRAIT_GROUP_MASK : uint64_t
{
    TGM_NONE                = 0,
    TGM_PERK_POINTS_DOWN    = BIT(1),
    TGM_PERK_POINTS_UP      = BIT(2),
	TGM_DESTROY				= BIT(3),
	TGM_BOUNCE				= BIT(4),
	TGM_REZ_UP				= BIT(5),
	TGM_REZ_DOWN			= BIT(6),
	TGM_CRIT_UP				= BIT(7),
	TGM_CRIT_DOWN			= BIT(8),
	TGM_DMG_UP				= BIT(9),
	TGM_DMG_DOWN			= BIT(10),
	TGM_MELEE_AUTOHIT_UP	= BIT(11),
	TGM_MELEE_AUTOHIT_DOWN	= BIT(12),
	TGM_MAX_REZ_UP			= BIT(13),
	TGM_MAX_REZ_DOWN		= BIT(14),
	TGM_STATS_MORE			= BIT(15),
	TGM_STATS_LESS			= BIT(16),
	TGM_ATK_SPD_DOWN		= BIT(17),
	TGM_ATK_SPD_UP			= BIT(18),
	TGM_MORE_XP				= BIT(19),
	TGM_LESS_XP				= BIT(20),
	TGM_MORE_MAX_STATS		= BIT(21),
	TGM_MANUAL_MAX_STATS	= BIT(22),
    TGM_KB_DOWN             = BIT(23),
    TGM_KB_UP               = BIT(24),
    TGM_SYNS_UP             = BIT(25),
    TGM_SYNS_DOWN           = BIT(26),
    TGM_MF_MORE             = BIT(27),
    TGM_BARBARIAN           = BIT(28),
    TGM_SPELLS_ON           = BIT(29),
    TGM_SPELLS_OFF          = BIT(30),
    TGM_NO_PISTOL           = BIT(31),
    TGM_PISTOL              = BIT(32),
    TGM_FTR                 = BIT(33),
    TGM_WEIRD               = BIT(34),
    TGM_NASTY               = BIT(35),
    TGM_LEPER               = BIT(36),
    TGM_BRUISER             = BIT(37),
    TGM_LITHE               = BIT(38),
    TGM_AC_DOWN             = BIT(39),
    TGM_AC_UP               = BIT(40),
    TGM_BLOOD_OATH          = BIT(41),
    TGM_PSION               = BIT(42),
    TGM_TR_HUNTER           = BIT(43),
    TGM_COINBOUND           = BIT(44),
    TGM_SMALL_FRAME         = BIT(45),
    TGM_DOOMWHORL           = BIT(46),
    TGM_RABID               = BIT(47),
    TGM_LOTR                = BIT(48),
    TGM_OLDFASH             = BIT(49),
    TGM_CRUPELLARIUS        = BIT(50),
    TGM_ABNEG               = BIT(51),
    TGM_FAST_MET            = BIT(52),
    TGM_GIANT               = BIT(53),
    TGM_PAL                 = BIT(54)

};
bit_enum( TRAIT_GROUP_MASK );

std::vector TraitsExcludedCombinations = {
    TGM_PERK_POINTS_DOWN | TGM_PERK_POINTS_UP,
	TGM_DESTROY			 | TGM_BOUNCE,
	TGM_REZ_UP			 | TGM_REZ_DOWN,
	TGM_CRIT_UP			 | TGM_CRIT_DOWN,
	TGM_DMG_UP			 | TGM_DMG_DOWN,
	TGM_MELEE_AUTOHIT_UP | TGM_MELEE_AUTOHIT_DOWN,
	TGM_MAX_REZ_UP		 | TGM_MAX_REZ_DOWN,
	TGM_STATS_MORE		 | TGM_STATS_LESS,
	TGM_ATK_SPD_DOWN	 | TGM_ATK_SPD_UP,
	TGM_MORE_XP			 | TGM_LESS_XP,
	TGM_MANUAL_MAX_STATS | TGM_MORE_MAX_STATS,
    TGM_KB_DOWN          | TGM_KB_UP,
    TGM_SYNS_UP          | TGM_SYNS_DOWN,
    TGM_MF_MORE          | TGM_BARBARIAN,
    TGM_SPELLS_ON        | TGM_SPELLS_OFF,
    TGM_NO_PISTOL        | TGM_PISTOL,
    TGM_DMG_UP           | TGM_PISTOL,
    TGM_FTR              | TGM_PERK_POINTS_UP,
    TGM_FTR              | TGM_LESS_XP,
    TGM_FTR              | TGM_PERK_POINTS_DOWN,
    TGM_FTR              | TGM_ATK_SPD_DOWN,
    TGM_FTR              | TGM_WEIRD,
    TGM_FTR              | TGM_STATS_MORE,
    TGM_NASTY            | TGM_MORE_MAX_STATS,
    TGM_NASTY            | TGM_BARBARIAN,
    TGM_NASTY            | TGM_LEPER,
    TGM_FTR              | TGM_PISTOL,
    TGM_BRUISER          | TGM_LITHE,
    TGM_MANUAL_MAX_STATS | TGM_LITHE,
    TGM_LEPER            | TGM_LITHE,
    TGM_AC_UP            | TGM_AC_DOWN,
    TGM_BLOOD_OATH       | TGM_PSION,
    TGM_PERK_POINTS_DOWN | TGM_COINBOUND,
    TGM_TR_HUNTER        | TGM_COINBOUND,
    TGM_BARBARIAN        | TGM_COINBOUND,
    TGM_SMALL_FRAME      | TGM_DOOMWHORL,
    TGM_CRIT_UP          | TGM_RABID,
    TGM_LOTR             | TGM_PERK_POINTS_DOWN,
    TGM_LOTR             | TGM_PERK_POINTS_UP,
    TGM_LOTR             | TGM_FTR,
    TGM_OLDFASH          | TGM_CRUPELLARIUS,
    TGM_MELEE_AUTOHIT_UP | TGM_CRUPELLARIUS,
    TGM_CRIT_UP          | TGM_CRUPELLARIUS,
    TGM_ABNEG            | TGM_REZ_DOWN,
    TGM_ABNEG            | TGM_FAST_MET,
    TGM_GIANT            | TGM_PISTOL,
    TGM_GIANT            | TGM_FTR,
    TGM_GIANT            | TGM_MELEE_AUTOHIT_UP,
    TGM_GIANT            | TGM_PAL,
    TGM_GIANT            | TGM_SMALL_FRAME,
    TGM_GIANT            | TGM_MANUAL_MAX_STATS,
    TGM_GIANT            | TGM_PERK_POINTS_UP,
    TGM_GIANT            | TGM_RABID,
    TGM_GIANT            | TGM_BRUISER,
    TGM_GIANT            | TGM_MORE_MAX_STATS,
    TGM_GIANT            | TGM_STATS_MORE,
    TGM_GIANT            | TGM_LITHE

};

std::vector<TraitId> TraitsAvailableList;

//----- (th2) ------------------------------------------------------------
const char* GetTraitName( TraitId id )
{
    switch( id )
    {
        default:
        case TraitId::NoTrait:			return "Sem Traco";
        case TraitId::Gifted:			return "Talentoso";
        case TraitId::Kamikaze:			return "Kamikaze";
        case TraitId::HeavyHanded:		return "Mao Pesada";
        case TraitId::Skilled:			return "Habilidoso";
        case TraitId::Barbarism:		return "Barbarismo";
        case TraitId::Finesse:			return "Precisao";
        case TraitId::Survivor:			return "Sobrevivente";
        case TraitId::Weird:			return "Estranho";
        case TraitId::OldFashioned:		return "A Moda Antiga";
        case TraitId::Domesticated:		return "Domesticado";
        case TraitId::Rabid:			return "Raivoso";
        case TraitId::Bruiser:			return "Brutamontes";
        case TraitId::Negotiant:		return "Negociante";
        case TraitId::Leper:			return "Leproso";
        case TraitId::Rudiarius:		return "Rudiarius";
        case TraitId::Scrounger:		return "Catador";
        case TraitId::Adventurer:		return "Aventureiro";
        case TraitId::ThickSkinned:		return "Pele Grossa";
        case TraitId::RatelHide:		return "Couro de Ratel";
        case TraitId::Forgetful:		return "Esquecido";
        case TraitId::WildSorcery:		return "Feiticaria Selvagem";
        case TraitId::Cautious:			return "Cauteloso";
		case TraitId::OldHabit:			return "Velho Habito";
		case TraitId::GoldDigger:		return "Cacador de Ouro";
		case TraitId::ArrowDancing:		return "Danca das Flechas";
		case TraitId::PointBlank:		return "Queima-Roupa";
		case TraitId::FastMetabolism:	return "Metabolismo Rapido";
		case TraitId::Bouncer:			return "Brigao";
		case TraitId::Sandman:			return "Homem de Areia";
		case TraitId::ARoseWithThorns:	return "Rosa com Espinhos";
		case TraitId::Pyromaniac:		return "Piromaniaco";
		case TraitId::AvatarOfCold:		return "Avatar do Frio";
		case TraitId::BestDefense:		return "A Melhor Defesa...";
		case TraitId::GrimDeal:			return "Acordo Sombrio";
		case TraitId::HolyAura:			return "Aura Sagrada";
		case TraitId::Strafer:			return "Atirador Movel";
		case TraitId::PiercingShot:		return "Tiro Perfurante";
		case TraitId::Destroyer:		return "Destruidor";
		case TraitId::ChromaticSkin:	return "Pele Cromatica";
		case TraitId::Tormentor:		return "Atormentador";
		case TraitId::Armadillo:		return "Tatu";
		case TraitId::BloodyMess:		return "Carnificina";
		case TraitId::Bestiarius:		return "Bestiarius";
		case TraitId::Petrifier:		return "Petrificador";
		case TraitId::DarkPact:			return "Pacto Sombrio";
		case TraitId::Toxic_at_Heart:	return "Coracao Toxico";
		case TraitId::Hunger:			return "Fome";
		case TraitId::Fechtmeister:		return "Fechtmeister";
		case TraitId::WreckingBlock:	return "Bloqueio Brutal";
		case TraitId::TwoTowers:		return "Duas Torres";
		case TraitId::PuncturingStab:	return "Estocada Perfurante";
		case TraitId::BloodAndSand:		return "Sangue e Areia";
		case TraitId::BloodForBlood:	return "Sangue por Sangue";
		case TraitId::BigFrame:			return "Corpo Grande";
		case TraitId::CrossbowTraining:	return "Treino com Besta";
		case TraitId::BlisteredSkin:	return "Pele Calejada";
		case TraitId::Cleric:			return "Clerigo";
		case TraitId::Bloodless:		return "Sem Sangue";
		case TraitId::Engineer:			return "Engenheiro";
		case TraitId::Necropathy:		return "Necropatia";
		case TraitId::TreasureHunter:	return "Cacador de Tesouros";
		case TraitId::BreakerOfStones:	return "Quebra-Pedras";
		case TraitId::Cannibalism:		return "Canibalismo";
		case TraitId::Black_Witchery:	return "Bruxaria Negra";
		case TraitId::Axepertise:		return "Pericia com Machado";
		case TraitId::MonkeyGrip:		return "Pegada de Macaco";
		case TraitId::Zealot:			return "Zelote";
		case TraitId::Adrenaline:		return "Adrenalina";
        case TraitId::Sisyphean:		return "Tarefa de Sisifo";
		case TraitId::BendTheRules:		return "Quebrar as Regras";
        case TraitId::Barbarian:		return "Barbaro";
        case TraitId::Psion:		    return "Psion";
        case TraitId::Devastator:	    return "Devastador";
        case TraitId::Thrill_Seeker:    return "Cacador de Emocoes";
        case TraitId::Psychotic:        return "Psicotico";
        case TraitId::SmallFrame:       return "Corpo Pequeno";
        case TraitId::BlueBlood:        return "Sangue Azul";
        case TraitId::Juggernaut:       return "Colosso";
        case TraitId::Prodigy:          return "Prodigio";
        case TraitId::Insensitive:      return "Insensivel";
        case TraitId::Hydramancer:      return "Hidromante";
        case TraitId::IronFisted:       return "Punho de Ferro";
        case TraitId::Paladin:          return "Paladino";
        case TraitId::Unshakable:       return "Inabalavel";
        case TraitId::ResoluteGuard:    return "Guarda Resoluta";
        case TraitId::Ranger:           return "Patrulheiro";
        case TraitId::Mamluk:           return "Mamluk";
        case TraitId::Vigorous:         return "Vigoroso";
        case TraitId::Pistoleer:        return "Pistoleiro";
        case TraitId::FearTheReaper:    return "Tema o Ceifador";
        case TraitId::NastyDisposition: return "Mau Temperamento";
        case TraitId::CrowdSeeker:      return "Busca Multidoes";
        case TraitId::Stoneform:        return "Forma de Pedra";
        case TraitId::LitheBuild:       return "Corpo Agil";
        case TraitId::BloodOath:        return "Juramento de Sangue";
        case TraitId::ManaFlux:         return "Fluxo de Mana";
        case TraitId::Coinbound:        return "Preso ao Ouro";
        case TraitId::Doomwhorl:        return "Redemoinho Fatal";
        case TraitId::LordOfTheRings:   return "Senhor dos Aneis";
        case TraitId::Crupellarius:     return "Crupellarius";
        case TraitId::Fatality:         return "Fatalidade";
        case TraitId::Abnegation:       return "Abnegacao";
        case TraitId::Giant:            return "Gigante";
        case TraitId::Feral:            return "Selvagem";
    }
}

//----- (th2) ------------------------------------------------------------
const char* GetTraitBenefitDescription( TraitId id )
{
    switch( id )
    {
    default:
    case TraitId::NoTrait:			return  "";
    case TraitId::Gifted:			return  "+5 atributos base e +25 nos limites";
    case TraitId::Kamikaze:			return  "+CLVL de precisao";
    case TraitId::HeavyHanded:		return  "+(80%CLVL) dano fisico corpo a corpo";
    case TraitId::Skilled:			return  "+CLVL+(CLVL^2/150) em todos atributos";
    case TraitId::Barbarism:		return  "limite de resistencia magica sobe para 90%";
    case TraitId::Finesse:			return  "+(CLVL/27+10)% chance de critico";
    case TraitId::Survivor:			return  "+CLVL*2 regeneracao de vida";
    case TraitId::Weird:			return  "+(CLVLx2) vida";
    case TraitId::OldFashioned:		return  "+armadura e dano por CLVL; +40 DEX maxima";
    case TraitId::Domesticated:		return  "+30% experiencia";
    case TraitId::Rabid:			return  "dobra o dano base corpo a corpo";
    case TraitId::Bruiser:			return  "+150 FOR maxima base";
    case TraitId::Negotiant:		return  "+10% desconto e melhores itens nas lojas";
    case TraitId::Leper:			return  "+75 DEX maxima e +75 MAG maxima";
    case TraitId::Rudiarius:		return  "comeca com +750 ouro";
    case TraitId::Scrounger:		return  "+50% Magic Find";
    case TraitId::Adventurer:		return  "+1 ponto de atributo por nivel";
    case TraitId::ThickSkinned:		return  "+(CLVL/9) resistencia melee e a flechas";
    case TraitId::RatelHide:		return  "-(CLVL/7) DFE";
    case TraitId::Forgetful:		return  "+CLVL^2+100 experiencia";
    case TraitId::WildSorcery:		return  "+30% dano de todas as magias";
    case TraitId::Cautious:			return  "+30% dano fora de queima-roupa";
	case TraitId::OldHabit:			return  "+200% melee em monstro comum com <=25% vida";
	case TraitId::GoldDigger:		return  "+(2xCLVL) ouro derrubado";
	case TraitId::ArrowDancing:		return  "+(CLVL/2) resistencia a flechas";
	case TraitId::PointBlank:		return  "+65% dano total a queima-roupa";
	case TraitId::FastMetabolism:	return  "+(CLVL/10) regeneracao de vida e mana";
	case TraitId::Bouncer:			return  "+50% dano total corpo a corpo";
	case TraitId::Sandman:			return  "+5 res. melee; limites min/max +10%";
	case TraitId::ARoseWithThorns:	return  "+(CLVL/2) dano de espinhos dos itens";
	case TraitId::Pyromaniac:		return  "+25% dano de frascos de fogo";
	case TraitId::AvatarOfCold:		return  "+25% dano de gelo e resistencia ao frio";
	case TraitId::BestDefense:		return  "+(25+CLVL/15)% dano dos lacaios";
	case TraitId::GrimDeal:			return  "+1 Perk a cada nivel";
	case TraitId::HolyAura:			return  "mortos-vivos proximos sofrem 1+CLVL*MAG/40 DPS";
	case TraitId::Strafer:			return  "Multishot vira 5 flechas com controle manual";
	case TraitId::PiercingShot:		return  "(CLVL/3)% chance de a flecha atravessar";
	case TraitId::Destroyer:		return  "+15% dano total";
	case TraitId::ChromaticSkin:	return  "+(50%CLVL) resistencias magicas";
	case TraitId::Tormentor:		return  "+20% dano elemental das armas";
	case TraitId::Armadillo:		return  "+CLVL/13+2 camadas de Reflect";
	case TraitId::BloodyMess:		return  "sangramento extra; crit melee +(CLVL/2)^2+20";
	case TraitId::Bestiarius:		return  "+30% dano de armas cortantes contra feras";
	case TraitId::Petrifier:		return  "pode ferir Stonecursed (metade do dano)";
	case TraitId::DarkPact:			return  "+CLVL% dano de magias acidas";
	case TraitId::Toxic_at_Heart:	return  "acido queima monstros 80% mais rapido";
	case TraitId::Hunger:			return  "melee rouba +1% da vida e mana totais";
	case TraitId::Fechtmeister:		return  "melee 1 frame mais rapido; +CLVL/2 armadura";
	case TraitId::WreckingBlock:	return  "bloquear melee reflete +(CLVL/2)% dano";
	case TraitId::TwoTowers:		return  "usa 2 escudos; +CLVL/6 chance de bloqueio";
	case TraitId::PuncturingStab:	return  "(CLVL/5)% de ignorar resistencia melee e DFE";
	case TraitId::BloodAndSand:		return  "DFE pode absorver ate 75% do dano melee";
	case TraitId::BloodForBlood:	return  "+30% dano melee com vida abaixo de 40%";
	case TraitId::BigFrame:			return  "+3 vida por nivel e por ponto de VIT";
	case TraitId::CrossbowTraining:	return  "+150% da DEX no dano base com bestas";
	case TraitId::BlisteredSkin:	return  "+1 regen. de vida por 25 de vida maxima";
	case TraitId::Cleric:			return  "+50% dano de magias Sagradas";
	case TraitId::Bloodless:		return  "monstros nao roubam sua vida";
	case TraitId::Engineer:			return  "+(15+CLVL/2)% dano de armadilhas";
	case TraitId::Necropathy:		return  "lacaios causam +20% dano dentro da sua luz";
	case TraitId::TreasureHunter:	return  "monstros unicos derrubam +1 item";
	case TraitId::BreakerOfStones:	return  "lacaios atacam Stonecursed (50% dano)";
	case TraitId::Cannibalism:		return  "lacaios roubam 20% vida em ataques melee";
	case TraitId::Black_Witchery:	return  "magia a distancia muito mais poderosa";
	case TraitId::Axepertise:		return  "usa machados de 2 maos; +2 resistencia a atordoamento";
	case TraitId::MonkeyGrip:		return  "usa arma melee de 2 maos com uma mao";
	case TraitId::Zealot:			return  "ataques ficam 1 frame mais rapidos";
	case TraitId::Adrenaline:		return  "mais regeneracao de vida em combate";
	case TraitId::Sisyphean:		return  "+(2xCLVL) vida e mana atuais";
	case TraitId::BendTheRules:		return  "atributos base podem chegar a 900";
    case TraitId::Barbarian:		return  "+180%CLVL Vantagens; +CLVL/2 resistencia a atordoamento";
    case TraitId::Psion:		    return  "inimigos proximos sofrem 3+CLVL*MAG/100 DPS";
    case TraitId::Devastator:	    return  "acesso a auras elementais que causam dano";
    case TraitId::Thrill_Seeker:    return  "+50% XP quando vida esta abaixo de 35%";
    case TraitId::Psychotic:        return  "Fury deixa voce mais forte e resistente";
    case TraitId::SmallFrame:       return  "autohit melhora: -5% melee, -3% distancia; AC=DEX/3";
    case TraitId::BlueBlood:        return  "+10 atributos iniciais e +10% XP";
    case TraitId::Juggernaut:       return  "100% resistencia a knockback";
    case TraitId::Prodigy:          return  "+1 ponto de Sinergia a cada 4 niveis";
    case TraitId::Insensitive:      return  "+(CLVL/2) classe de armadura";
    case TraitId::Hydramancer:      return  "ganha Hydra com ataques elementais variados";
    case TraitId::IronFisted:       return  "+CLVL dano melee e a distancia";
    case TraitId::Paladin:          return  "ganha poderes magicos e de conjuracao";
    case TraitId::Unshakable:       return  "+(40%CLVL) resistencia a atordoamento";
    case TraitId::ResoluteGuard:    return  "+(60%CLVL) resistencias magicas";
    case TraitId::Ranger:           return  "ganha habilidades exclusivas de Arqueiro";
    case TraitId::Mamluk:           return  "ganha habilidades de guerreiro do deserto";
    case TraitId::Vigorous:         return  "+35% vida maxima";
    case TraitId::Pistoleer:        return  "pode usar pistola como arma";
    case TraitId::FearTheReaper:    return  "+1 Perk a cada nivel";
    case TraitId::NastyDisposition: return  "+(10+CLVL/3) precisao; +(25+CLVL/2)% dano";
    case TraitId::CrowdSeeker:      return  "+25% chance de evitar perda de durabilidade";
    case TraitId::Stoneform:        return  "+CLVL classe de armadura";
    case TraitId::LitheBuild:       return  "+100 DEX maxima; inimigos erram +8%";
    case TraitId::BloodOath:        return  "estados nao alteram regeneracao de vida/mana";
    case TraitId::ManaFlux:         return  "+(1+2xCLVL/21) niveis de magia";
    case TraitId::Coinbound:        return  "+100%CLVL Gold Find";
    case TraitId::Doomwhorl:        return  "resistencia inata a distancia absorve +20%";
    case TraitId::LordOfTheRings:   return  "pode equipar ate 8 aneis";
    case TraitId::Crupellarius:     return  "+limites melee/flecha; +150%CLVL AC; +100 VIT max";
    case TraitId::Fatality:         return  "+10% chance de golpe com 300% de dano";
    case TraitId::Abnegation:       return  "-2 DFE; +(CLVL/3) MDR/ADR/resistencias";
    case TraitId::Giant:            return  "+1 vida por VIT base; +100 VIT maxima";
    case TraitId::Feral:            return  "sem cooldown em magias ofensivas de invocador";
    }
}

//----- (th2) ------------------------------------------------------------
const char* GetTraitPenaltyDescription( TraitId id )
{
    switch( id )
    {
    default:
    case TraitId::NoTrait:			return  "";
    case TraitId::Gifted:			return  "-(CLVLx2) mana";
    case TraitId::Kamikaze:			return  "-(CLVL/3) classe de armadura";
    case TraitId::HeavyHanded:		return  "-(1+CLVL/26) em todos niveis de magia";
    case TraitId::Skilled:			return  "taxa de Perks reduzida em CLVL/2";
    case TraitId::Barbarism:		return  "-(CLVL/5) regeneracao de mana";
    case TraitId::Finesse:			return  "-50% dano base";
    case TraitId::Survivor:			return  "-CLVL em todas resistencias";
    case TraitId::Weird:			return  "magias custam o dobro de mana";
    case TraitId::OldFashioned:		return  "nao pode usar armadura corporal";
    case TraitId::Domesticated:		return  "-1 ponto de atributo por nivel";
    case TraitId::Rabid:			return  "nao pode beber pocoes de vida ou mana";
    case TraitId::Bruiser:			return  "-150 DEX maxima base";
    case TraitId::Negotiant:		return  "-50 VIT maxima base";
    case TraitId::Leper:			return  "NPCs nao falam com voce, exceto Gillian";
    case TraitId::Rudiarius:		return  "comeca com -5 VIT base";
    case TraitId::Scrounger:		return  "-(1+CLVL/15) resistencia a atordoamento";
    case TraitId::Adventurer:		return  "-20% vida e -20% mana";
    case TraitId::ThickSkinned:		return  "-66%CLVL precisao";
    case TraitId::RatelHide:		return  "-35% resistencia a knockback";
    case TraitId::Forgetful:		return  "perde XP constantemente: CLVL^2/10";
    case TraitId::WildSorcery:		return  "nao pode beber pocoes de vida ou mana";
    case TraitId::Cautious:			return  "-50% dano a queima-roupa";
	case TraitId::OldHabit:			return  "+(CLVL/8) dano recebido";
	case TraitId::GoldDigger:		return  "armadura reduzida em 120%CLVL";
	case TraitId::ArrowDancing:		return  "-(CLVL/2) resistencia melee";
	case TraitId::PointBlank:		return  "-25% dano fora de queima-roupa";
	case TraitId::FastMetabolism:	return  "-CLVL resistencia a acido";
	case TraitId::Bouncer:			return  "ataques melee ficam 2 frames mais lentos";
	case TraitId::Sandman:			return  "+(1+CLVL/15)% chance minima de sofrer melee";
	case TraitId::ARoseWithThorns:	return  "-(CLVL/3) chance atual/max de bloqueio";
	case TraitId::Pyromaniac:		return  "DEX nao aumenta classe de armadura";
	case TraitId::AvatarOfCold:		return  "-25% dano de fogo e resistencia ao fogo";
	case TraitId::BestDefense:		return  "-(25+CLVL/15)% vida dos lacaios";
	case TraitId::GrimDeal:			return  "AC, vida, mana, regen, DFE e stun -40%CLVL";
	case TraitId::HolyAura:			return  "-20% experiencia recebida";
	case TraitId::Strafer:			return  "ataques levam +1 frame";
	case TraitId::PiercingShot:		return  "-(2*CLVL) precisao";
	case TraitId::Destroyer:		return  "armas quebram 2x mais rapido";
	case TraitId::ChromaticSkin:	return  "seus ataques nao atordoam monstros";
	case TraitId::Tormentor:		return  "perde totalmente a chance de critico";
	case TraitId::Armadillo:		return  "dano melee reduzido em CLVL-1";
	case TraitId::BloodyMess:		return  "+2% autohit melee";
	case TraitId::Bestiarius:		return  "-25% dano contundente contra mortos-vivos";
	case TraitId::Petrifier:		return  "Stone Curse: cooldown de 60s";
	case TraitId::DarkPact:			return  "regen. de mana reduzida em CLVL/2";
	case TraitId::Toxic_at_Heart:	return  "sem criticos; -40% dano acido";
	case TraitId::Hunger:			return  "monstros ganham mais DFE quanto mais fundo";
	case TraitId::Fechtmeister:		return  "nao pode usar escudos";
	case TraitId::WreckingBlock:	return  "escudos perdem durabilidade 2x mais rapido";
	case TraitId::TwoTowers:		return  "nao usa armas melee; +10% autohit melee";
	case TraitId::PuncturingStab:	return  "-CLVL precisao";
	case TraitId::BloodAndSand:		return  "-(CLVL/5) regeneracao de vida";
	case TraitId::BloodForBlood:	return  "nao ganha vida ao subir de nivel";
	case TraitId::BigFrame:			return  "+3% autohit melee e +2% a distancia";
	case TraitId::CrossbowTraining:	return  "+5% autohit a distancia";
	case TraitId::BlisteredSkin:	return  "limite de resistencia magica fica em 75%";
	case TraitId::Cleric:			return  "-20% dano de outros tipos de magia";
	case TraitId::Bloodless:		return  "voce tambem nao pode roubar vida";
	case TraitId::Engineer:			return  "nao ganha vida/mana ao subir de nivel";
	case TraitId::Necropathy:		return  "-50% regen. base de mana; -CLVL mana";
	case TraitId::TreasureHunter:	return  "Gold/Magic Find -(CLVL/2+75)%";
	case TraitId::BreakerOfStones:	return  "Stone Curse: cooldown de 120s";
	case TraitId::Cannibalism:		return  "lacaios: +9% chance minima de sofrer melee";
	case TraitId::Black_Witchery:	return  "facas de arremesso deixam de existir";
	case TraitId::Axepertise:		return  "nao pode usar armas blunt nem sharp";
	case TraitId::MonkeyGrip:		return  "-(10+CLVL) precisao/AC; -20% acerto maximo";
	case TraitId::Zealot:			return  "-(5+CLVL) precisao; -15% acerto maximo";
	case TraitId::Adrenaline:		return  "regen. de vida cai quando fica parado";
	case TraitId::Sisyphean:		return  "XP total -(75+CLVL/10)%, incluindo Perks/itens";
	case TraitId::BendTheRules:		return  "soma de atributos base limitada a 1400";
    case TraitId::Barbarian:		return  "so usa itens brancos; livros so Fury/Heal/Portal";
    case TraitId::Psion:		    return  "menos mana base e sem regeneracao natural";
    case TraitId::Devastator:	    return  "precisa gastar Perks para obter as auras";
    case TraitId::Thrill_Seeker:	return  "-25% XP quando vida esta acima de 65%";
    case TraitId::Psychotic:	    return  "perde o controle durante Fury";
    case TraitId::SmallFrame:	    return  "res. melee/flecha: -10 atual e -10% maxima";
    case TraitId::BlueBlood:	    return  "-1 ponto de atributo por nivel";
    case TraitId::Juggernaut:	    return  "nao pode aprender Teleport";
    case TraitId::Prodigy:	        return  "niveis base de magia -CLVL/18";
    case TraitId::Insensitive:	    return  "Sinergia so a cada 7 niveis; regen mana -CLVL/9";
    case TraitId::Hydramancer:      return  "maioria das magias ofensivas tem cooldown";
    case TraitId::IronFisted:       return  "critico reduzido em (CLVL/10+1)%";
    case TraitId::Paladin:          return  "nao pode usar malhos nem bestas";
    case TraitId::Unshakable:       return  "-CLVL classe de armadura";
    case TraitId::ResoluteGuard:    return  "-(30%CLVL) resistencia a atordoamento";
    case TraitId::Ranger:           return  "so pode usar arcos";
    case TraitId::Mamluk:           return  "magias ofensivas ficam pouco eficazes";
    case TraitId::Vigorous:         return  "ataques ficam 1 frame mais lentos";
    case TraitId::Pistoleer:        return  "nao pode usar outras armas";
    case TraitId::FearTheReaper:    return  "vida inicial 50; VIT/niveis nao dao vida";
    case TraitId::NastyDisposition: return  "precos dos vendedores ficam 3x maiores";
    case TraitId::CrowdSeeker:      return  "raio de ativacao em cadeia dos monstros +2";
    case TraitId::Stoneform:        return  "VIT nao concede resistencias naturais";
    case TraitId::LitheBuild:       return  "inventario fica pela metade";
    case TraitId::BloodOath:        return  "DFE +(1+CLVL/16)";
    case TraitId::ManaFlux:         return  "-20% mana maxima";
    case TraitId::Coinbound:        return  "todos atributos -CLVL/5";
    case TraitId::Doomwhorl:        return  "+8% autohit no combate a distancia";
    case TraitId::LordOfTheRings:   return  "taxa de Perks reduzida em CLVL/2";
    case TraitId::Crupellarius:     return  "-50% dano base; -100 FOR max; -10 precisao";
    case TraitId::Fatality:         return  "monstros tambem podem dar esse golpe";
    case TraitId::Abnegation:       return  "-40%CLVL regeneracao de vida e mana";
    case TraitId::Giant:            return  "pocoes tem apenas metade do efeito";
    case TraitId::Feral:            return  "sem Teleport; metade da regen natural de mana";
    }
}

//----- (th2) ------------------------------------------------------------
const char* GetTraitDescription( TraitId id )
{
    if( id == TraitId::NoTrait ){
        return "Nenhum traco selecionado";
    }else{
		// Uma unica quebra preserva espaco vertical para os tracos mais longos.
		sprintf(InfoPanelBuffer, "BENEFICIO: %s\nPENALIDADE: %s", GetTraitBenefitDescription(id), GetTraitPenaltyDescription(id) );
        return InfoPanelBuffer;
    }
}

//----- (th2) ------------------------------------------------------------
int GetTraitSpellIcon( TraitId id )
{
    switch( id )
    {
        default:
        case TraitId::NoTrait:			return 27;
        case TraitId::Gifted:			return 138;
        case TraitId::Kamikaze:			return 186;
        case TraitId::HeavyHanded:		return 147;
        case TraitId::Skilled:			return 165;
        case TraitId::Barbarism:		return 143;
        case TraitId::Finesse:			return 167;
        case TraitId::Survivor:			return 179;
        case TraitId::Weird:			return 180;
        case TraitId::OldFashioned:		return 76;
        case TraitId::Domesticated:		return 82;
        case TraitId::Rabid:			return 127;
        case TraitId::Bruiser:			return 124;
        case TraitId::Negotiant:		return 130;
        case TraitId::Leper:			return 181;
        case TraitId::Rudiarius:		return 162;
        case TraitId::Scrounger:		return 146;
        case TraitId::Adventurer:		return 77;
        case TraitId::ThickSkinned:		return 170;
        case TraitId::RatelHide:		return 229;
        case TraitId::Forgetful:		return 223;
        case TraitId::WildSorcery:		return 154;
        case TraitId::Cautious:			return 184;
		case TraitId::OldHabit:			return 213;
		case TraitId::GoldDigger:		return 162;
		case TraitId::ArrowDancing:		return 141;
		case TraitId::PointBlank:		return 216;
		case TraitId::FastMetabolism:	return 155;
		case TraitId::Bouncer:			return 144;
		case TraitId::Sandman:			return 85;
		case TraitId::ARoseWithThorns:	return 78;
		case TraitId::Pyromaniac:		return 136;
		case TraitId::AvatarOfCold:		return 105;
		case TraitId::BestDefense:		return 48;
		case TraitId::GrimDeal:			return 70;
		case TraitId::HolyAura:			return 200;
		case TraitId::Strafer:			return 166;
		case TraitId::PiercingShot:		return 188;
		case TraitId::Destroyer:		return 171;
		case TraitId::ChromaticSkin:	return 214;
		case TraitId::Tormentor:		return 97;
		case TraitId::Armadillo:		return 91;
		case TraitId::BloodyMess:		return 230;
		case TraitId::Bestiarius:		return 156;
		case TraitId::Petrifier:		return 119;
		case TraitId::DarkPact:			return 69;
		case TraitId::Toxic_at_Heart:	return 183;
		case TraitId::Hunger:			return 134;
		case TraitId::Fechtmeister:		return 148;
		case TraitId::WreckingBlock:	return 101;
		case TraitId::TwoTowers:		return 80;
		case TraitId::PuncturingStab:	return 157;
		case TraitId::BloodAndSand:		return 68;
		case TraitId::BloodForBlood:	return 205;
		case TraitId::BigFrame:			return 122;
		case TraitId::CrossbowTraining:	return 185;
		case TraitId::BlisteredSkin:	return 222;
		case TraitId::Cleric:			return 201;
		case TraitId::Bloodless:		return 76;
		case TraitId::Engineer:			return 195;
		case TraitId::Necropathy:		return 64;
		case TraitId::TreasureHunter:	return 44;
		case TraitId::BreakerOfStones:	return 119;
		case TraitId::Cannibalism:		return 134;
		case TraitId::Black_Witchery:	return 32;
		case TraitId::Axepertise:		return 152;
		case TraitId::MonkeyGrip:		return 204;
		case TraitId::Zealot:			return 212;
		case TraitId::Adrenaline:		return 89;
		case TraitId::Sisyphean:		return 117;
		case TraitId::BendTheRules:		return 114;
        case TraitId::Barbarian:		return 189;
        case TraitId::Psion:		    return 208;
        case TraitId::Devastator:	    return 197;
        case TraitId::Thrill_Seeker:	return 128;
        case TraitId::Psychotic:	    return 129;
        case TraitId::SmallFrame:	    return 83;
        case TraitId::BlueBlood:	    return 231;
        case TraitId::Juggernaut:	    return 75;
        case TraitId::Prodigy:	        return 253;
        case TraitId::Insensitive:      return 247;
        case TraitId::Hydramancer:      return 178;
        case TraitId::IronFisted:       return 246;
        case TraitId::Paladin:          return 175;
        case TraitId::Unshakable:       return 227;
        case TraitId::ResoluteGuard:    return 98;
        case TraitId::Ranger:           return 250;
        case TraitId::Mamluk:           return 245;
        case TraitId::Vigorous:         return 240;
        case TraitId::Pistoleer:        return 119;
        case TraitId::FearTheReaper:    return  66;
        case TraitId::NastyDisposition: return 235;
        case TraitId::CrowdSeeker:      return 243;
        case TraitId::Stoneform:        return  73;
        case TraitId::LitheBuild:       return 215;
        case TraitId::BloodOath:        return 254;
        case TraitId::ManaFlux:         return 234;
        case TraitId::Coinbound:        return 251;
        case TraitId::Doomwhorl:        return 232;
        case TraitId::LordOfTheRings:   return 108;
        case TraitId::Crupellarius:     return 209;
        case TraitId::Fatality:         return 244;
        case TraitId::Abnegation:       return 254;
        case TraitId::Giant:            return 206;
        case TraitId::Feral:            return 176;
    }
}

//----- (th2) ------------------------------------------------------------
uint GetRequiredClassMaskForTrait( TraitId id )
{
    switch( id )
    {
        default:
        case TraitId::NoTrait:			return IPCM_ALL_CLASSES;
        case TraitId::Gifted:			return IPCM_ALL_CLASSES;
        case TraitId::Kamikaze:			return IPCM_ANY_WARRIOR
										     | IPCM_ANY_MONK
										     | IPCM_ANY_SAVAGE;
        case TraitId::HeavyHanded:		return IPCM_ANY_WARRIOR
											 | IPCM_ANY_MONK
											 | IPCM_ANY_SAVAGE;
        case TraitId::Skilled:			return IPCM_ALL_CLASSES;
        case TraitId::Barbarism:		return IPCM_ALL_CLASSES;
        case TraitId::Finesse:			return IPCM_ANY_WARRIOR
											 | IPCM_ARCHER
										     | IPCM_SHARPSHOOTER
										     | IPCM_ANY_MONK
										     | IPCM_ROGUE
										     | IPCM_ASSASSIN
										     | IPCM_BERSERKER
											 | IPCM_EXECUTIONER
											 | IPCM_MURMILLO
											 | IPCM_THRAEX
											 | IPCM_DIMACHAERUS
											 | IPCM_SECUTOR | IPCM_DRUID;
        case TraitId::Survivor:			return IPCM_ALL_CLASSES;
        case TraitId::Weird:			return IPCM_ALL_CLASSES;
        case TraitId::OldFashioned:		return IPCM_ANY_GLADIATOR;
        case TraitId::Domesticated:		return IPCM_ALL_CLASSES;
        case TraitId::Rabid:			return IPCM_SAVAGE
											 | IPCM_EXECUTIONER | IPCM_DRUID;
        case TraitId::Bruiser:			return IPCM_SHINOBI
											 | IPCM_THRAEX
											 | IPCM_DIMACHAERUS
											 | IPCM_SECUTOR;
        case TraitId::Negotiant:		return IPCM_ANY_WARRIOR
											 | IPCM_ANY_ARCHER
											 | IPCM_ANY_MONK
											 | IPCM_ANY_ROGUE;
        case TraitId::Leper:			return IPCM_EXECUTIONER;
        case TraitId::Rudiarius:		return IPCM_ANY_GLADIATOR;
        case TraitId::Scrounger:		return IPCM_ALL_CLASSES;
        case TraitId::Adventurer:		return IPCM_ALL_CLASSES;
        case TraitId::ThickSkinned:		return IPCM_ANY_WARRIOR
											 | IPCM_ARCHER
											 | IPCM_SCOUT
											 | IPCM_ANY_MONK
											 | IPCM_ANY_SAVAGE;
        case TraitId::RatelHide:		return IPCM_ANY_WARRIOR
											 | IPCM_ANY_MONK
											 | IPCM_ANY_ROGUE
											 | IPCM_ANY_SAVAGE;
        case TraitId::Forgetful:		return IPCM_ALL_CLASSES;
        case TraitId::WildSorcery:		return IPCM_MAGE
											 | IPCM_ELEMENTALIST
											 | IPCM_WARLOCK | IPCM_DRUID;
        case TraitId::Cautious:			return IPCM_SHARPSHOOTER;
		case TraitId::OldHabit:			return IPCM_EXECUTIONER;
		case TraitId::GoldDigger:		return IPCM_ROGUE;
		case TraitId::ArrowDancing:		return IPCM_SCOUT
											 | IPCM_MONK
											 | IPCM_KENSEI
											 | IPCM_ROGUE
											 | IPCM_BERSERKER
											 | IPCM_DIMACHAERUS;
		case TraitId::PointBlank:		return IPCM_ARCHER;
		case TraitId::FastMetabolism:	return IPCM_ALL_CLASSES;
		case TraitId::Bouncer:			return IPCM_SAVAGE;
		case TraitId::Sandman:			return IPCM_ANY_WARRIOR
											 | IPCM_ANY_MONK
											 | IPCM_IRON_MAIDEN
											 | IPCM_ANY_SAVAGE;
		case TraitId::ARoseWithThorns:	return IPCM_IRON_MAIDEN;
		case TraitId::Pyromaniac:		return IPCM_BOMBARDIER;
		case TraitId::AvatarOfCold:		return IPCM_ELEMENTALIST;
		case TraitId::BestDefense:		return IPCM_ANY_SUMMONER;
		case TraitId::GrimDeal:			return IPCM_ANY_ARCHER
											 | IPCM_WARRIOR
											 | IPCM_INQUISITOR
											 | IPCM_GUARDIAN
											 | IPCM_MAGE
											 | IPCM_ELEMENTALIST
											 | IPCM_ANY_SUMMONER
											 | IPCM_ANY_MONK
											 | IPCM_ANY_ROGUE
											 | IPCM_ANY_GLADIATOR
											 | IPCM_SAVAGE
											 | IPCM_BERSERKER | IPCM_DRUID;
		case TraitId::HolyAura:			return IPCM_TEMPLAR;
		case TraitId::Strafer:			return IPCM_SCOUT;
		case TraitId::PiercingShot:		return IPCM_SHARPSHOOTER;
		case TraitId::Destroyer:		return IPCM_SAVAGE;
		case TraitId::ChromaticSkin:	return IPCM_GUARDIAN 
											 | IPCM_TEMPLAR 
											 | IPCM_SHUGOKI 
											 | IPCM_ASSASSIN | IPCM_DRUID;
		case TraitId::Tormentor:		return IPCM_INQUISITOR;
		case TraitId::Armadillo:		return IPCM_BERSERKER;
		case TraitId::BloodyMess:		return IPCM_DIMACHAERUS;
		case TraitId::Bestiarius:		return IPCM_SECUTOR;
		case TraitId::Petrifier:		return IPCM_SHINOBI;
		case TraitId::DarkPact: 		return IPCM_WARLOCK;
		case TraitId::Toxic_at_Heart: 	return IPCM_BOMBARDIER;
		case TraitId::Hunger: 			return IPCM_SHUGOKI;
		case TraitId::Fechtmeister:		return IPCM_WARRIOR;
		case TraitId::WreckingBlock:	return IPCM_IRON_MAIDEN;
		case TraitId::TwoTowers:		return IPCM_IRON_MAIDEN;
		case TraitId::PuncturingStab:	return IPCM_ASSASSIN;
		case TraitId::BloodAndSand:		return IPCM_MURMILLO;
		case TraitId::BloodForBlood:	return IPCM_THRAEX;
		case TraitId::BigFrame:			return IPCM_ROGUE;
		case TraitId::CrossbowTraining:	return IPCM_GUARDIAN;
		case TraitId::BlisteredSkin:	return IPCM_KENSEI;
		case TraitId::Cleric:			return IPCM_MAGE;
		case TraitId::Bloodless:		return IPCM_MONK;
		case TraitId::Engineer:			return IPCM_TRAPPER;
		case TraitId::Necropathy:		return IPCM_NECROMANCER;
		case TraitId::TreasureHunter:	return IPCM_ALL_CLASSES;
		case TraitId::BreakerOfStones:	return IPCM_DEMONOLOGIST;
		case TraitId::Cannibalism:		return IPCM_BEASTMASTER;
		case TraitId::Black_Witchery:	return IPCM_ASSASSIN;
		case TraitId::Axepertise:		return IPCM_ROGUE;
		case TraitId::MonkeyGrip:		return IPCM_SAVAGE;
		case TraitId::Zealot:			return IPCM_INQUISITOR
											 | IPCM_GUARDIAN
											 | IPCM_TEMPLAR
											 | IPCM_ARCHER
											 | IPCM_SCOUT 
											 | IPCM_ANY_MONK
											 | IPCM_ROGUE
											 | IPCM_ASSASSIN
											 | IPCM_BERSERKER
											 | IPCM_EXECUTIONER
											 | IPCM_THRAEX
											 | IPCM_SECUTOR; 
		case TraitId::Adrenaline:		return IPCM_BERSERKER;
		case TraitId::Sisyphean:		return IPCM_ANY_WARRIOR & ~IPCM_TEMPLAR
											 | IPCM_ANY_ARCHER
											 | IPCM_ANY_MAGE & ~IPCM_MAGE
											 | IPCM_ANY_MONK
											 | IPCM_ANY_ROGUE
											 | IPCM_ANY_SAVAGE;
		case TraitId::BendTheRules:		return IPCM_ANY_WARRIOR
											 | IPCM_ANY_ARCHER 
											 | IPCM_ANY_MAGE// mor: might wanna remove this as magi have 900 cap anyway
											 | IPCM_MONK 
											 | IPCM_KENSEI 
											 | IPCM_SHUGOKI 
											 | IPCM_ANY_ROGUE 
											 | IPCM_SAVAGE 
											 | IPCM_BERSERKER;
        case TraitId::Barbarian:		return IPCM_SAVAGE;
        case TraitId::Psion:		    return IPCM_MAGE;
        case TraitId::Devastator:	    return IPCM_INQUISITOR;
        case TraitId::Thrill_Seeker:    return IPCM_SCOUT
                                             | IPCM_KENSEI
                                             | IPCM_SHUGOKI
                                             | IPCM_ROGUE
                                             | IPCM_IRON_MAIDEN
                                             | IPCM_SAVAGE
                                             | IPCM_BERSERKER
                                             | IPCM_DIMACHAERUS;
        case TraitId::Psychotic:        return IPCM_BERSERKER;
        case TraitId::SmallFrame:       return IPCM_WARRIOR | IPCM_INQUISITOR | IPCM_TEMPLAR
                                             | IPCM_ANY_ARCHER
                                             | IPCM_ANY_MAGE
                                             | IPCM_MONK | IPCM_KENSEI | IPCM_SHINOBI
                                             | IPCM_ASSASSIN | IPCM_BOMBARDIER
                                             | IPCM_SECUTOR | IPCM_DRUID;
        case TraitId::BlueBlood:		return IPCM_ALL_CLASSES & ~IPCM_ANY_SAVAGE;
        case TraitId::Juggernaut:		return IPCM_ANY_WARRIOR | IPCM_ANY_MONK | IPCM_ANY_SAVAGE & ~IPCM_SAVAGE;
        case TraitId::Prodigy:		    return IPCM_ALL_CLASSES;
        case TraitId::Insensitive:		return IPCM_ALL_CLASSES & ~IPCM_ANY_MAGE;
        case TraitId::Hydramancer:      return IPCM_WARLOCK;
        case TraitId::IronFisted:       return IPCM_WARRIOR | IPCM_TEMPLAR | IPCM_ARCHER | IPCM_ANY_MONK 
                                             | IPCM_ROGUE | IPCM_IRON_MAIDEN | IPCM_BERSERKER | IPCM_EXECUTIONER | IPCM_ANY_GLADIATOR;
        case TraitId::Paladin:          return IPCM_TEMPLAR;
        case TraitId::Unshakable:		return IPCM_ALL_CLASSES;
        case TraitId::ResoluteGuard:	return IPCM_WARRIOR | IPCM_INQUISITOR
                                               | IPCM_ANY_ARCHER
                                               | IPCM_ANY_MAGE
                                               | IPCM_MONK | IPCM_KENSEI | IPCM_SHINOBI
                                               | IPCM_ROGUE | IPCM_IRON_MAIDEN | IPCM_BOMBARDIER
                                               | IPCM_ANY_SAVAGE;
        case TraitId::Ranger:		        return IPCM_WARRIOR;
        case TraitId::Mamluk:		        return IPCM_ELEMENTALIST;
        case TraitId::Vigorous:		        return IPCM_ANY_WARRIOR
                                               | IPCM_ARCHER | IPCM_TRAPPER
                                               | IPCM_SHUGOKI
                                               | IPCM_ASSASSIN /* | IPCM_IRON_MAIDEN*/
                                               | IPCM_BERSERKER/* | IPCM_EXECUTIONER*/
                                               | IPCM_THRAEX | IPCM_SECUTOR | IPCM_DRUID;
        case TraitId::Pistoleer:            return IPCM_GUARDIAN;
        case TraitId::FearTheReaper:        return IPCM_INQUISITOR|IPCM_GUARDIAN|IPCM_ANY_MONK
                                               | IPCM_BERSERKER | IPCM_ANY_GLADIATOR | IPCM_DRUID;
        case TraitId::NastyDisposition:     return IPCM_WARRIOR|IPCM_GUARDIAN|IPCM_ARCHER|IPCM_SHARPSHOOTER|IPCM_TRAPPER|IPCM_ANY_MONK|IPCM_ANY_SAVAGE;
        case TraitId::CrowdSeeker:          return IPCM_ALL_CLASSES;
        case TraitId::Stoneform:            return IPCM_ANY_WARRIOR | IPCM_ANY_ARCHER | IPCM_ANY_MONK 
                                                | IPCM_ASSASSIN | IPCM_IRON_MAIDEN | IPCM_ANY_SAVAGE & ~IPCM_SAVAGE;
        case TraitId::LitheBuild:           return IPCM_ANY_WARRIOR|IPCM_ANY_ARCHER|IPCM_ANY_MONK|IPCM_ANY_ROGUE & ~IPCM_IRON_MAIDEN|IPCM_ANY_SAVAGE;
        case TraitId::BloodOath:            return IPCM_WARRIOR | IPCM_INQUISITOR | IPCM_ANY_ARCHER | IPCM_MAGE | IPCM_ELEMENTALIST| IPCM_MONK | IPCM_SHINOBI 
                                                | IPCM_ANY_ROGUE | IPCM_SAVAGE | IPCM_ANY_GLADIATOR & ~IPCM_THRAEX | IPCM_DRUID;
        case TraitId::ManaFlux:             return IPCM_MAGE | IPCM_WARLOCK | IPCM_ANY_SUMMONER | IPCM_DRUID;
        case TraitId::Coinbound:            return IPCM_ANY_WARRIOR | IPCM_ANY_ARCHER | IPCM_ANY_MAGE | IPCM_ANY_ROGUE & ~IPCM_ROGUE | IPCM_ANY_MONK
                                                | IPCM_SAVAGE | IPCM_EXECUTIONER | IPCM_BERSERKER;
        case TraitId::Doomwhorl:            return IPCM_ANY_WARRIOR & ~IPCM_WARRIOR | IPCM_ANY_ARCHER | IPCM_ANY_MAGE 
                                                | IPCM_ANY_MONK | IPCM_ANY_SAVAGE | IPCM_BOMBARDIER | IPCM_ASSASSIN | IPCM_DRUID;
        case TraitId::LordOfTheRings:       return IPCM_MONK;
        case TraitId::Crupellarius:         return IPCM_MURMILLO;
        case TraitId::Fatality:             return IPCM_ANY_WARRIOR & ~IPCM_INQUISITOR | IPCM_ANY_ARCHER & ~IPCM_SCOUT 
                                                | IPCM_ANY_MONK & ~IPCM_MONK | IPCM_ROGUE | IPCM_ASSASSIN | IPCM_ANY_SAVAGE;
        case TraitId::Abnegation:           return IPCM_TEMPLAR;
        case TraitId::Giant:                return IPCM_ANY_WARRIOR | IPCM_ANY_ARCHER | IPCM_ANY_MONK & ~IPCM_SHINOBI | IPCM_ANY_ROGUE & ~IPCM_ROGUE | IPCM_ANY_SAVAGE;
        case TraitId::Feral:                return IPCM_BEASTMASTER;
    }
}

//----- (th2) ------------------------------------------------------------
TRAIT_GROUP_MASK GetTraitGroups( TraitId id )
{
    switch( id )
    {
        default:
        case TraitId::NoTrait:          return TGM_NONE;
        case TraitId::Gifted:           return TGM_MORE_MAX_STATS;
        case TraitId::Kamikaze:         return TGM_NONE;
        case TraitId::HeavyHanded:      return TGM_DMG_UP;
        case TraitId::Skilled:          return TGM_PERK_POINTS_DOWN;
        case TraitId::Barbarism:        return TGM_MAX_REZ_UP;
        case TraitId::Finesse:          return TGM_CRIT_UP;
        case TraitId::Survivor:         return TGM_REZ_DOWN;
        case TraitId::Weird:            return TGM_WEIRD;
        case TraitId::OldFashioned:     return TGM_OLDFASH;
        case TraitId::Domesticated:     return TGM_STATS_LESS;
        case TraitId::Rabid:            return TGM_RABID;
        case TraitId::Bruiser:          return TGM_BRUISER;
        case TraitId::Negotiant:        return TGM_MORE_MAX_STATS;
        case TraitId::Leper:            return TGM_LEPER;
        case TraitId::Rudiarius:        return TGM_NONE;
        case TraitId::Scrounger:        return TGM_MF_MORE;
        case TraitId::Adventurer:       return TGM_STATS_MORE;
        case TraitId::ThickSkinned:     return TGM_NONE;
        case TraitId::RatelHide:        return TGM_KB_DOWN;
        case TraitId::Forgetful:        return TGM_MORE_XP;
        case TraitId::WildSorcery:      return TGM_SPELLS_ON;
        case TraitId::Cautious:         return TGM_NONE;
		case TraitId::OldHabit:         return TGM_NONE;
		case TraitId::GoldDigger:       return TGM_NONE;
		case TraitId::ArrowDancing:     return TGM_NONE;
		case TraitId::PointBlank:	    return TGM_NONE;
		case TraitId::FastMetabolism:	return TGM_FAST_MET;
		case TraitId::Bouncer:		    return TGM_BOUNCE;
		case TraitId::Sandman:		    return TGM_MELEE_AUTOHIT_UP;
		case TraitId::ARoseWithThorns:	return TGM_NONE;
		case TraitId::Pyromaniac:		return TGM_NONE;
		case TraitId::AvatarOfCold:		return TGM_SPELLS_ON;
		case TraitId::BestDefense:		return TGM_NONE;
		case TraitId::GrimDeal:			return TGM_PERK_POINTS_UP;
		case TraitId::HolyAura:			return TGM_NONE;
		case TraitId::Strafer:			return TGM_ATK_SPD_DOWN;
		case TraitId::PiercingShot:		return TGM_NONE;
		case TraitId::Destroyer:		return TGM_DESTROY;
		case TraitId::ChromaticSkin:	return TGM_REZ_UP;
		case TraitId::Tormentor:		return TGM_CRIT_DOWN;
		case TraitId::Armadillo:		return TGM_DMG_DOWN;
		case TraitId::BloodyMess:		return TGM_NONE;
		case TraitId::Bestiarius:		return TGM_NONE;
		case TraitId::Petrifier:		return TGM_NONE;
		case TraitId::DarkPact:			return TGM_NONE;
		case TraitId::Toxic_at_Heart:	return TGM_NONE;
		case TraitId::Hunger:			return TGM_NONE;
		case TraitId::Fechtmeister:		return TGM_MELEE_AUTOHIT_DOWN;
		case TraitId::WreckingBlock:	return TGM_NONE;
		case TraitId::TwoTowers:		return TGM_NONE;
		case TraitId::PuncturingStab:	return TGM_NONE;
		case TraitId::BloodAndSand:		return TGM_NONE;
		case TraitId::BloodForBlood:	return TGM_NONE;
		case TraitId::BigFrame:			return TGM_NONE;
        case TraitId::CrossbowTraining:	return TGM_NO_PISTOL;
		case TraitId::BlisteredSkin:	return TGM_MAX_REZ_DOWN;
		case TraitId::Cleric:			return TGM_NONE;
		case TraitId::Bloodless:		return TGM_NONE;
		case TraitId::Engineer:			return TGM_NONE;
		case TraitId::Necropathy:		return TGM_NONE;
		case TraitId::TreasureHunter:	return TGM_TR_HUNTER;
		case TraitId::BreakerOfStones:	return TGM_NONE;
		case TraitId::Cannibalism:		return TGM_NONE;
		case TraitId::Black_Witchery:	return TGM_NONE;
		case TraitId::Axepertise:		return TGM_NONE;
		case TraitId::MonkeyGrip:		return TGM_NONE;
		case TraitId::Zealot:			return TGM_ATK_SPD_UP;
		case TraitId::Adrenaline:		return TGM_NONE;
		case TraitId::Sisyphean:		return TGM_LESS_XP;
		case TraitId::BendTheRules:		return TGM_MANUAL_MAX_STATS;
        case TraitId::Barbarian:		return TGM_BARBARIAN;
        case TraitId::Psion:		    return TGM_PSION;
        case TraitId::Devastator:	    return TGM_NONE;
        case TraitId::Thrill_Seeker:    return TGM_NONE;
        case TraitId::Psychotic:        return TGM_NONE;
        case TraitId::SmallFrame:       return TGM_SMALL_FRAME;
        case TraitId::BlueBlood:        return TGM_NONE;
        case TraitId::Juggernaut:       return TGM_KB_UP;
        case TraitId::Prodigy:          return TGM_SYNS_UP;
        case TraitId::Insensitive:      return TGM_SYNS_DOWN;
        case TraitId::Hydramancer:      return TGM_NONE;
        case TraitId::IronFisted:       return TGM_CRIT_DOWN;
        case TraitId::Paladin:          return TGM_PAL;
        case TraitId::Unshakable:       return TGM_AC_DOWN;
        case TraitId::ResoluteGuard:    return TGM_REZ_UP;
        case TraitId::Ranger:           return TGM_MELEE_AUTOHIT_UP;
        case TraitId::Mamluk:           return TGM_SPELLS_OFF;
        case TraitId::Vigorous:         return TGM_ATK_SPD_DOWN;
        case TraitId::Pistoleer:        return TGM_PISTOL;
        case TraitId::FearTheReaper:    return TGM_FTR;
        case TraitId::NastyDisposition: return TGM_NASTY;
        case TraitId::CrowdSeeker:      return TGM_NONE;
        case TraitId::Stoneform:        return TGM_AC_UP;
        case TraitId::LitheBuild:       return TGM_LITHE;
        case TraitId::BloodOath:        return TGM_BLOOD_OATH;
        case TraitId::ManaFlux:         return TGM_NONE;
        case TraitId::Coinbound:        return TGM_COINBOUND;
        case TraitId::Doomwhorl:        return TGM_DOOMWHORL;
        case TraitId::LordOfTheRings:   return TGM_LOTR;
        case TraitId::Crupellarius:     return TGM_CRUPELLARIUS;
        case TraitId::Fatality:         return TGM_NONE;
        case TraitId::Abnegation:       return TGM_ABNEG;
        case TraitId::Giant:            return TGM_GIANT;
        case TraitId::Feral:            return TGM_NONE;
    }
}

//----- (th2) ------------------------------------------------------------
Portrait GetTraitPicId( TraitId id )
{
    if( id == TraitId::NoTrait ){
        return PcxHeros[50];
    }else{
        return PcxHeros[81 + (int)id - 1];
    }
}

//----- (th2) ------------------------------------------------------------
std::vector<TraitId> CalcAvailableTraitList( PLAYER_FULL_CLASS fullClass, decltype(Player::traits) traits )
{
    const uint playerFullClassMask = (1u << static_cast<uint>( fullClass ) );
    
    std::vector<TraitId> result;
    
    auto isTraitExcluded = [&]( TraitId traitId ) -> bool
    {
		// Nothing to exclude if other trait is not selected
        if( traitId == TraitId::NoTrait ) return false;
        // Exclude the same trait
        if( has(traits, traitId) ) return true;

		// Conditions for specific traits
		switch( traitId ){
            case TraitId::Fatality:
		    case TraitId::CrowdSeeker: if( IsMultiplayer() ) return true;
		}

        // Exclude trait if it is from groups that conflicted with other trait groups !! Need to dig deeper here. Much more easier way to exclude trait from trait list after picking up first one
        auto groups = GetTraitGroups( traitId );
		for(auto& trait: traits) groups |= GetTraitGroups(trait);
		if( std::any_of( TraitsExcludedCombinations.begin(), TraitsExcludedCombinations.end(),
                         [groups]( auto excluded ){ return (groups & excluded) == excluded; } ) ){
            return true;
        }
        // Not exclude otherwise
        return false;
    };
    
    for( int i = 0, ie = int(TraitId::TRAIT_COUNT); i < ie; ++i ){
        const auto traitId = static_cast<TraitId>( i );
        const uint requiredClassMask = GetRequiredClassMaskForTrait( traitId );
        if( requiredClassMask & playerFullClassMask ){
            if( !isTraitExcluded( traitId ) ){
                result.push_back( traitId );
            }
        }
    }
    
    return result;
}

//----- (th2) ------------------------------------------------------------
void __fastcall SetTraitInfoText( HWND parent, CharSaveInfo* saveInfo, TraitId traitId, int buttonId )
{
    ShowWindowList( parent, CharParamNameList, SW_HIDE );
    ShowWindowList( parent, CharParamValueList, SW_HIDE );
    ShowWindowList( parent, ClassDescriptionList, SW_SHOW );
    
    Portrait portrait = PcxHeros[5];
    const char* description = "";
    
    // Now we use just hero image
    portrait = getHeroPortrait(saveInfo);
    
    switch(buttonId){
	case ID_TRAITS_CONTINUE:
		description = "Escolha ate 4 tracos. E opcional. Eles ficam no personagem para sempre e podem ativar ou desativar Game Changers, Perks e Sinergias.";
		break;
    case ID_SELECT_TRAIT_1 or ID_SELECT_TRAIT_2 or ID_SELECT_TRAIT_3 or ID_SELECT_TRAIT_4:
		description = GetTraitDescription( saveInfo->Traits[buttonId - ID_SELECT_TRAIT_1] );
		portrait    = GetTraitPicId      ( saveInfo->Traits[buttonId - ID_SELECT_TRAIT_1] );
		break;
	default:
		description = GetTraitDescription( traitId );
		portrait    = GetTraitPicId      ( traitId );
		break;
    }

	//const int BUFFER_SIZE = 256;
	//char buffer[ BUFFER_SIZE ];
	//LoadStringA( HInstance, descriptionIndex, buffer, BUFFER_SIZE );
	//description = buffer;

    DrawReadableTextToElem( parent, ID_CLASS_DESCRIPTION, description );
    
    HWND portraitWin = GetDlgItem( parent, ID_PLAYER_PORTRAIT );
    RECT rect;
    InvalidateRect( portraitWin, 0, 0 );
    GetClientRect( portraitWin, &rect );
    AdjustScrollRect( &rect, 0, rect.bottom * portrait.id );
	SDlgSetBitmap( portraitWin, 0, "Static", -1, 1, portrait.pcx->data, &rect, portrait.pcx->size.cx, portrait.pcx->size.cy, -1 );
}

//----- (th2) ------------------------------------------------------------
void TraitSelectButtonRefresh( const HWND hdlg, int buttonId, TraitId traitId )
{
    if( const HWND btn = GetDlgItem( hdlg, buttonId ); btn ){
        if( auto textWin = (TextWin*) GetWindowLongA( btn, GWL_USERDATA ); textWin ){
            WriteTextToElemData( textWin, GetTraitName( traitId ) );
        }
    }
};

//----- (th2) ------------------------------------------------------------
void TraitSelectNextTrait( const HWND hdlg, const HWND button, int order )
{
    const auto& buttonsOrder = ( order > 0 ) ? nextTraitOrder : prevTraitOrder;
    HWND currentButton = button;
    for( auto i{ 0u }, ie{ buttonsOrder.size() }; i < ie; ++i ){
        currentButton = GetDlgItem( hdlg, buttonsOrder[ GetWindowLongA( currentButton, GWL_ID ) - ID_TRAIT_1 ] );
        if( IsWindowEnabled( currentButton ) ){
            SetFocus( currentButton );
            break;
        }
    }
}

//----- (th2) ------------------------------------------------------------
int GetAvailableTraitCount()
{
    return static_cast<int>( TraitsAvailableList.size() );
}

//----- (th2) ------------------------------------------------------------
void __fastcall ResetTraitButtons( HWND hdlg, const int topIndex )
{
    for( int i = 0; TraitButtonList[i] != 0; ++i ){
        int saveButtonId = TraitButtonList[i];
        HWND saveButton = GetDlgItem( hdlg, saveButtonId );
        if( saveButton ){
            const int currentTraitIndex = topIndex + i;
            if( currentTraitIndex < GetAvailableTraitCount() ){
                EnableWindow( saveButton, true );
                if( auto traitWin = (TraitWin*) GetWindowLongA( saveButton, GWL_USERDATA ); traitWin ){
                    WriteTextToElemData( (TextWin *) traitWin, GetTraitName( TraitsAvailableList[currentTraitIndex] ) );
                    traitWin->traitIndex = (void*)currentTraitIndex;
                }
            }else{
                EnableWindow( saveButton, false );
            }
        }
    }
    ResetButtonText( hdlg, TraitButtonList, 2, 1 );
}

//----- (th2) ------------------------------------------------------------
void TraitRefreshCurrentTraitInfo( HWND hdlg, int button )
{
    if( const HWND activeElem = GetDlgItem( hdlg, button ); activeElem ){
        if( const auto traitWin = (TraitWin *)GetWindowLongA( activeElem, GWL_USERDATA ); traitWin ){
            const auto buttonId = GetWindowLongA( activeElem, GWL_ID );
            SelectedTraitId = TraitsAvailableList[(int)traitWin->traitIndex];
            SetTraitInfoText( GetParent( hdlg ), &NewSaveInfo, SelectedTraitId, buttonId );
        }
    }
}

//----- (th2) ------------------------------------------------------------
int __fastcall GetTraitElemIndex( HWND elem )
{
    int result = 0;
    if( elem ){
        if( auto* traitWin = (TraitWin *) GetWindowLongA( elem, GWL_USERDATA ); traitWin ){
            return (int)traitWin->traitIndex;
        }
    }
    return result;
}

//----- (th2) ------------------------------------------------------------
void TraitRefreshScrollState( const HWND hdlg )
{
    SetScrollOnElem( hdlg, ID_SCROLL, GetAvailableTraitCount(), GetTraitElemIndex( GetFocus() ) );
}

//----- (th2) ------------------------------------------------------------
void __fastcall TraitPageDown( const HWND button )
{
    const HWND hdlg = GetParent( button );
    if( !hdlg ){
        return;
    }
    
    const HWND firstBut = GetDlgItem( hdlg, ID_TRAIT_1 );
    if( !firstBut ){
        return;
    }
    
    auto traitWin = (TraitWin *) GetWindowLongA( GetDlgItem( hdlg, ID_TRAIT_6 ), GWL_USERDATA );
    if( !traitWin ){
        return;
    }
    
    if( auto traitIndex = (int)traitWin->traitIndex; traitIndex + 1 < GetAvailableTraitCount() ){
        const int topSaveIndex = GetTraitElemIndex( firstBut );
        const int nextTopTraitIndex = std::min( topSaveIndex + 6, GetAvailableTraitCount() - 6 );
        PlaySoundTitleMove();
        ResetTraitButtons( hdlg, nextTopTraitIndex );
        TraitRefreshCurrentTraitInfo( hdlg, GetWindowLongA( button, GWL_ID ) );
        TraitRefreshScrollState( hdlg );
    }else{
        TraitSelectNextTrait( hdlg, firstBut, -1 );
    }
}

//----- (th2) ------------------------------------------------------------
void __fastcall TraitPageUp( const HWND button )
{
    const auto hdlg = GetParent( button );
    if( !hdlg ){
        return;
    }
    
    const HWND firstBut = GetDlgItem( hdlg, ID_TRAIT_1 );
    if( !firstBut ){
        return;
    }
    
    const auto traitWin = (const TraitWin *) GetWindowLongA( firstBut, GWL_USERDATA );
    if( !traitWin ){
        return;
    }
    
    if( const auto traitIndex = (int)traitWin->traitIndex; traitIndex == 0 ){
        const auto lastBut = GetDlgItem( hdlg, ID_TRAIT_6 );
        TraitSelectNextTrait( hdlg, lastBut, 1 );
    }else{
        const int topSaveIndex = GetTraitElemIndex( firstBut );
        const int nextTopTraitIndex = std::max( topSaveIndex - 6, 0 );
        PlaySoundTitleMove();
        ResetTraitButtons( hdlg, nextTopTraitIndex );
        TraitRefreshCurrentTraitInfo( hdlg, GetWindowLongA( button, GWL_ID ) );
        TraitRefreshScrollState( hdlg );
    }
}

//----- (th2) ------------------------------------------------------------
void __fastcall TraitDown( const HWND button )
{
    const auto hdlg = GetParent( button );
    
    if( auto traitWin = (TraitWin *) GetWindowLongA( button, GWL_USERDATA ); traitWin ){
        if( auto traitIndex = (int)traitWin->traitIndex; traitIndex + 1 < GetAvailableTraitCount() ){
            if( GetWindowLongA( button, GWL_ID ) < ID_TRAIT_6 ){
                TraitSelectNextTrait( hdlg, button, 1 );
            }else{
                if( auto newBut = GetDlgItem( hdlg, ID_TRAIT_2 ); newBut ){
                    if( auto newWin = (TraitWin*)GetWindowLongA( newBut, GWL_USERDATA ); newWin ){
                        const auto nextTopTraitIndex = (int)newWin->traitIndex;
                        PlaySoundTitleMove();
                        ResetTraitButtons( hdlg, nextTopTraitIndex );
                        TraitRefreshCurrentTraitInfo( hdlg, GetWindowLongA( button, GWL_ID ) );
                        TraitRefreshScrollState( hdlg );
                    }
                }
            }
        }
    }
}

//----- (th2) ------------------------------------------------------------
void __fastcall TraitUp( const HWND button )
{
    const auto hdlg = GetParent( button );
    
    if( GetWindowLongA( button, GWL_ID ) > ID_TRAIT_1 ){
        TraitSelectNextTrait( hdlg, button, -1 );
        return;
    }else{
        if( auto traitWin = (TraitWin*)GetWindowLongA( button, GWL_USERDATA ); traitWin ){
            if( auto traitIndex = (int)traitWin->traitIndex; traitIndex > 0 ){
                const auto nextTopTraitIndex = traitIndex - 1;
                PlaySoundTitleMove();
                ResetTraitButtons( hdlg, nextTopTraitIndex );
                TraitRefreshCurrentTraitInfo( hdlg, GetWindowLongA( button, GWL_ID ) );
                TraitRefreshScrollState( hdlg );
            }
        }
    }
}

//----- (th2) ------------------------------------------------------------
LRESULT __stdcall TraitSelectButtonProc( const HWND button, unsigned int Msg, WPARAM wParam, LPARAM lParam )
{
    LRESULT result = 0;
    auto oldProc = (WNDPROC)GetPropA( button, "UIOLDPROC" );
    const auto hdlg = GetParent( button );
    
    switch( Msg ){
        case WM_GETDLGCODE:
            result = 4;
            break;
        case WM_KEYFIRST:
            switch( wParam ){
                case VK_RETURN:
                case VK_SPACE:
                    SendMessageA( hdlg, 273, 1, 0 );
                    break;
                case VK_ESCAPE:
                    SendMessageA( hdlg, 273, 2, 0 );
                    break;
                case VK_TAB:
                    TraitSelectNextTrait( hdlg, button, ( GetKeyState( VK_SHIFT ) >= 0 ) ? 1 : -1 );
                    break;
                case VK_LEFT:
                case VK_UP:
                    TraitUp( button );
                    break;
                case VK_RIGHT:
                case VK_DOWN:
                    TraitDown( button );
                    break;
                case VK_PRIOR:
                    TraitPageUp( button );
                    break;
                case VK_NEXT:
                    TraitPageDown( button );
                    break;
                case VK_DELETE:
                    SendMessageA( hdlg, Msg, wParam, lParam );
                    break;
                default:
                    break;
            }
            break;
        case WM_DESTROY:
            RemovePropA( button, "UIOLDPROC" );
            if( oldProc ){
                SetWindowLongA( button, GWL_WNDPROC, (LONG)oldProc );
            }
            [[fallthrough]];
        default:
            if( oldProc ){
                result = CallWindowProcA_( oldProc, button, Msg, wParam, lParam );
            }else{
                result = DefWindowProcA_( button, Msg, wParam, lParam );
            }
            break;
        case WM_PAINT:
            PaintElem( button );
            break;
    }
    return result;
}

//----- (th2) ------------------------------------------------------------
int __stdcall DialogSelectTraits( HWND hdlg, unsigned int Msg, WPARAM wParam, LPARAM lParam )
{
    static int classElemList[] = { ID_CAPTION, 0 };
    static int buttons[] = { ID_TRAITS_CONTINUE, ID_SELECT_TRAIT_1, ID_SELECT_TRAIT_2, ID_SELECT_TRAIT_3, ID_SELECT_TRAIT_4, 0 };
	static int classElementList[] = { ID_OK_BUTTON, ID_CANCEL_BUTTON, 0 };
    
    int result;
	bool needToCallDefDialogProc = true;
    XinputVirtualKeyboard();
	CheckEnter( Msg, wParam, lParam );
	switch( Msg ){
		case WM_INITDIALOG:
		{
            if( is(GameMode, GM_COLISEUM, GM_CLASSIC) ){
                SDlgEndDialog(hdlg, lParam == 1 ? -1 : ID_TRAITS_CONTINUE);
                return SDlgDefDialogProc_(hdlg, Msg, wParam, lParam);
            }
		    char tempBuf[32];
			LoadStringA( HInstance, NewHeroTitle(), tempBuf, 31 );
			WriteAndDrawDialogTitle( GetParent( hdlg ), tempBuf );
			SetWindowLongA( hdlg, GWL_USERDATA, (LONG)GetWindowLongA( GetParent( hdlg ), GWL_USERDATA ) );
			InitButtonListProc( hdlg, buttons );
			InitTextElemList( hdlg, classElemList, 5 );
			InitButtonListText( hdlg, classElementList, 4, 0 );
			InitButtonListText( hdlg, buttons, 2, 1 );
			InitSelectionAndLoadPentagram( "ui_art\\focus16.pcx" );
            
            for(uint i = 0; i < size(NewSaveInfo.Traits); ++i) TraitSelectButtonRefresh( hdlg, ID_SELECT_TRAIT_1 + i, NewSaveInfo.Traits[i] );
			ResetButtonText( hdlg, buttons, 2, 1 );
			
			SDlgSetTimer( hdlg, 1, 55, 0 );
			needToCallDefDialogProc = false;
			result = 0;
			break;
		}
		case WM_DESTROY:
			DeletePentagram();
			DeleteElementListData( hdlg, buttons );
			DeleteElementListData( hdlg, classElementList );
			DeleteElementListData( hdlg, classElemList );
			WriteAndDrawDialogTitle( GetParent( hdlg ), 0 );
			break;
		
		case WM_COMMAND:
			if( HIWORD_IDA( wParam ) == BN_KILLFOCUS ){
				LeaveButton( hdlg, (HWND) lParam );
			}else if( HIWORD_IDA( wParam ) == BN_SETFOCUS ){
	
				SelectButton( (HWND) lParam );
				AnimateSelectionPentagram( hdlg, (HWND) lParam );
    
				SetTraitInfoText( GetParent( hdlg ), &NewSaveInfo, TraitId::NoTrait, (unsigned __int16) wParam );
				
			}else if( HIWORD_IDA(wParam) == BN_DOUBLECLICKED || (ushort)wParam == 1 ){
				PlaySoundTitleSelect();
				SDlgKillTimer( hdlg, 1 );
				SDlgEndDialog( hdlg, GetWindowLongA( GetFocus(), GWL_ID ) );
			}else if( (ushort) wParam == 2 ){
				PlaySoundTitleSelect();
				SDlgKillTimer( hdlg, 1 );
				SDlgEndDialog( hdlg,  2 );
			}
			
			break;
		case WM_LBUTTONDOWN:
			if( CheckCursorOnButton( hdlg, GetDlgItem( hdlg, ID_OK_BUTTON ), (unsigned __int16) lParam, (unsigned int) lParam >> 16u ) ){
				PlaySoundTitleSelect();
				SDlgKillTimer( hdlg, 1 );
				SDlgEndDialog( hdlg,  GetWindowLongA( GetFocus(), GWL_ID ) );
			}else if( CheckCursorOnButton( hdlg, GetDlgItem( hdlg, ID_CANCEL_BUTTON ), (unsigned __int16) lParam, (unsigned int) lParam >> 16u ) ){
				PlaySoundTitleSelect();
				SDlgKillTimer( hdlg, 1 );
				SDlgEndDialog( hdlg,  2 );
			}
			break;
		case WM_TIMER:
			AnimateSelectionPentagram( hdlg, GetFocus() );
			needToCallDefDialogProc = false;
			result = 0;
			break;
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			SendMessageA( SDrawGetFrameWindow( 0 ), Msg, wParam, lParam );
			break;
		default:
			break;
	}

	if( needToCallDefDialogProc )
	{
		result = SDlgDefDialogProc_( hdlg, Msg, wParam, lParam );
	}
	
	return result;
}

//----- (th2) ------------------------------------------------------------
int __stdcall DialogSelectTrait( HWND hdlg, unsigned int Msg, WPARAM wParam, LPARAM lParam )
{
    int result;
    bool needToCallDefDialogProc = true;
    
    switch( Msg ){
        case WM_INITDIALOG:
        {
            SelectedTraitId = TraitId::NoTrait;
            const auto fullClassId = GetPlayerFullClass( PLAYER_CLASS(NewSaveInfo.Class)
                                                       , PLAYER_SUBLASS(NewSaveInfo.SubClass)
                                                       , PLAYER_SPECIALIZATION(NewSaveInfo.Specialization) );
            TraitsAvailableList = CalcAvailableTraitList( fullClassId, NewSaveInfo.Traits );
            
            for( int i = 0; TraitButtonList[i] != 0; ++i ){
                int saveButtonId = TraitButtonList[i];
                HWND saveButton = GetDlgItem( hdlg, saveButtonId );
                if( saveButton ){
                    SetPropA( saveButton, "UIOLDPROC", (HANDLE)GetWindowLongA( saveButton, GWL_WNDPROC ) );
                    SetWindowLongA( saveButton, GWL_WNDPROC, (LONG)TraitSelectButtonProc );
                }
            }
            
            char tempBuf[32];
			LoadStringA( HInstance, NewHeroTitle(), tempBuf, 31 );
			WriteAndDrawDialogTitle( GetParent( hdlg ), tempBuf );
            SetWindowLongA( hdlg, GWL_USERDATA, GetWindowLongA( GetParent( hdlg ), GWL_USERDATA ) );
            InitTextElemList( hdlg, TraitTitleList, 5 );
            InitButtonListText( hdlg, TraitOkCancelList, 4, 0 );
            InitButtonListText( hdlg, TraitButtonList, 2, 1 );
            ResetTraitButtons( hdlg, 0 );
            InitSelectionAndLoadPentagram( "ui_art\\focus16.pcx" );
            SDlgSetTimer( hdlg, 1, 55, 0 );
            InitScroll( hdlg, ID_SCROLL );
            if( GetAvailableTraitCount() <= 6 ){
                ShowWindow( GetDlgItem( hdlg, ID_SCROLL ), 0 );
            }
            needToCallDefDialogProc = false;
            result = 0;
            break;
        }
        case WM_DESTROY:
        {
            DeleteScroll( hdlg, ID_SCROLL );
            DeletePentagram();
            DeleteElementListData( hdlg, TraitButtonList );
            DeleteElementListData( hdlg, TraitOkCancelList );
            DeleteElementListData( hdlg, TraitTitleList );
            WriteAndDrawDialogTitle( GetParent( hdlg ), 0 );
            break;
        }
        case WM_COMMAND:
        {
            if( HIWORD_IDA( wParam ) == BN_KILLFOCUS ){
                LeaveButton( hdlg, (HWND) lParam );
            }else if( HIWORD_IDA( wParam ) == BN_SETFOCUS ){
                InvalidateRect( GetParent( hdlg ), NULL, NULL ); //removes menu freezes // character selection menu
                UpdateWindow( GetParent( hdlg ) ); //removes menu freezes // character selection menu
                SelectButton( (HWND) lParam );
                AnimateSelectionPentagram( hdlg, (HWND) lParam );
                TraitRefreshCurrentTraitInfo( hdlg, (unsigned __int16) wParam );
                TraitRefreshScrollState( hdlg );
            }else if( HIWORD_IDA( wParam ) == BN_DOUBLECLICKED || (ushort)wParam == 1 ){ // Enter
                PlaySoundTitleSelect();
                SDlgKillTimer( hdlg, 1 );
                SDlgEndDialog( hdlg, 1 );
            }else if( (ushort)wParam == 2 ){
                PlaySoundTitleSelect();
                SDlgKillTimer( hdlg, 1 );
                SDlgEndDialog( hdlg, 2 );
            }
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        {
            int cursorX = (unsigned __int16) lParam;
            int cursorY = (unsigned int) lParam >> 16;
            if( CheckCursorOnButton( hdlg, GetDlgItem( hdlg, ID_OK_BUTTON ), cursorX, cursorY ) ){
                PlaySoundTitleSelect();
                SDlgKillTimer( hdlg, 1 );
                SDlgEndDialog( hdlg,  1 );
            }else if( CheckCursorOnButton( hdlg, GetDlgItem( hdlg, ID_CANCEL_BUTTON ), cursorX, cursorY ) ){
                PlaySoundTitleSelect();
                SDlgKillTimer( hdlg, 1 );
                SDlgEndDialog( hdlg,  2 );
            }else if( CheckCursorOnButton( hdlg, GetDlgItem( hdlg, ID_SCROLL ), cursorX, cursorY ) ){
                switch( GetScrollAction( GetDlgItem( hdlg, ID_SCROLL ), cursorX, cursorY ) ){
                    case 1:
                        TraitUp( GetFocus() );
                        break;
                    case 2:
                        TraitDown( GetFocus() );
                        break;
                    case 3:
                        TraitPageUp( GetFocus() );
                        break;
                    case 4:
                        TraitPageDown( GetFocus() );
                        break;
                    default:
                        break;
                }
            }
            break;
        }
        case WM_LBUTTONUP:
        {
            if( CheckScrollPressAndRelease( GetDlgItem( hdlg, ID_SCROLL ) ) ){
                TraitRefreshScrollState( hdlg );
            }
            break;
        }
        case WM_TIMER:
            AnimateSelectionPentagram( hdlg, GetFocus() );
            needToCallDefDialogProc = false;
            result = 0;
            break;
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
            SendMessageA( SDrawGetFrameWindow( nullptr ), Msg, wParam, lParam );
            break;
    }
    
    if( needToCallDefDialogProc ){
        result = SDlgDefDialogProc_( hdlg, Msg, wParam, lParam );
    }
    
    return result;
}
