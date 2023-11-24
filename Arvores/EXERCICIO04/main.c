#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int key;
} T;

typedef struct node
{
    struct node *esq, *dir;
    T data;
} Node;

typedef struct abb
{
    Node *raiz;
} ABB;

void inserir(ABB *arvore, T dados)
{
    arvore->raiz = inserir_privado(arvore->raiz, dados);
}

Node *inserir_privado(Node *p, T dados)
{
    if (!p)
    {
        Node *novo = (Node *)malloc(sizeof(Node));
        novo->data = dados;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    else if (dados.key < p->data.key)
    {
        p->esq = inserir_privado(p->esq, dados);
    }
    else if (dados.key > p->data.key)
    {
        p->dir = inserir_privado(p->dir, dados);
    }
    else
    {
        p->data = dados;
    }
    return p;
}

Node *busca(Node *p, T key)
{
    while (p)
    {
        if (key.key < p->data.key)
            p = p->esq;
        else if (key.key > p->data.key)
            p = p->dir;
        else
            return p;
    }
    return p;
}

void pre_ordem(Node *a)
{
    if (a)
    {
        printf("%d ", a->data.key);
        pre_ordem(a->esq);
        pre_ordem(a->dir);
    }
}

void pos_ordem(Node *a)
{
    if (a)
    {
        pos_ordem(a->esq);
        pos_ordem(a->dir);
        printf("%d ", a->data.key);
    }
}

void em_ordem(Node *a)
{
    if (a)
    {
        em_ordem(a->esq);
        printf("%d ", a->data.key);
        em_ordem(a->dir);
    }
}

void remover(ABB *arvore, T dado)
{
    arvore->raiz = remover_privado(arvore->raiz, dado);
}

Node* remover_privado(Node *raiz, T dado)
{
    if (!raiz)
        return NULL;
    else
    {
        if (raiz->data.key == dado.key)
        {
            if (!raiz->esq && !raiz->dir) //é um nó folha
            {
                free(raiz);
                return NULL;
            }
            else
            {
                if (raiz->esq && raiz->dir)
                { // possui dois filhos
                    Node *aux = raiz->esq;
                    while (aux->dir)
                        aux = aux->dir;
                    raiz->data = aux->data;
                    aux->data = dado;
                    raiz->esq = remover_privado(raiz->esq, dado);
                    return raiz;
                }
                else
                { // possui apenas um filho
                    Node *aux;
                    if (raiz->esq)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    return aux;
                }
            }
        }
        else
        {
            if (dado.key < raiz->data.key)
                raiz->esq = remover_privado(raiz->esq, dado);
            else
                raiz->dir = remover_privado(raiz->dir, dado);
            return raiz;
        }
    }
}

void main()
{

    ABB abb;
    abb.raiz = NULL;
    T dado;
    int N, x;
    scanf("%d",&N);

    for(int i=0; i<N; i++)
    {
        scanf("%d ",&x);
        dado.key=x;
        inserir(&abb, dado);
    }

    printf("Pr.: ");pre_ordem(abb.raiz);
    printf("\nIn.: ");em_ordem(abb.raiz);
    printf("Po.: ");pos_ordem(abb.raiz);
    return;
}