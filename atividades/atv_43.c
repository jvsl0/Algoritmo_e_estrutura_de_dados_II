#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Inimigo;

int main() {
    FILE *arquivo;
    
    Inimigo inimigo_atual;
    
    Inimigo maior_ameaca = {"Nenhum", 0, -1}; 
    int inimigos_lidos = 0;

    printf("--- Identificando a Maior Ameaça na Horda ---\n");

    
    arquivo = fopen("wave_data.txt", "r");

    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo wave_data.txt");
        printf("Certifique-se de que o arquivo esta no diretorio correto.\n");
        return EXIT_FAILURE;
    }

    printf("Lendo dados de inimigos...\n");

    
    while (fscanf(arquivo, "%s %d %d", 
                  inimigo_atual.nome, 
                  &inimigo_atual.vida, 
                  &inimigo_atual.ataque) == 3) {
        
        inimigos_lidos++;

        
        if (inimigo_atual.ataque > maior_ameaca.ataque) {
            
            maior_ameaca = inimigo_atual;
        }
    }

    
    fclose(arquivo);

    printf("\nAnalise de %d inimigos concluida.\n", inimigos_lidos);

    
    if (maior_ameaca.ataque != -1) {
        printf("Maior Ameaca: %s, Vida: %d, Ataque: %d\n", 
               maior_ameaca.nome, maior_ameaca.vida, maior_ameaca.ataque);
    } else {
        printf("Nenhum inimigo valido encontrado no arquivo.\n");
    }

    return EXIT_SUCCESS;
}