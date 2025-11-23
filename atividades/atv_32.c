#include <stdio.h>


struct Personagem {
    int posX;
    int posY;
    int moedas;
};


struct Personagem atualizarPersonagem(struct Personagem p) {
    printf("[Funcao] Movimentando por Passagem de Valor...\n");
   
    p.posX = 10;
    p.posY = 5;
    p.moedas += 1; 

    
    return p;
}

int main() {
    struct Personagem jogador;

    
    jogador.posX = 0;
    jogador.posY = 0;
    jogador.moedas = 0;

    printf("--- Opcao 1: Passagem por Valor (Retorno de Struct) ---\n");
    printf("Posicao inicial: (%d, %d) - Moedas: %d\n\n", 
           jogador.posX, jogador.posY, jogador.moedas);

    
    jogador = atualizarPersonagem(jogador); 
    
    printf("\nPosicao atualizada: (%d, %d) - Moedas: %d\n", 
           jogador.posX, jogador.posY, jogador.moedas);

    return 0;
}