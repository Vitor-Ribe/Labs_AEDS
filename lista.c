#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/*
 * Implemente as seguintes funções utilizando uma lista ligada.
 * Você deve implementar uma versão sem nó cabeça.
 */

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
    *ap_lista = NULL;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o inicio da lista. */
void insere_fim(Lista * ap_lista, int valor){
    No *novo = (No *)malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = NULL;

        if(*ap_lista == NULL){
            *ap_lista = novo;
        }else{
            No *aux = *ap_lista;
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
    }else
        printf("\nErro ao alocar memoria!\n");
}

/* Insere valor no inicio da lista apontada por ap_lista. */
void insere_inicio(Lista * ap_lista, int valor){
    No *novo = (No *)malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = *ap_lista;
        *ap_lista = novo;
    }else
        printf("\nErro ao alocar memoria!\n");
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
int remove_fim(Lista * ap_lista){
    if(*ap_lista == NULL){
        return -1;
    }else{
        No *aux = *ap_lista, *aux2;
        int valor;

        if(aux->proximo == NULL){
            *ap_lista = NULL;
            valor = aux->valor;
        }else{
            while(aux->proximo){
                aux2 = aux;
                aux = aux->proximo;
            }
            aux2->proximo = NULL;
            valor = aux->valor;
        }
        free(aux);
        return valor;
    }
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
int remove_inicio(Lista * ap_lista){
    if(*ap_lista == NULL){
        return -1;
    }else{
        No *aux = *ap_lista;
        int valor = aux->valor;

        if(aux->proximo == NULL)
            *ap_lista = NULL;
        else
            *ap_lista = aux->proximo;

        free(aux);
        return valor;
    }
}

/* Remove o i-ésimo elemento da lista, caso ele exista. Retorna se o elemento
foi removido. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
bool remove_i_esimo(Lista * ap_lista, int i){

    No *atual = *ap_lista, *anterior=NULL;
    int contador=1;

    if(*ap_lista == NULL)
        return false;

    while(atual != NULL){
        if(contador == i){
            if(anterior == NULL)
                *ap_lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
        contador++;
    }
    return false;
}

/* Retorna o valor do i-ésimo elemento da lista, caso ele exista.
Retorna -1 caso contrário. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
int recupera_i_esimo(Lista lista, int i){
    int contador = 0;
    if(lista == NULL)
        return -1;

    while(lista != NULL){
        contador++;
        if(contador == i)
            return lista->valor;
        lista = lista->proximo;
    }
    return -1;
}

/* Retorna o tamanho da lista. */
int tamanho(Lista lista){
    int contador=0;
    while(lista != NULL){
        contador++;
        lista = lista->proximo;
    }
    return contador;
}

/* Remove todas as ocorrências de valor da lista apontada por ap_lista.
 * Retorna o numero de ocorrências removidas.
 */
int remove_ocorrencias(Lista *ap_lista, int valor){
    No *atual = *ap_lista, *anterior = NULL;
    int numero_ocorrencias=0;

    if(*ap_lista == NULL)
        return 0;

    while(atual != NULL){
        if(atual->valor == valor){
            numero_ocorrencias++;

            if(anterior == NULL)
                *ap_lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }else{
            anterior = atual;
            atual = atual->proximo;
        }
    }
    return numero_ocorrencias;
}

/* Busca elemento valor na lista.
   Retorna a posição na lista, começando de 1=primeira posição.
   Retorna -1 caso não encontrado.
*/
int busca(Lista lista, int valor){
    int contador = 0;
    if(lista == NULL)
        return -1;

    while(lista != NULL){
        contador++;
        if(lista->valor == valor)
            return contador;
        lista = lista->proximo;
    }
    return -1;
}

/* Imprime a lista na saida padrão, no formato:
   (1,3,2,3,4,2,3,1,4)
   em uma linha separada.
 */
void imprime(Lista lista){
    printf("(");
    while(lista != NULL){
        printf("%d", lista->valor);
        lista = lista->proximo;
        if(lista != NULL)
            printf(",");
    }
    printf(")\n");
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    if(*ap_lista != NULL){
        No *aux = *ap_lista, *aux2;
        while(aux != NULL){
            aux2 = aux->proximo;
            free(aux);
            aux = aux2;
        }
        *ap_lista = NULL;
    }
}

