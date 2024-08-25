#include <stdio.h>

void preenche_subconjunto(int *W, int m){
    for (int i = 0; i < m; i++){
        int k;
        scanf("%d", &k);

        int elemento, mascara = 0;
        for (int j = 0; j < k; j++){
            scanf("%d", &elemento);
            mascara |= (1 << elemento);
        }
        W[i] = mascara;
    }
}

int calcula_cobertura(int *W, int i, int m){
    int cobertura = 0;
    for (int j = 0; j < m; j++){
        if (i & (1 << j))
            cobertura |= W[j];
    }
    return cobertura;
}

int conta_bits_ativos(int i){
    int contagem = 0;
    while (i > 0){
        if (i & 1)
            contagem++;
        i >>= 1;
    }
    return contagem;
}

int valida_solucao(int *W, int i, int m, int n){
    int visibilidade[15] = {0};
    for (int j = 0; j < m; j++){
        if (i & (1 << j)){
            for (int k = 0; k < n; k++){
                if (W[j] & (1 << k)){
                    if (visibilidade[k] == 1)
                        return 0;
                    visibilidade[k] = 1;
                }
            }
        }
    }
    return 1;
}

void imprime_solucao(int *W, int i, int m, int n, int contagem){
    printf("%d\n", contagem);
    for (int j = 0; j < m; j++){
        if (i & (1 << j)){
            int cont_aux = 0;
            for (int k = 0; k < n; k++){
                if (W[j] & (1 << k))
                    cont_aux++;
            }
            printf("%d ", cont_aux);
            cont_aux = 0;

            for (int l = 0; l < n; l++){
                if (W[j] & (1 << l)){
                    if (cont_aux > 0)
                        printf(" ");

                    printf("%d", l);
                    cont_aux++;
                }
            }
            printf("\n");
        }
    }
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    int W[m];
    preenche_subconjunto(W, m);

    int conjunto_cheio = (1 << n) - 1;
    int total_combinacoes = (1 << m);
    int solucao_encontrada = 0;

    for (int i = 1; i < total_combinacoes; i++){
        int cobertura = calcula_cobertura(W, i, m);
        if (cobertura == conjunto_cheio){
            int contagem = conta_bits_ativos(i);
            if (valida_solucao(W, i, m, n)){
                imprime_solucao(W, i, m, n, contagem);
                solucao_encontrada = 1;
                break;
            }
        }
    }
    if (!solucao_encontrada)
        printf("Insoluvel\n");
    return 0;
}
