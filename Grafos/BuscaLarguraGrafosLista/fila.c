#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


void inicializaFila(Fila *f){
    f->tam = 0;
    f->inicio = NULL;
  f->fim = NULL;
}

void destroiFila(Fila *f)
{
    for (int i = 0; i < f->tam; i++)
      removerFila(f);
    f->tam = 0;
}

void inserirFila(Fila *f, int dado)
{
    NodeF *novo = (NodeF *)malloc(sizeof(NodeF));
  
    novo->dado = dado;
    novo->prox = NULL;
  
    if(vaziaFila(f)==0){
      f->inicio = f->fim = novo;
    }else{
      f->fim->prox = novo;
      f->fim = novo;
    }
    f->tam++;
}

void removerFila(Fila *f)
{
    NodeF *aux = f->inicio;
    if (vaziaFila(f)!=0)
    {
      f->inicio = aux->prox;
      free(aux);
      f->tam--;
    }
}

int primeiroFila(Fila *f)
{
  return f->inicio->dado;
}

int vaziaFila(Fila *f)
{
    if (f->tam == 0)
        return 0;
    else
        return 1;
}