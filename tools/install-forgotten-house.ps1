# Deploy the Forgotten House level asset to the game installation.
# Does not alter any existing MPQ archives, game saves, or other game files.
[CmdletBinding()]
param(
    [Parameter(Mandatory=$true)]
    [string]$GameDir
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
$source = Join-Path $repoRoot "Sociedade de Tristram\TH\res\thdata\Levels\L1Data\ForgottenHouse.DUN"
$gameDirFull = [System.IO.Path]::GetFullPath($GameDir)
$destinationDir = Join-Path $gameDirFull "Levels\L1Data"
$destination = Join-Path $destinationDir "ForgottenHouse.DUN"

if (-not (Test-Path -LiteralPath $gameDirFull -PathType Container)) {
    throw "Pasta do jogo nao encontrada: $gameDirFull"
}
if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
    throw "Mapa nao encontrado no repositorio: $source"
}
if ((Get-Item -LiteralPath $source).Length -ne 19588) {
    throw "O arquivo ForgottenHouse.DUN nao tem o tamanho esperado (19588 bytes). Interrompendo."
}
if (-not (Test-Path -LiteralPath (Join-Path $gameDirFull "Sociedade de Tristram.exe") -PathType Leaf)) {
    throw "Nao achei Sociedade de Tristram.exe na pasta informada. Nao vou copiar arquivos para o lugar errado."
}
$process = Get-Process -Name "Sociedade de Tristram" -ErrorAction SilentlyContinue
if ($process) {
    throw "Feche o jogo antes de instalar o mapa da missao."
}
New-Item -ItemType Directory -Force -Path $destinationDir | Out-Null

$incomingHash = (Get-FileHash -LiteralPath $source -Algorithm SHA256).Hash
if (Test-Path -LiteralPath $destination -PathType Leaf) {
    $oldHash = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash
    if ($oldHash -eq $incomingHash) {
        Write-Host "Mapa ja instalado corretamente: $destination"
        return
    }
    $backup = "$destination.bak-$(Get-Date -Format 'yyyyMMdd-HHmmss')"
    Copy-Item -LiteralPath $destination -Destination $backup -ErrorAction Stop
    Write-Host "Backup do mapa anterior: $backup"
}
Copy-Item -LiteralPath $source -Destination $destination -Force -ErrorAction Stop
$installedHash = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash
if ($installedHash -ne $incomingHash) {
    throw "A verificacao SHA-256 falhou: o arquivo copiado nao corresponde ao original."
}
Write-Host "Mapa ForgottenHouse.DUN instalado e verificado em $destination"
Write-Host "Nenhum MPQ, save ou executavel foi modificado."
