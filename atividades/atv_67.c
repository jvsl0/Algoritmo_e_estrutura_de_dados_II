#include <stdio.h>
#include <stdlib.h>


void bubble_sort_otimizado(int *arr, int n) {
    int i, j, temp;
    int troca; 
    
    for (i = 0; i < n - 1; i++) {
        troca = 0; 
        
        for (j = 0; j < n - i - 1; j++) {
            
            if (arr[j] < arr[j + 1]) {
                
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                troca = 1; 
            }
        }

        
        if (troca == 0) {
            
            break;
        }
    }
}


void imprimir_pontuacoes(const int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n; 
    int *pontuacoes = NULL; 
    int i;

    printf("--- Placar de Pontuacoes Eficiente (Bubble Sort Otimizado Decrescente) ---\n");

    
    printf("Digite a quantidade de pontuacoes (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de pontuacoes deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    pontuacoes = (int *)malloc(n * sizeof(int));
    if (pontuacoes == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("Digite as %d pontuacoes (inteiros):\n", n);
    for (i = 0; i < n; i++) {
        printf("Pontuacao %d: ", i + 1);
        if (scanf("%d", &pontuacoes[i]) != 1 || pontuacoes[i] < 0) {
            printf("Erro na leitura da pontuacao. Deve ser um inteiro nao-negativo.\n");
            free(pontuacoes);
            return EXIT_FAILURE;
        }
    }

    
    bubble_sort_otimizado(pontuacoes, n);

    
    printf("\n============================================\n");
    printf("Placar Final Ordenado (Decrescente):\n");
    imprimir_pontuacoes(pontuacoes, n);
    printf("============================================\n");

    
    free(pontuacoes);
    
    return EXIT_SUCCESS;
}