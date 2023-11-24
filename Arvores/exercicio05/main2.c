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

typedef struct node
{
    T dado;
    unsigned int frequencia;
    struct node *dir, *esq, *prox;
} Node;

typedef struct arvore
{
    Node *raiz;
} Arvore;

typedef struct lista
{
    Node *inicio;
    int tam;
} Lista;

void cria_lista(Lista *l)
{
    l->inicio = NULL;
    l->tam = 0;
}

void inserir_lista(Lista *l, Node *no)
{
    Node *aux;
    if (!l->inicio)
    {
        l->inicio = no;
    }
    else if (no->frequencia < l->inicio->frequencia)
    {
        no->prox = l->inicio;
        l->inicio = no;
    }
    else
    {
        aux = l->inicio;
        while (aux->prox && aux->prox->frequencia <= no->frequencia)
            aux = aux->prox;
        no->prox = aux->prox;
        aux->prox = no;
    }
    l->tam++;
}

void preencher_lista(unsigned int tab[], Lista *l)
{
    for (int i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            Node *novo = (Node *)malloc(sizeof(Node));
            if (novo)
            {
                novo->dado.key = i;
                novo->frequencia = tab[i];
                novo->dir = novo->esq = novo->prox = NULL;
                inserir_lista(l, novo);
            }
        }
    }
}

Node *remove_inicio(Lista *l)
{
    Node *aux = NULL;
    if (l->inicio)
    {
        aux = l->inicio;
        l->inicio = aux->prox;
        aux->prox = NULL;
        l->tam--;
    }
    return aux;
}

Node *montar_arvore(Lista *l)
{
    Node *a, *b, *novo = (Node *)malloc(sizeof(Node));
    while (l->tam > 1)
    {
        a = remove_inicio(l);
        b = remove_inicio(l);
        if (novo)
        {
            novo->frequencia = a->frequencia + b->frequencia;
            novo->esq = a;
            novo->dir = b;
            novo->prox = NULL;
            inserir_lista(l, novo);
        }
    }
    return l->inicio;
}

void imprimir_arvore(Node *raiz, int tam)
{
    if (!raiz->esq && !raiz->dir)
    {
        printf("\tFolha: %c\tAltura: %d", raiz->dado.key, tam);
    }
    else
    {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

void imprimir_lista(Lista *l)
{
    Node *aux = l->inicio;
    printf("Lista ordenada: Tamanho: %d\n", l->tam);
    while (aux)
    {
        printf("\tCarater: %c Frequencia: %u\n", aux->dado.key, aux->frequencia);
        aux = aux->prox;
    }
}

int altura_arvore(Node *raiz)
{
    int esq, dir;
    if (!raiz)
        return -1;
    else
    {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if (esq > dir)
            return esq;
        else
            return dir;
    }
}

char** aloca_dicionario(int colunas)
{
    char **dicionario;

    dicionario = (char**)malloc(sizeof(char*)*TAM);

    for(int i=0; i<TAM; i++)
        dicionario = calloc(colunas, sizeof(char));

    return dicionario;
}

void gerar_dicionario(char **dicionario, Node *raiz, char *caminho, int colunas)
{
    char esquerda[], direita[];
    if(raiz->esq== NULL && raiz-> dir == NULL)
        strcpy(dicionario[raiz->dado.key], caminho);
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprime_dicionario(char **dicionario)
{
    for(int i=0; i <TAM; i++)
        printf("\t%3d: %s\n", i, dicionario[i]);
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
    Lista l;
    int colunas;
    char** dicionario;

    scanf("%[^EOF]", entrada);
    preenche_tab(entrada, tab);
    // imprime_tab(tab);

    cria_lista(&l);
    preencher_lista(tab, &l);
    // imprimir_lista(&l);

    Node *raiz;
    raiz = montar_arvore(&l);
    imprimir_arvore(raiz, 0);

    colunas = altura_arvore(raiz)+1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, raiz, "", colunas);
    imprime_dicionario(dicionario);

}