# A Casa Esquecida: erro de arquivo ao seguir a canção

## Causa identificada no código

`MemoryGenerateHouse()`, em `src/PlayerTrade.cpp`, chama diretamente:

`LoadQuestDungeonMainMapChurch("Levels\\L1Data\\ForgottenHouse.DUN", 40, 34)`

O mapa existe no repositório em
`Sociedade de Tristram/TH/res/thdata/Levels/L1Data/ForgottenHouse.DUN`
(19588 bytes), mas `tools/build-win32.ps1` compila apenas o executável.
`OpenGameArchives()` habilita `SFileEnableDirectAccess(1)`, que permite
carregar arquivos externos da instalação. O mecanismo genérico de erros de
arquivos pode mencionar DIABDAT.MPQ quando falta um recurso de nível.

Assim, a hipótese mais forte para a falha logo após selecionar
**Seguir a canção até a casa** é a ausência do mapa na pasta de execução.
O teste em jogo ainda é necessário para confirmar.

## Deploy seguro (sem modificar saves e sem substituir MPQ)

Do diretório `Sociedade de Tristram/TH`, no PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File "..\\..\\tools\\install-forgotten-house.ps1" -GameDir "C:\\CAMINHO\\DA\\PASTA\\DO\\JOGO"
```

O script verifica a origem (19588 bytes), exige que a pasta tenha o
executável, evita instalação com o jogo aberto, copia o arquivo em
`Levels/L1Data/ForgottenHouse.DUN` e verifica seu SHA-256.
Se houver versão diferente do mapa, cria backup antes de substituí-la.
Não copia nem modifica `DIABDAT.MPQ`, `TH4data.mor`, saves ou EXE.

**Não altere o caminho dentro do código sem antes confirmar o caminho
resolvido por SFileOpenFile.** Não coloque o mapa dentro de `res/thdata`
na pasta do jogo; a raiz do caminho interno já começa em `Levels`.

## Teste

Após instalação, feche e reabra o jogo e escolha novamente a missão
em um personagem de teste, com cópia dos saves.

Se ainda ocorrer o erro, registrar: pasta do executável iniciado,
presença de `Levels/L1Data/ForgottenHouse.DUN` naquela pasta, e, se
possível, o nome do recurso exato que falhou. Investigar se o carregador
consulta a pasta de trabalho ou diretório do EXE e a existência da paleta
`Levels/L1Data/zContrastique.pal` no pacote de dados.

Compilação não é necessária para a cópia do asset; a branch acrescenta
somente o instalador e sua documentação.
