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

void subconj(int n, int M, int elem[][n]){
    int limit_mask = (1<<n); // conjunto
    int melhorValor = 0, melhorPeso = 0;

    for(int mask=0; mask<limit_mask; mask++){   // percorre todos os subconjuntos possiveis
        int totalPeso = 0, totalValor = 0;

        for(int i=0; i<n; i++){ //  percorre todos os elementos do subconjunto
            if(mask & (1<<i)){  //  somente os bits ativos
                totalPeso += elem[0][i];
                totalValor += elem[1][i];
            }
        }
        if(totalPeso <= M && totalValor > melhorValor){ //  compara se o valor e o peso do subconjunto é o maior do conjunto
            melhorValor = totalValor;
            melhorPeso = totalPeso;
        }
    }
    printf("\nMelhor valor: %d. Melhor peso: %d\n", melhorValor, melhorPeso);
}

int main(){
    int n, M;
    // entradas
    do{
        printf("\nDigite numero de elementos: ");
        scanf("%d", &n);
        if(n <= 0 || n > 20)
            printf("\nValor diferente do esperado (n <= 20)!\n");
    }while(n <= 0 || n > 20); // restrição de quantidade máxima de elementos
    do{
        printf("\nDigite capacidade maxima da mochila: ");
        scanf("%d", &M);
        if(M <= 0 || M > 1000000)
            printf("\nValor diferente do esperado (M <= 10⁶)!\n");
    }while(M <= 0 || M > 1000000); // restrição de peso máximo da mochila

    //criando vetor
    int elemento[2][n];

    preencheVetor(n, elemento);
    subconj(n, M, elemento);
//imprimeVetor(n, elemento);
    return 0;
}
