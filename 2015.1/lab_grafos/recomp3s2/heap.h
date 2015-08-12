/*  Algoritmos para manipulação da fila de prioridades. A estrutura
    no_heap foi usada para que a fila de prioridades fosse ordenada
    pelo peso d dos vértices. A Fila de prioridades foi implementada
    usando vetores. */

#include <stdio.h>
#include <stdlib.h>

typedef struct no_heap NoHeap;

struct no_heap{
    int no;
    int d;
};

int filho_esquerda(int i){
    return (i<<1)+1;
}

int filho_direita(int i){
    return (i<<1)+2;
}

void heapify(NoHeap* v,int hsize,int i){
    int l = filho_esquerda(i);
    int r = filho_direita(i);
    int maior;

    if( l < hsize && v[l].d < v[i].d)
        maior = l;
    else
        maior = i;

    if(r < hsize && v[r].d < v[maior].d)
        maior = r;

    if(maior != i){
        NoHeap temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;
        heapify(v,hsize,maior);
    }
}

void monta_heap(NoHeap* v,int hsize){
    int i,j;
    for(i = (hsize)/2;i >= 0; i--){
        heapify(v,hsize,i);
    }
}

int remove_heap(NoHeap* v,int* hsize){
    NoHeap raiz = v[0];
    v[0] = v[*hsize-1];
    *hsize = *hsize-1;
    heapify(v,*hsize,0);
    return raiz.no;
}

int contem_heap(NoHeap* v, int hsize, int elem){
    int i;
    for(i = 0; i < hsize; i++){
        if(v[i].no == elem)
            return 1;
    }
    return 0;
}

void imprime_heap(NoHeap* v,int hsize){
    int i;
    for(i = 0; i < hsize; i++)
        printf("%d %d /",v[i].no,v[i].d);
    puts("");
}
