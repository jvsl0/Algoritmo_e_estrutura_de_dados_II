#include <stdio.h>
#include <stdlib.h>


int calcular_dano_cascata(int nivel) {
    
    if (nivel <= 1) {
        return 1;
    }
    
    
    return nivel + calcular_dano_cascata(nivel - 1);
}

int main() {
    int nivel_mago;
    int dano_total;

    printf("--- Calculadora de Dano de Ataque em Cascata (Recursivo) ---\n");

   
    printf("Digite o nivel do Mago (inteiro positivo): ");
    if (scanf("%d", &nivel_mago) != 1 || nivel_mago <= 0) {
        printf("Erro: Nivel invalido. Deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    dano_total = calcular_dano_cascata(nivel_mago);

    
    printf("\n--- Resultado do Ataque em Cascata ---\n");
    printf("Nivel do Mago: %d\n", nivel_mago);
    printf("Dano Total (Soma de 1 ate %d): %d\n", nivel_mago, dano_total);
    printf("--------------------------------------\n");

    return EXIT_SUCCESS;
}