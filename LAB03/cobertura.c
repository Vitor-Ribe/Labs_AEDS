#include <stdio.h>


int le_n(){
    int n;
    do{
        printf("\nDigite o tamanho do conjunto S: ");
        scanf("%d", &n);
        if(n < 0 || n > 15)
            printf("\nDIGITE UM TAMANHO ENTRE 1 e 14!\n");
    }while(n < 0 || n > 15);
    return n;
}

int le_m(){
    int m;
    do{
        printf("\nDigite o tamanho da colecao W: ");
        scanf("%d", &m);
        if(m < 0 || m > 15)
            printf("\nDIGITE UM TAMANHO ENTRE 1 e 14!\n");
    }while(m < 0 || m > 15);
    return m;
}

void preenche_subconjunto(int *W, int n, int m){
    //percorre todos os elementos da coleção W
    for(int i=0; i<m; i++){
        int k; //numero de elementos da subcoleção
        do{
            printf("\nDigite o numero de elementos da subcolecao %d: ", i+1);
            scanf("%d", &k);
            if(k < 0 || k > n)  //verificação caso o usuario digite um numero impossivel de elementos
                printf("\nNUMERO DE ELEMENTOS NAO PODE SER MENOR QUE ZERO OU MAIOR QUE A QUANTIDADE DE ELEMENTOS DO CONJUNTO S!\n");
        }while(k < 0 || k > n);

        int elemento, mascara = 0;
        printf("\nDigite os elementos da subcolecao: ");
        //adiciona a quantidade k de elementos da subcoleção
        for(int i=0; i<k; i++){
            do{
                scanf("%d", &elemento);
                if(elemento >= 0 && elemento < n)    //restrição para não aceitar elementos que não fazem parte do conjunto S
                    mascara = mascara | (1 << elemento); //a mascara recebe a representação em bits ativos do decimal de elemento
                else
                    printf("\nELEMENTO NAO FAZ PARTE DO CONJUNTO S!\n");
            }while(elemento < 0 || elemento > n);
        }
        W[i] = mascara; //adiciona o valor da mascara ao representante da subcoleção no vetor
    }
}

int main(){

    int n = le_n();  //tamanho do conjunto S
    int m = le_m();  //tamanho da coleção W

//Criacao da colecao W
    int W[m];
    preenche_subconjunto(W, n, m);

    int conjunto_cheio = (1 << n) - 1;  //cria uma mascara que representa todos os elementos do conjunto ativos

// Testes de combinação

    int total_combinacoes = (1 << m);   //recebe o numero de combinações possíveis entre as subcoleções
    int solucao_encontrada = 0;

    //percorre todas as combinações possíveis entre as subcoleções
    for(int i=1; i<total_combinacoes; i++){

        int cobertura, contagem=0;
        //verifica quais subcoleções fazem parte da combinação
        for(int j=0; j<m; j++){
            if(i&(1 << j)){
                cobertura |= W[j];
                contagem++;
            }
        }

        if(cobertura == conjunto_cheio){
            printf("\nSolucao encontrada com %d subconjuntos", contagem);
            for(int j=0; j<m; j++){
                if(i&(1 << j)){
                    printf("\nSubconjunto %d: ", j+1);
                    for(int k=0; k<n; k++){
                        if(W[j] & (1 << k)){
                            printf("%d ", k);
                        }
                    }
                    printf("\n");
                }
            }
            solucao_encontrada = 1;
            break;
        }
    }
    if(!solucao_encontrada){
        printf("\nInsoluvel\n");
    }
    return 0;
}
