#include<stdio.h>
#include<stdlib.h>

int main(){

    int n_inimigos;

    int *ponteiro_onda;

    printf("Digite a quantidade de inimigos da onda: \n");
    scanf("%d", &n_inimigos);

    ponteiro_onda = malloc(sizeof(int) * n_inimigos);

    for(int i = 0; i < n_inimigos; i++){
        printf("Digite o id do inimgo %d: ", i+1);
        scanf("%d", ponteiro_onda + i);
    }

    printf("Onda de inimigos criada com sucesso! IDs: ");
    for(int i = 0; i < n_inimigos; i++){
        printf("%d ", *(ponteiro_onda + i));
    }
    printf("\n");

    return 0;

}