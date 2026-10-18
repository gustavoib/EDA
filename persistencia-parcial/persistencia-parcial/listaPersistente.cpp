#include "listaPersistente.hpp"
#include <vector>

ListaPersistente::ListaPersistente() {
  // a versão 0 é a lista vazia
  raizes.push_back(nullptr);
}

ListaPersistente::~ListaPersistente() {
  for (Node* no : todosNos) {
    delete no;
  }
}

int ListaPersistente::versaoAtual() const {
  return (int)raizes.size() - 1;
}

Node* ListaPersistente::criarNo(int chave, Node* prox) {
  Node* novo = new Node(chave, prox);
  todosNos.push_back(novo);
  return novo;
}

// Cria a próxima versão, que começa igual a anterior
// as alterações de ins/rem são feitas depois, todas com o número
// da nova versão
void ListaPersistente::novaVersao() {
  raizes.push_back(raizes.back());
}

// Versões que não existem são tratadas como a versão mais recente
int ListaPersistente::ajustarVersao(int versao) const {
  if (versao < 0 || versao > versaoAtual()) {
    return versaoAtual();
  }
  return versao;
}

void ListaPersistente::alterarProx(Node* no, Node* novoProx) {
  int v = versaoAtual();

  // caso especial: quem aponta para novoProx é a raiz da versão atual
  if (no == nullptr) {
    raizes[v] = novoProx;
    if (novoProx != nullptr) {
      novoProx->anterior = nullptr;
    }
    return;
  }

  Node* proxAntigo = no->proxMaisRecente();

  // O antigo prox deixa de ser apontado por nó na última versão
  if (proxAntigo != nullptr && proxAntigo->anterior == no) {
    proxAntigo->anterior = nullptr;
  }

  if (!no->modsCheia()) {
    // caso 1: ainda cabe uma modificação no nó
    no->mods[no->numMods].versao = v;
    no->mods[no->numMods].prox = novoProx;
    no->numMods++;

    if (novoProx != nullptr) {
      novoProx->anterior = no;
    }
  } else {
    // caso 2: mods cheia -> cria uma cópia com os valores mais recentes
    Node* copia = criarNo(no->chave, novoProx);
    Node* antecessor = no->anterior;

    if (novoProx != nullptr) {
      novoProx->anterior = copia;
    }

    // O nó antigo continua existindo para as versões passadas,
    // mas não faz mais parte da última versao
    no->anterior = nullptr;

    // Quem apontava para o nó antigo agora precisa apontar para a copia
    alterarProx(antecessor, copia);
  }
}

void ListaPersistente::inserir(int chave) {
  novaVersao();
  int v = versaoAtual();

  // procura o antecessor: o último nó com chave <= nova chave
  Node* antecessor = nullptr;
  Node* atual = raizes[v];
  while (atual != nullptr && atual->chave <= chave) {
    antecessor = atual;
    atual = atual->proxNaVersao(v);
  }

  // o nó novo não existe em versões antigas, então seus campos podem ser
  // preenchidos diretamente, sem usar mods
  Node* novo = criarNo(chave, atual);
  if (atual != nullptr) {
    atual->anterior = novo;
  }

  alterarProx(antecessor, novo);
}

void ListaPersistente::remover(int chave) {
  novaVersao();
  int v = versaoAtual();

  Node* antecessor = nullptr;
  Node* atual = raizes[v];
  while (atual != nullptr && atual->chave < chave) {
    antecessor = atual;
    atual = atual->proxNaVersao(v);
  }

  // Se não encontrou, a nova versao fica igual a anterior
  if (atual == nullptr || atual->chave != chave) {
    return;
  }

  alterarProx(antecessor, atual->proxNaVersao(v));
}

// procura a menor chave estritamente maior que chave na versão pedida
bool ListaPersistente::sucessor(int chave, int versao, int& resposta) const {
  int v = ajustarVersao(versao);

  Node* atual = raizes[v];
  while (atual != nullptr) {
    if (atual->chave > chave) {
      resposta = atual->chave;
      return true;
    }
    atual = atual->proxNaVersao(v);
  }
  return false;
}

std::vector<int> ListaPersistente::elementos(int versao) const {
  int v = ajustarVersao(versao);

  std::vector<int> resultado;
  Node* atual = raizes[v];
  while (atual != nullptr) {
    resultado.push_back(atual->chave);
    atual = atual->proxNaVersao(v);
  }
  return resultado;
}
