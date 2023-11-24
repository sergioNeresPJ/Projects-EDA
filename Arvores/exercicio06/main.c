#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct T
{
    char key[50];
    int tam;
} T;

typedef struct node
{
    T dado;
    struct node *direita, *esquerda;
} Node;

typedef struct abb
{
    Node *raiz;
} ABB;

Node *inserir_privado(Node *raiz, T dado)
{
    if (raiz == NULL)
    {
        Node *aux = (Node *)malloc(sizeof(Node));
        strcpy(aux->dado.key, dado.key);
        aux->dado.tam = dado.tam;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }
    else
    {
        if (dado.tam < raiz->dado.tam)
            raiz->esquerda = inserir_privado(raiz->esquerda, dado);
        else
            raiz->direita = inserir_privado(raiz->direita, dado);
        return raiz;
    }
}

void inserir(ABB *arvore, T dado)
{
    arvore->raiz = inserir_privado(arvore->raiz, dado);
}

Node *busca(Node *raiz, T dado)
{
    while (raiz)
    {
        if (dado.tam < raiz->dado.tam)
            raiz = raiz->esquerda;
        else if (dado.tam > raiz->dado.tam)
            raiz = raiz->direita;
        else if (strcmp(dado.key, raiz->dado.key) == 0)
            return raiz;
    }
    return NULL;
}

// função para remover nós da Árvore binária
Node *remove_privado(Node *raiz, T dado)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else
    { // procura o nó a remover
        if (strcmp(dado.key, raiz->dado.key) == 0)
        {
            // remove nós folhas (nós sem filhos)
            if (raiz->esquerda == NULL && raiz->direita == NULL)
            {
                free(raiz);
                return NULL;
            }
            else
            {
                // remover nós que possuem 2 filhos
                if (raiz->esquerda != NULL && raiz->direita != NULL)
                {
                    Node *aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    strcpy(raiz->dado.key, aux->dado.key);
                    raiz->dado.tam = aux->dado.tam;
                    strcpy(aux->dado.key, dado.key);
                    aux->dado.tam = dado.tam;
                    raiz->esquerda = remove_privado(raiz->esquerda, dado);
                    return raiz;
                }
                else
                {
                    // remover nós que possuem apenas 1 filho
                    Node *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
            }
        }
        else
        {
            if (dado.tam > raiz->dado.tam)
                raiz->direita = remove_privado(raiz->direita, dado);
            else
                raiz->esquerda = remove_privado(raiz->esquerda, dado);

            return raiz;
        }
    }
}

void remover(ABB *arvore, T dado)
{
    arvore->raiz = remove_privado(arvore->raiz, dado);
}

int main()
{
    ABB arvore;
    T dado;
    arvore.raiz = NULL;
    Node *node;
    char opcao, c[MAX];

    do
    {
        scanf("%c ", &opcao);
        switch (opcao)
        {
        case 'P':
            scanf("%s", &c);
            strcpy(dado.key, c);
            dado.tam = strlen(dado.key);
            inserir(&arvore, dado);
            break;
        case 'G':
            scanf("%s", &c);
            strcpy(dado.key, c);
            node = busca(arvore.raiz, dado);
            if (node != NULL)
                printf("%s encontrada\n", node->dado.key);
            else
                printf("%s nao foi encontrada\n", dado.key);
            break;
        case 'R':
            scanf("%s", &c);
            strcpy(dado.key, c);
            remover(&arvore, dado);
            break;
        }
    } while (opcao != EOF);

    return 0;
}