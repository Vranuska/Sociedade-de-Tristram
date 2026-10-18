# Sigilos — vinculação inicial (18/10/2026)

## Implementado
- Aba compacta `S` no canto inferior direito da tela de inventário, sem
  sobrepor os controles de organizar, companheiros ou baú.
- A aba mostra cinco posições fixas, uma por afinidade: Véu, Ferro,
  Arcano, Pacto e Brasas.
- Com o Sigilo correto no cursor, clicar na respectiva posição o vincula.
  Com o cursor vazio, clicar na posição ocupada o retira para o cursor.
- O armazenamento utiliza `Player::TalismanSlots[0..4]`, já parte do
  `Player` serializado na versão atual; não há alteração de tamanho,
  identificação dos itens, enumeração de slots, pacote de rede ou save version.
- Personagens recém-criados inicializam os slots reservados como vazios,
  em vez de usar o zero de `memset` como um `ItemCode` válido.
- Slots ocupados nunca são sobrescritos; outras categorias de item
  são recusadas. Os cinco identificadores de Sigilo são estáveis.
- O inventário normal, o cinto e as áreas de equipamento não são
  reendereçados pela aba dos Sigilos.
- Vinculação temporariamente disponível **apenas em modo de um jogador**.
  Multiplayer exige sincronização de posse de itens antes de ser habilitado.

## Ainda pendente
- Não há bônus passivos, efeitos de combate nem evolução dos Sigilos.
- Os cinco protótipos não são dropados e ainda não têm receita.
- Não há migração de conteúdo desconhecido colocado por outras versões
  nos slots de Talisman; não substituir saves sem backup.
- Não há teste de salvamento/carregamento feito em execução real.

## Testes manuais necessários
1. Faça cópia dos saves originais antes de iniciar o jogo modificado.
2. Rode `python tools/check_sigil_binding.py` e
   `powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1`.
3. Abra o inventário, clique no pequeno botão `S` (canto inferior direito),
   confira a página de cinco espaços; clique novamente para voltar à mochila.
4. Teste com um Sigilo de cada ID **apenas se já tiver esses itens**
   (por enquanto não há loot nem receitas novas). Não use itens de missão
   nem recursos antigos para testes.
5. Vincule com o cursor e retire clicando no mesmo espaço. Confirme que o
   Sigilo volta intacto e que um item diferente não entra no espaço.
6. Feche/abra o inventário, use o cinto e os equipamentos, teste organização,
   companheiros, baú e caixas de diálogo com a aba aberta/fechada.
7. Faça o teste de salvamento/carregamento **em cópias** dos personagens.
8. Em sessão multiplayer, confirme que a vinculação é recusada.

A compilação e os testes de gameplay desta etapa ainda não foram executados
no computador da autora.
