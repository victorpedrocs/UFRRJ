/*

Objetivo:   Separar um grafo G=(V,E) com pesos nas arestas em K partições de vértices mais próximos.
            A separação é feita removendo as K-1 arestas com maior peso da Árvore Geradora Mínima(MST).
            O Algoritmo usado pra deteminar a MST foi o algoritmo de Prim.

*/

#include<stdio.h>
#include<stdlib.h>
#include "grafos.h"


int main(void){

    int i,k,s;
    // Usuário determina em quantos grupos o grafo será dividido.
    puts("Em quantos grupos o grafo será dividido?");
    scanf("%d",&k);

    // Aloca as estruturas usadas na execução e monta o grafo a partir do arquivo.
    int ordem;
    FILE* arquivo = fopen("arquivo.txt","r");
    fscanf(arquivo,"%d\n",&ordem);

    Lista** g = malloc(ordem*sizeof(Lista*));
    int** pesos = aloca_matriz(ordem);
    int* key = malloc(ordem*sizeof(int));
    int* pred = malloc(ordem*sizeof(int));
    char* cor = malloc(ordem*sizeof(char));
    Arestas* l = arestas_cria();

    monta_grafo(g,pesos,arquivo,ordem);

    puts("Qual o vértice inicial");
    scanf("%d",&s);

    //Determina a árvore geradora mínima.
    prim(g,pesos,ordem,pred,key,s);

    /*Transforma a árvore geradora mínima num novo grafo, representado
    pela lista de Arestas. */
    l = gera_arvore(ordem,key,pred,pesos);

    // Remoção das arestas da árvore geradora mínima.
    for(i = 0; i < k-1; i++)
         l = remove_aresta(l,pesos,i);

    /* Percorre a árvore geradora mínima já com as arestas removidas.
    Como após a remoção das cada grupo se torna uma componente conexa,
    a busca em profundidade já pode determinar quem são os grupos próximos. */
    busca_profundidade(l,ordem,cor);

    // Libera o espaço alocado pelas estruturas de memória.
    for(i = 0; i < ordem; i++){
        lista_libera(g[i]);
        free(pesos[i]);
    }

    free(key);
    free(pred);
    free(g);
    free(pesos);
    arestas_libera(l);
    return 0;
}
