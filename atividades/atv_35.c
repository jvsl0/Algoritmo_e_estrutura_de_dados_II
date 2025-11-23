#include <stdio.h>
#include <string.h> 

#define NUM_ITENS 3
#define TAMANHO_NOME 50


struct ItemColetavel {
    char nome[TAMANHO_NOME];
    int valor_pontos;
};


int main() {
    
    struct ItemColetavel inventario[NUM_ITENS];
    int i;
    
    
    char nome_temp[TAMANHO_NOME];

    printf("--- Simulacao de Inventario e Coleta de Itens (%d itens) ---\n\n", NUM_ITENS);

    
    for (i = 0; i < NUM_ITENS; i++) {
        printf("--- Item %d ---\n", i + 1);

        
        printf("Digite o nome do item: ");
        
        if (scanf("%49s", nome_temp) != 1) {
             printf("Erro na leitura do nome. Encerrando.\n");
             return 1;
        }
        
        strcpy(inventario[i].nome, nome_temp);

        
        printf("Digite o valor em pontos: ");
        if (scanf("%d", &inventario[i].valor_pontos) != 1) {
            printf("Erro na leitura dos pontos. Encerrando.\n");
            return 1;
        }
        printf("\n");
    }

    
    struct ItemColetavel item_mais_valioso = inventario[0];

    
    for (i = 1; i < NUM_ITENS; i++) {
        
        if (inventario[i].valor_pontos > item_mais_valioso.valor_pontos) {
            
            item_mais_valioso = inventario[i];
            
            
        }
    }

    
    printf("------------------------------------------\n");
    printf("Resultado do Inventario:\n");
    printf("O item mais valioso coletado foi: %s (Valor: %d pontos)\n", 
           item_mais_valioso.nome, item_mais_valioso.valor_pontos);
    printf("------------------------------------------\n");

    return 0;
}