#include <stdio.h>
#include <stdlib.h>

typedef struct data{
    int key;
}Data;

typedef struct node{
    Data dado;
    struct node *esquerdo, *direito;
    int altura;
}Node;

typedef struct arvore{
    Node *raiz;
}AVL;

Node* novo_no(int x){
    Node *novo = (Node*)malloc(sizeof(Node));

    if(novo){
        novo->dado.key = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    return novo;
}

int maior(int a, int b){
    return (a > b)? a: b;
}

int altura_do_no(Node *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int fator_de_balanceamento(Node *no){
    if(no)
        return (altura_do_no(no->esquerdo) - altura_do_no(no->direito));
    else
        return 0;
}

Node* rotacao_esquerda(Node *a){
    Node *b, *c;

    b = a->direito; // b aponta para a subárvore direita da raiz a
    c = b->esquerdo; // c aponta para o filho esquerdo de b

    b->esquerdo = a; // o filho esquerdo de b passa a ser a raiz a
    a->direito = c; // o filho direito de a passa a ser c

    // ajeita a altura dos nós que foram movimentados
    a->altura = maior(altura_do_no(a->esquerdo), altura_do_no(a->direito)) + 1;
    b->altura = maior(altura_do_no(b->esquerdo), altura_do_no(b->direito)) + 1;

    return b;//retorna a nova raiz
}


Node* rotacao_direita(Node *a){
    Node *b, *c;

    b = a->esquerdo;
    c = b->direito;

    b->direito = a;
    a->esquerdo = c;

    a->altura = maior(altura_do_no(a->esquerdo), altura_do_no(a->direito)) + 1;
    b->altura = maior(altura_do_no(b->esquerdo), altura_do_no(b->direito)) + 1;

    return b;
}



Node* rotacao_esquerda_direita(Node *raiz){
    raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
    return rotacao_direita(raiz);
}

Node* rotacao_direita_esquerda(Node *raiz){
    raiz->direito = rotacao_direita(raiz->direito);
    return rotacao_esquerda(raiz);
}

Node* balancear(Node *raiz){
    int fb = fator_de_balanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fator_de_balanceamento(raiz->direito) <= 0)
        raiz = rotacao_esquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fator_de_balanceamento(raiz->esquerdo) >= 0)
        raiz = rotacao_direita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fator_de_balanceamento(raiz->esquerdo) < 0)
        raiz = rotacao_esquerda_direita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fator_de_balanceamento(raiz->direito) > 0)
        raiz = rotacao_direita_esquerda(raiz);

    return raiz;
}

Node* inserir(Node *raiz, int x){
    if(raiz == NULL) //se a arvore estiver vazia, significa que achou a posição em que o node deve ser inserido
        return novo_no(x);
    else{ // define se a inserção será à esquerda ou à direita
        if(x < raiz->dado.key)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else
            raiz->direito = inserir(raiz->direito, x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(altura_do_no(raiz->esquerdo), altura_do_no(raiz->direito)) + 1;

    raiz = balancear(raiz);
    return raiz;//retorna a raiz nova da arvore ja balanceada
}

Node* remover(Node *raiz, int chave) {
    if(raiz == NULL){
        return NULL;
    } else { // procura o nó a remover
        if(raiz->dado.key == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    Node *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->dado.key = aux->dado.key;
                    aux->dado.key = chave;
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    Node *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->dado.key)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(altura_do_no(raiz->esquerdo), altura_do_no(raiz->direito)) + 1;

        raiz = balancear(raiz);
        return  raiz;
    }
}


void imprimir(Node *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->dado.key);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}


int main(){
    int P;
    scanf("%d",&P);

    int x;
    AVL garrafas;
    for(int i=0; i<P; i++){
        scanf("%d ",&x);
        inserir(&garrafas.raiz, x);
    }

    int E;
    AVL embalagens;
    scanf("%d", &E);
    for(int i=0; i<E; i++){
        scanf("%d ",&x);
        inserir(&embalagens.raiz, x);
    }

    imprimir(&garrafas.raiz, 1);
    imprimir(&embalagens.raiz, 1);
}