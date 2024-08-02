#include <stdio.h>
#include <stdlib.h>
#include "polinomio.h"


/* Inicializa um polinômio vazio. */
void inicializa_polinomio(Polinomio * ap_pol){
    *ap_pol = (No*)malloc(sizeof(No));
    if(*ap_pol != NULL){
        (*ap_pol)->antec = *ap_pol;
        (*ap_pol)->prox = *ap_pol;
    }else
        printf("\nErro ao alocar memoria!\n");
}

/* Define que o coeficiente de grau grau do polinomio pol eh igual a coef. Deve manter os
 * coeficientes ordenados por grau. */
void define_coeficiente(Polinomio pol, int grau, int coef) {
    if(coef == 0){
        return;
    }

    No *novo = (No*)malloc(sizeof(No));
    if(novo){
        novo->valor.coef = coef;
        novo->valor.grau = grau;

        // Caso a lista esteja vazia
        if(pol->prox == pol){
            pol->prox = novo;
            pol->antec = novo;
            novo->prox = pol;
            novo->antec = pol;

        }else{
            No *atual = pol->prox;
            while(atual != pol && atual->valor.grau < grau) {
                atual = atual->prox;
            }

            // Inserir o novo nó antes do nó atual
            novo->prox = atual;
            novo->antec = atual->antec;
            atual->antec->prox = novo;
            atual->antec = novo;
        }
    } else {
        printf("\nErro ao alocar memoria!\n");
    }
}


/* Zera o polinomio, tornando-o um polinomio inicializado, mas igual a zero. Desaloca a memória liberada. */
void zera(Polinomio pol){
    No *atual = pol->prox, *aux;
    while(atual != pol){
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    pol->antec = pol;
    pol->prox = pol;
}

/* Computa a soma dos polinomios a e b colocando o resultado em res.
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void soma(Polinomio res, Polinomio a, Polinomio b){
    No *pont1 = a->prox, *pont2 = b->prox;
    zera(res);

    while(pont1 != a || pont2 != b){
        if(pont1 == a && pont2 != b){   //caso polinomio a volte ao nó cabeça
            define_coeficiente(res, pont2->valor.grau, pont2->valor.coef);
            pont2 = pont2->prox;
        }else if(pont1 != a && pont2 == b){  //caso polinomio b volte ao nó cabeça
            define_coeficiente(res, pont1->valor.grau, pont1->valor.coef);
            pont1 = pont1->prox;
        }else if(pont1->valor.grau > pont2->valor.grau){    //caso grau de polinomio a for maior que polinomio b
            define_coeficiente(res, pont2->valor.grau, pont2->valor.coef);
            pont2 = pont2->prox;
        }else if(pont1->valor.grau < pont2->valor.grau){    //caso grau de polinomio b for maior que polinomio a
            define_coeficiente(res, pont1->valor.grau, pont1->valor.coef);
            pont1 = pont1->prox;
        }else{  //caso grau de polinomio a for igual a grau de polinomio b
            int soma = pont1->valor.coef + pont2->valor.coef;
            define_coeficiente(res, pont1->valor.grau, soma);
            pont1 = pont1->prox;
            pont2 = pont2->prox;
        }
    }
}

/* Computa a subtracao dos polinomios a e b colocando o resultado em res.
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void subtrai(Polinomio res, Polinomio a, Polinomio b){
    No *pont1 = a->prox, *pont2 = b->prox;
    zera(res);

    while(pont1 != a || pont2 != b){
        if(pont1 == a && pont2 != b){ //caso polinomio a volte ao nó cabeça
            define_coeficiente(res, pont2->valor.grau, pont2->valor.coef);
            pont2 = pont2->prox;
        }else if(pont1 != a && pont2 == b){ //caso polinomio b volte ao nó cabeça
            define_coeficiente(res, pont1->valor.grau, pont1->valor.coef);
            pont1 = pont1->prox;
        }if(pont1->valor.grau > pont2->valor.grau){ //caso grau de polinomio a for maior que polinomio b
            define_coeficiente(res, pont2->valor.grau, 0 - pont2->valor.coef);
            pont2 = pont2->prox;
        }else if(pont1->valor.grau < pont2->valor.grau){    //caso grau de polinomio b for maior que polinomio a
            define_coeficiente(res, pont1->valor.grau, pont1->valor.coef);
            pont1 = pont1->prox;
        }else{  //caso grau de polinomio a for igual a grau de polinomio b
            int subtracao = pont1->valor.coef - pont2->valor.coef;
            define_coeficiente(res, pont1->valor.grau, subtracao);
            pont1 = pont1->prox;
            pont2 = pont2->prox;
        }
    }
}


/* Imprime o polinomio pol no formato do exemplo abaixo
 * [(0,2),(3,-2),(10,5)]
 * onde este polinomio tem 3 coeficientes, o de grau 0 com valor 2, o de grau 3 com valor -2 e o de
 * grau 10 com valor 5.
 */
void imprime(Polinomio pol){
    No *atual = pol->prox;
    printf("[");
    while(atual != pol){
        printf("(%d,%d)", atual->valor.grau, atual->valor.coef);
        atual = atual->prox;
        if(atual != pol)
            printf(",");
    }
    printf("]\n");
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_polinomio(Polinomio *ap_pol){
    zera(*ap_pol);
    free(*ap_pol);
    *ap_pol = NULL;
}
