

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personagem.h"


#define MAX_NOME 50
#define MAX_CLASSE 30


struct personagem {
    char nome[MAX_NOME];
    char classe[MAX_CLASSE];
    int nivel;
    int hp;
};



Personagem* cria_party(int num_membros) {
    if (num_membros <= 0) {
        return NULL;
    }
   
    Personagem* party = (Personagem*)malloc(num_membros * sizeof(struct personagem));
    if (party == NULL) {
        perror("Erro ao alocar memoria para a Party");
        exit(EXIT_FAILURE);
    }
    return party;
}

void registra_membros(Personagem* party, int num_membros) {
    if (party == NULL || num_membros <= 0) return;

    printf("\n--- Registro dos Membros da Equipe ---\n");
    for (int i = 0; i < num_membros; i++) {
        printf("\n[%d/%d] Novo Membro:\n", i + 1, num_membros);

        
        int c; while ((c = getchar()) != '\n' && c != EOF); 

        
        printf("  Nome: ");
        if (fgets(party[i].nome, MAX_NOME, stdin) != NULL) {
            party[i].nome[strcspn(party[i].nome, "\n")] = '\0'; 
        }

        // Classe
        printf("  Classe: ");
        if (fgets(party[i].classe, MAX_CLASSE, stdin) != NULL) {
            party[i].classe[strcspn(party[i].classe, "\n")] = '\0'; 
        }

        
        printf("  Nivel: ");
        scanf("%d", &party[i].nivel);
        printf("  HP (Vida): ");
        scanf("%d", &party[i].hp);
    }
}

void exibe_relatorio(const Personagem* party, int num_membros) {
    if (party == NULL || num_membros <= 0) return;

    printf("\n==========================================\n");
    printf(" RELAToRIO DA EQUIPE (Total: %d Membro(s)) \n", num_membros);
    printf("==========================================\n");

    for (int i = 0; i < num_membros; i++) {
        printf("\n# Membro %d: %s\n", i + 1, party[i].nome);
        printf("    Classe: %s\n", party[i].classe);
        printf("    Nivel: %d\n", party[i].nivel);
        printf("    HP: %d\n", party[i].hp);
    }
    printf("\n==========================================\n");
}

void libera_party(Personagem* party) {
    
    free(party);
    printf("\nMemoria da Party liberada com sucesso.\n");
}