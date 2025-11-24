#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PLACAR 5


void imprimir_placar(const int *placar) {
    int i;
    for (i = 0; i < TAMANHO_PLACAR; i++) {
        printf("%d", placar[i]);
        if (i < TAMANHO_PLACAR - 1) {
            printf(" | ");
        }
    }
    printf("\n");
}


void inserir_novo_recorde(int *placar, int novo_tempo) {
    
    if (novo_tempo >= placar[TAMANHO_PLACAR - 1]) {
        printf("O tempo %d e muito lento para entrar no Top 5 atual.\n", novo_tempo);
        return;
    }

    
    
    int i = TAMANHO_PLACAR - 2; 

    
    while (i >= 0 && placar[i] > novo_tempo) {
        placar[i + 1] = placar[i]; 
        i--;
    }

    
    placar[i + 1] = novo_tempo;
    printf("NOVO RECORD: %d inserido com sucesso!\n", novo_tempo);
}

int main() {
    
    int placar[TAMANHO_PLACAR] = {120, 125, 130, 142, 150}; 
    int novo_tempo;

    printf("--- Sistema de Leaderboard Top 5 (Corrida Arcade) ---\n");
    printf("Placar Atual (Tempos em segundos, Crescente):\n");
    imprimir_placar(placar);

   
    printf("\nDigite o novo tempo de corrida do jogador (inteiro): ");
    if (scanf("%d", &novo_tempo) != 1 || novo_tempo <= 0) {
        printf("Erro: Tempo invalido.\n");
        return EXIT_FAILURE;
    }

    
    inserir_novo_recorde(placar, novo_tempo);

    
    printf("\n========================================\n");
    printf("Placar Atualizado (Top 5):\n");
    printf("Posicao 1 (Mais Rapido): %d\n", placar[0]);
    printf("Placar Completo: ");
    imprimir_placar(placar);
    printf("========================================\n");
    
    return EXIT_SUCCESS;
}