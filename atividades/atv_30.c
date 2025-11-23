#include <stdio.h>
#include <string.h> 


struct Jogador {
    char nome[50];    
    int vidas;        
    int pontuacao;    
};


int main() {
    
    struct Jogador player1;
    
    
    player1.vidas = 3;
    player1.pontuacao = 0;

    
    char nome_digitado[50]; 

    printf("--- Tela de Criacao de Personagem ---\n");
    
    
    printf("Digite o nome do seu personagem: ");
    
    if (scanf("%49s", nome_digitado) != 1) {
        printf("Erro ao ler o nome. Encerrando.\n");
        return 1;
    }

    
    strcpy(player1.nome, nome_digitado);

    printf("\n--- Criacao Concluida ---\n");
    printf("Personagem criado! Bem-vindo, %s! Vidas: %d, Pontuacao: %d\n",
           player1.nome, player1.vidas, player1.pontuacao);

    return 0;
}