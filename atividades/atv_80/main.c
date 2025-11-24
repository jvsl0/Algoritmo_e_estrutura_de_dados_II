
#include <stdio.h>
#include <stdlib.h>
#include "personagem.h" 

int main() {
    int num_membros;
    
    Personagem* party = NULL;

    printf("Gerenciador de Equipes RPG \n");

    
    printf("Defina o numero de membros da equipe: ");
    if (scanf("%d", &num_membros) != 1 || num_membros <= 0) {
        printf("Número invalido. Encerrando.\n");
        return 1;
    }

    
    party = cria_party(num_membros);
    if (party == NULL) {
        printf("Falha na alocação da equipe.\n");
        return 1;
    }

    
    registra_membros(party, num_membros);

    
    exibe_relatorio(party, num_membros);

    
    libera_party(party);

    return 0;
}