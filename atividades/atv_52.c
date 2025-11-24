#include <stdio.h>
#include <stdlib.h> 
#include <math.h>   


typedef struct {
    int x;
    int y;
} Unidade;


double calcular_distancia(Unidade u1, Unidade u2) {
    
    double delta_x = (double)u2.x - u1.x;
    double delta_y = (double)u2.y - u1.y;
    return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

int main() {
    int n;          
    Unidade *unidades = NULL;
    float raio_explosao;
    int duplas_proximas = 0;
    int i, j;
    
    printf("--- Analise de Proximidade de Inimigos (AoE) ---\n");

    // Leia o número de unidades n
    printf("Digite o numero de unidades inimigas (n): ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        printf("Erro: O numero de unidades deve ser um inteiro maior que 1.\n");
        return EXIT_FAILURE;
    }

    
    unidades = (Unidade *)malloc(n * sizeof(Unidade));
    if (unidades == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Leitura das Coordenadas ##\n");
    for (i = 0; i < n; i++) {
        printf("Unidade %d (x y): ", i + 1);
        if (scanf("%d %d", &unidades[i].x, &unidades[i].y) != 2) {
            printf("Erro na leitura das coordenadas.\n");
            free(unidades);
            return EXIT_FAILURE;
        }
    }
    
    
    printf("\nDigite o Raio de Explosao (float): ");
    if (scanf("%f", &raio_explosao) != 1 || raio_explosao <= 0) {
        printf("Erro: Raio invalido.\n");
        free(unidades);
        return EXIT_FAILURE;
    }

    
    printf("\n## Analisando Duplas de Proximidade (Raio <= %.2f) ##\n", raio_explosao);
    
    
    for (i = 0; i < n; i++) {
        
        for (j = i + 1; j < n; j++) {
            
            double distancia = calcular_distancia(unidades[i], unidades[j]);
            
            
            if (distancia <= raio_explosao) {
                duplas_proximas++;
                printf("  [Dupla Proxima] Unidade %d (%d,%d) <-> Unidade %d (%d,%d). Distancia: %.2f\n", 
                       i + 1, unidades[i].x, unidades[i].y,
                       j + 1, unidades[j].x, unidades[j].y,
                       distancia);
            }
        }
    }

    
    printf("\n-------------------------------------------------\n");
    printf("Total de duplas de inimigos dentro do raio: %d\n", duplas_proximas);
    printf("-------------------------------------------------\n");

    
    free(unidades);

    return EXIT_SUCCESS;
}