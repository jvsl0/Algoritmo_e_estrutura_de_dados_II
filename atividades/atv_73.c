#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void particao(int n, int v[]) {
    if (n == 0) return; 
    int pivo = v[n - 1];

    
    int *s = (int *)malloc(n * sizeof(int));
    if (s == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o vetor secundario.\n");
        return;
    }

    int indice_inicio = 0; 
    int indice_fim = n - 1; 

    
    for (int i = 0; i < n - 1; i++) {
        if (v[i] <= pivo) {
            
            s[indice_inicio] = v[i];
            indice_inicio++;
        } else {
            
            s[indice_fim] = v[i];
            indice_fim--;
        }
    }

    
    s[indice_inicio] = pivo;

    
    memcpy(v, s, n * sizeof(int));

    
    free(s);
}

int main() {
    int n; 
    int i;

    printf("--- Triagem Rapida de Itens (Particao Quick Sort) ---\n\n");

    
    printf("Digite a quantidade de itens no bau (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    int *niveis_poder = (int *)malloc(n * sizeof(int));
    if (niveis_poder == NULL) {
        printf("Erro: Falha na alocacao de memoria para os niveis de poder.\n");
        return EXIT_FAILURE;
    }

    printf("Digite o nivel de poder para cada um dos %d itens:\n", n);
    for (i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        if (scanf("%d", &niveis_poder[i]) != 1) {
            printf("Erro na leitura do nivel de poder.\n");
            free(niveis_poder);
            return EXIT_FAILURE;
        }
    }

    
    printf("\nO Pivô (ultimo item, nivel %d) sera usado como referencia.\n", niveis_poder[n-1]);

    
    particao(n, niveis_poder);

    
    printf("\n========================================================\n");
    printf("Lista de itens apos a triagem rapida (particao):\n");
    for (i = 0; i < n; i++) {
        printf("%d", niveis_poder[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n========================================================\n");

    
    free(niveis_poder);

    return EXIT_SUCCESS;
}