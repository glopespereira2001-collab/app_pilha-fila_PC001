#include "pilha.h"
#include <sstream>
#include <limits>
#include <vector>

Pilha::Pilha() : topo(nullptr), tamanho(0) {}

Pilha::~Pilha() {
    while (!vazia()) {
        pop();
    }
}

void Pilha::push(int valor) {
    NoPilha* novo = new NoPilha(valor);
    novo->proximo = topo;
    topo = novo;
    tamanho++;
}

int Pilha::pop() {
    if (vazia()) return -1;
    NoPilha* temp = topo;
    int valor = temp->valor;
    topo = topo->proximo;
    delete temp;
    tamanho--;
    return valor;
}

bool Pilha::vazia() const {
    return topo == nullptr;
}

int Pilha::getTamanho() const {
    return tamanho;
}

int Pilha::getSoma() const {
    int soma = 0;
    NoPilha* atual = topo;
    while (atual != nullptr) {
        soma += atual->valor;
        atual = atual->proximo;
    }
    return soma;
}

int Pilha::getMax() const {
    if (vazia()) return 0;
    int max_val = std::numeric_limits<int>::min();
    NoPilha* atual = topo;
    while (atual != nullptr) {
        if (atual->valor > max_val) max_val = atual->valor;
        atual = atual->proximo;
    }
    return max_val;
}

int Pilha::getMin() const {
    if (vazia()) return 0;
    int min_val = std::numeric_limits<int>::max();
    NoPilha* atual = topo;
    while (atual != nullptr) {
        if (atual->valor < min_val) min_val = atual->valor;
        atual = atual->proximo;
    }
    return min_val;
}

std::string Pilha::getElementos() const {
    if (vazia()) return "";
    std::vector<int> elems;
    NoPilha* atual = topo;
    while (atual != nullptr) {
        elems.push_back(atual->valor);
        atual = atual->proximo;
    }
    
    std::stringstream ss;
    // Para a pilha, a saída deve ser da base para o topo, 
    // então iteramos o vetor de trás pra frente.
    for (int i = elems.size() - 1; i >= 0; --i) {
        ss << elems[i];
        if (i > 0) ss << " ";
    }
    return ss.str();
}
