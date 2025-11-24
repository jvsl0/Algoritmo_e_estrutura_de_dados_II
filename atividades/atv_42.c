#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int resolucao_x;
    int resolucao_y;
    float volume_som;
} Configuracao;

int main() {
    FILE *arquivo;
    Configuracao config_jogo;
    
    printf("--- Verificacao de Arquivo de Configuracao ---\n");

    
    arquivo = fopen("config.txt", "r");

    
    if (arquivo == NULL) {
        printf("Erro: Arquivo config.txt nao encontrado!\n");
        
        return EXIT_FAILURE; 
    }

    
    printf("Arquivo config.txt aberto com sucesso. Carregando dados...\n");

    
    if (fscanf(arquivo, "%d %d %f", 
               &config_jogo.resolucao_x, 
               &config_jogo.resolucao_y, 
               &config_jogo.volume_som) != 3) {
        
        printf("Erro: Falha na leitura dos dados do arquivo.\n");
        
        fclose(arquivo); 
        return EXIT_FAILURE;
    }
    
    
    fclose(arquivo);

    
    printf("\nConfiguracoes carregadas:\n");
    printf("Resolucao: %dx%d\n", config_jogo.resolucao_x, config_jogo.resolucao_y);
    printf("Volume: %.1f\n", config_jogo.volume_som);

    return EXIT_SUCCESS;
}