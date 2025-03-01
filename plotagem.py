import networkx as nx
import matplotlib.pyplot as plt

def ler_grafo(arquivo):
    """Função para ler o grafo a partir de um arquivo"""
    with open(arquivo, "r") as f:
        linhas = f.readlines()
    
    num_nos = int(linhas[0].strip())  # Número de nós
    arestas = [tuple(map(int, linha.strip().split())) for linha in linhas[1:]]
    
    return num_nos, arestas

def ler_resultado_busca(arquivo_resultado):
    """Função para ler o caminho encontrado pela busca irreversível"""

    caminho = []
    with open(arquivo_resultado, 'r') as f:
        n = int(f.readline())

        for i in range(n-1):
            linha = f.readline()
            caminho.append(linha.split(" ")[0])

        linha = f.readline().split(" ")
        caminho.append(linha[0])
        caminho.append(linha[1])

    return list(map(int, caminho))

def plotar_grafo(arquivo_grafo, arquivo_resultado):
    """Função para plotar o grafo com o caminho encontrado pela busca irreversível"""
    num_nos, arestas = ler_grafo(arquivo_grafo)
    caminho = ler_resultado_busca(arquivo_resultado)  # Lê o caminho da busca

    G = nx.Graph()
    for u, v, peso in arestas:
        G.add_edge(u, v, weight=peso)
    
    pos = nx.spring_layout(G, seed=42)  # Melhor distribuição dos nós
    
    plt.figure(figsize=(8, 6))  # Ajusta o tamanho da figura
    edge_widths = 2 
    
    # Desenhar nós e arestas com ajustes visuais
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray',
            node_size=1000, font_size=12, width=edge_widths, edgecolors='black')
    
    # Adicionar rótulos de peso nas arestas com tamanho maior
    labels = {(u, v): peso for u, v, peso in arestas}
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=14, font_color='red', label_pos=0.3)

    # Destacar o caminho da busca depois dos outros componentes
    caminho_edges = [(caminho[i], caminho[i + 1]) for i in range(len(caminho) - 1)]
    
    # Desenhando as arestas do caminho com um "marca-texto" amarelo e transparência aumentada
    nx.draw_networkx_edges(G, pos, edgelist=caminho_edges, width=8, edge_color='yellow', alpha=0.3)

    # Pinta o nó de início de rosa e adiciona o contorno
    inicio = caminho[0]  # O primeiro nó do caminho é o nó de início
    nx.draw_networkx_nodes(G, pos, nodelist=[inicio], node_color='pink', node_size=1000, edgecolors='black')

    plt.show()

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Uso: python plotagem.py <arquivo_grafo> <arquivo_resultado>")
    else:
        plotar_grafo(sys.argv[1], sys.argv[2])
