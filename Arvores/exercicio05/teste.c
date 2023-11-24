#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM 256
#define MAX 50000

typedef struct dado
{
    unsigned char key;
} Dado;

typedef struct no
{
    Dado dado;
    int frequencia;
    struct no *esq, *dir, *proximo;
} No;

typedef struct
{
    No *inicio;
    int tam;
} Lista;

//----------- tabela de frequência ----------------------
void inicializa_tabela_com_zero(unsigned int tab[])
{
    int i;
    for (i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[])
{
    int i = 0;

    while (texto[i] != '\0')
    {
        tab[texto[i]]++;
        i++;
    }
    /*O valor do caratere respectivo a tabela ASCiI é o indice do vetor. Se há um 'a' na string de entrada,
      o valor respectivo do 'a' na tabela ASCiI é 97, portanto, a posiçao 97 no vetor tab receberá um incremento de 1 unidade
      indicando que houve uma aparição deste caratere na string de entrada*/
}

//----------- Lista Encadeada Ordenada ----------------------

void criar_lista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no)
{
    No *aux;
    // a lista está vazia?
    if (lista->inicio == NULL)
    {
        lista->inicio = no;
    }
    // tem frequência menor que o início da lista
    else if (no->frequencia < lista->inicio->frequencia)
    {
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else
    {
        aux = lista->inicio;
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista)
{
    int i;
    No *novo;
    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            novo = malloc(sizeof(No));
            if (novo)
            {
                novo->dado.key = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            }
        }
    }
}
//------------- Montar a Árvore de Huffman ----------------------

No *remove_no_inicio(Lista *l)
{
    No *aux = NULL;

    if (l->inicio)
    {
        aux = l->inicio;
        l->inicio = aux->proximo;
        aux->proximo = NULL;
        l->tam--;
    }

    return aux;
}

No *montar_arvore(Lista *l)
{
    No *primeiro, *segundo, *novo;
    while (l->tam > 1)
    {
        primeiro = remove_no_inicio(l);
        segundo = remove_no_inicio(l);
        novo = malloc(sizeof(No));

        if (novo)
        {
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(l, novo);
        }
    }
    return l->inicio;
}

//-------------- Montar o dicionário ---------------------

int altura_arvore(No *raiz)
{
    int esq, dir;

    if (raiz == NULL)
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

char **aloca_dicionario(int colunas)
{
    char **dicionario;
    int i;

    dicionario = malloc(sizeof(char *) * TAM);

    for (i = 0; i < TAM; i++)
        dicionario[i] = calloc(colunas, sizeof(char));

    return dicionario;
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas)
{
    char esquerda[colunas], direita[colunas];

    if (raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->dado.key], caminho);
    else
    {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

//-------------- Codificar em bits----------------------------

int calcula_tamanho_string(char **dicionario, unsigned char *texto)
{
    int i = 0, tam = 0;
    while (texto[i] != '\0')
    {
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }
    return tam + 1;
}

char *codificar(char **dicionario, unsigned char *texto)
{

    int i = 0, tam = calcula_tamanho_string(dicionario, texto);
    char *codigo = calloc(tam, sizeof(char));

    while (texto[i] != '\0')
    {
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    return codigo;
}

int main()
{

    unsigned char texto[MAX];
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas, bits;
    char **dicionario;
    char *codificado;
    scanf("%[^EOF]", texto);

    //----------- tabela de frequência ---------------
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(texto, tabela_frequencia);

    //----------- Lista Encadeada Ordenada -----------
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);

    //----------- Montar a Árvore de Huffman ---------
    arvore = montar_arvore(&lista);

    //----------- Montar o dicionário ----------------
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);

    //----------- Codificar em bits---------------------------
    codificado = codificar(dicionario, texto);
    bits = strlen(codificado);
    printf("%d\n", bits);

    return 0;
}