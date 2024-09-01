#include <stdio.h>

void preencheVetor(int n, int vet[2][n]){
    for(int i=0; i<n; i++){
        printf("\n\nDigite o peso do elemento %d: ", i+1);
        scanf("%d", &vet[0][i]);
        printf("\nDigite o valor do elemento %d: ", i+1);
        scanf("%d", &vet[1][i]);
    }
}

void imprimeVetor(int n, int vet[2][n]){
    printf("\nELEMENTOS\n");
    for(int i=0; i<n; i++){
        printf("%d %d", vet[0][i], vet[1][i]);
        printf("\n");
    }
}

int main(){
    int n, M;
    // entradas
    do{
        printf("\nDigite numero de elementos: ");
        scanf("%d", &n);
        if(n < 0 || n > 20)
            printf("\nValor diferente do esperado (n <= 20)!\n");
    }while(n < 0 || n > 20); // restrição de quantidade máxima de elementos
    do{
        printf("\nDigite capacidade maxima da mochila: ");
        scanf("%d", &M);
        if(M < 0 || M > 1000000)
            printf("\nValor diferente do esperado (M <= 10⁶)!\n");
    }while(M < 0 || M > 1000000); // restrição de peso máximo da mochila

    //criando vetor
    int elemento[2][n];

    preencheVetor(n, elemento);
//imprimeVetor(n, elemento);
    return 0;
}
