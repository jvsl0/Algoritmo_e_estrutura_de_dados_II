#include <stdio.h>


struct Jogador {
    float pos_x;          
    int pontuacao;      
    int tem_pulo_duplo; 
};


int main() {
    
    struct Jogador heroi;

    
    heroi.pos_x = 50.0f;
    heroi.pontuacao = 0;
    heroi.tem_pulo_duplo = 0; 

    
    const char *pulo_duplo_status;

    
    
    
    pulo_duplo_status = (heroi.tem_pulo_duplo == 1) ? "Sim" : "Nao";
    
    printf("--- Estado do Personagem ---\n");
    printf("Inicio da fase! Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n\n",
           heroi.pos_x, heroi.pontuacao, pulo_duplo_status);

    
    
    printf(">> Acoes do Heroi no Jogo <<\n");
    
    
    heroi.pontuacao += 10;
    printf("Heroi coletou uma moeda! Pontos +10.\n");

    
    heroi.tem_pulo_duplo = 1;
    printf("Heroi coletou o Power-up de Pulo Duplo!\n\n");

    
    pulo_duplo_status = (heroi.tem_pulo_duplo == 1) ? "Sim" : "Nao";

    printf("--- Relatorio Final (Apos Acoes) ---\n");
    printf("Itens coletados! Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n",
           heroi.pos_x, heroi.pontuacao, pulo_duplo_status);

    return 0;
}