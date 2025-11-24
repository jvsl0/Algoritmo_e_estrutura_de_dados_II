#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int eliminacoes;
} Jogador;


void selection_sort_decrescente(Jogador *jogadores, int n) {
    int i, j, indice_max;
    Jogador temp;

    
    for (i = 0; i < n - 1; i++) {
        
        indice_max = i;

       
        for (j = i + 1; j < n; j++) {
            
            if (jogadores[j].eliminacoes > jogadores[indice_max].eliminacoes) {
                indice_max = j;
            }
        }

        
        if (indice_max != i) {
            temp = jogadores[i];
            jogadores[i] = jogadores[indice_max];
            jogadores[indice_max] = temp;
        }
    }
}


void imprimir_leaderboard(const Jogador *jogadores, int n) {
    int i;
    printf("\n## Leaderboard (Decrescente por Eliminacoes) ##\n");
    printf("----------------------------------------------\n");
    printf("%-5s | %-15s | %s\n", "Pos", "Nome", "Eliminacoes");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d | %-15s | %d\n", i + 1, jogadores[i].nome, jogadores[i].eliminacoes);
    }
    printf("----------------------------------------------\n");
}

int main() {
    int n; 
    Jogador *leaderboard = NULL; 
    int i;

    printf("--- Sistema de Leaderboard da Arena (Selection Sort) ---\n");

    
    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de jogadores deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    leaderboard = (Jogador *)malloc(n * sizeof(Jogador));
    if (leaderboard == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Cadastro dos Resultados dos Jogadores ##\n");
    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i + 1);
        
        
        while (getchar() != '\n'); 
        
        printf("  Nome: ");
        
        if (fgets(leaderboard[i].nome, sizeof(leaderboard[i].nome), stdin) == NULL) { 
            goto erro_leitura; 
        }
        
        leaderboard[i].nome[strcspn(leaderboard[i].nome, "\n")] = 0;
        
        printf("  Eliminacoes (Kills): ");
        if (scanf("%d", &leaderboard[i].eliminacoes) != 1 || leaderboard[i].eliminacoes < 0) {
            printf("Erro: Eliminacoes deve ser um numero nao-negativo.\n");
            goto erro_leitura; 
        }
    }

    
    selection_sort_decrescente(leaderboard, n);

    
    imprimir_leaderboard(leaderboard, n);

    
    free(leaderboard);
    
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(leaderboard);
    return EXIT_FAILURE;
}