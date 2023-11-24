#include <stdio.h>
#include <stdlib.h>

typedef struct nodeP *linkP;

struct nodeP{
    int dado;
    struct nodeP *prox;
};

typedef struct{
    unsigned tam;
    linkP inicio;
}Pilha;

void inicializaP(Pilha *p);
void insereP(Pilha *p, int d);
void removeP(Pilha *p);
int primeiroP(Pilha *p);
int vaziaP(Pilha *p);