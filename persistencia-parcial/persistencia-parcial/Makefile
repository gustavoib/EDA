INPUT = entrada.txt
TESTES = testes

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

FONTES = main.cpp node.cpp listaPersistente.cpp
CABECALHOS = node.hpp listaPersistente.hpp

.PHONY: build run test clean

build: programa

programa: $(FONTES) $(CABECALHOS)
	$(CXX) $(CXXFLAGS) -o programa $(FONTES)

run:
	@./programa $(INPUT)

test: build
	@for entrada in $(TESTES)/*.in; do \
		esperada=$${entrada%.in}.out; \
		if ./programa $$entrada | diff -q - $$esperada > /dev/null; then \
			echo "OK     $$entrada"; \
		else \
			echo "FALHOU $$entrada"; \
		fi; \
	done

clean:
	rm -f programa
