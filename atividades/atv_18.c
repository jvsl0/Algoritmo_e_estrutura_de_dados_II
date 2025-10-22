#include<stdio.h>
#include<stdlib.h>

int main(){

    int *vida_inimigo = malloc(sizeof(int));

    if(vida_inimigo == NULL){
        printf("alocacao de memoria falhou");
        return 1;
    }

    *vida_inimigo = 80;
    printf("Um novo inimigo apareceu com %d de vida!\n", *vida_inimigo);

    *vida_inimigo -= 35;
    printf("O jogador atacou! Vida restante do inimigo: %d", *vida_inimigo);

    return 0;
}