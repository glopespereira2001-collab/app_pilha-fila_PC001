#ifndef PILHA_H
#define PILHA_H

#include <string>

// Estrutura do Nó para a Pilha
struct NoPilha {
    int valor;
    NoPilha* proximo;
    NoPilha(int v) : valor(v), proximo(nullptr) {}
};

class Pilha {
private:
    NoPilha* topo;
    int tamanho;

public:
    Pilha();
    ~Pilha();

    void push(int valor);
    int pop();
    bool vazia() const;

    int getTamanho() const;
    int getSoma() const;
    int getMax() const;
    int getMin() const;

    std::string getElementos() const;
};

#endif
