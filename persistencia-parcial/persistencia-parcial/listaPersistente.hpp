#ifndef LISTAPERSISTENTE_HPP_
#define LISTAPERSISTENTE_HPP_

#include <vector>

#include "node.hpp"

class ListaPersistente {
 public:
  ListaPersistente();
  ~ListaPersistente();

  // operações
  void inserir(int chave);
  void remover(int chave);

  // operações de consulta (não criam versão)
  bool sucessor(int chave, int versao, int& resposta) const;
  std::vector<int> elementos(int versao) const;

  int versaoAtual() const;

 private:
  // raizes[v] = primeiro nó da lista na versão v (nullptr se vazia)
  std::vector<Node*> raizes;

  std::vector<Node*> todosNos;

  Node* criarNo(int chave, Node* prox);
  void novaVersao();
  int ajustarVersao(int versao) const;

  // Faz no->prox = novoProx na versão atual
  // Se no == nullptr, quem muda é a raiz da versão atual
  void alterarProx(Node* no, Node* novoProx);
};

#endif  // LISTAPERSISTENTE_HPP_
