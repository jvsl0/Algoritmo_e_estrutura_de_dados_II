#include <stdio.h>
#include <stdlib.h>
#include "heroi/heroi.h" 

int main() {
    int num_herois;
    Heroi* equipe = NULL;

    printf(" Sistema de Montagem de Equipe \n");

    
    printf("Quantos herois farao parte da equipe para esta missao? ");
    if (scanf("%d", &num_herois) != 1 || num_herois <= 0) {
        printf("Quantidade invalida. Saindo do programa.\n");
        return 1;
    }

    
    int c; while ((c = getchar()) != '\n' && c != EOF); 

    
    equipe = alocar_roster(num_herois);
    if (equipe == NULL) {
        printf("Falha critica na alocação de memoria.\n");
        return 1;
    }

    
    ler_roster(equipe, num_herois);

    
    imprimir_roster(equipe, num_herois);

    
    free(equipe);
    printf("Memoria do roster liberada. Missao concluida.\n");

    return 0;
}