#include <stdio.h>

int main() {
    float forca_base;
    float bonus_arma;
    float bonus_buff;
    float dano_total;

    printf("--- Calculo de Dano Final do Personagem ---\n");

    
    
    printf("Digite a Forca Base do Personagem: ");
    if (scanf("%f", &forca_base) != 1) {
        printf("Erro na leitura da Forca Base.\n");
        return 1;
    }

    printf("Digite o Bonus de Dano da Arma: ");
    if (scanf("%f", &bonus_arma) != 1) {
        printf("Erro na leitura do Bonus da Arma.\n");
        return 1;
    }

    printf("Digite o Bonus do Feitico (Buff): ");
    if (scanf("%f", &bonus_buff) != 1) {
        printf("Erro na leitura do Bonus do Buff.\n");
        return 1;
    }

    
    dano_total = forca_base + bonus_arma + bonus_buff;

    
    printf("\n------------------------------------------------\n");
    printf("Dano Final Calculado (O(1)):\n");
    printf("Dano Total: %.2f\n", dano_total);
    printf("------------------------------------------------\n");

    return 0;
}