#include <stdio.h>


struct Posicao {
    int x; 
    int y; 
};


void mover_personagem(struct Posicao *p_posicao, int movimento_x, int movimento_y) {
    
    
    
    p_posicao->x += movimento_x;
    
    
    p_posicao->y += movimento_y;
    
    printf("[FUNCAO] Movimento de (%d, %d) aplicado com sucesso!\n", movimento_x, movimento_y);
}

int main() {
    
    struct Posicao posicao_jogador = { .x = 0, .y = 0 };

    
    struct Posicao *ponteiro_posicao = &posicao_jogador;

   
    printf("--- Movimentando o Personagem no Mapa ---\n");
    printf("Posicao inicial do jogador: X=%d, Y=%d\n\n", 
           posicao_jogador.x, posicao_jogador.y);

    
    mover_personagem(ponteiro_posicao, 10, 5);

    printf("\n");

    
    printf("Posicao final do jogador: X=%d, Y=%d\n", 
           posicao_jogador.x, posicao_jogador.y);

    return 0;
}