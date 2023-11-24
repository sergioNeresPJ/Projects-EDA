#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int key;
} T;

typedef struct node
{
    struct node *esq, *dir, *prox;
    T data;
} Node;

typedef struct abb
{
    Node *raiz;
} ABB;

typedef struct fila
{
  Node *inicio;
}Fila;

void inserir_fila(Fila *f, Node *a)
{
  Node *aux = f->inicio;

  if(aux){
    while(aux->prox)
      aux=aux->prox;
    aux->prox = a;
  }
  else
    f->inicio = a;
}

int remover_fila(Fila *f)
{
  Node *aux = f->inicio;
  f->inicio = aux->prox;
  return aux->data.key;
}

void em_nivel(Fila *f, Node *p)
{
  Node *aux = p;
  inserir_fila(f, aux);
  while(aux){//enquanto existir alguem na fila
    if(aux->esq)
      inserir_fila(f, aux->esq);
    if(aux->dir)
      inserir_fila(f, aux->dir);
    printf(" %d", remover_fila(f));
    aux=aux->prox;
  }
}

Node* inserir_privado(Node *p, T dados);
void inserir(ABB *arvore, T dados)
{
    arvore->raiz = inserir_privado(arvore->raiz, dados);
}

Node* inserir_privado(Node *p, T dados)
{
    if (!p)
    {
        Node *novo = (Node *)malloc(sizeof(Node));
        novo->prox=NULL;
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
        printf(" %d", a->data.key);
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
        printf(" %d", a->data.key);
    }
}

void em_ordem(Node *a)
{
    if (a)
    {
        em_ordem(a->esq);
        printf(" %d", a->data.key);
        em_ordem(a->dir);
    }
}

void inicializa_arvore(ABB *a)
{
  a->raiz=NULL;
}



int main()
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
  Fila f;f.inicio=NULL;
    printf("Pr.:");pre_ordem(abb.raiz);
    printf("\nIn.:");em_ordem(abb.raiz);
    printf("\nPo.:");pos_ordem(abb.raiz);
  printf("\nNi.:");em_nivel(&f,abb.raiz);
    return 0;
}