#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "pilha.h"

int t;

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

void dfs_private(int *flag, Pilha *p, Grafo *G,int vis[], int i){
  vis[i]=1;
  for(Node *aux = G->adj[i]; aux!=NULL; aux=aux->prox){
    if(vis[aux->dado]==0){
      vis[aux->dado]=1;
      dfs_private(flag, p, G,vis,  aux->dado);
    }
    else 
      *flag=1;
  }
  insereP(p, i);
}


void dfs(Grafo *G){
  int flag=0;
  Pilha p;
  inicializaP(&p);
  int vis[G->V];
  for(int i=0; i<G->V; i++) vis[i]=0;

  for(int i=0; i<G->V; i++)
     if(vis[i]==0)
       dfs_private(&flag, &p, G, vis, i);

  if(flag==0)
    for(int i=0; i<G->V; i++){
      printf("%d\n", primeiroP(&p));
      removeP(&p);
    }
  else
    printf("*");
}