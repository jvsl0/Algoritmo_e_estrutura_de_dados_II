#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int pontuacao;
} Jogador;


void bubble_sort_decrescente(Jogador *arr, int n) {
    int i, j;
    Jogador temp;

   
    for (i = 0; i < n - 1; i++) {
        
        for (j = 0; j < n - i - 1; j++) {
            
            if (arr[j].pontuacao < arr[j + 1].pontuacao) {
                
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void imprimir_leaderboard(const Jogador *jogadores, int n) {
    int i;
    printf("\n## Placar Final (Decrescente por Pontuacao) ##\n");
    printf("---------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("%d %d\n", jogadores[i].id, jogadores[i].pontuacao);
    }
    printf("---------------------------------------------\n");
}

int main() {
    int n; 
    Jogador *leaderboard = NULL; 
    int i;

    printf("--- Leaderboard da Arena de Batalha (Bubble Sort Struct) ---\n");

    
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

    
    printf("\n## Cadastro dos Jogadores (ID e Pontuacao) ##\n");
    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i + 1);
        
        printf("  ID (inteiro): ");
        if (scanf("%d", &leaderboard[i].id) != 1) { goto erro_leitura; }
        
        printf("  Pontuacao (inteiro): ");
        if (scanf("%d", &leaderboard[i].pontuacao) != 1) { goto erro_leitura; }
    }

    
    bubble_sort_decrescente(leaderboard, n);

    
    imprimir_leaderboard(leaderboard, n);

    
    free(leaderboard);
    
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    
    free(leaderboard);
    return EXIT_FAILURE;
}