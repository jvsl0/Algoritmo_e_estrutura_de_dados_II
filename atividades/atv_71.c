#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    int nivel_ameaca;
} NaveInimiga;


void intercalar(NaveInimiga *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; 
    int n2 = r - m;     

    
    NaveInimiga *L = (NaveInimiga *)malloc(n1 * sizeof(NaveInimiga));
    NaveInimiga *R = (NaveInimiga *)malloc(n2 * sizeof(NaveInimiga));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria no merge.\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }

    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    
    i = 0; 
    j = 0; 
    k = l; 

    while (i < n1 && j < n2) {
        
        if (L[i].nivel_ameaca <= R[j].nivel_ameaca) {
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


void ordenar_merge_sort(NaveInimiga *arr, int l, int r) {
    if (l < r) {
        
        int m = l + (r - l) / 2;

       
        ordenar_merge_sort(arr, l, m);     
        ordenar_merge_sort(arr, m + 1, r); 

        
        intercalar(arr, l, m, r);
    }
}

int main() {
    int n; 
    NaveInimiga *alvos = NULL;
    int i;

    printf("--- Modulo de Priorizacao de Alvos (Merge Sort) ---\n\n");

    
    printf("Digite a quantidade de naves inimigas (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    alvos = (NaveInimiga *)malloc(n * sizeof(NaveInimiga));
    if (alvos == NULL) {
        printf("Erro: Falha na alocacao de memoria para os alvos.\n");
        return EXIT_FAILURE;
    }

    
    printf("\nDigite o ID e o Nivel de Ameaca para cada uma das %d naves:\n", n);
    for (i = 0; i < n; i++) {
        printf("Nave %d (ID Nivel_Ameaca): ", i + 1);
        if (scanf("%d %d", &alvos[i].id, &alvos[i].nivel_ameaca) != 2 || alvos[i].nivel_ameaca < 0) {
            printf("Erro na leitura dos dados. Certifique-se de que o nivel de ameaca e nao-negativo.\n");
            free(alvos);
            return EXIT_FAILURE;
        }
    }

    
    ordenar_merge_sort(alvos, 0, n - 1);

    
    printf("\n===================================================================\n");
    printf("Prioridade de Alvos (ID's ordenados por Nivel de Ameaca Crescente):\n");
    for (i = 0; i < n; i++) {
        printf("%d", alvos[i].id);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n===================================================================\n");

    
    free(alvos);

    return EXIT_SUCCESS;
}