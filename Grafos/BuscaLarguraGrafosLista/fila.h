#include <stdio.h>
#include <stdlib.h>

typedef struct nodeF{
    int dado;
    struct nodeF *prox;
}NodeF;

typedef  struct fila
{
    int tam;
    NodeF *inicio;
    NodeF *fim;
}Fila;

void inicializaFila(Fila *f);
void destroiFila(Fila *f);
void inserirFila(Fila *f, int dado);
void removerFila(Fila *f);

int primeiroFila(Fila *f);
int vaziaFila(Fila *f);