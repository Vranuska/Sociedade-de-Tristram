# Melhorias em equipamentos únicos (2026-10-17)

Branch `feature/unique-refinement-20261017`, criada a partir da revisão de segurança do Quenching.

## O que mudou
- Itens únicos verdadeiros (não raros nem conjuntos) exibem o progresso de refinamento diretamente no painel de Griswold.
- Refino é desativado quando todos os espaços de efeitos estão ocupados e nenhum efeito de refinamento existe.
- Ao refinar um único, a operação só cobra se o bônus foi gerado e o ID/nome do único permaneceram intactos.
- Equipamentos marcados como itens de missão não podem ser refinados.
- Nenhuma alteração em formatos de save, nomes de únicos, raridades ou valores de bônus.
- Nenhuma arma de fogo.
- O script `tools/build-win32.ps1` localiza o `fxc.exe` x86 do Windows SDK e executa um rebuild `Debug|Win32` sem exigir alteração permanente do PATH.

## Testes Windows pendentes
1. Executar `powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1` na raiz do repositório.
2. Conferir que o arquivo `build\Sociedade de Tristram.exe` é gerado.
3. Abrir o refinamento de Griswold com um único identificado que ainda tenha espaço de efeitos.
4. Verificar o indicador `UNICO: aprimoramento 0/9` (ou nível aumentado por vantagens).
5. Refinar uma vez, conferir bônus, ouro, nome e índice do único; salvar e recarregar.
6. Verificar que um único sem espaço para novos efeitos não permite cobrança por tentativa inválida.
7. Validar conjunto, item raro, item comum e item de missão; conferir classes especiais.
8. Conferir se os companheiros, inventário, transmutação e missão Forgotten House continuam acessíveis.

A execução dos testes de Windows e gameplay depende do PC da autora.
