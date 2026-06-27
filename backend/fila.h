#ifndef FILA_H
#define FILA_H

#include <string>

// Estrutura do Nó para a Fila
struct NoFila {
    int valor;
    NoFila* proximo;
    NoFila(int v) : valor(v), proximo(nullptr) {}
};

class Fila {
private:
    NoFila* inicio;
    NoFila* fim;
    int tamanho;

public:
    Fila();
    ~Fila();

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
