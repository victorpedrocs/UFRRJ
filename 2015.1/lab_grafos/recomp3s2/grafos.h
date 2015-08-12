/*  Algoritmos para manipulação dos grafos.
    Os algoritmos usados nesse trabalho foram a
    busca em profundidade e  o Algoritmo de Prim. */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "lista.h"

void visita(Arestas* l, int u, char* cor){
    cor[u] = 'c';
    printf("%d ",u);
    Arestas* p;
    for(p = l;p != NULL;p = p->prox){
        if (p->origem == u){
            if(cor[p->destino] == 'b'){
                visita(l,p->destino,cor);
            }
        }
    }
    cor[u] = 'p';
}

int busca_profundidade(Arestas* l,int ordem, char* cor){
    int i = 0;
    int k = 0;
    Arestas* p;

    for(i = 0; i < ordem; i++){
        cor[i] = 'b';
    }

    for(i = 0; i < ordem; i++){
        if( cor[i] == 'b'){
            printf("grupo %d: ",++k);
            visita(l,i,cor);
            puts("");
        }
    }
    return k;
}

void prim(Lista** g, int** pesos, int ordem, int* pred, int* key, int s){
    int i, u;
    Lista* p;
    int hsize = ordem;
    NoHeap* heap = malloc(ordem*sizeof(NoHeap));
    for(i = 0; i < ordem; i ++){
        key[i] = 123456;
        pred[i] = -1;
        heap[i].no = i;
        heap[i].d = key[i];
    }

    key[s] = 0;
    heap[s].no = s;
    heap[s].d = key[s];
    monta_heap(heap,hsize);

    while(hsize > 0){
        u = heap[0].no;
        for(p = g[u]; p!= NULL; p = p->prox){
            if(contem_heap(heap,hsize,p->no) && pesos[u][p->no] < key[p->no]){
                pred[p->no] = u;
                heap[p->no].d = pesos[u][p->no];
                key[p->no] = pesos[u][p->no];
            }
        }
        remove_heap(heap,&hsize);
    }
}
/*  Utiliza as informações obtidas no algoritmo de prim(key e pred)
    para representar a arvore geradora minima como uma lista de arestas. */
Arestas* gera_arvore(int ordem,int* key,int* pred, int** pesos){
    Arestas* arvore = arestas_cria();
    int i;
    for(i = 0; i < ordem; i++){
        if(pred[i] >= 0){
            arvore = arestas_insere(arvore, pred[i],i);
        }
    }
    return arvore;
}

/*  Encontra a aresta com maior peso e a remove da MST. */
Arestas* remove_aresta(Arestas* l, int** pesos, int i){
    Arestas* p;
    int o = 0, d = 0;
    int maior = -123456;

    for(p = l; p != NULL; p = p->prox){
        if(pesos[p->origem][p->destino] > maior){
            o = p->origem;
            d = p->destino;
            maior = pesos[p->origem][p->destino];
        }
    }
    l = arestas_remove(l,o,d);
    return l;
}

//----------------------------------------------------------------

int** aloca_matriz(int n){
    int** m = calloc(n,sizeof(int));
    int i;

    for(i = 0;i < n; i++)
        m[i] = calloc(n,sizeof(int));

    return m;
}

void monta_grafo(Lista** g, int** matriz, FILE* arquivo, int ordem){
    int i = 0;
    int vertice1, vertice2,valorPeso;

    for(i = 0; i < ordem;i++){
        g[i] = lista_cria();
    }

    while(!feof(arquivo)){
        fscanf(arquivo,"%d %d %d\n",&vertice1,&vertice2,&valorPeso);
        matriz[vertice1][vertice2] = valorPeso;
        g[vertice1] = lista_insere(g[vertice1],vertice2);
    }

    fclose(arquivo);
}
