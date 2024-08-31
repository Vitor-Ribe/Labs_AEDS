#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

No* novo_no(int valor){
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}
/** Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x){
    if(ap_arv == NULL){
        ap_arv = novo_no(x);
        return;
    }
    if(x < (*ap_arv)->valor){
        insere(&(*ap_arv)->esq, x);
        return;
    }
    if(x > (*ap_arv)->valor){
        insere(&(*ap_arv)->dir, x);
        return;
    }
}
/** Remove valor x da árvore de busca binária. Em caso de nó com dois filhos, deve-se trocar de posição com o antecessor do nó removido e o remover então.  */
bool remove_(Arvore* ap_arv, int x){

    if(ap_arv == NULL) return false;


    if(x == (*ap_arv)->valor){
        // caso o nó não tenha filhos
        if((*ap_arv)->dir == NULL && (*ap_arv)->esq == NULL){
            free((*ap_arv));
            return true;
        }
        // caso o nó tenha apenas 1 filho
        if((*ap_arv)->dir == NULL){
            No *filho = (*ap_arv);
            (*ap_arv) = (*ap_arv)->esq;
            free(filho);
            return true;
        }
        if((*ap_arv)->esq == NULL){
            No *filho = (*ap_arv);
            (*ap_arv) = (*ap_arv)->dir;
            free(filho);
            return true;
        }
        // caso o nó tenha 2 filhos
        if((*ap_arv)->dir != NULL && (*ap_arv)->esq != NULL){
            No* substituto = menorNo(&(*ap_arv)->dir);
            (*ap_arv)->valor = substituto->valor;
            return remove_(&(*ap_arv)->dir, substituto->valor);
        }
    }

    // movimentação
    if(x < (*ap_arv)->valor)
        return remove_(&(*ap_arv)->esq, x);
    if(x > (*ap_arv)->valor)
        return remove_(&(*ap_arv)->dir, x);
}
No* menorNo(No* ap_noDireito){
    No* atual = ap_noDireito;
    while(atual->esq != NULL){
        atual = atual->esq;
    }
    return atual;
}
/** Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x){
    if(arv == NULL) return false;
    if(arv->valor == x) return true;
    if(x < arv->valor)
        return busca(arv->esq, x);
    if(x > arv->valor)
        return busca(arv->dir, x);
}
/** Imprime a árvore de busca binária */
void imprime(Arvore arv){




}
