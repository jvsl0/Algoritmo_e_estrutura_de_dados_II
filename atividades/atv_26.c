#include <stdio.h>
#include <stdlib.h>


#define TAMANHO_INICIAL 3
#define TAMANHO_EXPANDIDO 6


int main() {
    
    int *mochila = NULL; 
    int i;

    printf("--- A Mochila Expansivel do Aventureiro ---\n");
    printf("Capacidade inicial da mochila: %d itens.\n\n", TAMANHO_INICIAL);

    
    mochila = (int *)malloc(TAMANHO_INICIAL * sizeof(int));

    
    if (mochila == NULL) {
        printf("Erro: Falha na alocacao inicial da mochila.\n");
        return 1;
    }

    
    printf("## Coletando os 3 primeiros itens ##\n");
    for (i = 0; i < TAMANHO_INICIAL; i++) {
        printf("Digite o valor do Item %d: ", i + 1);
        
        if (scanf("%d", &mochila[i]) != 1) {
            printf("Erro na leitura. Encerrando.\n");
            free(mochila);
            return 1;
        }
    }
    printf("\n");

    
    printf("Itens atualmente na mochila (%d de %d): ", TAMANHO_INICIAL, TAMANHO_INICIAL);
    for (i = 0; i < TAMANHO_INICIAL; i++) {
        printf("%d", mochila[i]);
        if (i < TAMANHO_INICIAL - 1) {
            printf(", ");
        }
    }
    printf("\n\n");

    
    printf(">>> Heroi encontrou um Item de Expansao de Mochila! <<<\n");
    printf("A capacidade sera dobrada de %d para %d.\n\n", TAMANHO_INICIAL, TAMANHO_EXPANDIDO);
    

    
    int *mochila_temporaria = (int *)realloc(mochila, TAMANHO_EXPANDIDO * sizeof(int));

    
    if (mochila_temporaria == NULL) {
        printf("Erro: Falha ao expandir a mochila (realloc falhou).\n");
        
        free(mochila); 
        return 1;
    }

    
    mochila = mochila_temporaria;
    printf("Mochila expandida com sucesso para %d espacos!\n\n", TAMANHO_EXPANDIDO);

    
    printf("## Coletando os 3 novos itens ##\n");
    
    for (i = TAMANHO_INICIAL; i < TAMANHO_EXPANDIDO; i++) {
        
        printf("Digite o valor do Item Novo %d: ", i - TAMANHO_INICIAL + 1); 
        if (scanf("%d", &mochila[i]) != 1) {
            printf("Erro na leitura. Encerrando.\n");
            free(mochila);
            return 1;
        }
    }
    printf("\n");

    
    printf("## Mochila Completa (%d itens) ##\n", TAMANHO_EXPANDIDO);
    printf("Itens na mochila: ");
    for (i = 0; i < TAMANHO_EXPANDIDO; i++) {
        printf("%d", mochila[i]);
        if (i < TAMANHO_EXPANDIDO - 1) {
            printf(", ");
        }
    }
    printf("\n\n");
    printf("Resultado: Os itens antigos (posicoes 0-2) foram mantidos e os novos (posicoes 3-5) foram adicionados.\n");

    
    free(mochila);
    printf("\nMemoria da mochila liberada com sucesso.\n");

    return 0;
}