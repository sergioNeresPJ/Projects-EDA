#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
    unsigned V;
    unsigned A;
    int **adj;
}Grafo;

void inicializaGrafo(Grafo *G, unsigned vertices);
void destroiGrafo(Grafo *G);
void adicionaAresta(Grafo *G, unsigned a, unsigned b);

void bfs(Grafo *G, unsigned origem);