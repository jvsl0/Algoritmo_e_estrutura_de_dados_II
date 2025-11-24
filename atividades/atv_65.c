#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;


void insertion_sort_decrescente(Jogador *jogadores, int n) {
    int i, j;
    Jogador chave;

    
    for (i = 1; i < n; i++) {
        
        chave = jogadores[i];
        j = i - 1; 

        
        while (j >= 0 && jogadores[j].pontuacao < chave.pontuacao) {
            jogadores[j + 1] = jogadores[j]; 
            j = j - 1;
        }

        
        jogadores[j + 1] = chave;
    }
}


void imprimir_leaderboard(const Jogador *jogadores, int n) {
    int i;
    printf("\n## Ranking Final (Maior Pontuacao para a Menor) ##\n");
    printf("---------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        
        printf("%d %s\n", jogadores[i].pontuacao, jogadores[i].nome);
    }
    printf("---------------------------------------------------\n");
}

int main() {
    int n; 
    Jogador *leaderboard = NULL; 
    int i;

    printf("--- Leaderboard Arcade (Insertion Sort Decrescente) ---\n");

    
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
        
        printf("  Nome (ate 49 caracteres): ");
        
        if (fgets(leaderboard[i].nome, sizeof(leaderboard[i].nome), stdin) == NULL) { 
            goto erro_leitura; 
        }
        
        leaderboard[i].nome[strcspn(leaderboard[i].nome, "\n")] = 0;
        
        printf("  Pontuacao (inteiro): ");
        if (scanf("%d", &leaderboard[i].pontuacao) != 1 || leaderboard[i].pontuacao < 0) {
            printf("Erro: Pontuacao deve ser um numero nao-negativo.\n");
            goto erro_leitura; 
        }
    }

    
    insertion_sort_decrescente(leaderboard, n);

    
    imprimir_leaderboard(leaderboard, n);

   
    free(leaderboard);
    
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(leaderboard);
    return EXIT_FAILURE;
}