//gcc -o gulosoExato gulosoExato.c
//./gulosoExato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

struct grafo {
    int tamVertices;
    int *vetVisitado;  
    int **Matriz;      
} Grafo;

struct cliqueMax {
    int tamClique;
    int *vetClique;    
};

struct cliqueMax CliqueMax;

void pulaLinha() {
    printf("\n");
}

void imprimeMatriz() {
    printf("\n\n\t...Matriz de Adjacencia...\n\n");
    int i , j;
    printf("\tTotal de Vertices = %d\n\n", Grafo.tamVertices);
    printf("\t");
    for (i = 0; i <= Grafo.tamVertices; i++) {
        printf("%d\t", i);
    }
    pulaLinha(); pulaLinha();
    for (i = 0; i <= Grafo.tamVertices; i++) {
        printf("%d\t", i);
        for (j = 0; j <= Grafo.tamVertices; j++) {
            printf("%d\t", Grafo.Matriz[i][j]);
        }
        pulaLinha();
    }
    pulaLinha();
    printf("\nPress para sair..");
    getchar();
    pulaLinha();
    pulaLinha();
}

void limparGrafo() {
    int i, j;
    for (i = 0; i <= Grafo.tamVertices; i++) {
        Grafo.vetVisitado[i] = 0;
        for (j = 0; j <= Grafo.tamVertices; j++) {
            Grafo.Matriz[i][j] = 0;
        }
    }
}

void limpaClique() {
    int i;
    CliqueMax.tamClique = 0;
    for (i = 0; i <= Grafo.tamVertices; i++) {
        CliqueMax.vetClique[i] = -1;
    }
}

void lerArquivo() {
    FILE *f = fopen("FindMaxgen400_p0.9_55.txt", "r");
    if (f == NULL) {
        system("clear");
        printf("\n\n\tNao foi possivel acessar o arquivo...\n\n");
        exit(1);
    }
    printf("\n\n\t...Lendo Arquivo com Grafo...\n\n");
    char line[256];
    int totalVertices, totalEdges;
    char keyword[10];
    
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == 'p') {
            sscanf(line, "p %s %d %d", keyword, &totalVertices, &totalEdges);
            Grafo.tamVertices = totalVertices;

            // Alocar memória dinamicamente
            Grafo.vetVisitado = (int*) malloc((Grafo.tamVertices + 1) * sizeof(int));
            Grafo.Matriz = (int**) malloc((Grafo.tamVertices + 1) * sizeof(int*));
            for (int i = 0; i <= Grafo.tamVertices; i++) {
                Grafo.Matriz[i] = (int*) malloc((Grafo.tamVertices + 1) * sizeof(int));
            }

            CliqueMax.vetClique = (int*) malloc((Grafo.tamVertices + 1) * sizeof(int));
            limpaClique();
        } else if (line[0] == 'e') {
            int v, a;
            sscanf(line, "e %d %d", &v, &a);
            Grafo.Matriz[v][a] = 1;
            Grafo.Matriz[a][v] = 1;
        }
    }
    fclose(f);
}

void encontrarCliqueGuloso() {
    limpaClique();

    int i, j, vertice;
    int maiorAdj = 0;
    int adjacentes[Grafo.tamVertices + 1];

    // Escolher o vértice com o maior número de adjacentes (estratégia gulosa)
    for (vertice = 0; vertice <= Grafo.tamVertices; vertice++) {
        int contadorAdj = 0;
        for (i = 0; i <= Grafo.tamVertices; i++) {
            if (Grafo.Matriz[vertice][i] == 1) {
                contadorAdj++;
            }
        }
        if (contadorAdj > maiorAdj) {
            maiorAdj = contadorAdj;
            CliqueMax.vetClique[0] = vertice;  // O clique começa com este vértice
            CliqueMax.tamClique = 1;
        }
    }

    // Expandi o clique
    for (vertice = 0; vertice <= Grafo.tamVertices; vertice++) {
        if (vertice == CliqueMax.vetClique[0]) continue;
        int podeAdicionar = 1;

        for (i = 0; i < CliqueMax.tamClique; i++) {
            if (Grafo.Matriz[vertice][CliqueMax.vetClique[i]] != 1) {
                podeAdicionar = 0;
                break;
            }
        }

        if (podeAdicionar) {
            CliqueMax.vetClique[CliqueMax.tamClique] = vertice;
            CliqueMax.tamClique++;
        }
    }
}

void imprimeCliqueMax() {
    int i , j;
    printf("\n\n\t\t...Impressao das Arestas...\n\n");

    printf("\tClique maximo encontrado = %d.\n\n", CliqueMax.tamClique);

    for (i = 0; i < CliqueMax.tamClique; i++) {
        printf("\tVertice %d no clique.\n", CliqueMax.vetClique[i]);
    }

    for (i = 0; i < CliqueMax.tamClique - 1; i++) {
        for (j = i + 1; j < CliqueMax.tamClique; j++) {
            printf("\t\t%d <----> %d\n", CliqueMax.vetClique[i], CliqueMax.vetClique[j]);
        }
    }
}

int main() {
    lerArquivo();
    if (Grafo.tamVertices < 21)
        imprimeMatriz();
    else
        printf("\nNao vai imprimir tabela.. total de vertices > 20\n\n");

    clock_t ci , cf;
    ci = clock();  // clock inicial

    encontrarCliqueGuloso();

    cf = clock();  // clock final

    double tempoTotal = (double) (cf - ci) / CLOCKS_PER_SEC;

    imprimeCliqueMax();

    printf("\nTempo total Clique: %lf seg\n\n", tempoTotal);

    // Libere a memória alocada dinamicamente
    free(Grafo.vetVisitado);
    for (int i = 0; i <= Grafo.tamVertices; i++) {
        free(Grafo.Matriz[i]);
    }
    free(Grafo.Matriz);
    free(CliqueMax.vetClique);

    printf("Press enter..");
    getchar();

    return 0;
}
