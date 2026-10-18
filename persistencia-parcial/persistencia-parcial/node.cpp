#include "node.hpp"

Node::Node(int chave, Node* prox) {
  this->chave = chave;
  this->prox = prox;
  this->anterior = nullptr;
  this->numMods = 0;
}

// começa com o valor original e aplica a última mod com versão <= v
// mods são inseridas em ordem crescente de versão, então basta percorrer
// e guardando a última válida
Node* Node::proxNaVersao(int v) const {
  Node* resposta = prox;
  for (int i = 0; i < numMods; i++) {
    if (mods[i].versao <= v) {
      resposta = mods[i].prox;
    }
  }
  return resposta;
}

Node* Node::proxMaisRecente() const {
  if (numMods == 0) {
    return prox;
  }
  return mods[numMods - 1].prox;
}

bool Node::modsCheia() const {
  return numMods == MAX_MODS;
}
