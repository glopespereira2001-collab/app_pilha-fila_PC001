# 📄 Especificação do Projeto: Simulador Interativo para Estruturas de Dados

---

## 1. Visão Geral

**Objetivo:** Desenvolver uma aplicação web interativa e educacional que permita visualizar o funcionamento interno das estruturas de dados **Pilha (Stack)** e **Fila (Queue)**.

**Público-alvo:** Estudantes de disciplinas de Estrutura de Dados.

**Fluxo resumido:**
1. O usuário interage com a interface Streamlit (Python).
2. A cada ação, o Python invoca o binário C++ via subprocess, passando o histórico completo de comandos.
3. O C++ reconstrói a estrutura, calcula as métricas e retorna o estado via `stdout`.
4. O Python faz o parsing da saída e renderiza a visualização na tela.

---

## 2. Arquitetura Tecnológica

O sistema adota uma arquitetura **separada** entre lógica de dados e interface visual, comunicando-se via `stdout`:

| Camada | Tecnologia | Responsabilidade |
|---|---|---|
| **Back-end (Lógica)** | C++ puro | Classes `Pilha` e `Fila` com alocação dinâmica (ponteiros/nós). Recebe comandos via CLI, processa e retorna resultado via `stdout`. |
| **Front-end (Interface)** | Python + Streamlit | Interface web interativa. Mantém o histórico de comandos em `st.session_state` e invoca o binário C++ a cada interação. |

### 2.1. Estrutura de Arquivos do Projeto

```
projeto_extra_PC001/
├── spec.md              # Esta especificação
├── README.md            # Instruções de instalação e uso
│
├── backend/
│   ├── main.cpp         # Ponto de entrada — parsing de CLI, dispatch para Pilha ou Fila
│   ├── pilha.h          # Declaração da classe Pilha (lista encadeada)
│   ├── pilha.cpp        # Implementação da classe Pilha
│   ├── fila.h           # Declaração da classe Fila (lista encadeada)
│   ├── fila.cpp         # Implementação da classe Fila
│   └── Makefile         # Compilação: g++ -o main main.cpp pilha.cpp fila.cpp
│
├── frontend/
│   ├── app.py           # Aplicação Streamlit principal
│   └── requirements.txt # Dependência: streamlit
│
└── docs/
    └── entrega.txt      # Link do repositório Git (entregável)
```

---

## 3. Requisitos Funcionais

O sistema deve garantir o funcionamento estrito das regras mecânicas de cada estrutura.

### 3.1. Operações Base

| Operação | Pilha (LIFO) | Fila (FIFO) |
|---|---|---|
| **Escolha de Estrutura** | O usuário alterna livremente entre "Pilha" e "Fila" | — |
| **Push (Inserir)** | O elemento entra no **Topo** | O elemento entra no **Fim** |
| **Pop (Remover)** | Remove o elemento do **Topo** | Remove o elemento do **Início** |

- O valor inserido deve ser um **número inteiro** informado pelo usuário.
- Pop em estrutura vazia deve exibir uma **mensagem de erro amigável** (não deve travar).

### 3.2. Funcionalidades Extras (Analytics)

A cada alteração na estrutura, o painel deve recalcular e exibir **automaticamente**:

| Métrica | Descrição |
|---|---|
| **Tamanho** | Quantidade total de elementos atuais |
| **Somatório** | Soma dos valores de todos os elementos |
| **Maior elemento** | Valor máximo presente na estrutura |
| **Menor elemento** | Valor mínimo presente na estrutura |

> Quando a estrutura estiver vazia, todas as métricas devem mostrar `0` (ou `N/A`).

---

## 4. Requisitos Visuais e de Interface (Streamlit)

O front-end Python deve traduzir as saídas do C++ em representações visuais claras para o aprendizado.

### 4.1. Renderização de Pilha

- Deve crescer **verticalmente** (blocos empilhados de baixo para cima).
- O marcador visual deve destacar claramente qual é o elemento do **Topo** (local onde ocorrem as inserções e remoções).
- Implementação: usar `st.columns` ou HTML/CSS inline via `st.markdown` para renderizar blocos coloridos empilhados.

**Exemplo visual (Pilha com valores 10, 20, 30 — 30 é o topo):**
```
  ┌──────────┐
  │  30 ← TOPO │
  ├──────────┤
  │    20    │
  ├──────────┤
  │    10    │
  └──────────┘
```

### 4.2. Renderização de Fila

- Deve crescer **horizontalmente** (blocos lado a lado, da esquerda para a direita).
- O marcador visual deve indicar explicitamente qual extremidade é o **Início** (próximo a sair) e qual é o **Fim** (último a entrar).
- Implementação: usar `st.columns` para dispor os blocos lado a lado, com labels "INÍCIO" e "FIM".

**Exemplo visual (Fila com valores 10, 20, 30 — 10 é o início, 30 é o fim):**
```
  INÍCIO →  ┌────┐ ┌────┐ ┌────┐  ← FIM
             │ 10 │ │ 20 │ │ 30 │
             └────┘ └────┘ └────┘
```

### 4.3. Layout Geral da Interface

```
┌─────────────────────────────────────────────────────────┐
│  🧮 Simulador de Estruturas de Dados                    │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  [Pilha / Fila]  ← seletor (st.radio ou st.selectbox)  │
│                                                         │
│  ┌───────────────────┐  ┌─────────────┐                │
│  │ Valor: [___input]  │  │  [Inserir]  │                │
│  └───────────────────┘  └─────────────┘                │
│                          ┌─────────────┐                │
│                          │  [Remover]   │                │
│                          └─────────────┘                │
│                                                         │
│  ┌─── Visualização da Estrutura ──────────────────────┐ │
│  │                                                     │ │
│  │   (renderização visual da Pilha ou Fila aqui)       │ │
│  │                                                     │ │
│  └─────────────────────────────────────────────────────┘ │
│                                                         │
│  ┌─── Analytics ──────────────────────────────────────┐ │
│  │  Tamanho: 3  │  Soma: 60  │  Maior: 30  │ Menor: 10│ │
│  └─────────────────────────────────────────────────────┘ │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## 5. Protocolo de Comunicação (Subprocess / CLI)

Como os binários C++ **não retêm estado** entre os cliques do Streamlit, o histórico de inserções e remoções será mantido pelo **estado de sessão do Python** (`st.session_state`).

### 5.1. Fluxo de Comunicação

```
[Usuário clica "Inserir 42"]
        │
        ▼
[Python] Adiciona "push 42" ao st.session_state["historico"]
        │
        ▼
[Python] Invoca: subprocess.run(["./backend/main", "pilha", "push 10", "push 20", "push 42"])
        │
        ▼
[C++]   Reconstrói a estrutura do zero, replay de todos os comandos
        │
        ▼
[C++]   Imprime em stdout: "3 72 10 42 | 10 20 42"
        │
        ▼
[Python] Faz parsing da string → métricas + lista de elementos
        │
        ▼
[Python] Renderiza a visualização e o painel de analytics
```

### 5.2. Formato da Entrada (Python → C++)

```bash
./backend/main <tipo_estrutura> <comando_1> <comando_2> ... <comando_N>
```

- `<tipo_estrutura>`: `"pilha"` ou `"fila"` (string em minúsculas)
- `<comando_N>`: `"push <valor>"` ou `"pop"`

**Exemplos:**
```bash
# Inserir 10, 20, 30 em uma pilha
./backend/main pilha "push 10" "push 20" "push 30"

# Inserir 5, 15 e remover um da fila
./backend/main fila "push 5" "push 15" "pop"
```

### 5.3. Formato da Saída (C++ → Python via stdout)

```
<tamanho> <soma> <min> <max> | <elem_1> <elem_2> ... <elem_N>
```

- Métricas separadas por espaço antes do `|`.
- Elementos atuais da estrutura separados por espaço após o `|`.
- Se a estrutura estiver vazia: `0 0 0 0 |` (sem elementos após o pipe).

**Exemplos de saída:**
```
3 60 10 30 | 10 20 30
1 15 15 15 | 15
0 0 0 0 |
```

### 5.4. Tratamento de Erros

| Cenário | Comportamento do C++ |
|---|---|
| Pop em estrutura vazia | Ignora o comando (não faz nada, não imprime erro) |
| Comando inválido | Ignora o comando |
| Nenhum comando passado | Retorna `0 0 0 0 |` |

---

## 6. Detalhamento da Implementação C++ (Back-end)

### 6.1. Estrutura do Nó (Comum a Pilha e Fila)

```cpp
// Usado internamente por Pilha e Fila
struct No {
    int valor;
    No* proximo;
    No(int v) : valor(v), proximo(nullptr) {}
};
```

### 6.2. Classe Pilha (`pilha.h` / `pilha.cpp`)

```cpp
class Pilha {
private:
    No* topo;          // Ponteiro para o topo da pilha
    int tamanho;       // Contador de elementos

public:
    Pilha();           // Construtor: topo = nullptr, tamanho = 0
    ~Pilha();          // Destrutor: desaloca todos os nós

    void push(int valor);   // Cria novo nó, aponta para topo atual, atualiza topo
    int  pop();             // Remove nó do topo, retorna valor (retorna -1 se vazio)
    bool vazia() const;     // Retorna (topo == nullptr)

    // Métodos de travessia para analytics
    int  getTamanho() const;
    int  getSoma() const;       // Percorre toda a lista somando
    int  getMax() const;        // Percorre toda a lista comparando
    int  getMin() const;        // Percorre toda a lista comparando

    // Retorna string com elementos separados por espaço (da base ao topo)
    std::string getElementos() const;
};
```

**Lógica do Push (Pilha):**
1. Cria `No* novo = new No(valor)`
2. `novo->proximo = topo`
3. `topo = novo`
4. `tamanho++`

**Lógica do Pop (Pilha):**
1. Se `topo == nullptr`, retorna (estrutura vazia)
2. `No* temp = topo`
3. `topo = topo->proximo`
4. Captura `temp->valor`
5. `delete temp`
6. `tamanho--`

### 6.3. Classe Fila (`fila.h` / `fila.cpp`)

```cpp
class Fila {
private:
    No* inicio;        // Ponteiro para o início (frente) da fila
    No* fim;           // Ponteiro para o fim (traseira) da fila
    int tamanho;       // Contador de elementos

public:
    Fila();            // Construtor: inicio = fim = nullptr, tamanho = 0
    ~Fila();           // Destrutor: desaloca todos os nós

    void push(int valor);   // Cria novo nó, insere no fim
    int  pop();             // Remove nó do início, retorna valor
    bool vazia() const;     // Retorna (inicio == nullptr)

    // Métodos de travessia para analytics
    int  getTamanho() const;
    int  getSoma() const;
    int  getMax() const;
    int  getMin() const;

    // Retorna string com elementos separados por espaço (do início ao fim)
    std::string getElementos() const;
};
```

**Lógica do Push (Fila):**
1. Cria `No* novo = new No(valor)`
2. Se `fim != nullptr`: `fim->proximo = novo`
3. `fim = novo`
4. Se `inicio == nullptr`: `inicio = novo` (primeiro elemento)
5. `tamanho++`

**Lógica do Pop (Fila):**
1. Se `inicio == nullptr`, retorna (fila vazia)
2. `No* temp = inicio`
3. `inicio = inicio->proximo`
4. Se `inicio == nullptr`: `fim = nullptr` (fila ficou vazia)
5. Captura `temp->valor`
6. `delete temp`
7. `tamanho--`

### 6.4. main.cpp — Ponto de Entrada

```
Pseudocódigo:
1. Ler argv[1] → tipo_estrutura ("pilha" ou "fila")
2. Ler argv[2..N] → lista de comandos
3. Instanciar Pilha ou Fila
4. Para cada comando:
   - Se começa com "push": extrair valor inteiro, chamar push(valor)
   - Se é "pop": chamar pop()
   - Caso contrário: ignorar
5. Imprimir em stdout: "<tamanho> <soma> <min> <max> | <elementos>"
6. Retornar 0
```

### 6.5. Makefile

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = main
SRCS = main.cpp pilha.cpp fila.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
```

---

## 7. Detalhamento da Implementação Python (Front-end)

### 7.1. `app.py` — Estrutura Principal

```python
# Pseudocódigo do app.py

import streamlit as st
import subprocess

# ── Inicialização do estado ──
if "tipo" not in st.session_state:
    st.session_state.tipo = "pilha"
if "historico" not in st.session_state:
    st.session_state.historico = []

# ── Sidebar ou topo: seletor de estrutura ──
tipo = st.radio("Estrutura:", ["Pilha", "Fila"])
# Se o tipo mudou, limpar histórico
if tipo.lower() != st.session_state.tipo:
    st.session_state.tipo = tipo.lower()
    st.session_state.historico = []

# ── Controles de entrada ──
col1, col2 = st.columns([3, 1])
with col1:
    valor = st.number_input("Valor inteiro:", step=1, value=0)
with col2:
    if st.button("Inserir"):
        st.session_state.historico.append(f"push {valor}")
    if st.button("Remover"):
        st.session_state.historico.append("pop")

# ── Invocar o binário C++ ──
resultado = executar_cpp(st.session_state.tipo, st.session_state.historico)

# ── Parsing da saída ──
metricas, elementos = parse_saida(resultado)

# ── Renderização ──
if st.session_state.tipo == "pilha":
    renderizar_pilha(elementos)
else:
    renderizar_fila(elementos)

# ── Painel de Analytics ──
exibir_analytics(metricas)
```

### 7.2. Função `executar_cpp()`

```python
def executar_cpp(tipo: str, historico: list[str]) -> str:
    """Invoca o binário C++ e retorna a saída stdout."""
    cmd = ["./backend/main", tipo] + historico
    resultado = subprocess.run(cmd, capture_output=True, text=True, timeout=5)
    return resultado.stdout.strip()
```

### 7.3. Função `parse_saida()`

```python
def parse_saida(saida: str) -> tuple[dict, list[int]]:
    """Faz parsing da string 'tamanho soma min max | elem1 elem2 ...'"""
    partes = saida.split("|")
    metricas_raw = partes[0].strip().split()
    elementos_raw = partes[1].strip().split() if len(partes) > 1 and partes[1].strip() else []

    metricas = {
        "tamanho": int(metricas_raw[0]),
        "soma":    int(metricas_raw[1]),
        "min":     int(metricas_raw[2]),
        "max":     int(metricas_raw[3]),
    }
    elementos = [int(e) for e in elementos_raw]
    return metricas, elementos
```

### 7.4. Funções de Renderização

**`renderizar_pilha(elementos)`** — Usa `st.markdown` com HTML/CSS inline para desenhar blocos empilhados verticalmente. O último elemento da lista (topo) recebe uma cor diferente e o label "← TOPO".

**`renderizar_fila(elementos)`** — Usa `st.columns` para dispor blocos horizontalmente. O primeiro elemento recebe o label "INÍCIO →" e o último recebe "← FIM".

### 7.5. Função `exibir_analytics()`

Renderiza 4 colunas com `st.metric`:
```python
def exibir_analytics(metricas: dict):
    c1, c2, c3, c4 = st.columns(4)
    c1.metric("Tamanho", metricas["tamanho"])
    c2.metric("Somatório", metricas["soma"])
    c3.metric("Maior", metricas["max"])
    c4.metric("Menor", metricas["min"])
```

---

## 8. Protocolo de Compilação e Execução

### 8.1. Compilar o Back-end

```bash
cd backend
make          # Gera o binário ./main
```

### 8.2. Instalar Dependências Python

```bash
cd frontend
pip install -r requirements.txt
```

### 8.3. Executar a Aplicação

```bash
cd frontend
streamlit run app.py
```

> O `app.py` invocará `./backend/main` via subprocess. O path deve ser ajustado conforme a localização relativa.

---

## 9. Entregáveis e Submissão

| Entregável | Descrição |
|---|---|
| **Repositório Git** | Código-fonte estruturado contendo os arquivos `.cpp`, `.h`, `.py` e `Makefile`, hospedado no GitHub/GitLab |
| **README.md** | Instruções detalhadas de como instalar o Streamlit, compilar o C++ e executar o projeto |
| **Documento Final** | Arquivo `.txt` ou `.doc` contendo o link do repositório Git |

---

## 10. Checklist de Implementação

- [ ] Criar estrutura de pastas (`backend/`, `frontend/`, `docs/`)
- [ ] Implementar `No` struct, `Pilha` classe (`.h` + `.cpp`)
- [ ] Implementar `Fila` classe (`.h` + `.cpp`)
- [ ] Implementar `main.cpp` com parsing de CLI e output formatado
- [ ] Criar `Makefile`
- [ ] Testar o binário C++ isoladamente via terminal
- [ ] Implementar `app.py` (Streamlit) com estado de sessão
- [ ] Implementar renderização visual (Pilha vertical, Fila horizontal)
- [ ] Implementar painel de Analytics com `st.metric`
- [ ] Criar `requirements.txt`
- [ ] Criar `README.md` com instruções completas
- [ ] Teste integrado: Streamlit invocando C++ corretamente