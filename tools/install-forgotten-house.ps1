# Install only the Forgotten House quest map. Does not touch saves or MPQ archives.
# Example (run from Sociedade de Tristram/TH):
# powershell -NoProfile -ExecutionPolicy Bypass -File "..\..\tools\install-forgotten-house.ps1" -GameDirectory "D:\Games\Sociedade de Tristram"
param(
    [Parameter(Mandatory=$true)]
    [ValidateNotNullOrEmpty()]
    [string]$GameDirectory
)
$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$source = Join-Path $repoRoot "Sociedade de Tristram\TH\res\thdata\Levels\L1Data\ForgottenHouse.DUN"
if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
    throw "Mapa de origem nao encontrado: $source"
}
if (-not (Test-Path -LiteralPath $GameDirectory -PathType Container)) {
    throw "Pasta do jogo nao encontrada: $GameDirectory"
}
$destDirectory = Join-Path $GameDirectory "Levels\L1Data"
$destination = Join-Path $destDirectory "ForgottenHouse.DUN"
$sourceHash = (Get-FileHash -LiteralPath $source -Algorithm SHA256).Hash

if (Test-Path -LiteralPath $destination -PathType Leaf) {
    $existingHash = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash
    if ($sourceHash -eq $existingHash) {
        Write-Host "O mapa ja esta instalado, e o hash confere: $destination"
        exit 0
    }
    $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
    $backup = "$destination.backup-$stamp"
    $number = 1
    while (Test-Path -LiteralPath $backup) {
        $backup = "$destination.backup-$stamp-$number"
        $number++
    }
    Copy-Item -LiteralPath $destination -Destination $backup -ErrorAction Stop
    Write-Host "Backup preservado: $backup"
}

New-Item -ItemType Directory -Force -Path $destDirectory | Out-Null
Copy-Item -LiteralPath $source -Destination $destination -Force -ErrorAction Stop
$installedHash = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash
if ($sourceHash -ne $installedHash) {
    throw "Falha de verificacao: o hash do mapa copiado difere da origem."
}
Write-Host "Mapa instalado e validado: $destination"
Write-Host "Tamanho: $((Get-Item -LiteralPath $destination).Length) bytes"
Write-Host "Nenhum save, executavel ou MPQ foi modificado."
Write-Host "Inicie o jogo pelo executavel nessa mesma pasta e reteste a Casa Esquecida."
