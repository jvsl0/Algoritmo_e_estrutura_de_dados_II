#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    int pontos;
} Conquista;

int main() {
    FILE *arquivo;
    int N; 
    int total_pontos = 0;
    Conquista conquista_atual;
    int i;

    printf("--- Atualizacao de Log de Sessao de Jogo ---\n");

    
    arquivo = fopen("player_log.txt", "r+");

    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo player_log.txt");
        printf("Certifique-se de que o arquivo existe no diretorio.\n");
        return EXIT_FAILURE;
    }
    
    

    
    if (fscanf(arquivo, "%d", &N) != 1) {
        printf("ERRO: Falha ao ler o numero N de conquistas.\n");
        fclose(arquivo);
        return EXIT_FAILURE;
    }
    
    printf("Numero de conquistas a ler: %d\n", N);

    
    for (i = 0; i < N; i++) {
        
        if (fscanf(arquivo, "%d %d", &conquista_atual.id, &conquista_atual.pontos) != 2) {
            printf("AVISO: Leitura interrompida antes do final esperado (Conquista %d).\n", i + 1);
            break; 
        }
        total_pontos += conquista_atual.pontos;
    }

    
    printf("Total de pontos de experiencia ganhos na sessao: %d\n", total_pontos);
    
    
    
    
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        perror("ERRO: Falha ao mover o ponteiro para o final do arquivo");
        fclose(arquivo);
        return EXIT_FAILURE;
    }
    
    
    fprintf(arquivo, "\n--- SESSION CONCLUDED ---\n");
    
    printf("Marcador de 'Sessao Concluida' adicionado ao log.\n");

    
    fclose(arquivo);

    return EXIT_SUCCESS;
}