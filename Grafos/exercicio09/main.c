#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void) {
  
    Grafo grafo;
    unsigned v, w;

    scanf("%u", &v);
    inicializaGrafo(&grafo, v);
    do{
      scanf("%u, %u",&v, &w);
      if((v!=0)&&(w!=0)) adicionaAresta(&grafo, v-1, w-1);
    }while((v!=0)&&(w!=0));
    scanf("%u", &v);
    bfs(&grafo, v);
    destroiGrafo(&grafo);
    
    return 0;
}