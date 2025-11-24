#include <stdio.h>
#include <stdlib.h>


int calcularDanoEco(int n) {
    
    if (n == 1) {
        return 0;
    }

    
    if (n == 2) {
        return 1;
    }

    
    return calcularDanoEco(n - 1) + calcularDanoEco(n - 2);
}

int main() {
    int n; 
    int dano_bonus;

    printf("--- Calculadora de Dano Bonus do Golpe Ecoante (Fibonacci Recursivo) ---\n");

    // 1. Leitura do número do golpe (N)
    printf("Digite o numero do golpe na sequencia (N >= 1): ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Erro: O numero do golpe deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    dano_bonus = calcularDanoEco(n);

    
    printf("\n---------------------------------------\n");
    printf("Para o %d Golpe Ecoante:\n", n);
    printf("Dano Bonus Msstico: %d pontos\n", dano_bonus);
    printf("---------------------------------------\n");


    return EXIT_SUCCESS;
}