#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"
#include "fila.h"

void inicializaGrafo(Grafo *G, unsigned vertices)
{
    G->A = 0;
    G->V = vertices;
    G->adj = (int **)malloc(sizeof(int *) * G->V);
    for (int i = 0; i < G->V; i++)
    {
        G->adj[i] = (int *)malloc(sizeof(int) * G->V);
    }
}

void destroiGrafo(Grafo *G)
{
    for (int i = 0; i < G->V; i++)
    {
        free(G->adj[i]);
    }
    free(G->adj);
    G->A = G->V = 0;
}

void adicionaAresta(Grafo *G, unsigned a, unsigned b)
{
    if (G->adj[a][b] == 0)
    {
        G->adj[a][b] == 1;
        G->A++;
    }
}

void bfs(Grafo *G, unsigned origem)
{
    unsigned vis[G->V];
    unsigned vetor[G->V];
    unsigned vizinhos=0;

    for (unsigned v = 0; v < G->V; v++){
        vis[v] = 0;
        vetor[v] = 0;
    }

    Fila f;
    inicializaFila(&f);

    insereFila(&f, (origem-1));
    vis[origem-1] = 1;

    int dist = 0;

    for (int i=0; vaziaFila(&f)!=0; i++)
    {
        
        unsigned v = primeiroFila(&f);
        removerFila(&f);

        printf("%u %u\n", v, dist);

        if(vetor[dist]==i){
            vetor[dist]=vizinhos;
            dist++;
            vizinhos=0;
        }

        for (unsigned w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1)
                if (vis[w] == 0)
                {
                    vis[w] = 1;
                    insereF(&f, w);
                    vizinhos++;
                }

        
    }
}