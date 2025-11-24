#include <stdio.h>
#include <stdlib.h>


int contar_cristais_carregados(const int *cristais, int tamanho, int indice) {
    
    if (indice >= tamanho) {
        return 0;
    }

    
    int cristal_carregado = 0;

    
    if (cristais[indice] > 0) {
        cristal_carregado = 1;
    }

    
    return cristal_carregado + contar_cristais_carregados(cristais, tamanho, indice + 1);
}

int main() {
    int n; 
    int *inventario = NULL;
    int i;
    int total_carregados;

    printf("--- Contagem de Cristais de Mana Carregados (Recursivo) ---\n");

    
    printf("Digite a quantidade de cristais no inventario (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de cristais deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    inventario = (int *)malloc(n * sizeof(int));
    if (inventario == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Leitura dos Niveis de Carga ##\n");
    for (i = 0; i < n; i++) {
        printf("Carga do Cristal %d (inteiro): ", i + 1);
        if (scanf("%d", &inventario[i]) != 1) {
            printf("Erro na leitura da carga.\n");
            free(inventario);
            return EXIT_FAILURE;
        }
    }

   
    total_carregados = contar_cristais_carregados(inventario, n, 0);

    
    printf("\n------------------------------------------------\n");
    printf("Total de Cristais Carregados (Carga > 0): %d\n", total_carregados);
    printf("------------------------------------------------\n");

    
    free(inventario);

    return EXIT_SUCCESS;
}