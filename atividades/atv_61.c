#include <stdio.h>
#include <stdlib.h>


void selection_sort(int *arr, int n) {
    int i, j, indice_min, temp;

    
    for (i = 0; i < n - 1; i++) {
        
        indice_min = i;

       
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_min]) {
                indice_min = j;
            }
        }

        
        if (indice_min != i) {
            temp = arr[i];
            arr[i] = arr[indice_min];
            arr[indice_min] = temp;
        }
    }
}


void imprimir_vetor(const int *arr, int n) {
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
    int *scores = NULL; 
    int i;

    printf("--- High Score Sorter (Selection Sort) ---\n");

    
    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de jogadores deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    scores = (int *)malloc(n * sizeof(int));
    if (scores == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("Digite as %d pontuacoes, separadas por espaco ou quebra de linha:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &scores[i]) != 1) {
            printf("Erro na leitura da pontuacao.\n");
            free(scores);
            return EXIT_FAILURE;
        }
    }

    
    selection_sort(scores, n);

    
    printf("\n============================================\n");
    printf("Ranking Final (Menor para o Maior Score):\n");
    imprimir_vetor(scores, n);
    printf("============================================\n");

    
    free(scores);
    
    return EXIT_SUCCESS;
}