# SOCIEDADE DE TRISTRAM — DOCUMENTO MESTRE DE CONTINUIDADE
**Atualizado em:** 30/10/2026  
**Finalidade:** preservar a visão, decisões, progresso, pendências, riscos e procedimento de migração do projeto.  
**Status:** inventário histórico de trabalho. "Implementado" não significa necessariamente validado na versão atual do executável. Sempre confirmar no código e no jogo.

> **Regra de ouro:** Sociedade de Tristram não é só uma tradução nem uma troca de aparência. É uma evolução pessoal do Diablo I / The Heaven, com novas mecânicas, companheiros, exploração, narrativa, acessibilidade e qualidade de vida. Não sacrificar sistemas existentes, compatibilidade de saves ou identidade do jogo por um redesign superficial.

## 1. Identidade, origem e repositório
- **Nome:** Sociedade de Tristram.
- **Origem:** mod/fork de The Heaven, na linhagem de The Hell 4 e projetos predecessores. Preservar atribuições e créditos aos autores originais.
- **Motivação:** projeto pessoal da criadora e de seu marido, desenvolvido por carinho pelo jogo; foco em experiência rica, rejogável, menos repetitiva e com novas possibilidades de builds.
- **Repositório:** https://github.com/Vranuska/Sociedade-de-Tristram
- **Branch de UI em uso:** `feature/ui-rebuild-v1`.
- **Pasta do repositório no Windows:** `D:\Sociedade-de-Tristramrepo`.
- **Pasta de código:** `D:\Sociedade-de-Tristramrepo\Sociedade de Tristram\TH`.
- **Build conhecida:** `D:\Sociedade-de-Tristramrepo\Sociedade de Tristram\TH\build\Sociedade de Tristram.exe`.
- **Compilação conhecida:** na raiz do repositório, executar `.\tools\build-win32.ps1` (Debug/Win32).
- **Princípio operacional:** editar e versionar no GitHub, depois atualizar localmente por comandos Git; evitar scripts/patches avulsos como método principal de entrega.

## 2. Situação recente e histórico verificável
### Confirmado em conversa/teste
- A compilação Debug/Win32 foi concluída com sucesso após o ajuste de atributos.
- **Shift + clique no botão +** da tela de personagem distribui **10 pontos** por clique; validado no jogo.
- Em 29–30/10, as mudanças locais de `CharPanel.cpp` e `InventoryPanel.cpp` foram preservadas no commit local `62b35a9`, depois rebased com sucesso sobre `origin/feature/ui-rebuild-v1`. **Conferir se o commit local foi enviado ao remoto**: o pull/rebase não equivale a push.
- Commits remotos da base visual: `6d30f8e` (declaração da skin) e `23556a6` (desenho do fundo gótico no `UiKit`). **A nova skin ainda NÃO foi ligada ao desenho efetivo da tela de personagem**; não apresentar como interface concluída.
- `UiKit.cpp`, `UiKit.h` e a infraestrutura `UiCore` já existem para desenho em paleta de 8 bits e componentes reutilizáveis.
- A proteção local do botão Organizar em `InventoryPanel.cpp` foi ajustada para não bloquear o clique por estado indevido do cursor; **reteste em jogo pendente**.

### Funcionalidades relatadas como existentes ou protótipos
- Invocação de companheiros.
- Organização automática de inventário, com modos horizontal, vertical e por tipo; houve problemas de hitbox.
- Filtros de envio de itens ao banco/baú.
- Banco compartilhado entre personagens da conta.
- Fusão de pedras/gemas.
- Sockets/encaixes em acessórios, itens raros e únicos.
- Tradução PT-BR parcial, ajustes de fonte e textos.
- Ferramentas/comandos administrativos para criar/testar equipamentos; modo de teste que ignora alguns requisitos de atributos/nível e opção de ignorar restrições de classe.
- Mudanças em experiência, drops e progressão herdadas/documentadas no projeto: controle de velocidade solo, drops raros independentes, melhorias em afixos raros, XP no modo Easy, Swift Learner, Black Mushroom, Psion, Grim Deal e Infernal Bargain. **Auditar presença e comportamento na branch atual**.

## 3. VISÃO CENTRAL — COMPANHEIROS
**Sistema autoral criado para Sociedade de Tristram; não existia originalmente no Diablo I.**

### O que preservar
- Possibilidade de invocar, dispensar e administrar companheiros.
- Interface própria de companheiros, conectada à interface de inventário sem alterar indevidamente a lógica de combate, rede e salvamento.
- Companheiros com identidade, nomes, vínculo/afinidade e estado de desbloqueio.
- Exemplos observados: **Kuroko**, **Thor**, **Lord**, **Jason**, **Mizuki** e **Pitty**.
- Em teste com personagem novo, Kuroko apareceu com **nível 10, afinidade 100 e indicação MESTRE**; Thor e Lord apareceram desbloqueados, enquanto Jason, Mizuki e Pitty estavam bloqueados. **Investigar** se é configuração intencional, estado compartilhado indevido, persistência ou inicialização defeituosa.
- Problema visual identificado: título/cabeçalho da janela de companheiros ultrapassa a borda esquerda.

### Evolução planejada
- **Progressão e experiência próprias dos companheiros**, com critérios claros e balanceamento.
- **Habilidades equipáveis/selecionáveis** para companheiros, sem depender de soluções improvisadas.
- Melhorias da gestão: seleção, leitura do estado, afinidade, nível, bloqueios e habilidades na interface.
- Corrigir sprites, animações e invocação quando quebrados; testar ciclo completo (invocar, acompanhar, trocar/dispensar, salvar e carregar).
- Verificar IA, pathfinding, comportamento em portais/níveis, mortes e transições antes de ampliar recursos.
- Decidir e documentar se desbloqueios e afinidade são por personagem, por conta ou globais; não alterar persistência sem migração de save.

**Não afirmar que XP e habilidades equipáveis já estão finalizados: são parte da visão/roadmap.**

## 4. QUALIDADE DE VIDA E ITENS
### Inventário e banco
- Refazer visualmente **toda** a interface de inventário e Sigilos, não apenas remendar botões.
- Geometria única para **desenho, hover e clique**; nunca repetir coordenadas divergentes.
- Organizar inventário por orientações/modos, respeitando itens que não cabem e preservando posições quando necessário.
- Corrigir a hitbox de Organizar e testar todos os modos com mochila cheia, item no cursor e diferentes resoluções.
- Filtros de envio ao banco/baú, com opções claras e previsíveis.
- Banco compartilhado entre personagens da conta, preservando dados existentes.
- Melhorias de feedback visual, seleção, tooltips, botões, estados desabilitados e mensagens de erro.
- Sistema de Sigilos integrado visualmente, mas **sem reescrever suas regras**.
- Integração visual coerente entre inventário, Sigilos, banco e companheiros.

### Itens, gemas, equipamentos e builds
- Preservar fusão de gemas/pedras; evoluir para **fusão híbrida** (ideia registrada, detalhes ainda a especificar).
- Preservar sockets em acessórios, raros e únicos, verificando limites e persistência.
- Reduzir grind desnecessário e favorecer variedade de builds, incluindo combate corpo a corpo.
- Backlog documentado: **retirar penalidades negativas de itens únicos**, **rerrolar afixos mágicos/raros** e **compartilhamento de itens no multiplayer**. Tratar como propostas, não entregas.
- Comandos ADM para geração/teste de equipamentos, com controles para não afetar a experiência normal.

### Atributos e perks
- Shift + clique = 10 pontos (**implementado e testado**).
- **Campo numérico** para escolher exatamente quantos pontos distribuir.
- **Pressionar e segurar +** para distribuição contínua, com limites e sem envio indevido de comandos de rede.
- Distribuição em lote segura e indicação do saldo restante.
- **NPC em Tristram para redistribuir atributos e perks mediante pagamento em ouro**: proposta ainda não implementada. Definir custo, validações, limites e impacto no multiplayer/saves antes de codificar.

## 5. INTERFACE — DIREÇÃO DE ARTE E IMPLEMENTAÇÃO
**Referência estética:** Diablo IV, adaptado à identidade do Diablo I e à paleta/engine do projeto.

- Gótico sóbrio, pedra escura, ferro envelhecido, dourado antigo e vermelho profundo; tipografia legível.
- Evitar UI genérica, mal alinhada, com rótulos cortados, caixas sobrepostas ou simples pintura sobre arte antiga.
- Tela de personagem totalmente redesenhada, com nome, classe, nível, experiência, atributos, pontos disponíveis, dano, defesa, resistências e regeneração organizados hierarquicamente.
- Tradução visual dos rótulos; investigar **texto gravado na arte CEL** do painel antigo (`Data_CharCEL`) antes de presumir que traduzir strings C++ é suficiente.
- `CharPanel.cpp` usa coordenadas/hitboxes antigas. **Manter renderização e interação alinhadas** ao alterar layout.
- `UiKit` já contém primitivas e tema; há função `UiDrawCharacterBackdrop` implementada mas ainda não conectada à tela de personagem.
- UI de inventário, mochila, equipamentos, abas, Sigilos, baú, companheiros e notificações deve compartilhar componentes e regras.
- Respeitar limitações do framebuffer/paleta de 8 bits, clipping e fontes bitmap.
- Testar escalas/resoluções, estados hover/pressed/disabled, item no cursor e janelas simultâneas.

### Regra técnica inegociável para a reconstrução visual
**Não alterar** mecânicas, combate, serialização de saves, protocolos de rede, regras de itens/Sigilos ou dados persistentes como efeito colateral de uma tarefa puramente visual.

## 6. TRADUÇÃO, FONTES, NARRAÇÃO E ÁUDIO
- Objetivo: experiência **PT-BR coerente**, incluindo interface, classes, atributos, itens, NPCs, quests, tooltips, mensagens e diálogos.
- Revisar strings do código, recursos de arte que contêm texto e problemas de acentuação/codificação.
- Priorizar fonte legível sem perder atmosfera gótica.
- Houve problemas anteriores em tela de carregamento, sprites de pets e narração/dublagem: **revalidar** na build atual.
- Preservar originais e créditos de assets; distinguir traduções paralelas de The Hell 3 e The Heaven da implementação específica de Sociedade de Tristram.
- Arquivos de áudio e logs locais não rastreados devem ser inventariados antes de exclusão; não versionar dumps e binários por acidente.

## 7. QUESTS, MUNDO E NARRATIVA
### Princípios
- Narrativa integrada à exploração e ao lore; **não transformar quests em checklist**.
- Descobertas, segredos, relíquias e referências cruzadas que recompensem atenção do jogador.
- Diálogos naturais, apresentações bonitas e eventos com progressão e recompensas perceptíveis.
- Para NPCs/quests relevantes, preferir recursos narrativos do próprio jogo: marcador de quest quando cabível, falas exibidas adequadamente e interação coerente.

### Forgotten House / Casa Esquecida
- Foram desenvolvidos componentes de código e mapa, inclusive `DUN_115_FORGOTTEN_HOUSE = 115`, `PD_31_ForgottenHouse = 31` e `MemoryGenerateHouse()`, com mapa `Levels\L1Data\ForgottenHouse.DUN`.
- Histórico de teste: mapa/sala foram considerados **simples, feios e pouco interessantes**, com poucos inimigos, sem drop/recompensa satisfatória e texto mal apresentado.
- Houve relato de personagem preso e de conclusão sem portal/recompensa/encerramento claro; correção não foi validada.
- **Refazer a experiência narrativa e espacial**: mapa, composição, inimigos, diálogos, sinalização, progressão, recompensa e saída. Não considerar concluída só porque o mapa carrega.
- Personagens/elementos já associados ao protótipo incluem memórias, cuidador e Maera; preservar continuidade ao reescrever.
- Há branch histórica `feature/forgotten-house-deployment-20261018`; comparar com a branch atual antes de integrar.
- Outras ideias registradas: arco relacionado a **Adria** e um conjunto de aproximadamente seis propostas de quests/lore. **Recuperar especificações originais antes de inventar conteúdo novo**.

## 8. ESTABILIDADE, BUGS E TESTES
- Crashes históricos ao interagir com baú/caixa após portais e falhas em renderização de masmorra, incluindo `DrawSceneDungeonTop`.
- Arquivos históricos de diagnóstico: `SociedadeDeTristram_Error.log`, `TheHeaven_Error.log`, dumps e `Th4Crash.log`. Datas/builds variam; **não concluir que um erro foi corrigido com base em log antigo**.
- Revisar loading screen, sprites, invocação, áudio, inventário, hitboxes, quest Forgotten House e transições.
- Verificar compatibilidade de saves entre versões do próprio mod; há incompatibilidade histórica documentada com TH4.
- Criar matriz de testes: iniciar personagem, abrir painéis, alocar pontos, salvar/carregar, entrar/sair de portais, interagir com baús, equipar itens, usar banco, trocar companheiros, concluir quests e testar multiplayer quando pertinente.
- Compilar e testar **a versão exata** que será distribuída; não confundir Debug em `TH\build` com executáveis antigos na pasta do jogo.

## 9. BACKLOG PRIORIZADO
### P0 — Segurança e integridade
1. Preservar commits locais/remotos e fazer backup de saves e assets antes de mudanças estruturais.
2. Confirmar estado do Git e executar testes de compilação da branch atual.
3. Investigar crashes, regressões e integridade de saves; evitar exclusões indiscriminadas.

### P1 — Interface e funcionalidade prometida
4. Integrar `UiDrawCharacterBackdrop` de fato em `CharPanel.cpp`; revisar arte CEL antiga e rótulos.
5. Concluir redesign gótico da tela de personagem, com tradução completa.
6. Implementar entrada numérica, segurar + e distribuição em lote segura.
7. Concluir redesign do inventário, Sigilos e componentes compartilhados; validar hitboxes.
8. Retestar Organizar e filtros do banco, sem alterar suas regras.

### P2 — Companheiros e experiência
9. Corrigir janela, sprites, estado de desbloqueio, afinidade e persistência dos companheiros.
10. Especificar/implementar progressão, XP e habilidades equipáveis de companheiros.
11. Integrar interface de companheiros ao restante da UI.
12. Projetar NPC de respec de atributos/perks por ouro.

### P3 — Conteúdo e expansão
13. Recriar Forgotten House como quest completa e agradável de jogar.
14. Recuperar e especificar as demais quests, incluindo Adria.
15. Expandir fusão híbrida, melhorias de itens/afixos, compartilhamento multiplayer e builds.
16. Finalizar tradução, fontes, narração e polimento geral.

## 10. MAPA TÉCNICO INICIAL
- `Sociedade de Tristram/TH/src/CharPanel.cpp` — painel de personagem e distribuição de pontos.
- `Sociedade de Tristram/TH/src/InventoryPanel.cpp` — inventário e controles relacionados.
- `Sociedade de Tristram/TH/src/UiKit.cpp` e `include/UiKit.h` — desenho e componentes reutilizáveis.
- `UiCore` — geometria e regras compartilhadas de layout.
- `Panel.cpp`, módulos de NPC/quest, companions, stash e recursos de arte/áudio — auditar conforme cada tarefa.
- `theheaven.vcxproj` — verificar inclusão de novos arquivos C++ quando necessário.
- **Não confiar neste mapa como lista exaustiva**: consultar a árvore atual do repositório.

## 11. PROCEDIMENTO DE MIGRAÇÃO / RETOMADA
1. Ler este documento e o README do repositório.
2. Identificar branch ativa, commits remotos e locais, arquivos modificados e não rastreados.
3. **Nunca executar `git reset --hard`, `git clean -fd`, `git add -A` ou `git push --force` sem auditoria e autorização explícita.**
4. Antes de pull/rebase, preservar alterações rastreadas; antes de push, revisar o diff.
5. Tratar saves, arquivos de áudio, assets locais, executáveis e dumps como categorias diferentes; não incluir tudo em um commit.
6. Comandos de diagnóstico seguros:
   - `cd "D:\Sociedade-de-Tristramrepo"; git status --short`
   - `git branch --show-current`
   - `git log -5 --oneline`
   - `git log origin/feature/ui-rebuild-v1..HEAD --oneline` (commits ainda não enviados, se a referência remota estiver atualizada)
7. A atualização do código local deve ser via GitHub + Git. Não pedir à usuária que baixe patches avulsos.
8. Fazer alterações em etapas pequenas, com commits claros; compilar apenas quando a etapa estiver pronta e for útil testá-la.
9. Em cada etapa registrar: o que mudou, o que foi testado, o que continua pendente e o próximo comando.
10. **Estilo de colaboração:** respostas em português brasileiro, afetuosas, instruções técnicas curtas, um comando por vez, sempre com caminho completo quando necessário. Ao encerrar uma etapa, pedir autorização para prosseguir.

## 12. O QUE NÃO PODE SER PERDIDO
- Identidade e autoria do mod; créditos à linhagem de origem.
- Sistema autoral de companheiros e seus nomes/estados.
- Qualidade de vida: organização, banco compartilhado, filtros, fusão, sockets.
- Tradução PT-BR e direção artística gótica.
- Histórias e segredos, com atenção especial à reconstrução de Forgotten House.
- Segurança de saves, rede, lógica de itens e compatibilidade.
- Commits de UI e o atalho Shift+10 já validado.
- A distinção rigorosa entre **ideia**, **protótipo**, **código presente**, **compilado** e **testado em jogo**.

---
**Nota de fidelidade:** este documento compila decisões e fatos conhecidos de conversas anteriores. Detalhes não recuperados (por exemplo, a especificação integral das seis quests, custos exatos de respec e regras definitivas de XP dos companions) foram mantidos como pendências, não inventados. Atualizar este arquivo conforme cada funcionalidade for especificada e testada.
