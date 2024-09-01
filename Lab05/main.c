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
/* Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x){
    if(*ap_arv == NULL){
        (*ap_arv) = novo_no(x);
        return true;
    }
    if(x < (*ap_arv)->valor)
        return insere(&(*ap_arv)->esq, x);
    if(x > (*ap_arv)->valor)
        return insere(&(*ap_arv)->dir, x);
    return false;
}
No* maiorNo(Arvore* ap_noEsquerdo){
    No* maior = (*ap_noEsquerdo);
    while(maior->dir != NULL){
        maior = maior->dir;
    }
    return maior;
}
/* Remove valor x da árvore de busca binária. Em caso de nó com dois filhos, deve-se trocar de posição com o antecessor do nó removido e o remover então.  */
bool remove_(Arvore* ap_arv, int x){
    if(*ap_arv == NULL) return false;
    if(x == (*ap_arv)->valor){

        if((*ap_arv)->dir == NULL && (*ap_arv)->esq == NULL){
            free((*ap_arv));
            (*ap_arv) = NULL;
            return true;
        }

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

        if((*ap_arv)->dir != NULL && (*ap_arv)->esq != NULL){
            No* substituto = maiorNo(&(*ap_arv)->esq);
            (*ap_arv)->valor = substituto->valor;
            return remove_(&(*ap_arv)->esq, substituto->valor);
        }
    }

    if(x < (*ap_arv)->valor)
        return remove_(&(*ap_arv)->esq, x);
    if(x > (*ap_arv)->valor)
        return remove_(&(*ap_arv)->dir, x);

    return false;
}
/* Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x){
    if(arv == NULL) return false;
    if(arv->valor == x) return true;
    if(x < arv->valor) return busca(arv->esq, x);
    if(x > arv->valor) return busca(arv->dir, x);
    return false;
}
/*  Imprime a árvore de busca binária */
void auxImpressao(Arvore arv){
    if(arv){
        printf("[%d:e=", arv->valor);
        // Imprime filho esquerdo
        if(arv->esq)
            auxImpressao(arv->esq);
        else
            printf(".");

        printf(",d=");
        // Imprime filho direito
        if(arv->dir)
            auxImpressao(arv->dir);
        else
            printf(".");
        printf("]");
    }
}
void imprime(Arvore arv){
    if(arv){
        auxImpressao(arv);
        printf("\n");
    }else
        printf(".\n");
}
