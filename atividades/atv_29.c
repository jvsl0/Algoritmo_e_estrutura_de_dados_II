#include <stdio.h>


struct ItemColetavel {
    int valor_pontos; 
    float peso;       
};


int main() {
    

    struct ItemColetavel moeda_bronze = {
        .valor_pontos = 10,
        .peso = 0.5f 
    };

    struct ItemColetavel moeda_prata = {
        .valor_pontos = 50,
        .peso = 0.7f
    };

    struct ItemColetavel moeda_ouro = {
        .valor_pontos = 100,
        .peso = 1.0f 
    };

    
    int pontuacao_jogador = 0;

    printf("--- Simulacao de Coleta de Itens ---\n");
    printf("Pontuacao inicial do jogador: %d\n", pontuacao_jogador);
    

    pontuacao_jogador += moeda_ouro.valor_pontos;

    
    printf("\nMoeda de ouro coletada! Pontuacao atual: %d\n", pontuacao_jogador);
    
    return 0;
}