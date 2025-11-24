#include <stdio.h>
#include <stdlib.h> 

#define NOME_ARQUIVO "level_1_map.dat"

int main() {
    FILE *arquivo;

    printf("--- Simulacao de Carregamento Seguro de Assets ---\n");
    printf("Tentando abrir o arquivo: %s\n", NOME_ARQUIVO);

    
    arquivo = fopen(NOME_ARQUIVO, "r");

    
    if (arquivo == NULL) {
        
        
        printf("\nERRO CRITICO: Nao foi possivel carregar os dados do mapa.\n");
        
        
        perror("Detalhes do erro");

        
        exit(1);
    }

    
    printf("Sucesso! O arquivo foi carregado. (Isso nao deve ocorrer neste teste).\n");
    
    
    fclose(arquivo);

    return EXIT_SUCCESS;
}