# A casa que Tristram esqueceu

História original da Sociedade de Tristram; não atribuída ao Patreon/TH4.

## Primeira versão jogável

Adria abre a investigação. Cain, Gillian e Farnham guardam relatos incompatíveis, que o jogador registra em qualquer ordem. Depois dos três relatos, duas respostas à Adria ficam salvas. A opção **Seguir a canção até a casa** abre uma instância própria, sem mudar as quests originais.

Na casa, três lembranças ensinam o confronto: o espelho revela a criatura oculta, a tigela impede seu ataque periódico quando o jogador está próximo e a cadeira explica as quatro batidas. A primeira registra a posição do jogador; a quarta lança uma chama naquela direção. Reunir as três lembranças acorda **A Quarta Batida**, uma criatura com três vezes a vida de sua base. Seu comportamento original também permanece ativo.

Depois do combate, o nome no centro da sala oferece três decisões: devolver o nome a Maera, apagar o nome preservando sua vida, ou entregar a lembrança à Adria. Todas libertam Maera nesta primeira versão. A escolha fica salva e altera os diálogos; consequências e recompensas distintas ainda são expansão futura.

Maera aparece permanentemente perto de Gillian **somente após o resgate**. Seu menu independente oferece acesso ao painel dos companheiros e petiscos: +5 de afinidade por 300 ouro multiplicado pelo nível do companheiro. Uma porção por nível de cada companheiro; sem cobrança quando já servido, afinidade máxima ou ouro insuficiente. A recompensa inicial da quest é esse serviço.

Disponível no solo, fora de Coliseu, Ironman, Survival, Speedrun e Nightmare. Esses modos ficam excluídos para não abrir retorno à cidade que contorne suas regras.

## Visual provisório e expansão

A sala usa a arte de igreja existente. As lembranças usam livros como suportes visuais, com nomes e textos próprios; não há sprites dedicados de espelho/tigela/cadeira. Maera usa provisoriamente a arte da Gillian, com alocação própria. Novas missões de companheiros, treinamento de habilidades, receitas como itens e consequências maiores das escolhas ainda não foram implementados.

A narrativa preserva a ambiguidade da Adria: ela conhece a canção, pede um intermediário e quer guardar a memória que poderia denunciá-la. A mulher apagou sua identidade para proteger os animais que acolhia. O jogador decide o que a cidade pode recordar, sem rótulos de moralidade.

## Persistência

`AdditionalSaveInfo.unused`, já existente no save:

| Bytes | Conteúdo |
|---|---|
| 80 | Estado: 0 não iniciada; 1 relatos; 2 casa/confronto; 3 entidade derrotada; 4 resgate concluído |
| 81 | Depoimentos: Cain 1, Gillian 2, Farnham 4 |
| 82 | Resposta à Adria: 1 contradição; 2 acusação |
| 83 | Lembranças: espelho 1, tigela 2, cadeira 4 |
| 84 | Resgate de Maera |
| 85 | Decisão final, 1..3 |
| 96..101 | Último nível alimentado de cada um dos seis companheiros |

Nenhuma estrutura de save foi aumentada. O dungeon novo usa ID 115, dentro do limite reservado de 128. Não houve renumeração dos mapas anteriores. Towners foi ampliado consistentemente para 17 slots e o identificador novo usa diálogo independente, sem consultar tabelas antigas de fofocas.

## Validação

Teste isolado das funções reais em C++ com interfaces simuladas: transições da investigação, ordem dos relatos, restrições de modo, pistas, proteção contra guardião duplicado, quatro batidas, proteção da tigela, revelação pelo espelho, três finais e cobrança limitada dos petiscos. Não substitui o MSVC nem execução do jogo.

Asset DUN conferido: dimensões, tamanho das quatro camadas finas, conectividade do piso e posições de entrada, saída, pistas, luzes e guardião. O gerador reproduzível está em `tools/generate_forgotten_house.py`.

Pendente no Windows: compilar e testar colisões/renderização, combate, retorno à cidade, save/load durante cada etapa e reaparecimento de Maera em outra partida. A inicialização dos NPCs não é sobrescrita pelo carregamento do mapa salvo da cidade, que não restaura MonsterMap nesse caso.

## Roteiro de teste manual

Adria → aceitar → registrar os três relatos → Adria → responder → seguir canção. Ler e devolver as três lembranças, combater, ler o nome central e escolher. Voltar pela saída e falar com Maera perto de Gillian. Salvar/carregar e conferir que ela permanece. Alimentar um companheiro duas vezes no mesmo nível: apenas a primeira deve cobrar e dar afinidade. Após subir um nível, uma nova porção deve ser permitida.
