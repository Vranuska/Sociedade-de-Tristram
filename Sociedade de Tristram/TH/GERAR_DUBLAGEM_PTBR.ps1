param(
    [string]$Destino = "$PSScriptRoot\build",
    [string]$Perfis = "$PSScriptRoot\DUBLAGEM_PTBR.ini",
    [string]$Fonte = "$PSScriptRoot",
    [string]$SomentePersonagem = "",
    [switch]$Forcar
)

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Speech

function Ler-Ini([string]$Caminho) {
    $resultado = @{}
    if (-not (Test-Path -LiteralPath $Caminho)) { return $resultado }
    $secao = ""
    foreach ($linhaBruta in Get-Content -LiteralPath $Caminho -Encoding UTF8) {
        $linha = $linhaBruta.Trim()
        if (-not $linha -or $linha.StartsWith(";") -or $linha.StartsWith("#")) { continue }
        if ($linha -match '^\[(.+)\]$') {
            $secao = $Matches[1].Trim().ToUpperInvariant()
            if (-not $resultado.ContainsKey($secao)) { $resultado[$secao] = @{} }
            continue
        }
        if ($secao -and $linha -match '^([^=]+)=(.*)$') {
            $resultado[$secao][$Matches[1].Trim().ToLowerInvariant()] = $Matches[2].Trim()
        }
    }
    return $resultado
}

function Valor-Perfil($ini, [string]$personagem, [string]$chave, $padrao) {
    $secao = $personagem.ToUpperInvariant()
    if ($ini.ContainsKey($secao) -and $ini[$secao].ContainsKey($chave.ToLowerInvariant())) {
        return $ini[$secao][$chave.ToLowerInvariant()]
    }
    return $padrao
}

function Hash-Texto([string]$texto) {
    $sha = [System.Security.Cryptography.SHA256]::Create()
    try {
        $bytes = [System.Text.Encoding]::UTF8.GetBytes($texto)
        return ([System.BitConverter]::ToString($sha.ComputeHash($bytes))).Replace("-", "").ToLowerInvariant()
    } finally {
        $sha.Dispose()
    }
}

function Escolher-Voz($vozes, [string]$nomePreferido, [string]$genero) {
    if ($nomePreferido -and $nomePreferido -ne "auto") {
        $exata = $vozes | Where-Object { $_.VoiceInfo.Name -eq $nomePreferido } | Select-Object -First 1
        if ($exata) { return $exata }
    }

    $generoSapi = switch ($genero.ToLowerInvariant()) {
        "masculino" { "Male" }
        "feminino"  { "Female" }
        default     { "" }
    }
    if ($generoSapi) {
        $compativel = $vozes | Where-Object { $_.VoiceInfo.Gender.ToString() -eq $generoSapi } | Select-Object -First 1
        if ($compativel) { return $compativel }
    }
    return $vozes | Select-Object -First 1
}

function Criar-Ssml([string]$texto, [int]$velocidade, [string]$tom, [int]$volume, [int]$pausa) {
    $seguro = [System.Security.SecurityElement]::Escape($texto)
    $seguro = $seguro -replace '\.\s+', ". <break time=`"$($pausa)ms`"/> "
    $seguro = $seguro -replace '!\s+', "! <break time=`"$([Math]::Min($pausa + 50, 600))ms`"/> "
    $taxa = $velocidade * 8
    $taxaTexto = if ($taxa -ge 0) { "+$taxa%" } else { "$taxa%" }
    return "<speak version=`"1.0`" xml:lang=`"pt-BR`"><prosody rate=`"$taxaTexto`" pitch=`"$tom`" volume=`"$volume`">$seguro</prosody></speak>"
}

function Converter-StringCpp([string]$texto) {
    $texto = $texto -replace '\\n', "`n"
    $texto = $texto -replace '\\r', ""
    $texto = $texto -replace '\\t', " "
    $texto = $texto -replace '\\"', '"'
    $texto = $texto -replace '\\\\', '\'
    return $texto.Trim().TrimEnd('|').Trim()
}

function Perfil-PeloArquivo([string]$arquivo) {
    switch -Regex ($arquivo) {
        '\\Storyt'                   { return 'CAIN' }
        '\\Healer'                   { return 'PEPIN' }
        '\\Bmaid'                    { return 'GILLIAN' }
        '\\Bsmith'                   { return 'GRISWOLD' }
        '\\Drunk'                    { return 'FARNHAM' }
        '\\Witch'                    { return 'ADRIA' }
        '\\Pegboy'                   { return 'WIRT' }
        '\\Tavown'                   { return 'OGDEN' }
        '\\Wound|\\Deadguy'         { return 'MORADOR' }
        '\\Farmer'                   { return 'LESTER' }
        '\\Girl|\\Fgirl'            { return 'CELIA' }
        '\\Priest'                   { return 'TREMAIN' }
        '^Sfx\\Warrior\\'           { return 'GUERREIRO' }
        '^Sfx\\Rogue\\'             { return 'ARQUEIRA' }
        '^Sfx\\Sorceror\\'          { return 'MAGO' }
        '^Sfx\\Monk\\'              { return 'MONGE' }
        '^Sfx\\Monsters\\'          { return 'MONSTRO' }
        default                       { return 'NARRADOR' }
    }
}

function Ler-FalasDoCodigo([string]$raiz) {
    $arquivoFalas = Join-Path $raiz 'src\structs_speech.cpp'
    $arquivoSons = Join-Path $raiz 'src\structs_sounds.cpp'
    if (-not (Test-Path -LiteralPath $arquivoFalas) -or -not (Test-Path -LiteralPath $arquivoSons)) {
        Write-Host "AVISO: nao foi possivel ler todas as falas em $raiz\src." -ForegroundColor Yellow
        return @()
    }

    $sons = @{}
    $conteudoSons = Get-Content -LiteralPath $arquivoSons -Raw -Encoding UTF8
    $regexSom = [regex]'\{\s*(?<id>S_[A-Za-z0-9_]+)\s*,[^,]*,\s*"(?<arquivo>(?:\\.|[^"\\])*)"\s*\}'
    foreach ($match in $regexSom.Matches($conteudoSons)) {
        $caminho = Converter-StringCpp $match.Groups['arquivo'].Value
        if ($caminho -match '^Sfx\\' -and $caminho -match '\.wav$') {
            $sons[$match.Groups['id'].Value] = $caminho
        }
    }

    $resultado = @()
    $conteudoFalas = Get-Content -LiteralPath $arquivoFalas -Raw -Encoding UTF8
    $regexFala = [regex]'(?s)/\*\s*\d+\s*\*/\s*\{\s*"(?<texto>(?:\\.|[^"\\])*)"\s*,\s*[^,]+,\s*[^,]+,\s*(?<som>S_[A-Za-z0-9_]+)\s*\}'
    foreach ($match in $regexFala.Matches($conteudoFalas)) {
        $texto = Converter-StringCpp $match.Groups['texto'].Value
        $som = $match.Groups['som'].Value
        if (-not $texto -or -not $sons.ContainsKey($som)) { continue }
        $caminho = $sons[$som]
        $resultado += @{
            Personagem = Perfil-PeloArquivo $caminho
            Arquivo = $caminho
            Texto = $texto
        }
    }
    return $resultado
}

$synth = New-Object System.Speech.Synthesis.SpeechSynthesizer
$vozes = @($synth.GetInstalledVoices() | Where-Object {
    $_.Enabled -and $_.VoiceInfo.Culture.Name -eq "pt-BR"
})

if ($vozes.Count -eq 0) {
    Write-Host "ERRO: nenhuma voz pt-BR do Windows foi encontrada." -ForegroundColor Red
    Write-Host "Instale uma voz de Portugues (Brasil) em Configuracoes > Hora e idioma > Fala e execute novamente."
    exit 1
}

$ini = Ler-Ini $Perfis
$manifestoCaminho = Join-Path $Destino ".dublagem_ptbr_manifesto.json"
$logCaminho = Join-Path $Destino "Dublagem_PTBR.log"
$manifestoAnterior = @{}
if (Test-Path -LiteralPath $manifestoCaminho) {
    try {
        $json = Get-Content -LiteralPath $manifestoCaminho -Raw -Encoding UTF8 | ConvertFrom-Json
        foreach ($p in $json.PSObject.Properties) { $manifestoAnterior[$p.Name] = [string]$p.Value }
    } catch {
        $manifestoAnterior = @{}
    }
}
$manifestoNovo = @{}
if ($SomentePersonagem) {
    foreach ($chave in $manifestoAnterior.Keys) {
        $manifestoNovo[$chave] = $manifestoAnterior[$chave]
    }
}

# Cada fala aponta para o WAV exato usado pelo jogo. As classes derivadas
# compartilham os bancos de voz: Arqueira/Rogue, Guerreiro/Savage e Mago.
$falasFixas = @(
    # A Maldicao do Rei Leoric.
    @{ Personagem="CAIN"; Arquivo="Sfx\Towners\Storyt01.wav"; Texto="Ah, a historia de nosso Rei? A queda tragica de Leoric foi um golpe terrivel para esta terra. O povo sempre amou o Rei e agora vive com medo mortal dele. Ainda me pergunto como ele caiu tao longe da Luz. Somente os poderes mais vis do Inferno poderiam destruir um homem por dentro dessa maneira." },
    @{ Personagem="PEPIN"; Arquivo="Sfx\Towners\Healer01.wav"; Texto="A perda do filho foi demais para o Rei Leoric. Fiz o que pude para aliviar sua loucura, mas ela o venceu. Talvez libertar seu espirito da prisao terrena desfaca a maldicao." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid01.wav"; Texto="Nao gosto de pensar em como o Rei morreu. Prefiro lembrar do governante bondoso e justo que ele foi. Sua morte foi tao triste e pareceu muito errada." },
    @{ Personagem="GRISWOLD"; Arquivo="Sfx\Towners\Bsmith01.wav"; Texto="Forjei muitas armas e a maior parte das armaduras dos cavaleiros do Rei Leoric. Ainda nao acredito em sua morte. Alguma forca sinistra deve ter causado sua loucura!" },
    @{ Personagem="FARNHAM"; Arquivo="Sfx\Towners\Drunk01.wav"; Texto="Nao ligo para isso. Nenhum esqueleto vai ser meu rei. Leoric e o Rei. Rei, esta ouvindo? Vida longa ao Rei!" },
    @{ Personagem="ADRIA"; Arquivo="Sfx\Towners\Witch01.wav"; Texto="Os mortos que caminham entre os vivos seguem o Rei amaldicoado. Se voce nao encerrar seu reinado, ele marchara por esta terra e matara todos que ainda vivem." },
    @{ Personagem="WIRT"; Arquivo="Sfx\Towners\Pegboy01.wav"; Texto="Eu tenho um negocio. Nao vendo informacao e nao ligo para um Rei morto desde antes de eu nascer. Se precisa de algo contra o Rei dos mortos-vivos, posso ajudar." },

    # Conversas gerais de Gillian.
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid31.wav"; Texto="Bom dia! Como posso ajuda-lo?" },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid32.wav"; Texto="Minha avo sonhou que voce viria falar comigo. Ela tem visoes, sabia? Ela consegue enxergar o futuro." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid33.wav"; Texto="A mulher que vive na beira da cidade e uma bruxa! Ela parece gentil, e seu nome, Adria, soa muito bonito, mas eu tenho muito medo dela. Seria preciso alguem muito corajoso, como voce, para descobrir o que ela esta fazendo la." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid34.wav"; Texto="Nosso ferreiro e motivo de orgulho para o povo de Tristram. Alem de ser um mestre artesao, ele recebeu elogios do proprio Rei Leoric. Que sua alma descanse em paz. Griswold tambem e um grande heroi; pergunte a Cain." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid35.wav"; Texto="Cain e o contador de historias de Tristram desde que consigo me lembrar. Ele sabe tanta coisa que pode lhe contar praticamente qualquer coisa sobre quase tudo." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid36.wav"; Texto="Farnham e um bebado que enche a barriga de cerveja e os ouvidos de todos com bobagens. Eu sei que Pepin e Ogden sentem pena dele, mas fico frustrada vendo-o afundar cada vez mais em sua confusao todas as noites." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid37.wav"; Texto="Pepin salvou a vida da minha avo, e sei que nunca poderei retribuir isso. Sua capacidade de curar qualquer doenca e mais poderosa que a espada mais forte e mais misteriosa que qualquer magia que voce conheca. Se precisar de cura, Pepin pode ajuda-lo." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid39.wav"; Texto="Cresci com Canace, a mae de Wirt. Sei que ele sofreu e viu horrores que nem consigo imaginar, mas parte daquela escuridao ainda paira sobre ele." },
    @{ Personagem="GILLIAN"; Arquivo="Sfx\Towners\Bmaid40.wav"; Texto="Ogden e sua esposa acolheram minha avo e eu em sua casa e ate me deixaram trabalhar na taverna. Devo muito a eles e espero um dia ajuda-los a abrir um grande hotel no leste." },

    # Falas funcionais dos herois: requisito, magia, cidade, mana/recurso e mochila cheia.
    @{ Personagem="GUERREIRO"; Arquivo="Sfx\Warrior\Warior13.wav"; Texto="Ainda nao consigo usar isso." },
    @{ Personagem="GUERREIRO"; Arquivo="Sfx\Warrior\Warior34.wav"; Texto="Nenhuma magia esta selecionada." },
    @{ Personagem="GUERREIRO"; Arquivo="Sfx\Warrior\Warior27.wav"; Texto="Nao posso usar esta magia na cidade." },
    @{ Personagem="GUERREIRO"; Arquivo="Sfx\Warrior\Warior35.wav"; Texto="Nao tenho mana suficiente." },
    @{ Personagem="GUERREIRO"; Arquivo="Sfx\Warrior\Warior14.wav"; Texto="Nao posso carregar mais nada." },
    @{ Personagem="ARQUEIRA"; Arquivo="Sfx\Rogue\Rogue13.wav"; Texto="Ainda nao consigo usar isso." },
    @{ Personagem="ARQUEIRA"; Arquivo="Sfx\Rogue\Rogue34.wav"; Texto="Nenhuma magia esta selecionada." },
    @{ Personagem="ARQUEIRA"; Arquivo="Sfx\Rogue\Rogue27.wav"; Texto="Nao posso usar esta magia na cidade." },
    @{ Personagem="ARQUEIRA"; Arquivo="Sfx\Rogue\Rogue35.wav"; Texto="Nao tenho mana suficiente." },
    @{ Personagem="ARQUEIRA"; Arquivo="Sfx\Rogue\Rogue14.wav"; Texto="Nao posso carregar mais nada." },
    @{ Personagem="MAGO"; Arquivo="Sfx\Sorceror\Mage13.wav"; Texto="Ainda nao consigo usar isso." },
    @{ Personagem="MAGO"; Arquivo="Sfx\Sorceror\Mage34.wav"; Texto="Nenhuma magia esta selecionada." },
    @{ Personagem="MAGO"; Arquivo="Sfx\Sorceror\Mage27.wav"; Texto="Nao posso usar esta magia na cidade." },
    @{ Personagem="MAGO"; Arquivo="Sfx\Sorceror\Mage35.wav"; Texto="Nao tenho mana suficiente." },
    @{ Personagem="MAGO"; Arquivo="Sfx\Sorceror\Mage14.wav"; Texto="Nao posso carregar mais nada." },
    @{ Personagem="MONGE"; Arquivo="Sfx\Monk\Monk13.wav"; Texto="Ainda nao consigo usar isso." },
    @{ Personagem="MONGE"; Arquivo="Sfx\Monk\Monk34.wav"; Texto="Nenhuma magia esta selecionada." },
    @{ Personagem="MONGE"; Arquivo="Sfx\Monk\Monk27.wav"; Texto="Nao posso usar esta magia na cidade." },
    @{ Personagem="MONGE"; Arquivo="Sfx\Monk\Monk35.wav"; Texto="Nao tenho mana suficiente." },
    @{ Personagem="MONGE"; Arquivo="Sfx\Monk\Monk14.wav"; Texto="Nao posso carregar mais nada." }
)

# As falas funcionais acima sao mantidas como complemento. Para NPCs, quests,
# rumores e chefes, o texto traduzido e o caminho do WAV sao lidos diretamente
# das tabelas usadas pelo jogo, evitando uma segunda lista incompleta.
$falasPorArquivo = @{}
foreach ($fala in $falasFixas) { $falasPorArquivo[$fala.Arquivo] = $fala }
foreach ($fala in (Ler-FalasDoCodigo $Fonte)) { $falasPorArquivo[$fala.Arquivo] = $fala }
$falas = @($falasPorArquivo.Values | Sort-Object Arquivo)
if ($SomentePersonagem) {
    $perfilSolicitado = $SomentePersonagem.Trim().ToUpperInvariant()
    $falas = @($falas | Where-Object { $_.Personagem.ToUpperInvariant() -eq $perfilSolicitado })
    if ($falas.Count -eq 0) {
        Write-Host "ERRO: nenhuma fala encontrada para o perfil $perfilSolicitado." -ForegroundColor Red
        exit 1
    }
}

New-Item -ItemType Directory -Path $Destino -Force | Out-Null
Set-Content -LiteralPath $logCaminho -Value "Dublagem PT-BR - $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')" -Encoding UTF8
Write-Host "Vozes pt-BR encontradas: $($vozes.Count)"
foreach ($v in $vozes) { Write-Host "  $($v.VoiceInfo.Name) [$($v.VoiceInfo.Gender)]" }
Write-Host "Perfis: $Perfis"
Write-Host "Codigo-fonte: $Fonte"
Write-Host "Destino: $Destino"
if ($SomentePersonagem) { Write-Host "Filtro de personagem: $perfilSolicitado" }
Write-Host "Falas localizadas: $($falas.Count)"

$geradas = 0
$ignoradas = 0
foreach ($fala in $falas) {
    $personagem = $fala.Personagem
    $genero = [string](Valor-Perfil $ini $personagem "genero" "qualquer")
    $nomePreferido = [string](Valor-Perfil $ini $personagem "voz" "auto")
    $velocidade = [int](Valor-Perfil $ini $personagem "velocidade" "0")
    $tom = [string](Valor-Perfil $ini $personagem "tom" "0%")
    $volume = [int](Valor-Perfil $ini $personagem "volume" "100")
    $pausa = [int](Valor-Perfil $ini $personagem "pausa" "180")
    $voz = Escolher-Voz $vozes $nomePreferido $genero
    $assinatura = Hash-Texto "v3|$personagem|$($fala.Texto)|$($voz.VoiceInfo.Name)|$velocidade|$tom|$volume|$pausa"
    $manifestoNovo[$fala.Arquivo] = $assinatura
    $saida = Join-Path $Destino $fala.Arquivo

    if (-not $Forcar -and (Test-Path -LiteralPath $saida) -and
        $manifestoAnterior.ContainsKey($fala.Arquivo) -and
        $manifestoAnterior[$fala.Arquivo] -eq $assinatura) {
        Write-Host "  --  $($fala.Arquivo) (sem alteracoes)"
        $ignoradas++
        continue
    }

    $pasta = Split-Path -Parent $saida
    New-Item -ItemType Directory -Path $pasta -Force | Out-Null
    $synth.SelectVoice($voz.VoiceInfo.Name)
    $synth.Volume = [Math]::Max(0, [Math]::Min(100, $volume))
    $synth.Rate = [Math]::Max(-10, [Math]::Min(10, $velocidade))
    $synth.SetOutputToWaveFile($saida)
    try {
        $synth.SpeakSsml((Criar-Ssml $fala.Texto $velocidade $tom $volume $pausa))
    } catch {
        # Algumas vozes SAPI antigas ignoram prosodia SSML. Nesse caso o WAV
        # ainda e produzido com velocidade e volume proprios do personagem.
        $synth.Speak($fala.Texto)
    } finally {
        $synth.SetOutputToNull()
    }
    $linhaLog = "$personagem`t$($voz.VoiceInfo.Name)`t$($fala.Arquivo)"
    Add-Content -LiteralPath $logCaminho -Value $linhaLog -Encoding UTF8
    Write-Host "  OK  [$personagem] $($fala.Arquivo)"
    $geradas++
}

$manifestoNovo | ConvertTo-Json | Set-Content -LiteralPath $manifestoCaminho -Encoding UTF8
$synth.Dispose()
Write-Host ""
Write-Host "PRONTO: $geradas geradas; $ignoradas mantidas sem refazer."
Write-Host "Copie a pasta Sfx para a mesma pasta do TheHeaven.exe."
Write-Host "Use -Forcar se quiser recriar todos os WAVs."
