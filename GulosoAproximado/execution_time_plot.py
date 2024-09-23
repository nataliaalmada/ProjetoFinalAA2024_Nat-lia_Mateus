import pandas as pd
import random
import time
import matplotlib.pyplot as plt
import networkx as nx

# Função para ler o arquivo CLQ e construir o grafo
def read_clq_file(file_name):
    graph = nx.Graph()
    
    with open(file_name, "r") as file:
        for line in file:
            tokens = line.strip().split()
            if not tokens:
                continue

            if tokens[0] == "p":
                num_vertices = int(tokens[2])
                graph.add_nodes_from(range(1, num_vertices + 1))
            elif tokens[0] == "e":
                vertex1, vertex2 = int(tokens[1]), int(tokens[2])
                graph.add_edge(vertex1, vertex2)
    
    return graph

# Função para encontrar o clique máximo usando um algoritmo guloso
def encontrar_clique_guloso(graph):
    max_clique = []
    for node in graph.nodes():
        current_clique = [node]
        for neighbor in graph.neighbors(node):
            if all(neighbor in graph.neighbors(n) for n in current_clique):
                current_clique.append(neighbor)
        if len(current_clique) > len(max_clique):
            max_clique = current_clique
    return max_clique

# Medir o tempo de execução
def medir_tempo_execucao(graph):
    start_time = time.time()
    max_clique = encontrar_clique_guloso(graph)
    end_time = time.time()
    return end_time - start_time, max_clique

# Configurações do gáfico
def plotar_grafico(tempos):
    plt.figure(figsize=(10, 6))
    plt.plot(range(len(tempos)), tempos, marker='o')
    plt.title('Tempo de Execução para Encontrar o Clique Máximo')
    plt.xlabel('Execuções')
    plt.ylabel('Tempo (segundos)')
    plt.xticks(range(len(tempos)))
    plt.yticks([round(i * 0.005, 3) for i in range(int(max(tempos) / 0.005) + 1)])  # Eixo Y em incrementos de 0.005
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    graph = read_clq_file("clique_maximo_brock200_2.clq")
    
    tempos = []
    for _ in range(10):  # Realiza 10 execuções para coletar tempos
        tempo_execucao, _ = medir_tempo_execucao(graph)
        tempos.append(tempo_execucao)

    plotar_grafico(tempos)
