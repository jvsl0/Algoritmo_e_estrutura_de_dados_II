//Atividade 1
#include<stdio.h>

int main(){
    //!showMemory(start=65520)
    
    // Variável de Vida
    int vida_jogador = 100;
    
    // Ponteiro de Vida
    int *ponteiro_vida;
    
    // Ponteiro de Vida
    printf("vida atual do jogador: %d\n", vida_jogador);
    
    // Simulando Dano
    vida_jogador = 50;
    printf("o jogador sofreu dano! Vida atual: %d\n", vida_jogador);
    
    // Conectando o ponteiro ao endereço da variável
    ponteiro_vida = &vida_jogador;
    
    // Usando Power-up (restaurando vida com o ponteiro)
    *ponteiro_vida = 100;
    printf("Power-up coletado! Vida restaurada: %d\n", vida_jogador);
    
    return 0;
}