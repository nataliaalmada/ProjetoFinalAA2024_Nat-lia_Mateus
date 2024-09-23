#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar o grafo
struct grafo {
    int tamVertices;   // Número de vértices no grafo
    int **Matriz;      // Matriz de adjacência
} Grafo;

// Estrutura para armazenar o clique máximo aproximado
struct cliqueMax {
    int tamClique;     // Tamanho do clique máximo encontrado
    int *vetClique;    // Vértices que fazem parte do clique máximo
} CliqueMax;

// Função para alocar memória dinamicamente para a matriz de adjacência
void alocarMatriz() {
    // Alocar memória para a matriz de adjacência (linha por linha)
    Grafo.Matriz = (int**) malloc((Grafo.tamVertices + 1) * sizeof(int*)); // Alocar ponteiros para linhas
    if (Grafo.Matriz == NULL) {
        printf("Erro ao alocar memória para a matriz de adjacência\n");
        exit(1);
    }

    for (int i = 1; i <= Grafo.tamVertices; i++) {
        Grafo.Matriz[i] = (int*) malloc((Grafo.tamVertices + 1) * sizeof(int)); // Alocar colunas para cada linha
        if (Grafo.Matriz[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d da matriz\n", i);
            exit(1);
        }
        // Inicializar a matriz com 0 (sem aresta)
        for (int j = 1; j <= Grafo.tamVertices; j++) {
            Grafo.Matriz[i][j] = 0;
        }
    }

    // Alocar memória para o clique máximo
    CliqueMax.vetClique = (int*) malloc((Grafo.tamVertices + 1) * sizeof(int));
    if (CliqueMax.vetClique == NULL) {
        printf("Erro ao alocar memória para o clique máximo\n");
        exit(1);
    }
}

// Função para ler o arquivo DIMACS e construir o grafo
void lerArquivo(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Não foi possível acessar o arquivo\n");
        exit(1);
    }

    char line[256];
    int totalVertices, totalEdges;
    char keyword[10];

    // Ler o arquivo linha por linha
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == 'p') {
            // Linha que define o número de vértices e arestas
            sscanf(line, "p %s %d %d", keyword, &totalVertices, &totalEdges);
            Grafo.tamVertices = totalVertices;
            alocarMatriz();  // Alocar a matriz de adjacência
        } else if (line[0] == 'e') {
            // Linha que define uma aresta entre dois vértices
            int v, a;
            sscanf(line, "e %d %d", &v, &a);

            // Adicionar a aresta na matriz de adjacência, se os vértices forem válidos
            if (v <= Grafo.tamVertices && a <= Grafo.tamVertices) {
                Grafo.Matriz[v][a] = 1;
                Grafo.Matriz[a][v] = 1;  // Grafo não direcionado
            }
        }
    }
    fclose(f);
}

// Função para encontrar o clique máximo aproximado usando uma estratégia gulosa
void encontrarCliqueGuloso() {
    int maiorAdj = 0;
    int vertice;

    // Inicializa o clique com o vértice que tem o maior número de adjacências
    for (vertice = 1; vertice <= Grafo.tamVertices; vertice++) {
        int contadorAdj = 0;
        for (int i = 1; i <= Grafo.tamVertices; i++) {
            if (Grafo.Matriz[vertice][i] == 1) {
                contadorAdj++;
            }
        }
        if (contadorAdj > maiorAdj) {
            maiorAdj = contadorAdj;
            CliqueMax.vetClique[0] = vertice;  // O clique começa com esse vértice
            CliqueMax.tamClique = 1;
        }
    }

    // Expande o clique encontrando os vértices conectados ao clique atual
    for (vertice = 1; vertice <= Grafo.tamVertices; vertice++) {
        if (vertice == CliqueMax.vetClique[0]) continue;  // Não precisa verificar o vértice inicial
        int podeAdicionar = 1;

        // Verifica se o vértice é adjacente a todos os vértices do clique atual
        for (int i = 0; i < CliqueMax.tamClique; i++) {
            if (Grafo.Matriz[vertice][CliqueMax.vetClique[i]] != 1) {
                podeAdicionar = 0;
                break;
            }
        }

        // Se o vértice puder ser adicionado ao clique, adiciona
        if (podeAdicionar) {
            CliqueMax.vetClique[CliqueMax.tamClique] = vertice;
            CliqueMax.tamClique++;
        }
    }
}

// Função para imprimir o clique máximo e as arestas
void imprimeCliqueMax() {
    printf("\n\t\t...Impressão das Arestas...\n\n");

    // Imprimir o clique máximo encontrado
    printf("\tClique máximo encontrado = %d.\n\n", CliqueMax.tamClique);

    // Imprimir os vértices que estão no clique
    for (int i = 0; i < CliqueMax.tamClique; i++) {
        printf("\tVértice %d no clique.\n", CliqueMax.vetClique[i]);
    }

    // Imprimir as arestas entre os vértices no clique
    for (int i = 0; i < CliqueMax.tamClique - 1; i++) {
        for (int j = i + 1; j < CliqueMax.tamClique; j++) {
            printf("\t\t%d <----> %d\n", CliqueMax.vetClique[i], CliqueMax.vetClique[j]);
        }
    }
}

// Função principal
int main() {
    const char *arquivoDimacs = "relations.dimacs_500_test2.txt";  // Nome do arquivo gerado pelo script Python
    lerArquivo(arquivoDimacs);  // Lê o arquivo DIMACS e constrói o grafo

    clock_t start = clock();  // Medir tempo de execução
    encontrarCliqueGuloso();  // Encontra o clique máximo
    clock_t end = clock();  // Fim da medição de tempo

    // Imprimir o resultado
    imprimeCliqueMax();
    printf("\nTempo total Clique: %.6f seg\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Liberar memória alocada
    for (int i = 1; i <= Grafo.tamVertices; i++) {
        free(Grafo.Matriz[i]);
    }
    free(Grafo.Matriz);
    free(CliqueMax.vetClique);

    return 0;
}
