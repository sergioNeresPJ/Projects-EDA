#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 500000
#define TAM 256 // quantidade de valores da tabela ASCII

typedef struct t
{
    char key;
} T;

typedef struct nodeA
{
    T dado;
    unsigned int frequencia;
    struct nodeA *dir, *esq, *pai;
} NodeA;

typedef struct nodeF
{
    NodeA *nodeA;
    unsigned int index;
    struct nodeF *prox, *ant;
} NodeF;

typedef struct fila
{
    NodeF *inicio, *fim;
    unsigned int tamanho;
} Fila;

typedef struct arvore
{
    NodeA *raiz;
} Arvore;

void inicializa_fila(Fila *f)
{
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
}

void swap(NodeA *a, NodeA *b)
{
    NodeA *aux = (NodeA *)malloc(sizeof(NodeA));
    aux->dado = a->dado;
    aux->frequencia = a->frequencia;
    a->dado = b->dado;
    a->frequencia = b->frequencia;
    b->dado = aux->dado;
    b->frequencia = aux->frequencia;
    free(aux);
}

void fixUpFila(Fila *f, NodeA *n)
{
    // Caso base consiste em: o pai do elemento eh diferente de nulo.
    if (n->pai != NULL)
    {
        if (n->frequencia > n->pai->frequencia)
        {
            // Feito a troca de node e chamado o fixUp novamente, mas com o pai do elemento.
            swap(n, n->pai);
            fixUpFila(f, n->pai);
        }
    }
}

void inserirFila(Fila *f, T dado)
{

    NodeF *novo = (NodeF *)malloc(sizeof(NodeF));
    novo->nodeA = (NodeA *)malloc(sizeof(NodeA));
    novo->nodeA->dado = dado;

    /* Como a insercao na fila eh feita no final e o fixUp corrige possiveis alteracoes necessarias, os filhos sao nulos
    e o proximo tambem.*/
    novo->nodeA->dir = NULL;
    novo->nodeA->esq = NULL;
    novo->prox = NULL;

    if (novo)
    {
        if(f->tamanho==0) f->inicio = novo;
        novo->ant = f->fim;
        f->tamanho++;
        f->fim->prox = novo;
        f->fim = novo;
        novo->index = f->tamanho;

        NodeF *aux = f->inicio;
        // Encontra pai pela relacao pai-filho. Enquanto ’i’ for diferente do index do pai, o auxiliar percorre a fila, ate que o pai seja encontrado. Ao fim, o pai do novo elemento recebe o auxiliar. Esse auxiliar nao precisara ser desalocado pois ele nao foi alocado dinamicamente. int i = 1;
        for (int i=1; i != (novo->index / 2); i++) aux = aux->prox;
        novo->nodeA->pai = aux->nodeA;
        // Atualizando o indice filho do pai do elemento recebido. Se o index do novo elemento for exatamente a multiplicacao do index do pai por 2, sera o filho da esquerda, se nao, sera o filho da direita.
        if (aux->index * 2 == novo->index) novo->nodeA->pai->esq = novo->nodeA;
        else novo->nodeA->pai->dir = novo->nodeA;
        // Feito o fixUp para atualizar a prioridade da fila
        fixUpFila(f, novo->nodeA);
    }
}

void imprime_fila(Fila *f)
{
    NodeF *aux = f->inicio;
    while(aux)
    {
        printf("%c\n", aux->nodeA->dado.key);
        aux =aux->prox;
    }
}

/*CODIGOS REFERENTES A TABELA DE FREQUENCIA DOS CARACTERES DA STRING DE ENTRADA*/

void inicializa_tab_zero(unsigned int tab[])
{
    for (int i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preenche_tab(char entrada[], unsigned int tab[])
{
    inicializa_tab_zero(tab);
    for (int i = 0; entrada[i] != '\0'; i++)
        tab[entrada[i]]++;
    /*O valor do caratere respectivo a tabela ASCiI é o indice do vetor. Se há um 'a' na string de entrada,
    o valor respectivo do 'a' na tabela ASCiI é 97, portanto, a posiçao 97 no vetor tab receberá um incremento de 1 unidade
    indicando que houve uma aparição deste caratere na string de entrada*/
}

void imprime_tab(unsigned int tab[])
{
    for (int i = 0; i < TAM; i++)
        if (tab[i] > 0)
            printf("\t%d = %d = %c\n", i, tab[i], i);
}

int main()
{
    // tabela de frequencia
    unsigned int tab[TAM];
    char entrada[MAX];
    scanf("%[^EOF]", entrada);
    preenche_tab(entrada, tab);
    imprime_tab(tab);


    Fila f;
    T c;
    for(int i=0; i < strlen(entrada); i++){
        c.key=entrada[i];
        inserirFila(&f, c);
    }

    imprime_fila(&f);
    
}
