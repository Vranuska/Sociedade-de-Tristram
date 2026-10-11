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

## Jornada de vínculo: Quem fica esperando

Após o resgate, Maera oferece uma missão para cada companheiro a partir do nível 5. Uma jornada fica ativa por vez. O companheiro escolhido deve estar selecionado, chamado e próximo do personagem ao compartilhar as lembranças do espelho, da tigela e da cadeira na casa já libertada. A ordem é livre; cada cena tem um comportamento próprio para Jason, Kuroko, Mizuki, Thor, Lord ou Pitty. Não há exigência de mortes nem itens consumidos.

As três lembranças liberam a conclusão com Maera na cidade. Recompensa por companheiro, uma única vez: +15 afinidade e Instinto de Retorno. Com esse companheiro ativo, o personagem recebe +10 armadura e sua habilidade básica recebe -10% de recarga, respeitando os limites mínimos existentes. Jason recebe +20 armadura para o personagem e a mesma redução de recarga básica. O aprendizado aparece na ficha de habilidades e acompanha o personagem entre partidas.

Persistência adicional: byte 102 guarda o companheiro da jornada; 103 guarda a máscara das três lembranças; 104..109 guardam os seis aprendizados permanentes. Sem aumento da estrutura de save. A recompensa pertence ao companheiro escolhido, mesmo se outro estiver ativo ao retornar.

Verificações isoladas executadas com as funções reais e dependências simuladas: nível mínimo, companheiro escolhido, chamado e próximo, relatos dos seis companheiros, ordem livre, repetição das pistas sem duplicação, recompensa restrita à cidade, conclusão única por companheiro, redução real da recarga básica sem mudar a especial e preservação dos dados do resgate. Compilação no Windows e teste dentro do jogo ficam pendentes para esta etapa.

Teste manual: Maera → Quem fica esperando → aceitar com companheiro nível 5 → voltar à casa → compartilhar as três lembranças com ele por perto → voltar à cidade → concluir com Maera → conferir afinidade e Instinto na ficha. Salvar/carregar durante a missão, trocar de companheiro antes de uma pista e repetir após concluir devem preservar ou bloquear o progresso conforme as regras acima.

## Treinamento avançado: Eco do Vínculo

Após concluir a jornada de vínculo daquele companheiro, e a partir do nível 15, Maera ensina Eco por 5000 ouro. O aprendizado é permanente, individual e cobrado uma única vez. A compra equipa o Eco; reaplicar o treinamento aprendido não cobra novamente. A ficha permite alternar entre Original, Agilidade (-20% recarga) e Eco (segundo disparo com 60% do dano do básico). A especial e a passiva mantêm suas opções anteriores.

O Eco acompanha os projéteis básicos dos seis companheiros, com a mesma autoridade do personagem e a marca de dano dos companheiros. Não cria ecos recursivos nem duplica as novas/afterimages especiais. Thor conserva sua tempestade original, sem Eco na rajada especial. Falta de espaço na lista nativa de projéteis apenas impede o disparo extra; não invalida o básico já criado. O Instinto de Retorno continua aplicável junto com a opção escolhida.

Jason agora tem Estalo do Brejo (projéteis arcanos em 1/2/3 alvos conforme a evolução) e Coro do Brejo (nova arcana, a partir do nível 15). Usa efeitos nativos provisórios e as mesmas regras de custo gratuito e progressão de recarga dos demais companheiros. Sua ficha já permite equipar as variantes básicas e especiais. Os nomes das habilidades de todos os companheiros aparecem na ficha.

Bytes 110..115 de `AdditionalSaveInfo.unused` guardam os seis aprendizados de Eco. O modo equipado usa os bytes de habilidades já existentes, com valor 2 autorizado apenas após o aprendizado. Não há expansão do save.

Verificação reproduzível: `python tools/check_maera_echo.py` requer Python e g++. Compila as funções reais de treinamento/ataques contra APIs simuladas e verifica requisitos, ouro insuficiente, cobrança única, isolamento entre companheiros, dano do Eco, marca/autoridade dos projéteis, limite de projéteis, progressão e timers do Jason, filtros de alvos e caminho básico dos seis companheiros. Não substitui a compilação MSVC nem execução dentro do jogo.

Teste no jogo: conferir Jason antes e depois do nível 15; concluir sua jornada ou a de outro companheiro, aprender Eco com Maera, conferir débito de 5000 ouro uma vez, alternar as três variantes na ficha e salvar/carregar. Comparar Agilidade e Eco contra inimigos e confirmar que os ataques especiais não são duplicados pelo Eco.

## Segundo ensinamento: Convergência

No menu de treinamento da Maera, o segundo ensinamento libera a variante Convergência para a habilidade especial. Exige nível 25, afinidade 50, jornada de vínculo concluída e Eco aprendido daquele companheiro. O aprendizado custa 15000 ouro uma única vez; equipar novamente não cobra. A ficha permite alternar Original, Agilidade (-20% recarga) e Convergência (+40% dano da especial).

O bônus afeta a nova do Jason, a nova e os projéteis especiais do Kuroko, a nova da Mizuki, a tempestade do Thor, a nova do Lord e a nova da Pitty. Os disparos básicos e seus Ecos conservam o dano anterior. A opção não reduz a recarga; o Instinto de Retorno e a evolução continuam funcionando. Usa os efeitos nativos existentes, sem novas artes.

Bytes 116..121 guardam os seis aprendizados; o slot especial existente passa a aceitar a variante 2 apenas quando aprendida. Saves antigos seguem usando as variantes anteriores e nenhum campo muda de tamanho.

O teste isolado `tools/check_maera_echo.py` agora cobre também nível/afinidade/pré-requisitos, ouro insuficiente, cobrança única para os seis companheiros, dano de cada caminho especial real, conservação do dano básico e alternância para Agilidade. Compilação no Windows, salvamento dentro do jogo e efeitos visuais continuam pendentes para esta etapa.

Teste manual: com um companheiro elegível, Maera → Treinamento → Segundo ensinamento → aprender; confirmar o débito único de 15000, alternar a especial na ficha, salvar/carregar e comparar dano/recarga contra inimigos. A especial deve ganhar dano com Convergência e frequência com Agilidade.
