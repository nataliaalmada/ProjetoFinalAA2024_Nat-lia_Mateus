import networkx as nx
import matplotlib.pyplot as plt

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

def highlight_clique_edges(graph):
    max_clique = max(nx.find_cliques(graph), key=len)
    return [(u, v) for u in max_clique for v in max_clique if u < v and graph.has_edge(u, v)]

def plot_graph(graph):
    pos = nx.spring_layout(graph)
    max_clique_edges = highlight_clique_edges(graph)
    
    plt.figure(figsize=(10, 7))
    nx.draw(graph, pos, with_labels=True, node_size=500, node_color="lightblue", font_size=10, edge_color="black")
    
    if max_clique_edges:
        
        nx.draw_networkx_edges(graph, pos, edgelist=max_clique_edges, edge_color="green", width=1, label="Clique Máximo")
    
    plt.legend()
    plt.show()

graph = read_clq_file("clique_maximo_gen400_p0-9_55.clq")
plot_graph(graph)
