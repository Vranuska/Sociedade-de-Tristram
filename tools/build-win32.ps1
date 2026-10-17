# Sociedade de Tristram - Windows Debug/Win32 rebuild
# Locates the legacy DirectX HLSL compiler without changing system PATH.
param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug"
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
$projectDir = Join-Path $repoRoot "Sociedade de Tristram\TH"
$solution = Join-Path $projectDir "TheHeaven.sln"
$msbuild = "C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
$sdkBin = "C:\Program Files (x86)\Windows Kits\10\bin"

if (-not (Test-Path -LiteralPath $msbuild -PathType Leaf)) {
    throw "MSBuild nao encontrado: $msbuild"
}
if (-not (Test-Path -LiteralPath $solution -PathType Leaf)) {
    throw "Solucao nao encontrada: $solution"
}
if (-not (Test-Path -LiteralPath $sdkBin -PathType Container)) {
    throw "Windows SDK 10 nao encontrado: $sdkBin"
}

$fxc = Get-ChildItem -LiteralPath $sdkBin -Filter "fxc.exe" -File -Recurse -ErrorAction SilentlyContinue |
    Where-Object { $_.DirectoryName -match '\\x86$' } |
    Sort-Object FullName -Descending |
    Select-Object -First 1

if (-not $fxc) {
    throw "fxc.exe (x86) nao encontrado. Instale o componente Windows SDK DirectX Shader Compiler."
}

Write-Host "Usando fxc.exe: $($fxc.FullName)"
$previousPath = $env:Path
$env:Path = "$($fxc.DirectoryName);$previousPath"
try {
    Push-Location $projectDir
    try {
        & $msbuild $solution /t:Rebuild /p:Configuration=$Configuration /p:Platform=Win32 /m:1 /v:minimal
        if ($LASTEXITCODE -ne 0) {
            throw "Compilacao falhou (codigo $LASTEXITCODE)."
        }
        Write-Host "Compilacao concluida: $Configuration / Win32"
    } finally {
        Pop-Location
    }
} finally {
    $env:Path = $previousPath
}
