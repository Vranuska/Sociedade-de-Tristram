@echo off
setlocal EnableExtensions
title Sociedade de Tristram - Dublagem PT-BR da Gillian

set "REPO=%~1"
if not defined REPO if exist "%~dp0TheHeaven.sln" if exist "%~dp0src\structs_sounds.cpp" set "REPO=%~dp0"
if not defined REPO (
    echo Arraste a pasta do codigo-fonte The Heaven v0.2.0 para esta janela
    echo ou cole abaixo o caminho completo dela.
    echo.
    set /p "REPO=Pasta do codigo-fonte: "
)
set "REPO=%REPO:"=%"
if not exist "%REPO%\src\structs_speech.cpp" (
    echo.
    echo ERRO: nao encontrei src\structs_speech.cpp nessa pasta.
    pause
    exit /b 1
)

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0GERAR_DUBLAGEM_PTBR.ps1" -Destino "%REPO%\build" -Perfis "%~dp0DUBLAGEM_PTBR.ini" -Fonte "%REPO%" -SomentePersonagem GILLIAN
set "DUB_RESULT=%ERRORLEVEL%"
echo.
if not "%DUB_RESULT%"=="0" echo A dublagem da Gillian nao foi gerada. Leia o erro acima.
if "%DUB_RESULT%"=="0" echo WAVs da Gillian gravados em: %REPO%\build\Sfx\Towners
pause
exit /b %DUB_RESULT%
