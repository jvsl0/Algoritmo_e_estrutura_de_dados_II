#include <stdio.h>


typedef enum {
    PARADO,   // 0
    CORRENDO, // 1
    PULANDO   // 2
} EstadoPersonagem;


int main() {
    int entrada_numerica;
    
    
    EstadoPersonagem estado_atual;

    printf("--- Estado do Personagem no Jogo de Plataforma ---\n");
    

    printf("Digite o numero correspondente ao estado:\n");
    printf("0 - PARADO\n");
    printf("1 - CORRENDO\n");
    printf("2 - PULANDO\n");
    printf("Escolha: ");
    
    
    if (scanf("%d", &entrada_numerica) != 1) {
        printf("Erro na leitura da entrada.\n");
        return 1;
    }

    
    estado_atual = (EstadoPersonagem)entrada_numerica;

    printf("\n");

    
    if (estado_atual == PARADO) {
        printf("O personagem esta parado.\n");
    } else if (estado_atual == CORRENDO) {
        printf("O personagem esta correndo!\n");
    } else if (estado_atual == PULANDO) {
        printf("O personagem esta pulando no ar!\n");
    } else {
        
        printf("Estado invalido!\n");
    }
    
    printf("\nValor numerico do estado: %d\n", estado_atual);

    return 0;
}