# Sigilos — catálogo inicial e integridade de gemas (18/10/2026)

## Descoberta
O The Heaven já reservava cinco bases: **2504–2508**, com gráficos próprios, mas
nenhuma chance de drop. Elas estavam classificadas como `MC_GEM` apesar de não
terem uma entrada na tabela `Gems`. A rotina `SetItemGrade` indexava
essa tabela por subtração direta do ID, o que era perigoso para protótipos
fora da faixa de gemas.

## Implementado nesta branch
- IDs 2504 a 2508 preservados.
- Nomes: Sigilo do Veu (equilíbrio), de Ferro (combate), do Arcano (magia),
  do Pacto (invocações), das Brasas (elementos).
- Classificação `MC_0_NONE` para que não sejam consumidos como gemas.
- `SetItemGrade` agora procura apenas gemas reais; Sigilos legados com
  a classificação antiga são normalizados quando processados nessa rotina.
- Crafting, socketing e receita de transmutação de gemas verificam se o item
  realmente pertence ao catálogo `Gems`.
- Tooltips principais, secundários e auxiliares exibem afinidade e o aviso
  de que ainda não foram vinculados.
- Nenhuma alteração em `Player`, `Item`, versões de save, rede ou IDs
  de itens existentes; nenhuma arma de fogo criada.

## O que ainda NÃO existe
- Drop, receita de criação ou desbloqueio de Sigilos.
- Ativação, benefícios passivos ou espaços seguros para equipá-los.
- Persistência operacional da mochila Talisman, migração e sincronização.
- Qualquer efeito de Sigilos durante o combate.

## Verificações
Na raiz: `python tools/check_sigil_catalog.py` e
`python tools/check_sigil_foundation.py`.
Em seguida, `powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1`.

Gameplay: verifique inventário, gems normais no socketing e em Cain, saves
antigos, tooltips, companions e equipamentos. Este branch ainda aguarda
compilação e testes dentro do jogo.
