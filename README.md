# Simulador Interativo para Estruturas de Dados

Esta é uma aplicação web interativa desenvolvida com **Streamlit (Python)** e **C++** puro para visualização e aprendizado do funcionamento interno de Pilhas e Filas.

## 🛠️ Pré-requisitos

- **Python 3.9+** (com `pip`)
- **Compilador C++** (`g++`)
- **Make** (Opcional no Windows, mas recomendado)

## 🚀 Como executar o projeto

### 1. Compilar o Back-end em C++

Vá até o diretório `backend` e compile o projeto.

No Linux/Mac:
```bash
cd backend
make
```

No Windows (se não tiver `make`):
```cmd
cd backend
g++ -std=c++17 -Wall -Wextra -o main.exe main.cpp pilha.cpp fila.cpp
```

### 2. Configurar o Front-end em Python

Volte para a pasta raiz, entre em `frontend` e instale as dependências:

```bash
cd frontend
pip install -r requirements.txt
```

### 3. Rodar a Aplicação

Ainda no diretório `frontend`, execute o Streamlit:

```bash
streamlit run app.py
```

Isso abrirá automaticamente a interface do simulador no seu navegador (geralmente em `http://localhost:8501`).

## 📁 Estrutura do Repositório

- `backend/`: Código C++ responsável pela lógica, alocação dinâmica e cálculos matemáticos.
- `frontend/`: Código Python utilizando Streamlit para interface visual e parsing dos comandos.
- `docs/`: Documentos de entrega do projeto.
- `spec.md`: Especificação técnica completa.
