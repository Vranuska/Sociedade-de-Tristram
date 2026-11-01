# Implementação Vespera — etapa 01

Branch: `feature/vespera-lore-quests` (derivada de `feature/configurable-rates`).

## Código entregue
- `Sociedade de Tristram/TH/src/VesperaLoreQuest.h`: máquina de estados isolada, sem dependências do motor do jogo, com sete pistas, duas deduções profundas, conclusão básica, três finais e codificação explícita em 3 bytes.
- `tools/test_vespera_lore.cpp`: teste independente de ordem livre de pistas, repetição, exigência de prova, finais únicos, serialização e rejeição atômica de dados inválidos.

## Como executar o teste local
Na raiz do repositório, com g++ instalado:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic tools/test_vespera_lore.cpp -o vespera_lore_test
./vespera_lore_test
```

No Windows, execute `vespera_lore_test.exe`. Saída silenciosa com código 0 significa sucesso.

**O teste ainda não foi executado neste ambiente.** A lógica ainda NÃO está ligada ao jogo e NÃO usa bytes do save. Nenhum código de Maera, companheiros, quests ou mapas foi alterado.

## Observação de design
O encerramento exige a dedução `ForgeryProven` (L01 + L07 + [L04 ou L06]). O mistério secundário de intermediários distintos usa L05 + [L02 ou L03]. A regra poderá ser revista se playtests mostrarem que a exigência bloqueia a experiência básica.

## Próximo patch
1. Localizar enumeração e contagem de quests, inventário completo de flags persistidas e handlers de diálogo/objetos.
2. Escolher integração segura sem colidir com `AdditionalStateData.unused[0]`, `AdditionalSaveInfo.unused[80..86]`, `[96..121]` e quaisquer outros campos ocupados.
3. Conectar um primeiro indício ao cenário, registrar a flag e oferecer reação contextual de Cain/Gillian.
4. Testar compilação MSVC, salvamento e jogo real antes de declarar quest jogável.
