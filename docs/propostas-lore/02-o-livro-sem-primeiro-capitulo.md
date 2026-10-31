# VESPERA — DOSSIÊ DE PRODUÇÃO 02
## O Livro que Não Devia Ter um Primeiro Capítulo
**Sociedade de Tristram | proposta de quest investigativa | 31/10/2026**

**Status:** design narrativo e especificação preliminar; NÃO implementada. Complementa, não substitui, `docs/Vespera-Livro-das-Sombras-de-Santuario.md` e `docs/forgotten-house.md`.

### Tese de direção
Uma boa conspiração de Santuário não precisa revelar Lilith em uma sala secreta. Basta que um copista humano tenha eliminado duas palavras de uma oração — e que séculos depois pessoas sejam mortas por insistirem que a oração sempre foi assim. O jogador deve conseguir terminar a história sem entender sua dimensão cósmica. Quem observa as discrepâncias descobre algo maior.

### Cânone x invenção
**Âncoras canônicas a validar em fontes primárias antes do código:** Santuário surgiu da ruptura de anjos e demônios com a Guerra Eterna; Inarius e Lilith estão ligados à sua criação; os primeiros nefalem e o ocultamento da verdade sobre a origem do mundo são centrais à história posterior. Os habitantes de Tristram não conhecem necessariamente esses fatos. Não antecipar a campanha de Diablo IV.

**Original da mod:** o manuscrito, o copista Oren, a viúva Mara, o pregador itinerante, o objeto denominado “placa de bênção”, os registros de importação e as mortes. Nada disso deve ser apresentado como personagem ou artefato oficial.

### Verdade do mestre — não exibir em objetivos
Oren, copista de um pequeno scriptorium, recebeu duas versões de uma prece. A versão antiga descrevia o mundo como “o abrigo dos que recusaram a guerra”. A nova dizia “o abrigo dos que venceram a guerra”. Oren não conhecia Inarius ou Lilith; entendeu apenas que alguém havia transformado uma renúncia em vitória. Guardou a folha descartada dentro de uma capa de contas. Foi morto não por um demônio, mas por um homem que temia que o texto deslegitimasse a autoridade de seu patrono.

O patrono NÃO controla um culto mundial. É um financiador de peregrinos com interesses locais. Um terceiro ator, ligado a colecionadores de escritos arcanos, tentou comprar o original e acabou confundido com o assassino. A aparente grande conspiração é a interseção de pequenas ambições humanas com um segredo cosmológico real.

### Experiência do jogador
**Abertura invisível:** na cidade, um livro de contas de caravanas menciona uma remessa de “capas vazias”. Não há ponto de exclamação. Gillian pode comentar que capas são mais caras que folhas quando um viajante quer esconder o conteúdo.

**Primeira via:** numa masmorra, um cadáver possui uma folha de oração com a palavra “venceram” raspada. O texto é legível mesmo sem missão ativa.

**Segunda via:** Cain reconhece que o estilo da prece é antigo, mas não afirma conhecer sua origem. Ele pede que o jogador compare versões, não que mate alguém.

**Terceira via:** Farnham lembra de uma discussão entre dois viajantes; confunde o nome de um deles, mas descreve corretamente o anel de um intermediário. Seu relato não é prova isolada.

**Revelação básica:** o copista foi morto por uma falsificação e um conflito de interesses; o jogador pode apresentar as provas à viúva, a Cain ou destruir o registro.

**Revelação profunda:** a oração preservada não nomeia os criadores, mas sua formulação é compatível com uma tradição sobre a fuga da Guerra Eterna. Essa leitura é uma hipótese do jogador, não uma confirmação expositiva do NPC.

### Pistas justas (independentes)
| ID | Suporte | Evidência observável | Dedução possível |
|---|---|---|---|
| L01 | Folha raspada | Fibras rompidas sob “venceram” | Texto foi alterado |
| L02 | Contas de caravana | “Capas vazias” pesam mais que remessa anterior | Carga tinha conteúdo oculto |
| L03 | Fala de Gillian | Encadernação não corresponde ao preço declarado | Fraude comercial |
| L04 | Duas orações | Mesma cadência, verbos diferentes | Revisão deliberada |
| L05 | Selo de cera | Anel descrito por Farnham não coincide com selo do patrono | Dois intermediários, não um |
| L06 | Bilhete de Oren | “Não corrigiram o erro. Corrigiram o mundo.” | Oren sabia da alteração, não necessariamente da cosmologia |
| L07 | Lista de óbitos | Morte de Oren antecede suposta entrega assinada | Assinatura posterior é falsa |

**Condição para acusação responsável:** L01 + (L04 ou L06) + L07. **Condição para identificar intermediários distintos:** L05 + (L02 ou L03). Nenhum drop aleatório obrigatório; múltiplos caminhos para encontrar cada família de evidência.

### Diálogos originais
**Cain, primeira folha:** “Uma palavra raspada não me diz o que havia ali. Diz apenas que alguém temeu deixá-la.”

**Gillian, sobre as capas:** “Uma capa vazia? Nunca vi um mercador pagar frete para transportar o que não pesa.”

**Farnham:** “Eram dois. Não, três. Não me peça nomes. Um deles tinha um anel... não, não foi o anel que vi. Foi a marca que deixou na mesa.”

**Oren, anotação:** “Não corrigiram o erro. Corrigiram o mundo.”

**Mara, se o jogador expõe a fraude:** “Eu queria saber quem matou meu marido. Você me trouxe o motivo. Ainda não sei se isso me consola.”

**Cain, conclusão profunda:** “Algumas tradições começam como lembranças. Outras, como desculpas. Não confunda antiguidade com verdade — nem silêncio com ausência.”

### Três desfechos, nenhum altera o cânone
A. **Custódia:** entregar originais a Cain. Preserva prova e permite conversa posterior. O patrono continua em liberdade se não houver acusação suficiente.
B. **Exposição:** entregar provas à viúva e confrontar intermediário. Revela falsificação local, mas dispersa fragmentos do manuscrito.
C. **Silêncio:** destruir o registro; protege a viúva de perseguição imediata, mas impede dedução profunda naquele save. O jogador ainda pode entender a história pelas pistas já vistas.

### Um segredo para daqui a muitas quests
A frase “o abrigo dos que recusaram a guerra” reaparece, incompleta, em outra tradição. A repetição NÃO prova que todos os personagens pertencem à mesma facção. O jogador poderá perceber que a mesma ideia foi copiada, adulterada e instrumentalizada por grupos rivais. Este é o padrão de macrotrama: uma resposta real cria uma pergunta mais precisa.

### Integração técnica — ainda não executada
- Reutilizar apenas objetos e diálogos já auditados; nenhuma nova área/ID/salvamento reservado neste documento.
- Antes da implementação, inspecionar `BaseQuests.cpp`, `Quests.cpp`, `TownMap.cpp`, `Object.cpp`, `GenerateQuestFloor.cpp` e o mapa de persistência atual.
- A documentação `docs/forgotten-house.md` informa que a quest Maera usa DUN ID 115 e bytes 80–86, 96–121 ou mais: **não reutilizar nenhum desses espaços sem auditoria completa**.
- O arquivo `docs/forgotten-house.md` já registra uma versão ampliada da Casa Esquecida com cinco áreas, dois minibosses e Hóspede sem Rosto; esta informação substitui a suposição anterior de que o chefe único continuava sendo apenas A Quarta Batida.
- Construir matriz de flags somente depois de localizar espaços livres e confirmar compatibilidade com saves antigos.
- Testes obrigatórios: descoberta fora de ordem, diálogo repetido, save/load em cada fase, todos os finais, personagem sem pistas, modos restritos, regressão Maera/companheiros, compilação MSVC e jogo real.

### Próxima execução objetiva
1. Auditar as estruturas reais de quests e saves na branch ativa.
2. Validar em fontes canônicas a formulação histórica do apócrifo; nunca atribuir a frase a um texto oficial.
3. Fechar mapa de NPCs e disponibilidade temporal.
4. Criar matriz de flags e tabela de diálogos localizáveis.
5. Implementar em commits pequenos, preservando a Casa Esquecida e todos os sistemas.

### Regra de passagem de bastão
Esta quest está **projetada, não programada**. Em outra conversa, abrir este arquivo e o Livro das Sombras; não reiniciar o projeto nem declarar implementação antes de inspecionar o código.
