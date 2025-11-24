#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char tipo[50];
    int hp;
} Inimigo;

int main() {
    int n; 
    int i;
    
    printf("--- Analise de Esquadrao Inimigo (O(n)) ---\n");

    
    printf("Digite a quantidade de unidades inimigas (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: O numero de unidades deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }
    
    
    Inimigo esquadrao[n]; 
    
    printf("\n## Leitura das Unidades ##\n");

    
    for (i = 0; i < n; i++) {
        
        printf("Unidade %d:\n", i + 1);
        
        
        printf("  Tipo (Ex: Orc, Troll): ");
        if (scanf("%49s", esquadrao[i].tipo) != 1) {
            printf("Erro na leitura do tipo da unidade.\n");
            return EXIT_FAILURE;
        }

        
        printf("  HP: ");
        if (scanf("%d", &esquadrao[i].hp) != 1) {
            printf("Erro na leitura do HP da unidade.\n");
            return EXIT_FAILURE;
        }

        
        printf(">>> Inimigo: %s, HP: %d\n", esquadrao[i].tipo, esquadrao[i].hp);
    }

    printf("\nAnalise de esquadrao concluida. %d unidades processadas.\n", n);

    return EXIT_SUCCESS;
}