#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

void inicializaGrafo(Grafo *G, unsigned vertices){
    G->A=0;
    G->V=vertices;
    G->adj = (Node**)malloc(sizeof(Node*)*G->V);
    for(int i=0; i<G->V;i++){
        G->adj[i] = NULL;
    }
}

void destroiGrafo(Grafo *G){
    for(int i=0; i<G->V;i++){
        while(G->adj[i]){
            Node *aux = G->adj[i];
            G->adj[i] = G->adj[i]->prox;
            free(aux);
        }
    }
    free(G->adj);
    G->A = G->V = 0;
}

void adicionaAresta(Grafo *G, unsigned a, unsigned b){
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->dado = b;
    novo->prox = G->adj[a];
    G->adj[a] = novo;
    G->A++;
}

void buscaLargura(Grafo *G){
    int vis[G->V];

    for(int i=0; i<G->V;i++){
        vis[i]=0;
    }

    Fila f;
    inicializaFila(&f);
    inserirFila(&f, 0);
    vis[0]=1;

    while(vaziaFila(&f)!=0){
        int v = primeiroFila(&f);
        removerFila(&f);

        printf("%d ", v);

        for(Node *aux = G->adj[v]; aux!=NULL; aux=aux->prox){
            if(vis[aux->dado]==0){
                vis[aux->dado]=1;
                inserirFila(&f, aux->dado);
            }
        }
    }
    
}