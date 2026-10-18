# Sigilos — primeiros bônus passivos (18/10/2026)

Branch `feature/sigils-passives-20261018`, baseada em
`feature/sigils-binding-ui-20261018` (compilada com sucesso no Windows).

## Bônus em jogo solo

| Sigilo (base ID) | Bônus vinculado |
|---|---|
| Véu (2504) | +2 defesa e +3 resistência a elementos não físicos |
| Ferro (2505) | +3% dano físico e +5 precisão |
| Arcano (2506) | +4 pontos percentuais a magias com elemento (exceto Espírito de Ossos) |
| Pacto (2507) | +5% dano das invocações |
| Brasas (2508) | +6 pontos percentuais a magias de fogo |

### Implementação
- `CalcCharParams` já recalcula resistências, dano, precisão e poder mágico;
  os Sigilos são aplicados após equipamentos e bônus de refinamento, usando
  os cinco slots reservados e conferindo cada ID específico.
- Em recálculos sucessivos, os valores não são somados cumulativamente, pois
  são derivados novamente dos slots vinculados.
- O vínculo e a retirada chamam `RecalcPlayer` imediatamente.
- A aba `S` informa o bônus de cada espaço e seu estado; os três tooltips
  também mostram os efeitos disponíveis ao vincular.
- Reservas vazias legadas de personagem (itens zerados) são aceitas; espaços
  ocupados por itens desconhecidos não são sobrescritos.
- A aplicação **não ocorre em multiplayer**, assim como a operação de vínculo.
- `Player`, `Item`, enums e versão do save não mudaram.
- Não foram adicionados drops, receitas, progressão de níveis ou armas de fogo.

### Testes pendentes
1. Fazer backup dos saves antes de iniciar a build experimental.
2. Executar na raiz: `python tools/check_sigil_passives.py` e
   `python tools/check_sigil_binding.py`.
3. Compilar com `powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1`.
4. Com cópia de personagem e Sigilos de teste (se disponíveis), observar o
   aumento de atributos/dano compatível com cada bônus após vincular.
5. Desvincular e confirmar que os atributos retornam exatamente ao normal.
6. Alternar a aba, abrir baú e companheiros, manter itens no cursor, verificar
   slots ocupados por dados legados; garantir que nenhum item seja substituído.
7. Salvar, fechar e recarregar: conferir Sigilos e bônus, sempre em cópias.
8. Em multiplayer, nenhum bônus deve ser aplicado e o vínculo deve ser negado.

Esta branch é experimental. A compilação do novo código, o teste de interface
e o round-trip dos saves ainda **não foram realizados**.
