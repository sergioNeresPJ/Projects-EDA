#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void) {
  
    Grafo exemplo;

    inicializaGrafo(&exemplo, 6);
    adicionaAresta(&exemplo, 0, 2);
    adicionaAresta(&exemplo, 0, 3);
    adicionaAresta(&exemplo, 0, 5);
    adicionaAresta(&exemplo, 1, 0);
    adicionaAresta(&exemplo, 2, 1);
    adicionaAresta(&exemplo, 2, 4);
    adicionaAresta(&exemplo, 4, 1);
    adicionaAresta(&exemplo, 4, 3);
    buscaLargura(&exemplo);
    destroiGrafo(&exemplo);
    
    return 0;
}