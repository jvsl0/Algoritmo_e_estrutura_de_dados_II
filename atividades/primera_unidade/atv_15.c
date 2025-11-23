#include<stdio.h>
#include<string.h>

int main(){

    char nome_jogador[50];
    char titulo_conquistado[50];

    printf("digite o nome do jogador: \n");
    scanf("%s", nome_jogador);

    printf("digite o titulo conquistado: \n");
    scanf("%s", titulo_conquistado);

    strcat(nome_jogador, " ");
    
    strcat(nome_jogador, titulo_conquistado);

    printf("O heroi agora e conhecido como: %s\n", nome_jogador);

    return 0;
}