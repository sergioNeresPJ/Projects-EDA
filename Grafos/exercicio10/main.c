#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){

    Grafo exemplo;
    int n, m, a, b;
    scanf("%d %d", &n, &m);
    inicializaGrafo(&exemplo, n);
    for(int i=0; i<m; i++){
      scanf("%d %d", &a, &b); 
      adicionaAresta(&exemplo, b, a); 
    }
    dfs(&exemplo);
    destroiGrafo(&exemplo);
    
    return 0;
}