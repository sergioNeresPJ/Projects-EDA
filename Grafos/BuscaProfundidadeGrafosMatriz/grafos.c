#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

void inicializaGrafo(Grafo *G, unsigned vertices){
    G->A=0;
    G->V=vertices;
    G->adj = (int**)malloc(sizeof(int*)*G->V);
    for(int i=0; i<G->V;i++){
        G->adj[i] = (int*)malloc(sizeof(int)*G->V);
    }
}

void destroiGrafo(Grafo *G){
    for(int i=0; i<G->V;i++){
        free(G->adj[i]);
    }
    free(G->adj);
    G->A = G->V = 0;
}

void adicionaAresta(Grafo *G, unsigned a, unsigned b){
    if(G->adj[a][b]==0){
        G->adj[a][b]==1;
        G->A++;
    }
}

void buscaPPrivada(Grafo *G, int vis[], int i){
    vis[i] = 1;

    printf("%u ", i);

    for(int j=0; j<G->V;j++){
        if(G->adj[i][j]==1 && vis[j]==0)
            buscaPPrivada(G, vis, j);
    }
}

void buscaP(Grafo *G){
    int vis[G->V];

    for(int i=0; i<G->V;i++){
        vis[i]=0;
    }
    for(int i=0; i<G->V;i++){
        if(vis[i]==0)
            buscaPPrivada(G, &vis, i);
    }
}