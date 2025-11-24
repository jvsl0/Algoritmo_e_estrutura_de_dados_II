#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NOME 100


typedef struct {
    int posicao; 
    char nome[MAX_NOME];
} Piloto;


void intercala(Piloto *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; 
    int n2 = r - m;     

    
    Piloto *L = (Piloto *)malloc(n1 * sizeof(Piloto));
    Piloto *R = (Piloto *)malloc(n2 * sizeof(Piloto));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria na intercalacao.\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }

   
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    
    i = 0; 
    j = 0; 
    k = l; 

    while (i < n1 && j < n2) {
        
        if (L[i].posicao <= R[j].posicao) {
            arr[k] = L[i];
            i++;
        } else {
            
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    
    free(L);
    free(R);
}


void mergeSort(Piloto *arr, int l, int r) {
    if (l < r) {
        
        int m = l + (r - l) / 2;

        
        mergeSort(arr, l, m);     
        mergeSort(arr, m + 1, r); 

        
        intercala(arr, l, m, r);
    }
}

int main() {
    int n; 
    Piloto *competidores = NULL;
    int i;

    printf("--- Sistema de Placar de Corrida (Merge Sort) ---\n\n");

    
    printf("Digite o numero total de pilotos na corrida (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    competidores = (Piloto *)malloc(n * sizeof(Piloto));
    if (competidores == NULL) {
        printf("Erro: Falha na alocacao de memoria para os pilotos.\n");
        return EXIT_FAILURE;
    }

    
    printf("\nDigite a posicao de chegada (inteiro) e o nome (string) para cada piloto:\n");
    for (i = 0; i < n; i++) {
        printf("Piloto %d (Posicao Nome): ", i + 1);
        
        if (scanf("%d", &competidores[i].posicao) != 1 || competidores[i].posicao <= 0) {
            printf("Erro: A posicao deve ser um inteiro positivo.\n");
            free(competidores);
            return EXIT_FAILURE;
        }
        
        if (scanf("%99s", competidores[i].nome) != 1) { 
             printf("Erro na leitura do nome.\n");
            free(competidores);
            return EXIT_FAILURE;
        }
    }

    
    printf("\nIniciando a ordenacao do placar...\n");
    mergeSort(competidores, 0, n - 1);

    
    printf("\n====================================\n");
    printf("Classificacao Final (Podio Ordenado):\n");
    printf("====================================\n");
    for (i = 0; i < n; i++) {
        
        printf("%d %s\n", competidores[i].posicao, competidores[i].nome);
    }
    printf("====================================\n");

    
    free(competidores);

    return EXIT_SUCCESS;
}