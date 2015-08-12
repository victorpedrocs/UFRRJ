/*  Algoritmos para manipulação da listas encadeadas usadas no trabalho.
    Foram usadas duas listas, uma para a estrutura de adjacências que contém
    apenas o vértice(no), e outra para a lista de arestas que contém o vértice
    de origem e o vértice de destino. */

#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;
typedef struct arestas Arestas;

struct lista{
    int no;
    Lista* prox;
};

struct arestas{
    int origem;
    int destino;
    Arestas* prox;
};

//---------------------------------------

Lista* lista_cria(){
    return NULL;
}

Arestas* arestas_cria(){
    return NULL;
}

//---------------------------------------

int lista_vazia(Lista* l){
    return l == NULL;
}

int arestas_vazia(Arestas* l){
    return l == NULL;
}

//---------------------------------------

Lista* lista_insere(Lista* l, int n){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->no    = n;
    novo->prox  = l;
    return novo;
}

Arestas* arestas_insere(Arestas* l, int o, int d){
    Arestas* novo;
    Arestas* ant = NULL;
    Arestas* p = l;

    while(p != NULL && p->origem < o){
        ant = p;
        p= p->prox;
    }
    novo = (Arestas*)malloc(sizeof(Arestas));
    novo->origem    = o;
    novo->destino   = d;

    if(ant == NULL){
        novo->prox = l;
        l = novo;
    }else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    return l;
}

//----------------------------------------

void lista_imprime(Lista* l){
    Lista* p;
    for(p = l; p != NULL; p=p->prox){
        printf("%d ",p->no);
    }
    puts("---------");
}

void arestas_imprime(Arestas* l){
    Arestas* p;
    for(p = l; p != NULL; p =p->prox){
        printf("%d %d\n",p->origem,p->destino);
    }
    puts("---------");
}

//------------------------------------------

Lista* lista_remove(Lista* l, int x){
    Lista* ant = NULL;
    Lista* p = l;

    while(p != NULL && p->no != x){
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return l;

    if(ant == NULL)
        l = p->prox;
    else
        ant->prox = p->prox;

    free(p);
    return l;
}


Arestas* arestas_remove(Arestas* l, int o, int d){
    Arestas* ant = NULL;
    Arestas* p = l;

    while(p != NULL && p->origem != o && p->destino != d){
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return l;

    if(ant == NULL)
        l = p->prox;
    else
        ant->prox = p->prox;

    free(p);
    return l;
}

//------------------------------------------

void lista_libera(Lista* l){
    Lista* p = l;
    while(p!= NULL){
        Lista* t = p->prox;
        free(p);
        p = t;
    }
}

void arestas_libera(Arestas* l){
    Arestas* p = l;
    while(p != NULL){
        Arestas* t = p->prox;
        free(p);
        p = t;
    }
}
