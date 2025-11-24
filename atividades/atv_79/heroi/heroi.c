
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heroi.h"


#define TAM_NOME 50

struct Heroi {
    char nome[TAM_NOME];
    int hp;
    int ataque;
};



Heroi* alocar_roster(int quantidade) {
   
    Heroi* roster = (Heroi*)malloc(quantidade * sizeof(struct Heroi));
    if (roster == NULL) {
        perror("Erro ao alocar memoria para o roster.");
        exit(EXIT_FAILURE);
    }
    return roster;
}

void ler_roster(Heroi* roster, int quantidade) {
    if (roster == NULL) return;

    printf("\n--- Preenchendo o Roster de Herois ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nHeroi %d:\n", i + 1);
        
        
        printf("Nome: ");
        
        int c; while ((c = getchar()) != '\n' && c != EOF);
        if (fgets(roster[i].nome, TAM_NOME, stdin) != NULL) {
            
            roster[i].nome[strcspn(roster[i].nome, "\n")] = '\0'; 
        }

        
        printf("Pontos de Vida (HP): ");
        scanf("%d", &roster[i].hp);

        
        printf("Poder de Ataque: ");
        scanf("%d", &roster[i].ataque);
    }
    
    int c; while ((c = getchar()) != '\n' && c != EOF); 
}

void imprimir_roster(const Heroi* roster, int quantidade) {
    if (roster == NULL) return;
    
    printf("\n=====================================\n");
    printf(" ROSTER FINAL DA EQUIPE (Total: %d Heroi(s)) \n", quantidade);
    printf("=====================================\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n# Heroi %d: **%s**\n", i + 1, roster[i].nome);
        printf("    HP: %d\n", roster[i].hp);
        printf("    Ataque: %d\n", roster[i].ataque);
    }
    printf("\n=====================================\n");
}