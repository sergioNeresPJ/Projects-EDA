#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct Lista NoLista, *Lista;
typedef struct Arvore NoArvore, *Arvore, **Floresta;

struct Arvore
{
    int data;
    int profundidade;
    Arvore pai;
    Lista filhos;
};

struct Lista
{
    Arvore arv;
    Lista prox, ant;
};

Floresta inicializaFloresta(int n);
void liberaFloresta(Floresta X, int n);
Arvore criaArvore(int chave);

void link(Arvore A, Arvore B);
void cut(Arvore A);
void lca(Arvore A, Arvore B);

void operacao(Floresta in);

void confereArvore(Arvore A, char *str);
Arvore raiz(NoArvore *p);

void operacao(Floresta in)
{
    int a, b;
    char op[MAX];
    scanf("%s", op);
    if (strcmp(op, "cut") == 0)
    {
        scanf("%d", &a);
        cut(in[a - 1]);
    }
    else if (strcmp(op, "link") == 0)
    {
        scanf("%d %d", &a, &b);
        link(in[a - 1], in[b - 1]);
    }
    else if (strcmp(op, "lca") == 0)
    {
        scanf("%d %d", &a, &b);
        lca(in[a - 1], in[b - 1]);
    }
}

Floresta inicializaFloresta(int n)
{
    int i;
    Floresta nova = (Floresta)malloc(n * sizeof(Arvore));
    for (i = 0; i < n; i++)
    {
        nova[i] = criaArvore(i + 1);
    }
    return nova;
}

void liberaFloresta(Floresta X, int n)
{
    int i;
    Lista p;
    for (i = 0; i < n; i++)
    {
        for (p = X[i]->filhos->prox; p->arv != NULL; p = p->prox)
        {
            free(p);
        }
        free(p);
        free(X[i]);
    }
    free(X);
}

Arvore criaArvore(int chave)
{
    Arvore nova = (Arvore)malloc(sizeof(NoArvore));
    nova->data = chave;
    nova->pai = NULL;
    nova->profundidade = 1;
    nova->filhos = (Lista)malloc(sizeof(NoLista));
    nova->filhos->prox = nova->filhos;
    nova->filhos->ant = nova->filhos;
    nova->filhos->arv = NULL;
    return nova;
}

void link(Arvore A, Arvore B)
{
    Lista novo;
    A->pai = B;
    novo = (Lista)malloc(sizeof(NoLista));
    novo->ant = B->filhos->ant;
    novo->prox = B->filhos;
    novo->arv = A;
    B->filhos->ant->prox = novo;
    B->filhos->ant = novo;
    A->profundidade = B->profundidade + 1;
    novo = (Lista)malloc(sizeof(NoLista));
    novo->ant = B->filhos->ant;
    novo->prox = B->filhos;
    novo->arv = A;
    B->filhos->ant->prox = novo;
    B->filhos->ant = novo;
}

void cut(Arvore A)
{
    Lista p;
    for (p = A->pai->filhos->prox; p->arv != NULL; p = p->prox)
    {
        if (p->arv == A)
        {
            p->ant->prox = p->prox;
            p->prox->ant = p->ant;
            free(p);
            A->pai = NULL;
            A->profundidade = 1;
            return;
        }
    }
}

void lca(Arvore A, Arvore B)
{
    Arvore auxA = A, auxB = B;

    if (B->profundidade > A->profundidade)
    {
        while (auxB->profundidade > auxA->profundidade)
        {
            auxB = auxB->pai;
        }
    }
    else if (A->profundidade > B->profundidade)
    {
        while (auxA->profundidade > auxB->profundidade)
        {
            auxA = auxA->pai;
        }
    }

    for (; auxA != NULL; auxA = auxA->pai, auxB = auxB->pai)
    {
        if (auxA == auxB)
        {
            printf("%d\n", auxA->data);
            return;
        }
    }
}

int main()
{
    int i, n, m;
    Floresta entrada;
    scanf("%d %d", &n, &m);
    entrada = inicializaFloresta(n);
    for (i = 0; i < m; i++)
    {
        operacao(entrada);
    }
    liberaFloresta(entrada, n);
    return 0;
}