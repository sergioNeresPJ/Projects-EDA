#include<stdio.h>
#include<stdlib.h>
#include "heap.h"

Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return;
    }
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = capacity;
    h->arr = (int *) malloc(capacity*sizeof(int)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        return;
    }
    return h;
}

void insert(Heap *h, int key, int dis){
    nodeH novo = (nodeH)malloc(sizeof(struct nodeH));
    novo->dist = dis;
    novo->i = key;
    if( h->count < h->capacity){
        h->arr[h->count] = novo; 
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,int index){
    int tempD, tempI;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node]->dist > h->arr[index]->dist){
        //swap and recursive call
        tempD = h->arr[parent_node]->dist;
        tempI = h->arr[parent_node]->i;
        h->arr[parent_node]->dist = h->arr[index]->dist;
        h->arr[parent_node]->i = h->arr[index]->i;
        h->arr[index]->dist = tempD;
        h->arr[index]->i = tempI;
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    int tempI, tempD;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left]->dist < h->arr[parent_node]->dist)
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right]->dist < h->arr[min]->dist)
        min = right;

    if(min != parent_node){
        //swap and recursive call
        tempD = h->arr[parent_node]->dist;
        tempI = h->arr[parent_node]->i;
        h->arr[parent_node]->dist = h->arr[min]->dist;
        h->arr[parent_node]->i = h->arr[min]->i;
        h->arr[min]->dist = tempD;
        h->arr[min]->i = tempI;

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

int PopMin(Heap *h){
    int pop;
    nodeH aux = h->arr[0];
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return -1;
    }
    // replace first node by last and delete last
    pop = h->arr[0]->i;
    h->arr[0] = h->arr[h->count-1];
    free(aux);
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

void print(Heap *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %d ",h->arr[i]);
    }
    printf("->__/\\__\n");
}