#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para usar INT_MIN


int max(int a, int b) {
    return (a > b) ? a : b;
}


int encontrar_maximo_divisao_e_conquista(const int *fragmentos, int inicio, int fim) {
    int meio;
    int max_esquerda;
    int max_direita;

    
    if (inicio == fim) {
        return fragmentos[inicio];
    }

    
    if (inicio == fim - 1) {
        return max(fragmentos[inicio], fragmentos[fim]);
    }

    
    meio = inicio + (fim - inicio) / 2;

    
    max_esquerda = encontrar_maximo_divisao_e_conquista(fragmentos, inicio, meio);

    
    max_direita = encontrar_maximo_divisao_e_conquista(fragmentos, meio + 1, fim);

    
    return max(max_esquerda, max_direita);
}

int main() {
    int n; 
    int *fragmentos = NULL;
    int maximo_poder;
    int i;

    printf("--- Encontrando a Fonte de Poder Maxima (Divisao e Conquista) ---\n\n");

    
    printf("Digite a quantidade de Fragmentos de Alma no inventario (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    fragmentos = (int *)malloc(n * sizeof(int));
    if (fragmentos == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("Digite os %d niveis de poder dos fragmentos (inteiros):\n", n);
    for (i = 0; i < n; i++) {
        printf("Poder Fragmento %d: ", i + 1);
        if (scanf("%d", &fragmentos[i]) != 1) {
            printf("Erro na leitura do nivel de poder.\n");
            free(fragmentos);
            return EXIT_FAILURE;
        }
    }

    
    if (n > 0) {
        maximo_poder = encontrar_maximo_divisao_e_conquista(fragmentos, 0, n - 1);

        
        printf("\n======================================================\n");
        printf("O Fragmento de Alma com o Nivel de Poder Maximo e: %d\n", maximo_poder);
        printf("======================================================\n");
    } else {
        printf("\nInventario vazio. Nivel de poder maximo e 0.\n");
    }


    
    free(fragmentos);

    return EXIT_SUCCESS;
}