import streamlit as st
import subprocess
import os

# ── Configuração da Página ──
st.set_page_config(page_title="Simulador de Estruturas de Dados", layout="wide")

# ── Inicialização do estado ──
if "tipo" not in st.session_state:
    st.session_state.tipo = "pilha"
if "historico" not in st.session_state:
    st.session_state.historico = []

# ── Funções Auxiliares ──
def executar_cpp(tipo: str, historico: list[str]) -> str:
    """Invoca o binário C++ e retorna a saída stdout."""
    # O caminho do binário deve ser relativo à execução ou configurado corretamente
    backend_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "backend")
    bin_path = os.path.join(backend_dir, "main" if os.name != 'nt' else "main.exe")
    
    cmd = [bin_path, tipo] + historico
    try:
        resultado = subprocess.run(cmd, capture_output=True, text=True, timeout=5)
        return resultado.stdout.strip()
    except Exception as e:
        st.error(f"Erro ao executar o C++: {e}")
        return "0 0 0 0 | "

def parse_saida(saida: str) -> tuple[dict, list[int]]:
    """Faz parsing da string 'tamanho soma min max | elem1 elem2 ...'"""
    try:
        partes = saida.split("|")
        metricas_raw = partes[0].strip().split()
        elementos_raw = partes[1].strip().split() if len(partes) > 1 and partes[1].strip() else []

        metricas = {
            "tamanho": int(metricas_raw[0]) if len(metricas_raw) > 0 else 0,
            "soma":    int(metricas_raw[1]) if len(metricas_raw) > 1 else 0,
            "min":     int(metricas_raw[2]) if len(metricas_raw) > 2 else 0,
            "max":     int(metricas_raw[3]) if len(metricas_raw) > 3 else 0,
        }
        elementos = [int(e) for e in elementos_raw]
        return metricas, elementos
    except Exception as e:
        st.error(f"Erro no parsing: {e}")
        return {"tamanho": 0, "soma": 0, "min": 0, "max": 0}, []

# ── Funções de Renderização Visual ──
def renderizar_pilha(elementos: list[int]):
    st.markdown("### Visualização da Pilha")
    if not elementos:
        st.info("A Pilha está vazia.")
        return
    
    # Para renderizar verticalmente, iteramos de trás para frente (topo para a base)
    blocos = ""
    for i, val in enumerate(reversed(elementos)):
        bg_color = "#ff4b4b" if i == 0 else "#262730"
        label = " ← TOPO" if i == 0 else ""
        blocos += f'<div style="background-color:{bg_color};color:white;padding:15px;margin:5px;width:200px;text-align:center;border-radius:5px;font-weight:bold;">{val}{label}</div>'
    
    st.html(f'<div style="display:flex;flex-direction:column;align-items:center;width:100%;">{blocos}</div>')

def renderizar_fila(elementos: list[int]):
    st.markdown("### Visualização da Fila")
    if not elementos:
        st.info("A Fila está vazia.")
        return

    blocos = '<div style="margin-right:15px;font-weight:bold;">INÍCIO →</div>'
    for val in elementos:
        blocos += f'<div style="background-color:#262730;color:white;padding:15px;margin:5px;min-width:60px;text-align:center;border-radius:5px;font-weight:bold;">{val}</div>'
    blocos += '<div style="margin-left:15px;font-weight:bold;">← FIM</div>'
    
    st.html(f'<div style="display:flex;flex-direction:row;justify-content:center;align-items:center;width:100%;overflow-x:auto;">{blocos}</div>')

def exibir_analytics(metricas: dict):
    st.markdown("---")
    st.markdown("### Analytics")
    c1, c2, c3, c4 = st.columns(4)
    c1.metric("Tamanho", metricas["tamanho"])
    c2.metric("Somatório", metricas["soma"])
    c3.metric("Maior Elemento", metricas["max"] if metricas["tamanho"] > 0 else "N/A")
    c4.metric("Menor Elemento", metricas["min"] if metricas["tamanho"] > 0 else "N/A")

# ── Interface Principal ──
st.title("🧮 Simulador Interativo para Estruturas de Dados")

# Seletor de estrutura
tipo = st.radio("Selecione a Estrutura:", ["Pilha", "Fila"], horizontal=True)

# Limpar histórico ao trocar de estrutura
if tipo.lower() != st.session_state.tipo:
    st.session_state.tipo = tipo.lower()
    st.session_state.historico = []

st.markdown("---")

# Controles de entrada
col1, col2, col3 = st.columns([2, 1, 1])
with col1:
    valor = st.number_input("Valor inteiro para inserir:", step=1, value=0, format="%d")
with col2:
    if st.button("Inserir Elemento", use_container_width=True):
        st.session_state.historico.append(f"push {valor}")
with col3:
    if st.button("Remover Elemento", use_container_width=True):
        st.session_state.historico.append("pop")

st.markdown("---")

# Executar lógica C++ e atualizar visualização
saida_cpp = executar_cpp(st.session_state.tipo, st.session_state.historico)
metricas, elementos = parse_saida(saida_cpp)

# Renderização condicional
if st.session_state.tipo == "pilha":
    renderizar_pilha(elementos)
else:
    renderizar_fila(elementos)

# Analytics
exibir_analytics(metricas)
