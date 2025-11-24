#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void particao(int n, int v[]) {
    if (n <= 1) return; 
    int l = 0;
    int r = n - 1;

    
    int pivo = v[r];

   
    int i = l - 1;

    
    for (int j = l; j < r; j++) {
        
        if (v[j] < pivo) {
            
            i++;
            
            troca(&v[i], &v[j]);
        }
        
    }

    
    troca(&v[i + 1], &v[r]); 
}

int main() {
    int n; 
    int i;

    printf("--- Triagem de Unidades Mecha para Reparo (Particao In-Place) ---\n\n");

    
    printf("Digite o numero de unidades mecha (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    int *hp_unidades = (int *)malloc(n * sizeof(int));
    if (hp_unidades == NULL) {
        printf("Erro: Falha na alocacao de memoria para os HPs.\n");
        return EXIT_FAILURE;
    }

    printf("Digite os Pontos de Vida (HP) de cada uma das %d unidades:\n", n);
    for (i = 0; i < n; i++) {
        printf("Unidade %d HP: ", i + 1);
        if (scanf("%d", &hp_unidades[i]) != 1 || hp_unidades[i] < 0) {
            printf("Erro na leitura ou HP invalido.\n");
            free(hp_unidades);
            return EXIT_FAILURE;
        }
    }

    
    printf("\nO HP da ultima unidade (%d) sera usado como limiar de dano (Pivo).\n", hp_unidades[n-1]);

    
    particao(n, hp_unidades);

    
    printf("\n========================================================\n");
    printf("Lista de HPs apos a triagem (Mechas para Reparo no inicio):\n");
    for (i = 0; i < n; i++) {
        printf("%d", hp_unidades[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n========================================================\n");

    
    free(hp_unidades);

    return EXIT_SUCCESS;
}