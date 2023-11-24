#include <stdio.h>
#include <stdlib.h>

typedef struct nodeF{
    unsigned dado;
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
void inserirFila(Fila *f, unsigned dado);
void removerFila(Fila *f);

unsigned primeiroFila(Fila *f);
int vaziaFila(Fila *f);