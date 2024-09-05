#include <stdio.h>

void preencheVetor(int n, int vet[2][n]){
    for(int i=0; i<n; i++)
        scanf("%d %d", &vet[0][i], &vet[1][i]);
}

void subconj(int n, int M, int elem[][n]){
    int melhorValor = 0, limit_mask = (1<<n); // conjunto potencia

    for(int mask=0; mask<limit_mask; mask++){   // percorre todos os subconjuntos possiveis
        int totalPeso = 0, totalValor = 0;

        for(int i=0; i<n; i++) //  percorre todos os elementos do subconjunto
            if(mask & (1<<i)){  //  somente os bits ativos
                totalPeso += elem[0][i];
                totalValor += elem[1][i];
            }
        if(totalPeso <= M && totalValor > melhorValor) //  compara se o valor e o peso do subconjunto é o maior do conjunto
            melhorValor = totalValor;
    }
    printf("%d\n", melhorValor);
}

int main(){
    int n, M;
    scanf("%d %d", &n, &M);
    if((n <= 0 || n > 20) || (M <= 0 || M > 1000000))   //  restricoes
        return -1;

    int elemento[2][n];
    preencheVetor(n, elemento);
    subconj(n, M, elemento);
    return 0;
}
