// Copyright 2026 dcaracas

#ifndef NODE_HPP_
#define NODE_HPP_

// cada nó recebe no máximo 1 ponteiro de outro nó (seu antecessor)
// então o grau de entrada é p = 1 e cada nó guarda no máximo 2 modificações
const int P = 1;
const int MAX_MODS = 2 * P;

struct Node;
struct Mod {
  int versao;
  Node* prox;
};

struct Node {
  // lista encadeada base
  int chave;
  Node* prox;

  // ponteiro de retorno: quem aponta para este nó na última versão
  // se nullptr: nó é o primeiro da lista (quem aponta é a raiz) ou não é mais última versão
  Node* anterior;

  // mods
  Mod mods[MAX_MODS];
  int numMods;

  Node(int chave, Node* prox);

  // valor do campo prox na versão v
  Node* proxNaVersao(int v) const;

  // valor do campo prox na última versão
  Node* proxMaisRecente() const;

  bool modsCheia() const;
};

#endif  // NODE_HPP_
