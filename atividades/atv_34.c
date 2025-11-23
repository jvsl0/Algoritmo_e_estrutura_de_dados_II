#include <stdio.h>


struct Heroi {
    int saude;
    int pontuacao;
    int posX;
    int posY;
};

int main() {
    
    struct Heroi meuHeroi = {
        .saude = 100,
        .pontuacao = 0,
        .posX = 0,
        .posY = 0
    };

    printf("--- Gerenciamento de Atributos do Heroi ---\n");
    
    
    printf("Estado Inicial:\n");
    printf("  Saude: %d, Pontuacao: %d, Posicao: (%d, %d)\n\n",
           meuHeroi.saude, meuHeroi.pontuacao, meuHeroi.posX, meuHeroi.posY);

    
    struct Heroi *ptrHeroi = &meuHeroi; 

    printf("--- Simulacao de Acoes (Usando Ponteiro ->) ---\n");

    

    
    ptrHeroi->saude -= 25;
    printf("1. Dano Recebido (-25). Nova Saude: %d\n", ptrHeroi->saude);

    
    ptrHeroi->pontuacao += 50;
    printf("2. Moedas Coletadas (+50). Nova Pontuacao: %d\n", ptrHeroi->pontuacao);

    
    ptrHeroi->posX += 10;
    ptrHeroi->posY -= 5;
    printf("3. Movimento (X+10, Y-5). Nova Posicao: (%d, %d)\n", ptrHeroi->posX, ptrHeroi->posY);
    
    printf("\n");

    
    printf("--- Estado Final Completo do Heroi ---\n");
    printf("Saude: %d\n", ptrHeroi->saude);
    printf("Pontuacao: %d\n", ptrHeroi->pontuacao);
    printf("Posicao X: %d\n", ptrHeroi->posX);
    printf("Posicao Y: %d\n", ptrHeroi->posY);

    return 0;
}