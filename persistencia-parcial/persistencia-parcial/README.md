# Estruturas de Dados Avançadas - Trabalho 01

## Equipe

Bruna Gomes Carneiro (537993)
Diego Caracas Mendes (542564)
João Gustavo Irineu Braga (538609)

## Descrição

**Lista encadeada ordenada com persistência parcial**:

- **Linguagem de programação utilizada:** C++17, compilado com `g++`
- **Como compilar e rodar:**
  - `make build` compila e gera o executável `programa`
  - `make run INPUT=arquivo.in` roda o programa com o arquivo de entrada
  - `make test` roda os testes da pasta `testes/` e compara com as saídas esperadas

### Ideia Geral

Na lista encadeada, cada nó é apontado por no máximo um outro nó (o seu antecessor), então o grau de entrada é `p = 1`. Logo:

- campos base (`chave` e `prox`)
- um ponteiro de retorno (`anterior`) para quem aponta para ele na última versão
- uma lista de no máximo `2p = 2` modificações, cada uma no formato `(versão, novo prox)`

Como a chave de um nó nunca muda depois que ele é criado, o único campo modificável é o `prox`. Por isso a modificação guarda só a versão e o novo valor, sem precisar indicar o campo.

Cada `INC` ou `REM` cria uma nova versão e faz uma única alteração na lista (um ponteiro `prox` passa a apontar para outro nó).
Essa alteração pode gerar cópias de nós em cadeia, e todas essas modificações são marcadas com o número da nova versão. As raízes de cada versão ficam no vetor `raizes`.
Leituras e escritas têm custo adicional `O(1)` (amortizado) e o espaço total é `O(v)`.

### Estruturas

- **Mod:**
  - Definida em `node.hpp`
  - Representa uma modificação guardada dentro de um nó
  - O campo `versao` indica a partir de qual versão a modificação vale
  - O campo `prox` é o novo valor do ponteiro para o próximo nó

- **Node:**
  - Definida em `node.hpp` e implementada em `node.cpp`
  - Guarda a informação de um nó da lista encadeada persistente
  - O campo `chave` é o valor inteiro guardado no nó (nunca muda)
  - O campo `prox` é o valor original do ponteiro para o próximo nó (o valor de quando o nó foi criado)
  - O campo `anterior` é o ponteiro de retorno: indica qual nó aponta para este na última versão
    (`nullptr` se o nó é o primeiro da lista ou se não está mais na última versão)
  - O campo `mods[]` é a lista de modificações do nó, com tamanho fixo `MAX_MODS = 2`
  - O campo `numMods` indica quantas posições de `mods[]` estão ocupadas
  - O construtor `Node(chave, prox)` cria um nó sem modificações
  - A função `proxNaVersao(v)` retorna o valor de `prox` na versão `v`: parte do valor original e aplica
    a última modificação com versão menor ou igual a `v`
  - A função `proxMaisRecente()` retorna o valor de `prox` na última versão
  - A função `modsCheia()` diz se a lista de modificações está cheia

- **ListaPersistente:**
  - Definida em `listaPersistente.hpp` e implementada em `listaPersistente.cpp`
  - Guarda a lista encadeada ordenada persistente
  - O campo `raizes[]` guarda o primeiro nó da lista em cada versão (`raizes[0]` é a lista vazia)
  - O campo `todosNos[]` guarda todos os nós criados, só para liberar a memória no destrutor
  - O construtor cria a versão 0 (lista vazia) e o destrutor libera todos os nós
  - A função `versaoAtual()` retorna o número da versão mais recente
  - A função `criarNo()` cria um nó novo e o registra em `todosNos`
  - A função `novaVersao()` cria uma nova versão com a mesma raiz da versão anterior
  - A função `ajustarVersao()` trata versões inexistentes como a versão mais recente
  - A função `alterarProx(no, novoProx)` faz `no->prox = novoProx` na versão atual. Se ainda há espaço em
    `mods[]`, apenas anota a modificação (caso 1). Se `mods[]` está cheia, cria uma cópia do nó com os
    valores mais recentes e a lista de modificações vazia, e faz o antecessor (achado pelo ponteiro de
    retorno) apontar para a cópia, o que pode se repetir recursivamente (caso 2). Se `no` é `nullptr`,
    quem muda é a raiz da versão atual
  - A função `inserir(chave)` cria uma nova versão e insere a chave na posição correta (depois de chaves
    iguais, se houver repetição)
  - A função `remover(chave)` cria uma nova versão e remove uma ocorrência da chave, se ela existir
  - A função `sucessor(chave, versao, resposta)` procura a menor chave estritamente maior que `chave` na
    versão pedida, retorna `false` se não existir
  - A função `elementos(versao)` retorna os elementos da versão pedida em ordem crescente

- **main:**
  - Definida em `main.cpp`
  - Lê o arquivo de entrada passado como argumento, executa as operações `INC`, `REM`, `SUC` e `IMP` e
    imprime os resultados no terminal
  - A constante `SEPARADOR` define o separador usado no `IMP`

### Observações

- Para versões inexistentes, tanto o `IMP` quanto o `SUC` usam a versão mais recente.
