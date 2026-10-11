# A casa que Tristram esqueceu

História original da Sociedade de Tristram. Não é conteúdo atribuído ao Patreon/TH4.

## Estado da implementação

Capítulo I implementado: conversa da Adria, depoimentos de Cain/Gillian/Farnham, duas respostas à Adria, anotações consultáveis e progresso por personagem. Conteúdo inicialmente exclusivo do modo solo, fora do Coliseu. Sem alteração de quests originais ou serviços dos NPCs.

A casa, pistas físicas, encontro final, recompensas e NPC permanente ainda não estão implementados. O estado 2 é o fim do capítulo I, não conclusão da quest nem resgate.

## Direção narrativa

Alguém protegeu uma pessoa de uma entidade apagando sua existência da memória de Tristram. Investigar devolve lembranças, mas também torna essa pessoa localizável. Adria precisa de um intermediário porque a entidade reconheceria sua presença. A intenção dela permanece ambígua e deve ser demonstrada por contradições concretas, não explicada inteiramente num monólogo.

O jogador não precisa escolher em quem acreditar antes de ouvir todos. O registro de Cain, a tigela de Gillian e a canção de Farnham são três manifestações do mesmo evento. A resposta à Adria fica registrada para influenciar diálogos futuros; não encerra caminhos de conteúdo.

## Próximos capítulos

1. Entrada própria para a casa, pistas físicas e mudanças no ambiente. Evitar alterar a geometria original de Tristram antes de validar carregamento, colisões e persistência.
2. Objetos recuperados alteram as lembranças dos moradores. A cadeira e a tigela associam a sobrevivente aos animais desaparecidos, preparando sua futura função sem um anúncio de serviços.
3. Encontro próprio: canção anuncia ataque, espelho revela posição e cadeira indica alvo. Investigar ensina o combate. Não reutilizar uma morte normal de boss como se fosse o confronto da história.
4. Decisão entre apagar o nome, devolvê-lo ou entregar a lembrança à Adria. Consequências narrativas e recompensas distintas, sem rótulos de moralidade ou lista antecipada de prêmios.
5. Devolver o nome resgata diretamente a cuidadora. Outras decisões podem levar a um resgate posterior com consequências. A NPC só é colocada permanentemente na cidade após o resgate efetivo.

## NPC após o resgate

Cuidadora adulta, nome próprio ainda a definir. Mora num ponto validado da cidade. Deve aparecer após recarregar o personagem e em novas partidas, usando o estado individual de resgate. Retrato/sprite dedicado é desejável; uma arte existente pode servir como provisória, claramente identificada na entrega.

Funções planejadas: missões de treinamento que liberam habilidades individuais dos companheiros; receitas de comidas favoritas; histórias de novos resgates. Serviços devem ter implementação real antes de aparecerem como opções disponíveis.

Limite técnico atual: Towners[16], FreeTowners percorre 16 e algumas tabelas de fofoca usam IDs existentes. Não aumentar esse limite nem inserir um ID em tabelas antigas sem auditar todos os consumidores. NPC nova precisa de diálogo independente e slot disponível, ou expansão consistente de toda a estrutura.

## Persistência e validação

AdditionalSaveInfo.unused: byte 80 = estado (0 não iniciado, 1 investigação, 2 capítulo I concluído); 81 = máscara dos depoimentos (Cain 1, Gillian 2, Farnham 4); 82 = resposta à Adria (1 contradição, 2 acusação). Bytes 0..65 pertencem aos sistemas anteriores. Nenhum formato de save foi aumentado.

Teste isolado executado com as funções reais: aceitar/adiar; ouvir relatos sem registrar; registrar em sequência; exigir três relatos para avançar; salvar resposta; consultar anotações; impedir início no multiplayer; preservar bytes anteriores. Compilação MSVC e apresentação visual precisam ser verificadas no Windows.

Para testar no jogo: Adria → A casa esquecida → aceitar; procurar o novo assunto em Cain, Gillian e Farnham; registrar cada relato; voltar à Adria; escolher uma resposta; fechar/reabrir e salvar/carregar para conferir persistência. Os serviços existentes devem continuar acessíveis.
