# Sigilos — gerador de itens de teste (18/10/2026)

## Razão
A branch de bônus passivos compilou em Windows Debug/Win32, mas a vinculação,
os saves e os efeitos ainda precisam de testes **dentro do jogo**. Colocar
Sigilos no loot geral agora misturaria esse trabalho experimental com a
economia regular de drops.

## Ferramenta nova
No **modo Debug** (não Release), com o jogo em **single-player**,
pressione **Alt+Shift+S** em uma área com espaço livre perto do personagem.
O atalho cria **um** Sigilo no chão próximo ao personagem, na sequência:
Véu, Ferro, Arcano, Pacto, Brasas, retornando depois ao primeiro.
A cada tecla segurada, repetições automáticas são ignoradas. O ciclo só
avança se o item foi criado com sucesso; do contrário aparece mensagem
de falta de espaço. Não injeta itens no inventário, nem altera diretamente
a estrutura ou o formato dos saves.

Se a build definir `CHEATS`, é necessário habilitar a configuração
`devmode`; o antigo Alt+S sem Shift continua alternando magias livres.

## Como experimentar
1. Faça backup dos saves e use um personagem de teste.
2. Rode `python tools/check_sigil_test_spawn.py` na raiz do repositório.
3. Faça rebuild: `powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1`.
4. Entre em um jogo solo, aperte Alt+Shift+S com espaço próximo, recolha
   o Sigilo, abra inventário (I) e a aba S e clique no slot correspondente
   com o item no cursor.
5. Confira a alteração de atributos e depois clique com cursor vazio
   para retirar o Sigilo. Confirme que o item voltou inteiro e os bônus
   desapareceram.
6. Confira no save **de teste** se a vinculação persiste após salvar e
   recarregar. Depois confirme as rotinas normais de baú, gemas,
   companheiros, organização e armas que já existiam.
7. Multiplayer não permite gerar itens com o novo atalho nem vincular
   Sigilos; nenhum bônus passivo dos Sigilos deve funcionar nesse modo.

**Estado:** fonte publicada e verificação estática disponível. Ainda
aguarda compilação no Windows e validação em execução. A taxa normal de
drops permanece zero para os cinco protótipos.
