#include <iostream>
#include <string>
#include "pilha.h"
#include "fila.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "0 0 0 0 |" << std::endl;
        return 0;
    }

    std::string tipo = argv[1];

    if (tipo == "pilha") {
        Pilha p;
        for (int i = 2; i < argc; ++i) {
            std::string cmd = argv[i];
            if (cmd.find("push ") == 0) {
                int val = std::stoi(cmd.substr(5));
                p.push(val);
            } else if (cmd == "pop") {
                p.pop();
            }
        }
        std::cout << p.getTamanho() << " " 
                  << p.getSoma() << " " 
                  << p.getMin() << " " 
                  << p.getMax() << " | " 
                  << p.getElementos() << std::endl;

    } else if (tipo == "fila") {
        Fila f;
        for (int i = 2; i < argc; ++i) {
            std::string cmd = argv[i];
            if (cmd.find("push ") == 0) {
                int val = std::stoi(cmd.substr(5));
                f.push(val);
            } else if (cmd == "pop") {
                f.pop();
            }
        }
        std::cout << f.getTamanho() << " " 
                  << f.getSoma() << " " 
                  << f.getMin() << " " 
                  << f.getMax() << " | " 
                  << f.getElementos() << std::endl;
    } else {
        std::cout << "0 0 0 0 |" << std::endl;
    }

    return 0;
}
