# Sociedade de Tristram

**Um pequeno projeto feito por amor a Diablo I, com desenvolvimento em andamento.**

[Read in English](README.md) · [Código-fonte](Sociedade%20de%20Tristram/TH) · [Créditos](#créditos-e-origens)

Jogo Diablo desde **1996**. Mesmo depois de tantos anos, continuo apaixonada por Tristram. Este repositório é uma tentativa pessoal de dar vida a ideias que sempre quis experimentar no jogo. Estou aprendendo durante o processo: é um projeto modesto, não um produto acabado.

> **Importante:** este repositório está em desenvolvimento. Existem funcionalidades integradas ao código, protótipos em branches e ideias ainda não implementadas. Compilar não significa que tudo esteja testado ou pronto para jogar.

## Três projetos diferentes

| Projeto | Objetivo | Altera a jogabilidade? |
| --- | --- | --- |
| **Sociedade de Tristram** | Novas missões, companheiros, itens, interfaces, sistemas e ferramentas de teste | **Sim** |
| **Tradução PT-BR de The Hell 3** | Traduzir fielmente o mod original, sem recursos próprios da Sociedade de Tristram | **Não** |
| **Tradução PT-BR de The Heaven** | Traduzir fielmente o mod original, sem recursos próprios da Sociedade de Tristram | **Não** |

As duas iniciativas de tradução são **trabalhos independentes, planejados/em andamento**, não lançamentos prontos. Sociedade de Tristram utiliza **The Heaven**, que foi desenvolvido sobre **The Hell 4**. **The Hell 3 não é a base do nosso mod**: terá somente um projeto de tradução separado.

## O que estamos desenvolvendo

### Companheiros — sistema criado para este projeto

O sistema de companheiros **não existia no Diablo I original e não foi herdado de The Heaven**. Ele é uma criação do Sociedade de Tristram.

O código já contém estruturas para desbloqueio, seleção, invocação/dispensa, experiência, níveis, afinidade, estágios de evolução e bônus. Há um menu acessível por Farnham e controles relacionados no inventário. Entre os personagens estão **Jason Funderburker, Kuroko, Mizuki, Thor, Lord e Pitty**.

O menu atual é uma interface inicial: nossa intenção é criar uma **janela própria de gerenciamento**, com informações claras e habilidades equipáveis, papéis diferentes e evolução relevante até o fim do jogo.

### Itens, inventário e qualidade de vida

Estamos trabalhando na organização automática do inventário, em atalhos de interface, revisão de slots corretos de equipamentos, itens raros/únicos, encaixes, gemas e aprimoramento de funcionalidades existentes.

A revisão de tradução também verifica nomes, textos e descrições de itens, sem mudar desnecessariamente as mecânicas.

### Missões, exploração e narrativa

A ideia é oferecer mais do que lutas e recompensas: pequenos mistérios que incentivem explorar Tristram com atenção. **Forgotten House** já possui um mapa em uma branch de desenvolvimento, mas **a missão não está sendo anunciada como finalizada na branch principal**.

### Ferramentas de desenvolvimento e diagnóstico

Há um protótipo de **registro leve de eventos de diagnóstico** na branch [`feature/diagnostics-foundation`](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/diagnostics-foundation), com buffer limitado e geração de registro `Diagnostics/Session.log` quando solicitado.

Também usamos compilação Win32/MSBuild, testes e captura de logs durante o trabalho. Alguns scripts BAT/PowerShell de diagnóstico foram utilizados localmente e **não devem ser considerados publicados ou prontos no repositório**.

Estamos desenvolvendo/restaurando um **comando administrativo para criar e testar equipamentos**, inspecionar itens e facilitar a descoberta de erros. A ideia é não precisar depender de horas de jogo para reproduzir um problema específico de item, slot ou geração. A interface e os atalhos desse recurso ainda exigem consolidação e testes.

## Lista de desenvolvimento (a concluir)

Os itens com `[ ]` são tarefas planejadas ou em andamento, **não recursos concluídos**.

### Companheiros
- [ ] Criar uma janela dedicada de gerenciamento, em vez de várias telas de diálogo.
- [ ] Exibir experiência, nível, afinidade, evolução e habilidades de forma clara.
- [ ] Concluir o sistema de habilidades equipáveis e gemas de habilidade.
- [ ] Diferenciar funções dos companheiros e equilibrar a força no endgame.
- [ ] Testar salvamento, desbloqueios, invocação, desempenho e limitações do multijogador.

### Equipamentos e sistemas
- [ ] Estabilizar comando e interface de administrador para criar/testar equipamentos.
- [ ] Concluir auditoria de tradução e categorias/slots, incluindo itens únicos e acessórios.
- [ ] Melhorar agrupamento por tipo e disposição do inventário.
- [ ] Criar **fusão híbrida de gemas de tipos diferentes**, com efeitos próprios e receitas equilibradas.
- [ ] Diferenciar a fusão híbrida do aperfeiçoamento já existente de gemas iguais.
- [ ] Revisar encaixes, refinamento de itens únicos e segurança nos processos de melhoria.
- [ ] Evoluir opções de taxas configuráveis sem prejudicar a experiência padrão.

### Lore quests — ideias para desenvolver

**Conceitos a construir e testar**, ainda não são missões prontas:

- [ ] **The Forgotten House** — concluir o protótipo da casa esquecida: investigar o desaparecimento de seus moradores e descobrir algo escondido no local.
- [ ] **Ashes for Adria** — uma investigação sobre o passado de Adria, com possibilidade de um personagem ou encontro persistente após a missão.
- [ ] **The Letters Never Delivered** — reunir cartas jamais entregues, espalhadas por áreas perigosas, revelando uma história entre habitantes de Tristram.
- [ ] **The Bell Without a Tower** — descobrir a origem do sino que parece ecoar sob Tristram e a razão de seu segredo.
- [ ] **Farnham's Last Promise** — explorar as lembranças e o sofrimento de Farnham com respeito à sua personalidade.
- [ ] **Beneath the Old Cemetery** — uma área escondida que recompense curiosidade e dedicação com narrativa e uma descoberta significativa.

Cada proposta ainda precisa de roteiro, diálogo, gatilhos, integração ao mapa, recompensas, coerência com o lore e testes de salvamento. O objetivo não é acrescentar histórias aleatórias, mas manter a atmosfera de Diablo.

### Diagnóstico, estabilidade e apresentação
- [ ] Integrar e testar os componentes apropriados de diagnóstico na versão principal.
- [ ] Aperfeiçoar logs, rastreamento de problemas de portais/mapas e validação de geração de itens.
- [ ] Organizar scripts e instruções de compilação reproduzíveis.
- [ ] Consolidar branches sem perder recursos ou quebrar atalhos.
- [ ] Documentar alterações e adicionar capturas e instruções de instalação **quando houver uma versão testada**.

## Tradução pura: The Hell 3 e The Heaven

Esses dois esforços **não incluirão nossas alterações de gameplay**. A intenção é preservar o jogo de cada autor e entregar apenas localização para português brasileiro.

**The Hell 3 — somente tradução**
- [ ] Definir versão-base e catalogar textos.
- [ ] Traduzir menus, missões, diálogos, itens e descrições.
- [ ] Revisar terminologia, acentuação, codificação e limites das interfaces.
- [ ] Preparar instruções/arquivos separados, sem companheiros ou outras alterações do nosso projeto.

**The Heaven — somente tradução**
- [ ] Separar uma cópia limpa do upstream sem modificações da Sociedade de Tristram.
- [ ] Isolar traduções de alterações de código e balanceamento.
- [ ] Revisar nomes de itens, habilidades, NPCs, missões e tooltips.
- [ ] Testar e disponibilizar futuramente um pacote exclusivamente de tradução.

**As listas não indicam que já exista um patch pronto para distribuição.**

## Organização do código

O projeto C++ está em [`Sociedade de Tristram/TH/`](Sociedade%20de%20Tristram/TH). Conservamos o [README de The Heaven](Sociedade%20de%20Tristram/TH/README.md), as [notas técnicas](Sociedade%20de%20Tristram/TH/docs/BUILD.md) e os [registros originais de alterações](Sociedade%20de%20Tristram/TH/docs/CHANGELOG.md) como documentação da origem do código — **não como histórico de releases testados da Sociedade de Tristram**.

Branches de desenvolvimento:
- [Diagnóstico](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/diagnostics-foundation)
- [Taxas configuráveis e protótipo Forgotten House](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/configurable-rates)
- [Segurança de melhorias](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/quenching-safety-20261017)
- [Refinamento de itens únicos](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/unique-refinement-20261017)

## Créditos e origens

Este projeto só existe graças a pessoas que dedicaram anos a expandir Diablo. É essencial reconhecer os autores originais.

1. **Diablo I** — **Blizzard Entertainment**, pelo jogo e universo originais.
2. **The Hell / The Hell 4** — **Mordor e equipe The Hell**, pelo trabalho que fundamenta o motor e os sistemas herdados. [Código de The Hell 4 e notas dos autores](https://github.com/roboserg/the-hell-4-src) · [Equipe The Hell](https://www.patreon.com/thmod).
3. **The Heaven** — **roboserg**, autor do mod derivado de The Hell 4, nossa base técnica direta. [GitHub de The Heaven](https://github.com/roboserg/diablo-1-the-heaven).
4. **The Hell 3** — **Mordor / equipe The Hell**, reconhecidos separadamente no projeto de *tradução pura*. [Página de The Hell 3](https://www.moddb.com/mods/diablo-the-hell-3).
5. **Sociedade de Tristram** — desenvolvimento adicional, sistema original de companheiros, experimentos, conceitos de missões, traduções e integração por **Vranuska**.

Os créditos individuais da base permanecem em [`credits.txt`](Sociedade%20de%20Tristram/TH/res/credits.txt) e [`credits1.txt`](Sociedade%20de%20Tristram/TH/res/credits1.txt). Os arquivos e avisos originais devem ser preservados e consultados.

Projeto de fã **não oficial**, sem afiliação ou endosso da Blizzard Entertainment, equipe The Hell ou criador de The Heaven.

---

*Não quero substituir o Diablo I por outro jogo. Quero apenas continuar encontrando motivos para voltar a Tristram.*

**— Vranuska**
