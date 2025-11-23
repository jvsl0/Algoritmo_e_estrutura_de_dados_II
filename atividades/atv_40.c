#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 


typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

int main() {
    int n; 
    Jogador *vetor_jogadores = NULL;
    int i;
    
    
    printf("Digite o numero de jogadores na partida (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: Numero de jogadores invalido.\n");
        return 1;
    }
    
    
    vetor_jogadores = (Jogador *)malloc(n * sizeof(Jogador));
    if (vetor_jogadores == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return 1;
    }

    
    printf("\n--- Cadastro dos Jogadores ---\n");
    for (i = 0; i < n; i++) {
        char nome_temp[50];
        
        printf("Jogador %d:\n", i + 1);
        printf("  Nome: ");
        if (scanf("%49s", nome_temp) != 1) { 
            free(vetor_jogadores);
            printf("Erro na leitura do nome.\n");
            return 1;
        }
        strcpy(vetor_jogadores[i].nome, nome_temp);

        printf("  Pontuacao: ");
        if (scanf("%d", &vetor_jogadores[i].pontuacao) != 1) {
            free(vetor_jogadores);
            printf("Erro na leitura da pontuacao.\n");
            return 1;
        }
    }
    
    
    Jogador recordista = vetor_jogadores[0]; 

    for (i = 1; i < n; i++) {
        if (vetor_jogadores[i].pontuacao > recordista.pontuacao) {
            recordista = vetor_jogadores[i]; 
        }
    }
    
    
    FILE *arquivo = fopen("highscore.txt", "w");

    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir/criar highscore.txt.\n");
        free(vetor_jogadores);
        return 1;
    }
    
    
    fprintf(arquivo, "Nome: %s, Pontuacao: %d", recordista.nome, recordista.pontuacao);
    
    printf("\nRecorde salvo com sucesso em 'highscore.txt'!\n");

    
    fclose(arquivo);
    free(vetor_jogadores); 

    return 0;
}