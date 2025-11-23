#include<stdio.h>
#include<string.h>

int main(){

    char inventario [5][19];

    for(int i = 0; i < 5; i++){
        printf("Digite os itens que estao no inventario: ");
        scanf("%s", *(inventario + i));
    }

    char item_necessario [50];

    printf("Digite o nome do item necessario para abrir a porta: ");
    scanf("%s", item_necessario);

    for(int i = 0; i < 5; i++){
        if(strcmp(inventario[i], item_necessario) == 0){
            printf("Porta Aberta!");
            return 0;
        }
    }
    
    printf("A porta nao esta aberta.");
        
    return 1;
}