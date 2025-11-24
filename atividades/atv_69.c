#include <stdio.h>
#include <stdlib.h>


void intercalar_vetores(const int *alfa, int n, const int *beta, int m, int *resultado) {
    int i = 0; 
    int j = 0;
    int k = 0; 

    
    while (i < n && j < m) {
        
        if (alfa[i] <= beta[j]) {
            resultado[k] = alfa[i];
            i++; 
        } else {
            resultado[k] = beta[j];
            j++; 
        }
        k++; 
    }

    
    while (i < n) {
        resultado[k] = alfa[i];
        i++;
        k++;
    }

    
    while (j < m) {
        resultado[k] = beta[j];
        j++;
        k++;
    }
}


void imprimir_vetor(const int *arr, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d", arr[i]);
        
        if (i < tamanho - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n; 
    int m; 
    int *alfa = NULL;
    int *beta = NULL;
    int *resultado = NULL;
    int total_tamanho;
    int i;

    printf("--- Intercalando Ondas de Inimigos (Algoritmo Merge) ---\n\n");

    
    printf("Portal Alfa: Digite o numero de inimigos (N): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Erro: N deve ser um inteiro nao-negativo.\n");
        return EXIT_FAILURE;
    }

    if (n > 0) {
        alfa = (int *)malloc(n * sizeof(int));
        if (alfa == NULL) {
            printf("Erro: Falha na alocacao de memoria para Onda Alfa.\n");
            return EXIT_FAILURE;
        }

        printf("Digite os %d niveis de ameaca do Portal Alfa (JA ORDENADOS CRESCENTEMENTE):\n", n);
        for (i = 0; i < n; i++) {
            printf("Ameaca Alfa %d: ", i + 1);
            if (scanf("%d", &alfa[i]) != 1 || alfa[i] < 0) {
                printf("Erro na leitura da ameaca.\n");
                free(alfa);
                return EXIT_FAILURE;
            }
        }
    }

    
    printf("\nPortal Beta: Digite o numero de inimigos (M): ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Erro: M deve ser um inteiro nao-negativo.\n");
        if (alfa) free(alfa);
        return EXIT_FAILURE;
    }

    if (m > 0) {
        beta = (int *)malloc(m * sizeof(int));
        if (beta == NULL) {
            printf("Erro: Falha na alocacao de memoria para Onda Beta.\n");
            if (alfa) free(alfa);
            return EXIT_FAILURE;
        }

        printf("Digite os %d niveis de ameaca do Portal Beta (JA ORDENADOS CRESCENTEMENTE):\n", m);
        for (i = 0; i < m; i++) {
            printf("Ameaca Beta %d: ", i + 1);
            if (scanf("%d", &beta[i]) != 1 || beta[i] < 0) {
                printf("Erro na leitura da ameaca.\n");
                if (alfa) free(alfa);
                free(beta);
                return EXIT_FAILURE;
            }
        }
    }

    
    total_tamanho = n + m;
    if (total_tamanho > 0) {
        
        resultado = (int *)malloc(total_tamanho * sizeof(int));
        if (resultado == NULL) {
            printf("Erro: Falha na alocacao de memoria para Resultado.\n");
            if (alfa) free(alfa);
            if (beta) free(beta);
            return EXIT_FAILURE;
        }

        
        intercalar_vetores(alfa, n, beta, m, resultado);

        
        printf("\n============================================\n");
        printf("Lista Unificada de Inimigos (Crescente):\n");
        imprimir_vetor(resultado, total_tamanho);
        printf("============================================\n");
    } else {
        printf("\nNenhuma onda de inimigos foi lida. Lista unificada vazia.\n");
    }
    
    // --- Liberação da Memória ---
    if (alfa) free(alfa);
    if (beta) free(beta);
    if (resultado) free(resultado);

    return EXIT_SUCCESS;
}