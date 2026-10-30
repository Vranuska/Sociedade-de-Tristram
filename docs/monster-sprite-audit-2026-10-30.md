# Auditoria inicial do pipeline de monstros

Data da auditoria: 2026-10-30  
Branch examinada: `feature/ui-rebuild-v1`  
Repositório: [Vranuska/Sociedade-de-Tristram](https://github.com/Vranuska/Sociedade-de-Tristram/tree/feature/ui-rebuild-v1)

Esta nota registra fatos confirmados no código da branch e separa lacunas que ainda precisam ser verificadas com os recursos instalados do jogo. Não declara nenhuma criatura nova implementada.

## Matriz técnica baseada no código

| Tema | Evidência observada | Implicação para sprites novos | Estado |
|---|---|---|---|
| Registro do monstro | `src/BaseMonster.cpp` inicializa `BaseMonsters[BM_COUNT]` com índice, padrão de animação, largura, ataques, sons, tradução de cor, seis quantidades de quadros e seis atrasos. `enum BASE_MONSTER` fica em `include/enums.h`. | Uma criatura nova exige um tipo-base e registro próprios; reutilizar um índice existente substituiria comportamento/arte de outra criatura. Investigar consequências de acrescentar enum no fim da tabela e pontos que tratam limites. | Confirmado parcialmente |
| Carregamento | `src/Monster.cpp::LoadMonsterAnimation` monta o caminho a partir de `BaseMonster::AnimationFileName` e `TypeOfAnimation`, chama `LoadFile` e lê oito offsets iniciais para as direções. | Os arquivos precisam respeitar o cabeçalho e a organização que o carregador espera. A escrita/conversão CL2 ainda não existe como ferramenta identificada no repositório. | Confirmado |
| Formato de animação | A tabela referencia padrões como `Monsters\\Zombie\\Zombie%c.CL2`; o desenho chama `CL2_Draw`/ `CL2_DrawDark`. | CL2 é o formato de runtime identificado para monstros. Ainda falta localizar/validar a implementação do decodificador e especificar formalmente o layout de quadros, transparência e limites do arquivo. | Confirmado em uso; especificação pendente |
| Direções | O carregador de monstros percorre exatamente 8 direções (`dir < 8`); `MonsterAnim` contém `oriented[8]`. | Produzir oito vistas para cada animação do piloto. Não aplicar automaticamente o valor de 16 direções encontrado em outras estruturas: esse valor não rege este carregador. | Confirmado |
| Animações | Há seis posições de animação. A enumeração do motor distingue ficar/parado, andar, atacar, receber golpe, morrer e segundo ataque; o segundo ataque depende de `HasSecondAttack`. | O pacote do piloto deve declarar quantidade e atraso por animação e deve fornecer os seis canais esperados, com o segundo ataque habilitado somente se a criatura realmente o usar. | Confirmado |
| Quadros, dimensões e offsets | `BaseMonster` contém `animationFrameCount[6]`, `animationDelay[6]` e `SpritePitch`. O carregador define offsets de direção e chama `MonsterSpritePosAdjust`; o desenho valida o número de quadros do próprio bloco CL2. | Não fixar resolução ou tamanho artístico antes de comparar amostras reais. Centralizar o pivô/solo e manter enquadramento compatível com o pitch cadastrado. | Parcial |
| Transparência e composição | O caminho de desenho usa rotinas CL2 do motor e parâmetros de pitch/posição; a superfície do jogo usa a lógica de renderização isométrica e iluminação em `src/Draw.cpp`. | Confirmar o índice transparente e a regra de composição no decodificador CL2 antes de exportar. Os quadros devem ser avaliados no jogo contra o fundo, não somente em um visualizador RGBA. | Pendente |
| CEL | O código tem renderização de cenário/interface com rotinas CEL, incluindo `Surface_DrawCEL` e desenho de tiles em `Draw.cpp`; a árvore versionada contém CEL de interface. | CEL é efetivamente usado no motor, mas não foi identificado como formato do fluxo de monstros. Não converter sprites de monstro para CEL sem uma necessidade comprovada. | Confirmado |
| Paleta e iluminação | `src/palette.cpp::LoadPalette` lê 256 entradas RGB de três bytes; há uma tabela de iluminação de 27 × 256 bytes. `DrawMonster` escolhe CL2 normal ou escurecido conforme visibilidade e infravisão. Monstros podem carregar arquivo de tradução `.TRN`. | Arte precisa ser conferida com a paleta de cada área e seus níveis de luz. `.TRN` é uma remapagem de índices, não um substituto para desenho anatômico diferente. | Confirmado |
| Cadáver | A morte troca para o canal `ANIM_4_DIE`, marca `A_6_DEATH`, limpa a ocupação anterior e mantém o índice do monstro no mapa para o desenho durante a morte. | A animação de morte precisa terminar em pose legível; ainda falta rastrear remoção, sprite/corpo estático, salvamento e sincronização multiplayer. | Parcial |
| Ferramentas do repositório | A árvore `TH/tools` contém utilitários de itens/backgrounds, mas nenhum importador/exportador/visualizador CL2 foi encontrado. | Antes de produzir o lote, fazer um leitor de inspeção de CL2 e um conversor controlado, validando saída com o próprio renderizador do jogo. | Confirmado na árvore examinada |
| Recursos instalados | Os caminhos de monstros aparecem como dados externos carregados por `LoadFile`; a árvore de código consultada não contém as famílias completas de CL2 usadas pelo jogo. | Obter amostras locais autorizadas da instalação para testes de leitura, sem copiá-las para commits ou redistribuí-las. | Pendente |

## Formatos identificados até aqui

- **CL2**: animações de monstros; caminho confirmado em `BaseMonster.cpp`, carregamento em `LoadMonsterAnimation`, desenho em `DrawMonster`.
- **CEL**: cenário/interface e outras imagens do motor; não identificado como formato das animações dos monstros.
- **PAL**: paleta de 256 cores RGB, 3 bytes por entrada.
- **TRN**: arquivo de tabela de tradução de paleta associado a vários monstros.
- **WAV**: padrões de sons por criatura, cadastrados junto ao tipo-base.

Isso é um inventário do código versionado, não de todos os arquivos existentes na instalação do jogo.

## Proposta inicial de pipeline

1. **Conceito original**: ficha de silhueta, anatomia, materiais, paleta e comportamento; referências de Diablo servem para princípios, não como molde/copiar.
2. **Base 3D**: Blender para bloquear volumes e proporções, rig simples e câmera ortográfica/isométrica configurada após medir sprites reais.
3. **Animação**: ciclos discretos e contidos, com quadros-chave que preservem a leitura rígida de Diablo I. Criar oito direções e os seis canais aceitos pelo motor.
4. **Renderização**: PNGs com fundo transparente, luz e sombra coerentes, nomes e metadados determinísticos por direção/animação/quadro.
5. **Ajuste**: reduzir para pitch e dimensões medidos, mapear para a paleta-alvo e conferir os índices de transparência. Não definir números até validar arquivos reais.
6. **Conversão CL2**: implementar ou selecionar conversor somente depois de documentar a estrutura de CL2 observada no código e nos arquivos de amostra; validar ida e volta com checksum de quadros e visualização no motor.
7. **Integração isolada**: acrescentar novo registro ao fim dos IDs/tabelas sem reaproveitar IDs existentes; evitar mudanças nos structs de save/rede.
8. **Validação**: comparar as oito direções e seis estados, iluminação, ataques, morte, seleção, queda e comportamento em sessão multiplayer. Só então declarar funcional.

Blender é adequado para gerar vistas e animações coerentes, mas não exporta diretamente o CL2 específico deste motor. O ponto crítico a provar antes da produção completa é o conversor.

## Licença e procedência das referências

O estudo de Android Arts atribui a autoria das imagens a Arne Niklas Jansson. A página de permissões do próprio site diz que uso pessoal é permitido e que, para uso em publicações não comerciais ou em sites, o autor prefere manter controle sobre a publicação. Não encontrei concessão de licença de redistribuição para sprites de jogo.

- Estudo: https://androidarts.com/diablo/diablo.htm
- Permissões: https://www.androidarts.com/ProfileFAQ.htm

Portanto, não copiar, recortar, vetorizar por cima ou redistribuir as ilustrações. Usar somente princípios gerais discutidos pelo autor — silhuetas coerentes, variação anatômica, detalhes com função, pouca saturação, animação contida, suspense pela luz e diversidade sem recoloração repetida — para criar assets originais. Registrar autor, fonte e licença de cada asset que entrar no projeto.

## Criatura-piloto proposta

**Acólito de Lazarus — habitante corrompido da Casa Esquecida.**

É o melhor primeiro teste para a nova quest porque conecta a criatura à narrativa em desenvolvimento sem transformar um personagem querido em fan service e pode ter um papel tático mais simples que um chefe. A proposta visual inicial é um humano deformado e ainda reconhecível como antigo fiel: silhueta estreita e inclinada, túnica de lã/pano funerário rasgada, uma mão recolhida junto ao peito e a outra marcada por queimadura ritual; máscara/placa facial parcial feita de objeto litúrgico quebrado, sem símbolos ou desenho copiados da referência. Paleta de tecido cinza-terra, pele pálida suja, ferrugem e sangue seco, com qualquer acento sobrenatural muito restrito.

A ficha visual final depende de validar primeiro pitch, escala, quadros, comportamento de morte e canal de ataque disponíveis. O conceito não define ainda habilidades, estatísticas, relação canônica com Lazarus ou participação narrativa final.

## Próxima alteração proposta

Criar uma ferramenta pequena de inventário/preview de CL2, sem alterar o runtime: ler arquivos locais de amostra, listar dimensões/pitch, número de quadros e offsets por direção, e exportar uma folha de contato para inspeção. Antes de codificar o decodificador, localizar no repositório todas as declarações e implementações de `CL2_Draw` e obter amostras legítimas da instalação. O trabalho deve permanecer sem alterações em saves, rede, combate ou tabelas de gameplay nesta etapa.
