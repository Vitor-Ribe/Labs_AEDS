#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore
typedef struct No{
    int eh_num;
    char operador;
    int valor;
    struct No *esquerda, *direita;
} No;

// Cria um nó operador
No* criarNoOperador(char operador){
    No* novo = (No*)malloc(sizeof(No));
    novo->eh_num = 0;
    novo->operador = operador;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Cria um nó número
No* criarNoNumero(int valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->eh_num = 1;
    novo->valor = valor;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Função para converter string em número inteiro
int stringParaInteiro(char* str){
    int resultado = 0;
    while(*str){
        resultado = resultado * 10 + (*str - '0');
        str++;
    }
    return resultado;
}

// Constrói a árvore de expressão
No* construirArvore(char* tokens[], int inicio, int fim){
    if(inicio == fim)
        return criarNoNumero(stringParaInteiro(tokens[inicio])); // Nó número

    int pos_operador = -1;

    // Encontra operador de menor precedência ('%')
    for(int i=fim; i>=inicio; i--)
        if(tokens[i][0] == '%'){
            pos_operador = i;
            break;
        }
    
    // Se não encontrou '%', procura por '+' ou '-'
    for(int i=fim; i>=inicio; i--)
        if(tokens[i][0] == '+' || tokens[i][0] == '-'){
            pos_operador = i;
            break;
        }
    

    // Se não encontrou '+ ou '-', procura por '*' ou '/'
    if(pos_operador == -1)
        for(int i=fim; i>=inicio; i--)
            if(tokens[i][0] == '*' || tokens[i][0] == '/'){
                pos_operador = i;
                break;
            }

    // Cria nó do operador
    No* raiz = criarNoOperador(tokens[pos_operador][0]);

    // Constrói subárvores esquerda e direita
    raiz->esquerda = construirArvore(tokens, inicio, pos_operador - 1);
    raiz->direita = construirArvore(tokens, pos_operador + 1, fim);
    return raiz;
}

// Imprime em notação prefixa
void imprimirPrefixo(No* raiz){
    if(!raiz) return;
    if(raiz->eh_num)
        printf("%d", raiz->valor);
    else{
        printf("%c", raiz->operador);
        if(raiz->esquerda || raiz->direita) // Se houver filhos, imprime espaço
            printf(" ");
            
        imprimirPrefixo(raiz->esquerda);
        if(raiz->direita) // Se houver filho direito, imprime espaço
            printf(" ");
       
        imprimirPrefixo(raiz->direita);
    }
}

// Imprime em notação posfixa
void imprimirPosfixo(No* raiz){
    if(!raiz) return;
    if(raiz->eh_num)
        printf("%d", raiz->valor);
    else{
        imprimirPosfixo(raiz->esquerda);
        if(raiz->esquerda) // Se houver filho esquerdo, imprime espaço
            printf(" ");
        
        imprimirPosfixo(raiz->direita);
        printf(" %c", raiz->operador);
    }
}

// Calcula o valor da expressão
int calcularExpressao(No* raiz){
    if(raiz->eh_num) return raiz->valor; // Retorna valor se for número

    // Calcula subárvores esquerda e direita
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

// Libera a memória da árvore
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

