/* Sudhanshu Patel sudhanshuptl13@gmail.com */
/*
Min Heap implementation in c
*/
#include<stdio.h>
#include<stdlib.h>
/*
 Array Implementation of MinHeap data Structure
*/

#define HEAP_SIZE = 20;
struct Heap{
    int *arr;
    int count;
    int capacity;
    int heap_type; // for min heap , 1 for max heap
};

typedef struct Heap Heap;

Heap *CreateHeap(int capacity,int heap_type);
void insert(Heap *h, int key);
void print(Heap *h);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);
int PopMin(Heap *h);
int emptyHeap(Heap *h);