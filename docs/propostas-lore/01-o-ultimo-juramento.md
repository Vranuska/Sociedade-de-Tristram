# Sociedade de Tristram — Proposta narrativa 01: O Último Juramento

**Estado:** proposta de roteiro, NÃO implementada. Não substitui Forgotten House nem altera sistemas, saves ou mapas.
**Período:** durante os acontecimentos de Diablo I, antes do confronto final com Diablo.
**Âncora canônica:** os Horadrim, liderados na perseguição por Tyrael e com Jered Cain entre os que selaram Diablo, ocultaram sua Pedra das Almas sob a Catedral de Tristram. A ordem declinou; mais tarde Leoric, Lazarus e Albrecht foram envolvidos na corrupção de Diablo.
**Fonte primária de cronologia:** https://news.blizzard.com/pt-br/article/23725427/diablo-ii-a-historia-ate-aqui

## Premissa
A remoção de pedras de uma galeria sob a Catedral revela uma inscrição horádrica secundária e uma correspondência de um guardião mortal sem nome. Não há uma nova Pedra das Almas. A correspondência ordena que a existência de uma passagem de manutenção seja apagada dos registros para evitar que pessoas comuns encontrem o local do selo original.

## Estrutura jogável
1. **O indício:** uma carta manchada e o selo incompleto são encontrados numa área lateral de masmorra já existente. O jogador pode levá-los a Cain.
2. **O testemunho:** Cain identifica a tradição horádrica, mas não conhece o guardião da carta. Ele explica apenas o que é historicamente plausível; não prevê Diablo II/III.
3. **A descida:** numa ala isolada, o jogador encontra sinais de que moradores buscaram abrigo ali e foram deixados do lado errado de uma porta selada. Rastros de luta, marcas de unhas e um diário fragmentado contam o episódio sem exposição excessiva.
4. **O conflito:** um antigo mecanismo defensivo corrompido e os mortos que ele reteve protegem o registro. O combate usa inimigos e efeitos compatíveis com a arte da masmorra, sem chefes cósmicos inventados.
5. **A decisão:** (A) entregar o registro a Cain, para conservar conhecimento sob custódia; (B) destruir a cópia acessível, preservando a localização do selo; (C) guardar o registro, assumindo risco de futuras interpretações. Nenhuma opção muda o destino canônico da Pedra das Almas.
6. **Epílogo:** reações breves e distintas de Cain e dos moradores; recompensa material moderada e sem alteração do cânone.

## Diálogos originais — primeiro rascunho
**Cain, ao ver a carta:** “Não reconheço a mão que escreveu isto. Mas conheço o juramento. Havia homens encarregados de guardar portas que ninguém deveria encontrar.”
**Diário, última página:** “Disseram que o selo protegia a cidade. Do outro lado da porta, ouvi minha filha chamar. Continuei segurando a tranca.”
**Cain, conclusão:** “Há uma diferença entre guardar um segredo e permitir que ele decida por nós. Os Horadrim também tiveram de aprender isso.”

## Cânone e invenção
- **Canônico:** Horadrim, Jered Cain, a prisão de Diablo sob a Catedral, decadência da ordem, Leoric/Lazarus/Albrecht.
- **Original da mod:** guardião anônimo, correspondência, galeria, vítimas, mecanismo, decisões e falas acima.
- **Não permitido:** alterar o destino de Diablo, inventar outra Pedra das Almas, fazer Cain prever o futuro, inserir personagens de épocas posteriores sem justificativa.

## Preservação técnica
- Não remover Forgotten House, Maera, companheiros, jornadas, treinamento, progressão, nem suas chaves de save.
- Primeiro criar um roteiro aprovado e um mapa de compatibilidade com as funções existentes; só então implementar numa branch de trabalho separada.
- Investigar antes de reutilizar DUN_115 e bytes 80–124 do save, já ocupados por Forgotten House/Maera.
- Verificar build MSVC Win32, entrada/saída, combate, diálogos, escolhas e save/load antes de declarar jogável.

## Futuras quests ancoradas no cânone
- **Vestígios de Zakarum:** documentos e peregrinos sobre a fé de Akarat e sinais de corrupção institucional, sem deslocar Mephisto de sua prisão em Travincal.
- **Cinzas dos Clãs:** consequência local de antigas disputas de magos, após validar a cronologia em fontes primárias.
- **Os nomes que não voltaram:** vítimas da expedição de Lazarus à Catedral, com base na história confirmada do Açougueiro.

**Observação:** proposta narrativa deliberadamente separada do código; a seleção final das histórias e sua integração ainda precisam de revisão de lore e de viabilidade técnica.
