# Sigilos — fase inicial de segurança (18/10/2026)

## Estado real do código
A base The Heaven já declara `IS_Talisman`, `TalismanSlots`, `TalUsedAlt`,
`TalItemCount` e `activeInv`. Porém, `InventoryPanel.cpp` só trata
`IS_Inventory` como mochila real nas operações centrais. Um clique em
`IS_Talisman` pode cair no caso do cinto e acessar uma coluna além dos oito
espaços do cinto. Exibir o segundo inventário antes de conectá-lo às rotinas
de transferência, efeitos e persistência seria inseguro.

O commit desta fase:
- Mantém o inventário principal acessível, independentemente do bit `activeInv`;
- Não mostra a mochila secundária incompleta;
- Protege a retirada, a colocação e o hover de itens no slot reservado;
- Não altera `Player`, `Item`, arquivos de save, enums ou contratos de rede;
- Não adiciona armas de fogo.

## Objetivo da expansão
Sigilos são artefatos arcanos próprios, inspirados em Diablo/Santuário, com
efeitos que dependem de serem equipados em um espaço reservado. Guardá-los
na mochila comum não os ativa. As mecânicas definitivas de atributos,
raridade e obtenção devem ser balanceadas junto com as demais formas de loot;
nenhum bônus foi habilitado nesta fase.

## Sequência segura de implementação
1. Definir a classificação e catálogo dos Sigilos sem reutilizar códigos de
   itens de missão nem alterar IDs existentes.
2. Implementar a estrutura de armazenamento e regras de equipar/retirar,
   com testes de limites e transferência entre mochila e espaços de Sigilos.
3. Implementar migração de saves versionada e round-trip de
   salvamento/carregamento, incluindo personagens de versões anteriores.
4. Revisar serialização e sincronização em multiplayer antes de ativar drops
   e bônus; preservar o funcionamento no modo single-player.
5. Implementar a página visual e tooltips para os Sigilos, então habilitar
   os efeitos passivos, com limites que não invalidem os itens atuais.
6. Incluir fontes de loot coerentes com a lore, e balanceamento por classe.

## Testes
Executar da raiz do repositório:
`python tools/check_sigil_foundation.py`

Em seguida, compilar:
`powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\build-win32.ps1`

Teste manual inicial: inventário, cinto, equipamentos, organização, companions
e antigos saves continuam funcionando. Esse teste ainda não foi realizado.

**Atenção**: o verificador de fundação apenas examina a estrutura do código.
Ele não valida compilação, save, rede, gameplay nem a existência de Sigilos.
