#include <stdio.h>
#include <stdlib.h>

int main() {
    int energia_golem;
    int pulso = 0;

    printf("--- Ritual de Diminuicao Arcana ---\n");
    
    
    printf("Digite o nivel de energia inicial do Golem (inteiro positivo): ");
    if (scanf("%d", &energia_golem) != 1 || energia_golem <= 1) {
        printf("Erro: A energia deve ser um inteiro maior que 1 para iniciar o ritual.\n");
        return EXIT_FAILURE;
    }
    
    printf("\nRitual Iniciado:\n");

    
    while (energia_golem > 1) {
        pulso++;
        
        
        printf("Pulso %d: Energia atual = %d\n", pulso, energia_golem);
        
        
        energia_golem = energia_golem / 2; 
    }
    
    printf("\nRitual Concluido! Energia final = %d.\n", energia_golem);

    return EXIT_SUCCESS;
}