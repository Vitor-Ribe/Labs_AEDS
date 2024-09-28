#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do n� da �rvore
typedef struct No{
    int eh_num;
    char operador;
    int valor;
    struct No *esquerda, *direita;
} No;

// Cria um n� operador
No* criarNoOperador(char operador){
    No* novo = (No*)malloc(sizeof(No));
    novo->eh_num = 0;
    novo->operador = operador;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Cria um n� n�mero
No* criarNoNumero(int valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->eh_num = 1;
    novo->valor = valor;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Fun��o para converter string em n�mero inteiro
int stringParaInteiro(char* str){
    int resultado = 0;
    while(*str){
        resultado = resultado * 10 + (*str - '0');
        str++;
    }
    return resultado;
}

// Constr�i a �rvore de express�o
No* construirArvore(char* tokens[], int inicio, int fim){
    if(inicio == fim)
        return criarNoNumero(stringParaInteiro(tokens[inicio])); // N� n�mero

    int pos_operador = -1;

    // Encontra operador de menor preced�ncia ('%')
    for(int i=fim; i>=inicio; i--)
        if(tokens[i][0] == '%'){
            pos_operador = i;
            break;
        }
    
    // Se n�o encontrou '%', procura por '+' ou '-'
    for(int i=fim; i>=inicio; i--)
        if(tokens[i][0] == '+' || tokens[i][0] == '-'){
            pos_operador = i;
            break;
        }
    

    // Se n�o encontrou '+ ou '-', procura por '*' ou '/'
    if(pos_operador == -1)
        for(int i=fim; i>=inicio; i--)
            if(tokens[i][0] == '*' || tokens[i][0] == '/'){
                pos_operador = i;
                break;
            }

    // Cria n� do operador
    No* raiz = criarNoOperador(tokens[pos_operador][0]);

    // Constr�i sub�rvores esquerda e direita
    raiz->esquerda = construirArvore(tokens, inicio, pos_operador - 1);
    raiz->direita = construirArvore(tokens, pos_operador + 1, fim);
    return raiz;
}

// Imprime em nota��o prefixa
void imprimirPrefixo(No* raiz){
    if(!raiz) return;
    if(raiz->eh_num)
        printf("%d", raiz->valor);
    else{
        printf("%c", raiz->operador);
        if(raiz->esquerda || raiz->direita) // Se houver filhos, imprime espa�o
            printf(" ");
            
        imprimirPrefixo(raiz->esquerda);
        if(raiz->direita) // Se houver filho direito, imprime espa�o
            printf(" ");
       
        imprimirPrefixo(raiz->direita);
    }
}

// Imprime em nota��o posfixa
void imprimirPosfixo(No* raiz){
    if(!raiz) return;
    if(raiz->eh_num)
        printf("%d", raiz->valor);
    else{
        imprimirPosfixo(raiz->esquerda);
        if(raiz->esquerda) // Se houver filho esquerdo, imprime espa�o
            printf(" ");
        
        imprimirPosfixo(raiz->direita);
        printf(" %c", raiz->operador);
    }
}

// Calcula o valor da express�o
int calcularExpressao(No* raiz){
    if(raiz->eh_num) return raiz->valor; // Retorna valor se for n�mero

    // Calcula sub�rvores esquerda e direita
    int esquerda = calcularExpressao(raiz->esquerda);
    int direita = calcularExpressao(raiz->direita);

    switch(raiz->operador){
    	case '%': return esquerda % direita;
        case '+': return esquerda + direita;
        case '-': return esquerda - direita;
        case '*': return esquerda * direita;
        case '/': return esquerda / direita;
        default: return 0;
    }
}

// Libera a mem�ria da �rvore
void liberarArvore(No* raiz){
    if(!raiz) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
 
int main(){
    char linha[100];
    fgets(linha, 100, stdin);

    char* tokens[50];
    int ntokens = 0;
    char* token = strtok(linha," \n"); // Divide a linha em tokens
    while(token){
        tokens[ntokens++] = token;
        token = strtok(NULL," \n");
    }

    No* arvore = construirArvore(tokens, 0, ntokens-1);

    imprimirPrefixo(arvore);
    printf("\n");
    imprimirPosfixo(arvore);
    printf("\n");
    
    int resultado = calcularExpressao(arvore);
    printf("%d\n", resultado);

    liberarArvore(arvore);
    return 0;
}

