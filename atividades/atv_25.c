#include <stdio.h>
#include <stdlib.h>


int main() {
    int num_inimigos;
    
    int *status_inimigos = NULL; 
    int i;

    
    printf("--- Carregamento de Fase ---\n");
    printf("Quantos inimigos a fase tera? ");
    
    
    if (scanf("%d", &num_inimigos) != 1 || num_inimigos <= 0) {
        printf("Erro: Por favor, digite um numero inteiro positivo.\n");
        return 1; 
    }
    printf("\n");

    
    status_inimigos = (int *)calloc(num_inimigos, sizeof(int));

    
    if (status_inimigos == NULL) {
        printf("Erro: Falha na alocacao de memoria para os inimigos.\n");
        return 1; // Retorna com erro
    }

    
    printf("## Status Inicial dos Inimigos (Apos calloc) ##\n");
    printf("Status esperado (calloc): Todos **Inativos (0)**\n");
    for (i = 0; i < num_inimigos; i++) {
        
        printf("Inimigo %d: Inativo (%d)\n", i + 1, status_inimigos[i]);
    }
    printf("\n");

    
    printf("## Ativando Inimigos na Fase ##\n");
    printf("Alterando o status de todos os inimigos para **Ativo (1)**...\n");
    
    for (i = 0; i < num_inimigos; i++) {
        status_inimigos[i] = 1; 
    }
    printf("Todos os %d inimigos foram ativados.\n\n", num_inimigos);

    
    printf("## Relatorio Final de Status ##\n");
    printf("Status esperado: Todos **Ativos (1)**\n");
    for (i = 0; i < num_inimigos; i++) {
        printf("Inimigo %d: Ativo (%d)\n", i + 1, status_inimigos[i]);
    }
    printf("\n");

    
    free(status_inimigos);
    printf("Memoria alocada para os inimigos liberada com sucesso.\n");
    printf("--- Fim do Carregamento de Fase ---\n");

    return 0; 
}