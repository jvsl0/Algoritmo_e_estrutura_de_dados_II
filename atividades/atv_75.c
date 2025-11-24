#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int particao(int v[], int inicio, int fim) {
    
    int pivo = v[fim];

    
    int i = inicio - 1;

    
    for (int j = inicio; j <= fim - 1; j++) {
        
        if (v[j] <= pivo) {
            
            i++;
            
            troca(&v[i], &v[j]);
        }
    }

    
    troca(&v[i + 1], &v[fim]);

    
    return (i + 1);
}


void quickSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        
        int pi = particao(v, inicio, fim);

        
        quickSort(v, inicio, pi - 1);

        
        quickSort(v, pi + 1, fim);
    }
}

int main() {
    int n; 
    int i;

    printf("--- Ordenacao de Jogadores por MMR (Quick Sort) ---\n\n");

    
    printf("Digite a quantidade de jogadores na fila (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    int *mmr_jogadores = (int *)malloc(n * sizeof(int));
    if (mmr_jogadores == NULL) {
        printf("Erro: Falha na alocacao de memoria para os MMRs.\n");
        return EXIT_FAILURE;
    }

    printf("Digite o MMR de cada um dos %d jogadores:\n", n);
    for (i = 0; i < n; i++) {
        printf("Jogador %d MMR: ", i + 1);
        if (scanf("%d", &mmr_jogadores[i]) != 1) {
            printf("Erro na leitura do MMR.\n");
            free(mmr_jogadores);
            return EXIT_FAILURE;
        }
    }

    
    quickSort(mmr_jogadores, 0, n - 1);

    
    printf("\n========================================================\n");
    printf("MMRs ordenados (prontos para o Matchmaking):\n");
    for (i = 0; i < n; i++) {
        printf("%d", mmr_jogadores[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n========================================================\n");

    
    free(mmr_jogadores);

    return EXIT_SUCCESS;
}