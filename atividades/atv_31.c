#include <stdio.h>


typedef struct {
    int pontos;   
    float pos_x;  
    float pos_y;  
} Coletavel;


int main() {
    
    Coletavel gema_rara; 

    printf("--- Criacao de Item Coletavel ---\n");

    
    
    
    printf("Digite o valor em pontos do item: ");
    if (scanf("%d", &gema_rara.pontos) != 1) {
        printf("Erro na leitura dos pontos.\n");
        return 1;
    }
    
    
    printf("Digite a coordenada X (posicao horizontal): ");
    if (scanf("%f", &gema_rara.pos_x) != 1) {
        printf("Erro na leitura da posicao X.\n");
        return 1;
    }
    
    
    printf("Digite a coordenada Y (posicao vertical): ");
    if (scanf("%f", &gema_rara.pos_y) != 1) {
        printf("Erro na leitura da posicao Y.\n");
        return 1;
    }

    printf("\n");

    
    printf("Coletavel criado! Valor: %d pontos. Posicao: (X=%.1f, Y=%.1f)\n",
           gema_rara.pontos, gema_rara.pos_x, gema_rara.pos_y);

    return 0;
}