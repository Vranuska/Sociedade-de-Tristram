# O LIVRO DAS SOMBRAS DE SANTUÁRIO
**Bíblia narrativa, manual de enigmas e documento de passagem de bastão**

Projeto: **Sociedade de Tristram**. Autoria criativa: Vespera, sob direção da criadora da mod. **Estado: diretrizes e propostas, não implementação confirmada.**

> Este arquivo é a versão Markdown para preservação no GitHub do documento Word elaborado em 31/10/2026. O arquivo Word original não foi enviado: a integração GitHub disponível recebe arquivos UTF-8. Este texto conserva o conteúdo narrativo e técnico.

## 0. Mandato inegociável
Criar uma expansão de Diablo I que faça a pequena Tristram revelar vestígios de uma guerra milenar entre Céus, Infernos e humanidade. O jogador vive no presente de Diablo I; a autora conhece os jogos posteriores. Conhecimento futuro orienta a escrita, nunca é entregue artificialmente aos personagens.

- O cânone é a âncora; o espaço não narrado entre fatos canônicos é nosso campo de criação.
- Enigmas devem ser honestos: pistas disponíveis antes da solução, interpretação difícil, sem depender de adivinhação impossível.
- Não transformar missões em listas de tarefas, marcadores explícitos ou recompensas garantidas.
- O extraordinário deve parecer rumor, erro de percepção, detalhe de cenário ou tradição local até que os indícios se acumulem.
- Nunca apagar trabalho técnico, sistemas de companheiros, saves ou conteúdo anterior para consertar o roteiro.

## 1. O que foi decidido e não pode se perder
| Área | Decisão consolidada |
|---|---|
| Identidade | Sociedade de Tristram, mod de Diablo I construída sobre a cadeia The Hell 4 / The Heaven, com tradução PT-BR, sistemas novos e companheiros. |
| Escopo | Usar lore de Diablo I, II, III, IV e Immortal, além dos livros e tomos como referências, respeitando a cronologia. |
| Abordagem | Intrigas do passado que repercutem no futuro; qualquer personagem, culto, lugar ou facção pertinente, não apenas Adria. |
| Tom | Horror gótico, tragédia humana, ambiguidade moral, paranoia, investigação e silêncio. |
| Referência de design | Enigmas orgânicos e camuflados no espírito dos mistérios de RPG persistentes que a criadora admira no trabalho de Knightmare/CipSoft; inspiração metodológica, não reprodução de conteúdo específico. |
| Estado técnico | Última verificação anterior: feature/configurable-rates tinha 104 commits à frente de main; uma quest Forgotten House/Maera existia. Verificar novamente antes de editar. |
| Segurança | Não fazer reset, force-push, exclusões em massa nem reutilizar IDs/bytes de save sem auditoria. |

## 2. Disciplina de cânone e cronologia
A cronologia exata de cada arco precisa ser confrontada com os materiais de pesquisa fornecidos pela criadora e com fontes oficiais antes da implementação. Este documento separa explicitamente fatos estabelecidos, inferências e ficção original.

| Âncora do universo | Uso permitido na época de Diablo I | Armadilha a evitar |
|---|---|---|
| Guerra Eterna; criação de Santuário; Inarius e Lilith | Ecos em escrituras apócrifas, iconografia, ruínas e tradições fragmentadas. | Lilith aparecendo em Tristram sem fundamento cronológico. |
| Horadrim; Tal Rasha; Pedras das Almas | Correspondência, ordens, selos, deserções, testemunhos e erros de interpretação de antigos guardiões. | Inventar Pedra das Almas adicional ou mudar o aprisionamento conhecido. |
| Leoric, Lazarus, Albrecht e a Catedral | Vítimas, lacunas dos registros, escolhas da corte e repercussões locais. | Reescrever o destino central de Leoric/Albrecht. |
| Zakarum e a corrupção em Kurast | Peregrinos, mercadorias, cartas, disputas e práticas religiosas; confirmar estágio da corrupção na data. | Expor como conhecimento público o que ainda é segredo. |
| Vizjerei, Horazon e Bartuc | Textos herdados, métodos proibidos, efeitos de antigas guerras mágicas. | Transformar figuras históricas em participações gratuitas. |
| Adria e agentes infernais | Contradições, escolhas suspeitas, conhecimentos incomuns e pistas ambíguas. | Revelar ao herói o enredo completo de Diablo III. |
| Males Inferiores e intrigas demoníacas | Cultos, influência indireta, rivalidades e consequências humanas. | Usar cada demônio como chefe apenas para fan service. |

## 3. Método Vespera: engenharia reversa de um segredo
Antes de escrever qualquer diálogo, preencher um dossiê secreto, inacessível ao jogador: (1) verdade completa; (2) motivação de cada facção; (3) cronologia dos fatos; (4) versão pública; (5) mentira deliberada; (6) pistas que sobrevivem; (7) descoberta mínima; (8) descoberta profunda; (9) consequências; (10) evidência canônica e grau de confiança.

Cada enigma deve ter pelo menos três pistas independentes que convergem para a mesma conclusão, distribuídas entre ambiente, diálogo e documento ou mecânica. Uma pista não deve exigir que outra já tenha sido encontrada. Nenhuma solução dependerá exclusivamente de pixel hunting, sorte de drop ou conhecimento externo.

## 4. Gramática dos enigmas camuflados
| Técnica | Execução prática | Recompensa de atenção |
|---|---|---|
| Contradição útil | Dois NPCs contam a mesma noite com detalhes inconciliáveis. | Jogador identifica quem omite informação, não necessariamente quem mente. |
| Objeto deslocado | Um símbolo religioso aparece num item doméstico onde não deveria existir. | Descobre circulação de um culto por rotas comerciais. |
| Texto com dupla leitura | Carta inocente possui fórmula ritual em suas saudações repetidas. | Interpretação alternativa abre diálogo, não uma porta mágica arbitrária. |
| Arquitetura narrativa | Três salas possuem disposição de móveis idêntica, mas uma tem uma ausência. | A ausência indica censura ou repetição ritual. |
| Silêncio de NPC | Morador evita um nome que outros dizem sem hesitar. | O silêncio é uma pista, não confirmação de culpa. |
| Revisita transformadora | Uma fala antiga muda de significado após achar registro independente. | Jogador pode confrontar NPC e obter nova camada de verdade. |
| Consequência atrasada | Uma escolha muda um rumor ou inventário após várias sessões. | Mundo reage sem pop-up de missão concluída. |
| Pista negativa | Livro afirma que certo artefato jamais deixou o local, mas inventário registra uma caixa vazia. | Permite inferir fraude sem apresentar resposta pronta. |

## 5. Macrotrama: A Contabilidade dos Ausentes
**CONCEITO ORIGINAL DA MOD, NÃO CÂNONE:** uma rede dispersa de escribas, mercadores, penitentes e zeladores apaga dos registros pessoas que tiveram contato com vestígios da Guerra Eterna. Não é uma nova superfacção secreta que controla tudo; são pequenos agentes com motivos diferentes, alguns humanos, outros manipulados. O elo comum é uma convenção de escrituração: pessoas mortas, desaparecidas ou entregues a instituições aparecem como “dívidas quitadas”.

A verdade é que a expressão nasceu como linguagem administrativa inocente, foi reaproveitada por um grupo religioso e depois por intermediários de diferentes interesses. O jogador poderá interpretar a rede como conspiração única; evidências mais profundas revelam alianças temporárias e inimigos usando o mesmo código. A própria teoria inicial do jogador torna-se uma armadilha.

Assinatura ambiental recorrente: três riscos verticais ao lado de um círculo incompleto. **NÃO são runas oficiais de Diablo**: símbolo inventado pela mod, atribuído inicialmente a um escrivão humano. Em alguns lugares aparece invertido por motivos concretos (carimbo, impressão ou espelho). Nunca usar o símbolo como marcador de quest brilhante.

## 6. Quest principal: O Último Juramento — versão profunda
**Âncora:** legado horádrico e prisão de Diablo sob a Catedral. O episódio novo trata de guardiões secundários, não reescreve os feitos canônicos.

**VERDADE SECRETA:** décadas antes dos acontecimentos do jogo, um zelador herdou uma ordem de manter fechada uma passagem auxiliar. Durante um incidente, moradores buscaram abrigo e foram abandonados do lado errado. O registro oficial atribuiu as mortes a um desabamento. O zelador não era um servo de Diablo; era um homem aterrorizado pela responsabilidade de abrir uma porta.

**CAMADA FALSA:** uma carta sugere sacrifício ritual. **CAMADA REAL:** a escrita é uma lista de suprimentos e nomes de pessoas que o zelador tentou salvar. **CAMADA PROFUNDA:** um segundo documento revela que alguém, anos depois, reutilizou a linguagem do juramento para encobrir um desaparecimento não relacionado. O passado tornou-se método de crime no presente.

### 6.1 Fluxo sem checklist
1. **Ato I — O vestígio:** o jogador encontra uma folha contábil numa área lateral. Há três nomes riscados e um nome repetido com grafia diferente. Pode ignorá-la.
2. **Ato II — As versões:** Cain reconhece a estrutura de um juramento antigo, Gillian identifica uma família de mercadores e Farnham lembra o som de uma porta, mas seu testemunho é instável. Nenhum oferece coordenadas prontas.
3. **Ato III — A arquitetura:** um corredor secundário tem marcas de dobradiças no lado “errado” da parede. Há um diário e um selo que foi aberto e novamente fechado.
4. **Ato IV — A inversão:** o jogador descobre que o documento usado para acusar um zelador foi escrito depois de sua morte. A suposta confissão é uma falsificação.
5. **Ato V — Escolha:** entregar o dossiê a Cain, expor publicamente a falsificação ou ocultar o documento por temer seu uso. Cada escolha altera relações e informações, não o destino de Diablo.

### 6.2 Pistas e solução
| Pista | Onde aparece | O que sugere | O que prova |
|---|---|---|---|
| Duas tintas na mesma folha | Registro encontrado | Adições em datas diferentes | Documento foi alterado; não diz por quem. |
| Nome repetido com grafias distintas | Livro de contas / fala de Gillian | Erro ou identidade trocada | Ao comparar com outro registro, identifica o falsificador. |
| Dobradiças invertidas | Corredor da masmorra | Porta construída para conter algo | Mostra sentido original de fechamento, não motivo. |
| Data de sepultamento | Arquivo/epitáfio local | Zelador morreu antes da confissão | Invalida autoria atribuída. |
| Fórmula horádrica truncada | Cain e fragmento de carta | Conhecimento herdado e degradado | Distingue texto antigo de imitação recente. |

### 6.3 Falas-modelo
- **Cain:** “Conheço a forma deste juramento. Não conheço a mão que o escreveu. São coisas diferentes.”
- **Gillian:** “Aquele nome aparece duas vezes no livro. Meu pai dizia que era descuido. Ele nunca cometia descuidos com dívidas.”
- **Farnham:** “Eu ouvi a porta. Não a vi. Há noites em que penso que fui eu quem a fechou.”
- **Carta do zelador:** “Se eu abrir, talvez todos morram. Se eu não abrir, saberei exatamente quem deixei morrer.”

Última revelação, sem voz explicativa: o mesmo sinal de contabilidade aparece numa correspondência recente, com papel e tinta incompatíveis com o documento antigo.

## 7. Quatro arcos paralelos e sua função
| Arco | Mistério superficial | Verdade potencial / cautela canônica | Conexão discreta |
|---|---|---|---|
| O Dízimo de Travincal | Doações religiosas seguem para destinatário inexistente. | Ficção sobre intermediários humanos; confirmar situação do Zakarum na época. | A mesma convenção de contas, mas outro agente e outro propósito. |
| As Cinzas de Vizjerei | Receita de tinta produz alucinações quando aquecida. | Fragmento de técnica arcana antiga; evitar atribuir sem fonte a Horazon/Bartuc. | Uma falsificação usa tinta identificável pelo jogador. |
| O Livro sem Primeiro Capítulo | Escritura descreve a criação de Santuário sem citar seus autores. | Apócrifo humano inspirado na história de Inarius/Lilith; não revelar tudo. | Uma frase é copiada em carta de outro arco. |
| A Misericórdia do Açougueiro | Sobreviventes discordam sobre quem os conduziu à Catedral. | Investigar a expedição de Lazarus sem mudar os eventos centrais. | Um nome do registro de ausentes é o de um mensageiro. |

## 8. Arquitetura de descoberta em camadas
| Camada | Jogador casual | Jogador atento | Investigador obsessivo |
|---|---|---|---|
| Imediata | Resolve tragédia local. | Percebe contradição entre duas versões. | Registra datas, grafias, disposição de salas. |
| Intermediária | Recebe epílogo coerente. | Desmascara falsificação. | Conecta símbolo e papel a outras quests. |
| Profunda | Pode nunca ver. | Suspeita de rede maior. | Conclui que a rede não é única; atores rivais reciclam a mesma linguagem. |

Nenhuma camada profunda deve impedir o encerramento narrativo da missão básica. Segredos profundos oferecem conhecimento, pequenas reações e novas hipóteses, não poder indispensável.

## 9. Maera, Forgotten House e companheiros: plano de contenção
A quest existente “A casa que Tristram esqueceu” contém Maera, A Quarta Batida, mapa DUN_115 e persistência em AdditionalSaveInfo.unused. O texto existente registra bytes 80–85 e 96–124, além de jornadas e treinamentos dos seis companheiros. Estes são fatos da documentação técnica previamente lida; a compilação e o estado atual da branch precisam ser reconfirmados.

- Não apagar Maera nem seus serviços, progressão ou treinamentos para encaixar a nova história.
- Não reutilizar DUN_115, índices de diálogos, IDs de NPCs ou bytes 80–124 antes de inventário completo.
- Separar “missão de resgate” de “sistema de companheiros” por interfaces estáveis, se o código permitir.
- Se reescrever a origem de Maera, criar migração de saves e roteiro de teste antes de qualquer substituição.
- Tratar a história antiga como conteúdo legado até aprovação explícita de nova narrativa.

## 10. Regras de implementação e QA
- Criar branch dedicada a lore/quests a partir do HEAD correto, depois de comparar com a branch ativa e as alterações de UI.
- Antes de tocar código: mapear funções, assets DUN, IDs de quests, diálogos, NPCs, bytes de save, gatilhos e modos incompatíveis.
- Definir pistas como flags independentes; permitir ordem livre e múltiplas entradas para a mesma dedução.
- Não confiar em texto de interface como estado de jogo. Não traduzir strings internas usadas em comparações.
- Testar novos saves e saves anteriores, entrada/saída da masmorra, morte, recarga, modos especiais, ordem de coleta, NPC indisponível, escolhas e regressão de companheiros.
- Compilação local Windows/MSVC e teste dentro do jogo são obrigatórios para chamar uma quest de jogável.
- Cada commit deve ter escopo pequeno e relatório do que mudou; não declarar testes não executados.

## 11. Padrão obrigatório de entrega de cada quest
ID provisório; título; âncora canônica e fontes; janela cronológica; verdade secreta; versão pública; elenco e motivações; mapa de pistas; três caminhos de dedução; falsos indícios justos; estados e gatilhos; diálogos completos; consequências; integração com outras quests; inventário técnico; riscos de save; testes; distinção entre fato canônico, hipótese e invenção.

## 12. Handoff: instrução pronta para a próxima conversa
> Você é Vespera, Lore Master e designer de enigmas da Sociedade de Tristram. Leia este documento inteiro antes de propor ou alterar quests. Preserve o cânone de Diablo e a cronologia de Diablo I/II/III/IV/Immortal. Escreva mistérios sutis, com soluções planejadas, pistas distribuídas e várias camadas de interpretação. Nunca reduza a trama a Adria nem use aparições anacrônicas. Nunca apague sistemas existentes, sobretudo Maera e os companheiros, sem aprovação e plano de migração. Antes de editar o Git, confira branch, HEAD, commits recentes, arquivos e testes; descreva o estado real. Sua próxima tarefa é transformar O Último Juramento em dossiê de implementação com diálogos completos e matriz de flags, mas não implementar antes de auditar conflitos com Forgotten House. Se houver materiais de lore anexados ou na Biblioteca, leia-os e atualize as âncoras com referências específicas. Continue o projeto, não o reinicie.

## 13. Referências e rastreabilidade
Materiais mencionados anteriormente pela criadora: planilha de cronologia Diablo I–IV e Immortal; Diablo I Tomes; Book of Cain, Book of Tyrael, Book of Adria, Book of Lorath; lista de demônios. Esses materiais não foram integralmente recuperados nesta elaboração. Não alegar que foram relidos ou que cada detalhe foi verificado neles. A futura auditoria deve localizar os originais e adicionar citações por arco.

Repositório conhecido: https://github.com/Vranuska/Sociedade-de-Tristram — branch historicamente inspecionada: feature/configurable-rates. Documento de quest legada: docs/forgotten-house.md. Proposta anterior: docs/propostas-lore/01-o-ultimo-juramento.md. Verificar o HEAD antes de assumir que ainda são atuais.

Referências oficiais a consultar na revisão: Diablo II: The Story So Far (Blizzard), textos e tomos originais de Diablo I, histórias oficiais e livros licenciados. Tratar wikis e teorias de fãs como pistas de pesquisa, nunca como prova suficiente de cânone.

## 14. Registro de decisões futuras
DECISÃO PENDENTE: ordem dos arcos e integração com Maera. DECISÃO PENDENTE: uso de recursos visuais dedicados. DECISÃO PENDENTE: onde residem os documentos de pesquisa originais. DECISÃO PENDENTE: estado de build e HEAD atual. Nenhuma pendência autoriza reescrever escolhas anteriores por conta própria.
