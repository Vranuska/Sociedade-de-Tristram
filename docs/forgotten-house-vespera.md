# A casa que Tristram esqueceu — roteiro de Vespera

## O Hóspede sem Rosto

Maera não foi esquecida por acidente. Anos atrás, acolheu um animal que voltava do cemitério com uma sombra a mais. Alimentou o animal, fechou a porta e ouviu três batidas. Na manhã seguinte havia uma cadeira ocupada à mesa. Ninguém conseguia dizer por quem.

O Hóspede não invade casas: ocupa a expectativa de quem está faltando. Não tem um rosto próprio. Usa o intervalo entre a pessoa de quem sentimos falta e aquilo de que conseguimos nos lembrar. Enquanto alguém guardar um lugar para ele, pode aprender a ser essa pessoa.

Adria reconheceu o ritual e ensinou Maera a raspar seu nome dos registros. Não contou que o apagamento também destruiria as lembranças de quem Maera protegia. Cain registra três mortes; Gillian recorda uma criança; Farnham canta a frase que não deveria conhecer. Cada um conserva um pedaço de uma vida que já não cabe em ninguém.

Ao mandar o aventureiro reconstruir a casa, Adria termina uma experiência que não ousou terminar pessoalmente. Ela chama isso de resgate. A carta no quarto de hóspedes permite outra leitura: queria ver se uma entidade sem nome poderia ser transportada dentro da memória de uma pessoa.

O jogador salva Maera, mas não recebe uma confissão de Adria. A suspeita nasce de uma prova material: a mesma tinta e a mesma instrução de deixar uma cadeira vazia. Maera continua sendo uma pessoa capaz de decidir o que contar, não uma recompensa que pertence ao protagonista.

## Percurso implementado

- **Vestíbulo da espera:** passos e inimigos antes da sala original. A saída permanece acessível.
- **Casa antiga:** espelho, tigela, cadeira e nome continuam nas posições originais. As três pistas despertam o Hóspede na ala leste.
- **Arquivo das três mortes, a oeste:** O Escrivão das Três Mortes guarda o registro falsificado. Base visual e IA: Skeleton Lord; três vezes a vida base.
- **Abrigo de cinzas, ao sul:** A Ama de Cinzas guarda o caderno dos animais. Base visual e IA: Zombie; quatro vezes a vida base. Sua recomendação de alimentar a sombra contrasta com a recusa escrita por Maera.
- **Câmara de hóspedes, a leste:** arena ampla para O Hóspede sem Rosto e carta intitulada A Conviteira. A decoração usa os recursos nativos de igreja, livros e velas.

Dez Lembranças sem Dono ocupam as alas, com arte e comportamento nativos de Skeleton Warrior. Os dois minibosses são opcionais: oferecem evidências e tesouros adicionais sem bloquear personagens que já haviam reunido as pistas na primeira versão. Seus ataques continuam sendo os ataques nativos; não foram anunciadas mecânicas exclusivas para eles.

## Combate do Hóspede

Arte provisória e IA nativa de Hidden, nome próprio e cinco vezes a vida base. Não há sprite novo nesta entrega.

1. **Um lugar à mesa:** quatro batidas, separadas por 20 atualizações. A primeira registra a posição do aventureiro. A quarta envia uma chama para essa posição.
2. **Um rosto emprestado:** abaixo de dois terços da vida, intervalo de 16 atualizações e uma chama lateral adicional.
3. **Ninguém ficou esperando:** abaixo de um terço da vida, intervalo de 12 atualizações e duas chamas laterais adicionais.

Ecos interativos do espelho, da tigela e da cadeira repetem as pistas dentro da arena, sem deslocar os objetos originais. O espelho revela a invisibilidade. Estar junto da tigela na quarta batida suprime toda a rajada. O jogador aprende essas respostas nas pistas, antes de enfrentar o chefe. Os diálogos suspendem a contagem; capacidade esgotada de projéteis impede apenas o disparo que não couber.

Os dois minibosses deixam 500 ouro cada e o Hóspede, 1500, multiplicados por dificuldade + 1, além do caminho de drops nativo. O pagamento adicional dos minibosses é registrado uma única vez por personagem; o chefe usa a própria transição da quest para impedir repetição. Após o combate, o jogador volta ao nome no centro e conserva as três escolhas já existentes.

## Consequências e limites

Maera continua desbloqueada somente depois da decisão final. Seus serviços, jornadas e aprendizados existentes permanecem ligados aos mesmos bytes. O byte 86 registra os dois minibosses; os objetos centrais não mudam de coordenadas. Após o resgate, visitas para a jornada dos companheiros não geram os novos encontros.

O mapa foi ampliado de uma sala com 144 células de piso para cinco áreas com 564 células conectadas. Um nível já serializado num save pode conservar a geometria antiga: validar a versão ampliada em um mundo novo, preservando os arquivos de personagem e os saves anteriores. Não excluir saves para testar.

Ainda é necessário testar no Windows: carregamento de mapas especiais pelo ADM, geração do mapa novo, colisões dos corredores, visibilidade dos suportes das pistas, combate com companheiros, retorno à cidade e salvar/carregar nas três fases da quest. Sem dublagem ou sprites inéditos nesta versão.
