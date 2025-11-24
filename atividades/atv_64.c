#include <stdio.h>
#include <stdlib.h>


void insertion_sort(int *arr, int n) {
    int i, chave, j;

   
    for (i = 1; i < n; i++) {
        
        chave = arr[i];
        j = i - 1; 

        
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j]; 
            j = j - 1;
        }

        
        arr[j + 1] = chave;
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
    int *fragmentos = NULL; 
    int i;

    printf("--- Ritual de Encantamento: Organizador de Fragmentos (Insertion Sort) ---\n");

    
    printf("Digite a quantidade de Fragmentos de Alma coletados (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de fragmentos deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    fragmentos = (int *)malloc(n * sizeof(int));
    if (fragmentos == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("Digite os %d niveis de poder dos fragmentos:\n", n);
    for (i = 0; i < n; i++) {
        printf("Poder do Fragmento %d: ", i + 1);
        if (scanf("%d", &fragmentos[i]) != 1 || fragmentos[i] < 0) {
            printf("Erro na leitura do poder. Deve ser um inteiro nao-negativo.\n");
            free(fragmentos);
            return EXIT_FAILURE;
        }
    }

    
    insertion_sort(fragmentos, n);

    
    printf("\n================================================\n");
    printf("Fragmentos prontos para o Ritual (Ordem Crescente):\n");
    imprimir_vetor(fragmentos, n);
    printf("================================================\n");

    
    free(fragmentos);
    
    return EXIT_SUCCESS;
}