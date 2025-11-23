#include <stdio.h>


struct Inimigo {
    int vida;        
    int ataque;      
    float velocidade; 
};


int main() {
    

    
    struct Inimigo cogumelo_zumbi = {
        .vida = 20,
        .ataque = 5,
        .velocidade = 0.8
    };

    
    struct Inimigo cavaleiro_esqueleto = {
        .vida = 80,
        .ataque = 15,
        .velocidade = 1.2
    };

    

    printf("--- Modelando Inimigos do Jogo (Usando Structs) ---\n\n");

    
    printf("--- Atributos do Inimigo: Cogumelo Zumbi ---\n");
    printf("Vida: %d\n", cogumelo_zumbi.vida);
    printf("Ataque: %d\n", cogumelo_zumbi.ataque);
    
    printf("Velocidade: %.1f\n", cogumelo_zumbi.velocidade);

    printf("\n");

    
    printf("--- Atributos do Inimigo: Cavaleiro Esqueleto ---\n");
    printf("Vida: %d\n", cavaleiro_esqueleto.vida);
    printf("Ataque: %d\n", cavaleiro_esqueleto.ataque);
    printf("Velocidade: %.1f\n", cavaleiro_esqueleto.velocidade);

    return 0;
}