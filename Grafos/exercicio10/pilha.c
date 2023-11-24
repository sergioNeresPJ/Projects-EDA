#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void inicializaP(Pilha *p){
  p->tam=0;
  p->inicio=NULL;
}

void insereP(Pilha *p, int d){
  linkP novo = (linkP)malloc(sizeof(struct nodeP));
  novo->dado = d;
  
  if(vaziaP(p)==0){
    p->inicio = novo;
    novo->prox = NULL;
  }
  else{
    novo->prox = p->inicio;
    p->inicio = novo;
  }
  p->tam++;
}

void removeP(Pilha *p){
  linkP topo = p->inicio->prox;
  free(p->inicio);
  p->inicio = topo;
  p->tam--;
}

int primeiroP(Pilha *p){
  return p->inicio->dado;
}
int vaziaP(Pilha *p){
  return p->tam;
}