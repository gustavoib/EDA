#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "listaPersistente.hpp"

using namespace std;

const string SEPARADOR = ", ";

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
  bool primeiro = true;  // controla a quebra de linha entre as saídas

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

      if (!primeiro) cout << "\n";
      primeiro = false;

      cout << "SUC " << n << " " << m << "\n";

      int resposta;
      if (lista.sucessor(n, m, resposta)) {
        cout << resposta;
      } else {
        cout << "inf";
      }
    } else if (operacao == "IMP") {
      int m;
      arquivo >> m;

      if (!primeiro) cout << "\n";
      primeiro = false;

      cout << "IMP " << m << "\n";

      vector<int> elementos = lista.elementos(m);
      for (int i = 0; i < (int)elementos.size(); i++) {
        if (i > 0) {
          cout << SEPARADOR;
        }
        cout << elementos[i];
      }
    }
  }
  return 0;
}