#include <stdio.h>
#include <stdlib.h> 


typedef struct {
    int posicao_x;
    int posicao_y;
    int valor;
} Moeda;


int main() {
    int num_moedas;
    
    Moeda *vetor_moedas = NULL; 
    int i;
    int total_pontos = 0;

    printf("--- Coletando Moedas no Nivel ---\n");

    
    printf("Quantas moedas o nivel tera? ");
    if (scanf("%d", &num_moedas) != 1 || num_moedas <= 0) {
        printf("Erro: Por favor, digite um numero inteiro positivo.\n");
        return 1;
    }
    printf("\n");

    
    vetor_moedas = (Moeda *)malloc(num_moedas * sizeof(Moeda));

    
    if (vetor_moedas == NULL) {
        printf("Erro: Falha na alocacao de memoria para as moedas.\n");
        return 1;
    }

    
    printf("## Cadastro das Moedas ##\n");
    for (i = 0; i < num_moedas; i++) {
        printf("--- Moeda %d ---\n", i + 1);

        
        printf("Posicao X: ");
        if (scanf("%d", &vetor_moedas[i].posicao_x) != 1) { goto erro_leitura; }

        printf("Posicao Y: ");
        if (scanf("%d", &vetor_moedas[i].posicao_y) != 1) { goto erro_leitura; }

        printf("Valor em pontos: ");
        if (scanf("%d", &vetor_moedas[i].valor) != 1) { goto erro_leitura; }
        printf("\n");
    }

    
    for (i = 0; i < num_moedas; i++) {
        total_pontos += vetor_moedas[i].valor;
    }

    
    printf("----------------------------------\n");
    printf("Pontuacao maxima do nivel: %d\n", total_pontos);
    printf("----------------------------------\n");

    
    free(vetor_moedas);
    printf("Memoria alocada para as moedas liberada com sucesso.\n");

    return 0;

erro_leitura:
    printf("Erro na leitura dos dados. Encerrando.\n");
    if (vetor_moedas != NULL) {
        free(vetor_moedas);
    }
    return 1;
}