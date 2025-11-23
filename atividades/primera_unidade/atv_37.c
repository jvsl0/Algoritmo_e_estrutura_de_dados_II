#include <stdio.h>
#include <string.h> 


struct Atributos {
    int vida;
    int pontuacao;
};


struct Personagem {
    char nome[50];
    struct Atributos stats; 
};

int main() {
    
    struct Personagem jogador;
    char nome_digitado[50]; 

    printf("--- Personagem e Seus Atributos ---\n");
    
    
    printf("Digite o nome do seu personagem: ");
    
    if (scanf("%49s", nome_digitado) != 1) {
        printf("Erro na leitura do nome.\n");
        return 1;
    }
    
    strcpy(jogador.nome, nome_digitado);

    
    jogador.stats.vida = 100;
    jogador.stats.pontuacao = 0;

    
    printf("\nStatus Inicial -> Nome: %s | Vida: %d | Pontuacao: %d\n",
           jogador.nome, jogador.stats.vida, jogador.stats.pontuacao);

    
    jogador.stats.pontuacao += 10;
    printf("\n[Acao] Coletou uma moeda! (+10 pontos)\n");

    
    jogador.stats.vida -= 25;
    printf("[Acao] Sofreu dano! (-25 vida)\n");

    
    printf("\nStatus Final -> Nome: %s | Vida: %d | Pontuacao: %d\n",
           jogador.nome, jogador.stats.vida, jogador.stats.pontuacao);

    return 0;
}