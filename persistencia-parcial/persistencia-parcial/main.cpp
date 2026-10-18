// Copyright 2026 dcaracas

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "listaPersistente.hpp"

using namespace std;

const string SEPARADOR = " ";

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  ifstream arquivo(argv[1]);
  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo " << argv[1] << endl;
    return 1;
  }

  ListaPersistente lista;
  string operacao;

  while (arquivo >> operacao) {
    if (operacao == "INC") {
      int n;
      arquivo >> n;
      lista.inserir(n);
    } else if (operacao == "REM") {
      int n;
      arquivo >> n;
      lista.remover(n);
    } else if (operacao == "SUC") {
      int n, m;
      arquivo >> n >> m;
      cout << "SUC " << n << " " << m << "\n";

      int resposta;
      if (lista.sucessor(n, m, resposta)) {
        cout << resposta << "\n";
      } else {
        cout << "inf\n";
      }
    } else if (operacao == "IMP") {
      int m;
      arquivo >> m;
      cout << "IMP " << m << "\n";

      vector<int> elementos = lista.elementos(m);
      for (int i = 0; i < (int)elementos.size(); i++) {
        if (i > 0) {
          cout << SEPARADOR;
        }
        cout << elementos[i];
      }
      cout << "\n";
    }
  }

  return 0;
}
