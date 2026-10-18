# Casa Esquecida — preflight e instalador seguro (18/10/2026)

## Erro observado
Escolher **Seguir a canção até a casa** podia mostrar o diálogo genérico
`Sociedade de Tristram nao consegue acessar DIABDAT.MPQ`. O jogo já tinha
carregado a cidade e o arquivo-base. O novo mapa
`Levels\\L1Data\\ForgottenHouse.DUN`, ao contrário, é um arquivo solto
no repositório, não parte do executável compilado.

`LoadFile` usa `File_Open(... FIVE_TRY)`, sem um retorno seguro de falha,
e a rotina antiga de recuperação de arquivos trata muitos erros como
problemas de mídia/MPQ. Essa mensagem **não prova** que DIABDAT.MPQ
esteja ausente.

## O que esta branch faz
- Confere o mapa novo e a paleta exigida por `MemoryGenerateHouse()`
  via `SFileOpenFile`, antes de mudar o dungeon.
- Em caso de falta de recurso, não inicia a transição e informa o
  recurso ausente pelo console do jogo, tanto na missão principal
  quanto no retorno à casa para a jornada de Maera.
- Mantém todos os estados, quests, itens e estrutura de save intactos.
- Inclui `tools/install-forgotten-house.ps1` para instalar somente
  o mapa em `Levels\\L1Data` na **pasta da instalação usada para jogar**.
  O instalador verifica SHA256, não copia se o arquivo já for idêntico
  e salva um backup caso exista uma versão diferente.

## Instalação
Abra o PowerShell na pasta `Sociedade de Tristram/TH` e execute:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File "..\\..\\tools\\install-forgotten-house.ps1" -GameDirectory "D:\\CAMINHO\\DA\\SUA\\PASTA\\DO\\JOGO"
```

Altere apenas o caminho `D:\\CAMINHO...`. Não é necessário copiar
`DIABDAT.MPQ`, reempacotar `TH4data.mor` ou mexer nos saves.

Para compilar a proteção de entrada, use:

```powershell
python ..\\..\\tools\\check_forgotten_house_assets.py
powershell -NoProfile -ExecutionPolicy Bypass -File "..\\..\\tools\\build-win32.ps1"
```

**Teste real pendente**: entrar na casa e regressar à cidade, verificar
luz, sprites, pistas e escolha final com personagem de teste e saves
preservados. O instalador não pode confirmar a existência da paleta
no arquivo MPQ a partir do código-fonte.

Se um personagem já estiver salvo **dentro** da casa e faltarem assets,
restaurar os arquivos antes de tentar carregar: a guarda preventiva desta
etapa protege transições a partir da cidade, não estados de carregamento
já persistidos dentro da casa.
