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

**Correção de acionamento:** a versão inicial dependia da variável
`IsShiftPressed`, que não era atualizada quando a tecla Shift chegava como
`WM_SYSKEYDOWN` depois do Alt. O teste agora consulta `GetKeyState` e
é tratado em `WM_KEYDOWN` e `WM_SYSKEYDOWN`, independentemente da ordem
em que Alt e Shift foram pressionados.

Não é necessário habilitar `devmode` para **Alt+Shift+S** na build Debug,
mesmo que `CHEATS` esteja definido. A função antiga de **Alt+S** continua
exigindo as condições originais do modo de desenvolvimento quando disponível.

Ao funcionar, aparece uma mensagem começando com **TESTE SIGILOS:**.
Se ela não aparecer, confira se o executável executado é a nova build Debug,
se o jogo está em primeiro plano e se há uma partida carregada. A presença
do botão **S** no inventário indica que o código da interface de Sigilos está
carregado, embora não prove que o atalho esteja funcionando.

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

**Estado:** correção do atalho publicada e verificação estática disponível.
Ainda aguarda compilação no Windows e validação em execução. A taxa normal
de drops permanece zero para os cinco protótipos.
