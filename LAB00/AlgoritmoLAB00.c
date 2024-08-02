#include <stdio.h>

int main(){

    int num1, num2, soma1=0, soma2=0;

    scanf("%d %d", &num1, &num2);

    for(int i=num1-1; i>0; i--){
        if(num1%i == 0){
            soma1 += i;
        }
    }

    for(int i=num2-1; i>0; i--){
        if(num2%i == 0){
            soma2 += i;
        }
    }

    if(soma1 == num2 && soma2 == num1){
        printf("amigos\n");
    }else
        printf("nao amigos\n");

    return 0;
}
