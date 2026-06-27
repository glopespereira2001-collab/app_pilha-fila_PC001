#include "fila.h"
#include <sstream>
#include <limits>

Fila::Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {}

Fila::~Fila() {
    while (!vazia()) {
        pop();
    }
}

void Fila::push(int valor) {
    NoFila* novo = new NoFila(valor);
    if (fim != nullptr) {
        fim->proximo = novo;
    }
    fim = novo;
    if (inicio == nullptr) {
        inicio = novo;
    }
    tamanho++;
}

int Fila::pop() {
    if (vazia()) return -1;
    NoFila* temp = inicio;
    int valor = temp->valor;
    inicio = inicio->proximo;
    if (inicio == nullptr) {
        fim = nullptr;
    }
    delete temp;
    tamanho--;
    return valor;
}

bool Fila::vazia() const {
    return inicio == nullptr;
}

int Fila::getTamanho() const {
    return tamanho;
}

int Fila::getSoma() const {
    int soma = 0;
    NoFila* atual = inicio;
    while (atual != nullptr) {
        soma += atual->valor;
        atual = atual->proximo;
    }
    return soma;
}

int Fila::getMax() const {
    if (vazia()) return 0;
    int max_val = std::numeric_limits<int>::min();
    NoFila* atual = inicio;
    while (atual != nullptr) {
        if (atual->valor > max_val) max_val = atual->valor;
        atual = atual->proximo;
    }
    return max_val;
}

int Fila::getMin() const {
    if (vazia()) return 0;
    int min_val = std::numeric_limits<int>::max();
    NoFila* atual = inicio;
    while (atual != nullptr) {
        if (atual->valor < min_val) min_val = atual->valor;
        atual = atual->proximo;
    }
    return min_val;
}

std::string Fila::getElementos() const {
    if (vazia()) return "";
    std::stringstream ss;
    NoFila* atual = inicio;
    while (atual != nullptr) {
        ss << atual->valor;
        if (atual->proximo != nullptr) ss << " ";
        atual = atual->proximo;
    }
    return ss.str();
}
