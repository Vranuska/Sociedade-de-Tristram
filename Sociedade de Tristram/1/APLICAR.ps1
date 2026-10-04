$ErrorActionPreference = "Stop"
Write-Host "============================================================="
Write-Host "  CORRECAO DEFINITIVA DE SLOTS E AQUAMARINE - V7.1"
Write-Host "============================================================="
$root = (Read-Host "Pasta TH que contem TheHeaven.sln").Trim('"')
if (-not (Test-Path (Join-Path $root "TheHeaven.sln"))) { throw "TheHeaven.sln nao encontrado." }
if (Get-Process -Name @("TheHeaven", "Sociedade de Tristram") -ErrorAction SilentlyContinue) {
    throw "Feche completamente o jogo antes de instalar."
}

$stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$backup = Join-Path $root "backup-slots-unicos-aquamarine-v7-1-$stamp"
$files = @(
    "TheHeaven.sln",
    "theheaven.vcxproj",
    "src\Draw.cpp",
    "src\Missile.cpp",
    "src\Item.cpp",
    "src\Tooltip.cpp",
    "src\dataseg.cpp",
    "src\theheaven.rc",
    "src\Main.cpp",
    "src\Error.cpp",
    "src\Crafting.cpp",
    "src\InventoryPanel.cpp",
    "include\funcs.h",
    "include\vars.h",
    "res\sociedade_tristram.ico",
    "res\sociedade_tristram_icon.png"
)
foreach ($relative in $files) {
    $destination = Join-Path $root $relative
    $backupFile = Join-Path $backup $relative
    $payloadFile = Join-Path $PSScriptRoot ("payload\" + $relative)
    New-Item -ItemType Directory -Force (Split-Path $destination -Parent) | Out-Null
    New-Item -ItemType Directory -Force (Split-Path $backupFile -Parent) | Out-Null
    if (Test-Path $destination) { Copy-Item $destination $backupFile -Force }
    Copy-Item $payloadFile $destination -Force
    (Get-Item $destination).LastWriteTime = Get-Date
}

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) { throw "vswhere.exe nao encontrado." }
$msbuild = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe | Select-Object -First 1
if (-not $msbuild) { throw "MSBuild nao encontrado." }
$fxc = Get-ChildItem "${env:ProgramFiles(x86)}\Windows Kits\10\bin" -Filter fxc.exe -Recurse -ErrorAction SilentlyContinue |
    Where-Object { $_.FullName -match '\\x86\\fxc\.exe$|\\x64\\fxc\.exe$' } |
    Sort-Object FullName -Descending | Select-Object -First 1
if (-not $fxc) { throw "fxc.exe nao encontrado no Windows SDK." }
$env:Path = $fxc.Directory.FullName + ";" + $env:Path

Write-Host "Compilando Release / Win32..."
& $msbuild (Join-Path $root "TheHeaven.sln") /t:Rebuild /m /p:Configuration=Release /p:Platform=Win32
if ($LASTEXITCODE -ne 0) { throw "Compilacao falhou. Envie a tela da compilacao." }
$builtExe = Join-Path $root "build\Sociedade de Tristram.exe"
if (-not (Test-Path $builtExe)) { throw "build\Sociedade de Tristram.exe nao encontrado." }

$installed = $false
foreach ($game in @($root, (Split-Path $root -Parent)) | Select-Object -Unique) {
    if (-not (Test-Path (Join-Path $game "DIABDAT.MPQ"))) { continue }
    $gameBackup = Join-Path $backup "jogo"
    New-Item -ItemType Directory -Force $gameBackup | Out-Null
    $oldExe = Join-Path $game "TheHeaven.exe"
    $newExe = Join-Path $game "Sociedade de Tristram.exe"
    if (Test-Path $newExe) { Copy-Item $newExe (Join-Path $gameBackup "Sociedade de Tristram.exe") -Force }
    if (Test-Path $oldExe) { Move-Item $oldExe (Join-Path $gameBackup "TheHeaven.exe") -Force }
    Copy-Item $builtExe $newExe -Force
    $installed = $true
    Write-Host "Instalado em: $newExe"
    Write-Host "O executavel antigo foi movido para o backup."
}
if (-not $installed) { Write-Host "DIABDAT.MPQ nao encontrado. EXE compilado: $builtExe" }
Write-Host "SUCESSO. Backup: $backup"
