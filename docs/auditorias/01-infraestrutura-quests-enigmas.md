# AUDITORIA 01 — Infraestrutura de quests e enigmas
**Sociedade de Tristram | 31/10/2026 | branch feature/configurable-rates**
**Estado:** leitura estática de arquivos via GitHub. Não houve compilação nem teste no jogo. Não há mudanças no código de gameplay neste commit.

## Evidências diretamente observadas
### BaseQuests.cpp
- Declara `BaseQuest BaseQuests[Quest_Count]` com entradas de `Q_0_THE_MAGIC_ROCK` a `Q_38_OGDENS_SIGN_MP` na parte inspecionada.
- Cada registro tem ID, flags, níveis de início, tipos de masmorra, áreas especiais, retorno, speech index e nome.
- Há `BaseDungeon Dungeons[DungeonCount]`, com IDs de níveis e entradas para áreas especiais.
- **Implicação:** não adicionar quest simplesmente anexando uma entrada sem localizar a definição de `Quest_Count`, a enumeração de IDs e todas as tabelas indexadas.

### Quests.cpp
- Declara `Quest Quests[Quest_Count]`.
- Declara `QuestPanel_ActiveQuestsList[Quest_Count + 1]`, com comentário de entrada extra para a Irmandade.
- Define `SOCIETY_QUEST_LOG_INDEX = Quest_Count`.
- O diário da Irmandade lê `AdditionalStateData.unused[0]` e apresenta objetivos próprios via `SocietyQuestLogTitle()` e `SocietyQuestLogObjective()`.
- **Implicação:** a nova trama NÃO pode sobrescrever `AdditionalStateData.unused[0]`; o índice extra do painel já está ocupado. Evitar que enigma vire checklist de objetivos.

### TownMap.cpp
- Declara `TownersSpeechAboutQuestArray[TI_15_COUNT][Quest_Count]`, tabela bidimensional de falas por morador e quest.
- Declara `Towner Towners[17]`.
- **Implicação:** se `Quest_Count` mudar, revisar inicialização de TODAS as linhas da matriz, índices de `TI_15_COUNT`, loops de exibição, identificadores de speech e eventuais inconsistências entre 15 categorias de fala e 17 slots de NPC. Não presumir que todo NPC tem linha nessa matriz.

### GenerateQuestFloor.cpp
- Contém `HorazonQuestBookSpeechTable[16][6]`, `HorazonBooksCombinationTable[6][3]`, `InitHorazonQuestBook`, `SetupHorazon1Books` e `SetupHorazon2Books`.
- A segunda configuração usa `RNG(6)` para permutar três livros.
- **Implicação:** existem mecanismos de livros e combinação aproveitáveis como referência. Não acoplar o novo enigma a Horazon sem estudar efeitos colaterais, estados, diálogos e compatibilidade.

### Forgotten House — documentação atual
- `docs/forgotten-house.md` informa expansão de cinco áreas, dez inimigos comuns, dois minibosses opcionais e Hóspede sem Rosto com três fases, além dos objetos e finais originais.
- Registra DUN ID 115 e `AdditionalSaveInfo.unused` nos bytes 80–86 e 96–121, com outras expansões descritas posteriormente. O mapa integral de ocupação ainda NÃO foi concluído.
- **Implicação:** preservar Maera, companheiros, mapas e persistência; não atribuir bytes novos com base apenas nesta leitura.

## Revisão de cânone realizada
Fonte oficial: https://news.blizzard.com/pt-br/article/23725427/diablo-ii-a-historia-ate-aqui
- Inarius e Lilith, com anjos e demônios dissidentes, participaram da criação de Santuário.
- O Triuno, sob identidades Mefis, Dialon e Bala, e a Catedral da Luz, instituída por Inarius, disputavam influência sobre os humanos durante a Guerra Pecaminosa.
- Após Uldyssian, memórias humanas da Guerra Pecaminosa foram apagadas.
- Tyrael fundou os Horadrim; Jered Cain participou do aprisionamento de Diablo sob a Catedral de Tristram.
- Leoric, Lazarus, Albrecht e a expedição ao Açougueiro pertencem ao contexto imediato de Diablo I.

**Restrição de narrativa:** não tratar o Triuno e a Catedral da Luz como organizações necessariamente ativas em Tristram no período de Diablo I. Usar vestígios apócrifos, textos copiados e tradições distorcidas. Não fazer Cain identificar instantaneamente a origem de cada vestígio. O conhecimento canônico do autor não é conhecimento do NPC.

## Primeira matriz de risco
| Risco | Severidade | Ação obrigatória |
|---|---|---|
| Novo ID colide com `Quest_Count` e tabelas fixas | Alta | Auditar enum, todas as referências e loops |
| Novo objetivo ocupa slot extra da Irmandade | Alta | Projetar entrada independente sem sobrescrever índice |
| Flag de save conflita com Maera ou Irmandade | Crítica | Inventariar todas as leituras/escritas de unused |
| Livro novo interfere com puzzle de Horazon | Média/alta | Isolar objeto/handler e testar repetição e RNG |
| Falas de NPC extrapolam matriz | Alta | Conferir TI_15_COUNT, Towners[17], speech IDs |
| Enigma exige ordem única de pistas | Média | Permitir coleta livre, dedução por combinações |
| Quest interfere nos modos restritos | Alta | Copiar guardas apropriadas após inspeção |

## Próxima inspeção objetiva (ainda pendente)
1. Localizar definição de `Quest_Count` e enumeração `Q_*` em headers.
2. Encontrar todas as leituras/escritas de `AdditionalSaveInfo.unused` e `AdditionalStateData.unused`.
3. Examinar handlers de diálogo em `TownMap.cpp`, objetos em `Object.cpp` e rotinas de quest em `Quests.cpp` além das primeiras 160 linhas.
4. Verificar o tratamento de `DUN_115`, limites de `DungeonCount` e entrada/saída.
5. Preparar patch mínimo isolado com flags e diálogo somente depois do inventário.

## Direção narrativa após auditoria
**O Livro que Não Devia Ter um Primeiro Capítulo:** um apócrifo com vestígios de ideias da Guerra Pecaminosa. Uma palavra adulterada cria o crime local; duas tradições históricas manipuladas por facções rivais dão a profundidade. O enigma não prova sobrevivência institucional do Triuno ou da Catedral da Luz; prova que textos antigos podem ser reaproveitados por atores modernos.

**Princípio de Vespera:** o segredo não precisa estar atrás de uma parede. Pode estar numa palavra que todos leram, mas ninguém comparou.

## Handoff
Esta auditoria NÃO implementa a nova quest. Ao retomar: conferir branch e HEAD, ler este documento, `docs/Vespera-Livro-das-Sombras-de-Santuario.md`, `docs/forgotten-house.md` e `docs/propostas-lore/02-o-livro-sem-primeiro-capitulo.md`. Continuar o inventário técnico antes de modificar código.
