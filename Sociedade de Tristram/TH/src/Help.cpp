#include "stdafx.h"

// 0048ACA8
char HelpText[] =
"$ATALHOS:|F1: Abrir esta Ajuda|Esc: Abrir o menu principal|Tab: "\
"Mostrar o automapa|Espaco: Fechar paineis de informacao|S: Abrir "\
"atalhos de magias|B: Abrir livro de magias|I: Abrir inventario|C:"\
" Abrir personagem|Q: Abrir diario de missoes|F / G: Diminuir / "\
"aumentar brilho|Z: Zoom da tela|+ / -: Zoom do automapa|1 - 8: "\
"Usar item do cinto|F5 - F8: Definir atalho de magia|Shift + clique"\
" esquerdo: Atacar sem andar||$LOOT E QUALIDADE DE VIDA:|Ouro e "\
"coletado automaticamente quando a opcao Autopickup esta ativa.|O"\
" filtro de loot deixa os itens importantes visiveis no chao.|Seg"\
"ure ALT para revelar todos os itens, inclusive os ocultos pelo "\
"filtro.|Cores: azul = magico, amarelo = raro, laranja = unico, "\
"rosa = conjunto.|O bau compartilhado pode ser usado por todos os "\
"personagens e comeca com 10 abas liberadas. Pilhas de ouro tambem "\
"podem ser guardadas nele e retiradas por outro personagem.|Ferreiro: Reparar Tudo"\
" conserta o equipamento de uma vez.|Anciao: Identificar Tudo "\
"identifica os itens de uma vez.|Na loja: Ctrl + clique compra 5 "\
"unidades de consumiveis fixos; Ctrl + Shift + clique compra 10."\
"||$MOVIMENTO E COMBATE:|Segure o "\
"botao do mouse para continuar andando.|Segure Shift ao atacar para"\
" permanecer parado. Isso e especialmente util para arqueiros e "\
"magos.|Na cidade o movimento rapido reduz o tempo gasto entre os "\
"servicos.||$AUTOMAPA:|Pressione TAB para abrir o automapa. Use + e"\
" - para alterar o zoom e as setas para mover o mapa.|O automapa "\
"em tela cheia usa o visual classico, mais escuro e legivel.||"\
"$MAGIAS:|Abra a lista de habilidades e magias pelo botao de magias"\
". Clique na magia desejada para prepara-la e use o botao direito "\
"na area de jogo para lancar.|F5, F6, F7 e F8 podem guardar suas "\
"magias e habilidades mais usadas.||$GUIA DE BUILD - GUERREIRO:|"\
"Base: priorize FOR e VIT. Espada ou maca de uma mao + escudo e a "\
"opcao mais segura. Procure bloqueio, resistencias e vida.|Inquisid"\
"or: combate corpo a corpo com dano elemental; equilibre FOR, VIT "\
"e resistencias.|Guardiao: foque defesa, bloqueio, armadura e vida."\
" Excelente para jogar com seguranca.|Templario: escudo + dano "\
"sagrado/contra mortos-vivos; mantenha boa defesa antes de buscar "\
"mais dano.||$GUIA DE BUILD - ARQUEIRO:|Base: priorize DES e depois "\
"VIT. Arco, velocidade de ataque, acerto e critico sao as melhores "\
"prioridades.|Batedor: mobilidade e flechas elementais; DES + VIT.|"\
"Atirador: arco de longo alcance, dano critico e precisao.|Armadilh"\
"eiro: fortalece armadilhas e controle; mantenha distancia e use "\
"VIT suficiente para sobreviver a aproximacoes.||$GUIA DE BUILD - "\
"MAGO:|Base: priorize MAG e depois VIT. Dano de magia, mana e "\
"resistencias valem mais que dano de arma.|Elementalista: escolha "\
"um elemento principal e um secundario para inimigos resistentes.|"\
"Demonologista: invocacoes demoniacas e suporte magico.|Necromante:"\
" lacaios e magia sombria; deixe as invocacoes segurarem a linha de"\
" frente.|Mestre das Feras: invocacoes animais e sobrevivencia.|"\
"Bruxo: dano sombrio/acido e magia ofensiva; MAG alta com VIT "\
"suficiente para nao ser eliminado rapidamente.||$GUIA DE BUILD - "\
"MONGE:|Base: DES, FOR e VIT. Cajado, velocidade de ataque, esquiva"\
" e resistencias formam uma build equilibrada.|Kensei: dominio de "\
"armas e dano corpo a corpo.|Shugoki: armas pesadas, resistencia e "\
"vida.|Shinobi: velocidade, esquiva e ataques rapidos/a distancia."\
"||$GUIA DE BUILD - LADINO:|Base: priorize DES e VIT. Duas armas, "\
"velocidade e esquiva combinam bem.|Assassino: garras, velocidade e"\
" dano acido/veneno.|Donzela de Ferro: defesa, armadura e efeitos "\
"de retaliacao.|Bombardeiro: explosivos e dano em area; mantenha "\
"distancia do grupo de inimigos.||$GUIA DE BUILD - SELVAGEM:|Base:"\
" priorize FOR e VIT. Armas de duas maos, dano fisico e vida sao "\
"uma rota simples e forte.|Berserker: velocidade, furia e dano; "\
"compense com vida.|Executor: FOR e dano corpo a corpo pesado.|"\
"Thraex: mobilidade e agressao.|Murmillo: defesa, escudo e armadura"\
".|Dimachaerus: duas armas e dano rapido.|Secutor: equilibrio entre "\
"ataque e defesa.|Druida: combate hibrido e estilo animal; combine "\
"FOR/VIT com os bonus da forma escolhida.||$DICA DE BUILD:|Estas "\
"sao rotas recomendadas, nao obrigatorias. Antes de investir tudo "\
"em dano, garanta vida e resistencias suficientes para o nivel que"\
" esta jogando. Use o reset de atributos e vantagens da comerciante"\
" quando quiser experimentar outra configuracao.|&";

//----- (0041D0A9) --------------------------------------------------------
void ResetHelp()
{
	IsHELPVisible = false;
	SomeHelpMemory_1 = 0;
	SomeHelpMemory_2 = 0;
}

//----- (0041D0BB) --------------------------------------------------------
void GameHelp()
{
	int v0;   // edi@1
	int v2;   // edx@3
	int v3;   // ecx@3
	char v4;  // al@8
	char* v5; // eax@15
	int v6;   // edx@22
	int v7;   // ecx@22
	char v8;  // al@28
	char v9;  // al@13
	char v11; // al@34
	char v12; // ST10_1@39
	int v13;  // edx@39
	int v14;  // [sp+10h] [bp-4h]@2
	int v15;  // [sp+Ch] [bp-8h]@26
	SetGameHelpBigMenuBox();
	DrawDialogBox( Dialog_591_Width, Dialog_302_Height, TextBoxCel );
	DrawGameDialogTitleText(0, 2, 1, "Ajuda - Sociedade de Tristram", 3, 0);
	DrawDialogLine(5);
	v0 = HelpCurrentPosition;
	uint helpTextIndex = 0;
	if( HelpCurrentPosition > 0 ){
		v14 = HelpCurrentPosition;
		do{
			v2 = 0;
			v3 = 0;
			while( !HelpText[helpTextIndex] ){
				++helpTextIndex;
			}
			if( HelpText[helpTextIndex] == '$' ){
				++helpTextIndex;
			}



			v4 = HelpText[helpTextIndex];
			if( HelpText[helpTextIndex] != '&' ){
				while( v4 != '|' ){
					if( v3 >= 577 ){
						goto LABEL_15;
					}
					if( !v4 ){
						do{
							++helpTextIndex;
						}while( !HelpText[helpTextIndex] );
					}
					v9 = HelpText[helpTextIndex];
					InfoPanelBuffer[v2++] = HelpText[helpTextIndex++];
					v3 += FontWidthSmall[FontIndexSmall[Codepage[v9]]] + 1;
					v4 = HelpText[helpTextIndex];
				}
				if( v3 < 577 )
					goto LABEL_18;
				LABEL_15:
				// Было v2 = &BeforeSomeString2[v2], но v2 согласно алгоритма не может быть тут меньше 1
				v5 = &InfoPanelBuffer[v2 - 1];
				while( *v5 != ' ' ){
					--helpTextIndex;
					--v5;
				}
				LABEL_18:
				if( HelpText[helpTextIndex] == 124 ){
					++helpTextIndex;
				}
			}
		}while( v14-- != 1 );
	}
	v14 = 7;
	do{
		v7 = 0;
		v6 = 0;
		// Мистика. Есть строка HelpText. Есть указатель fn, присваиваем fn адрес HelpText, а fn принимает какое то другое значение. Не адрес HelpText
		// Затем делаю fn индексом HelpText. Читаю 0е значение и опять ошибка при чтении. Причём адрес какой то отличный от адреса HelpText
		// Может всё дело в размере или содержимом HelpText?
		while( !HelpText[helpTextIndex] ){// Break with error - incorrect pointer 0x79654b24
			++helpTextIndex;
		}
		if( HelpText[helpTextIndex] == 36 ){
			++helpTextIndex;
			LOBYTE_IDA(v15) = 2;
		}else{
			LOBYTE_IDA(v15) = 0;
		}
		v8 = HelpText[helpTextIndex];
		if( HelpText[helpTextIndex] == 38 ){
			HelpStringsCount = v0;
		}else{
			while( v8 != 124 ){
				if( v6 >= 577 ){
					goto LABEL_36;
				}
				if( !v8 ){
					do{
						++helpTextIndex;
					}while( !HelpText[helpTextIndex] );
				}
				v11 = HelpText[helpTextIndex];
				InfoPanelBuffer[v7++] = HelpText[helpTextIndex++];
				v6 += FontWidthSmall[FontIndexSmall[Codepage[v11]]] + 1;
				v8 = HelpText[helpTextIndex];
			}
			if( v6 < 577 ){
				goto LABEL_38;
			}
			LABEL_36:
			while( 1 ){
				--v7;
				if( InfoPanelBuffer[v7] == 32 ){
					break;
				}
				--helpTextIndex;
			}
			LABEL_38:
			if( v7 ){
				v12 = v15;
				v13 = v14;
				InfoPanelBuffer[v7] = 0;
				DrawHelpText(0, v13, (int)InfoPanelBuffer, v12);
				v0 = HelpCurrentPosition;
			}
			if( HelpText[helpTextIndex] == 124 ){
				++helpTextIndex;
			}
		}
		++v14;
	}while( v14 < 22 );
	DrawGameDialogTitleText(0, 23, 1, "ESC fecha - use as setas para rolar.", 3, 0);
}

//----- (0041D246) --------------------------------------------------------
char __fastcall DrawHelpText(int a1, int a2, int a3, char aFontSize)
{
	char result; // al@1
	int v5;      // ebx@1
	int v6;      // edi@1
	char v7;     // al@2
	int v8;      // esi@2
	v5 = 0;
	v6 = YOffsetHashTable[StringRowYPosition[a2] + 204] + a1 + 96;
	for( result = *(uchar*)a3; *(uchar*)a3; result = *(uchar*)a3 ){
		++a3;
		v7 = FontIndexSmall[Codepage[result]];
		v8 = (unsigned __int8)v7;
		v5 += FontWidthSmall[v7] + 1;
		if( v7 ){
			if( v5 <= 577 )
				DrawLetter(v6, (unsigned __int8)v7, aFontSize);
		}
		v6 += FontWidthSmall[v8] + 1;
	}
	return result;
}

//----- (0041D2DB) --------------------------------------------------------
void ShiftHelpUp()
{
	if( HelpCurrentPosition > 0 ){// Help button if busy by Fury spell
		--HelpCurrentPosition;
	}
}

//----- (0041D2EB) --------------------------------------------------------
void ShiftHelpDown()
{
	if( HelpCurrentPosition < HelpStringsCount ){// Help button if busy by Fury spell
		++HelpCurrentPosition;
	}
}
