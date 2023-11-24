#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    unsigned dado;
    struct node *prox;
}Node;

typedef struct grafo{
    unsigned V;
    unsigned A;
    Node **adj;
}Grafo;

void inicializaGrafo(Grafo *G, unsigned vertices);
void destroiGrafo(Grafo *G);
void adicionaAresta(Grafo *G, unsigned a, unsigned b);

void dfs(Grafo *G);