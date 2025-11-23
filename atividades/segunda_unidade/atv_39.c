#include <stdio.h>
#include <stdlib.h>


#define NUM_INIMIGOS 3
#define LIMITE_ELITE 200.0


typedef struct {
    char nome[50];
    float hp;
    float atk;
    float nivel_ameaca; 
} Inimigo;

int main() {
    Inimigo lista_inimigos[NUM_INIMIGOS];
    FILE *arquivo;
    int i = 0;
    
    printf("--- Dragon's Grimoire: Analise de Inimigos ---\n");


    arquivo = fopen("inimigos.txt", "r");

    
    if (arquivo == NULL) {
        perror("ERRO: Falha ao abrir o arquivo inimigos.txt");
        printf("Certifique-se de que o arquivo esta no diretorio correto.\n");
        return 1;
    }

    
    printf("Lendo e calculando Nivel de Ameaca...\n");
    
    
    while (i < NUM_INIMIGOS && 
           fscanf(arquivo, "%s %f %f", 
                  lista_inimigos[i].nome, 
                  &lista_inimigos[i].hp, 
                  &lista_inimigos[i].atk) == 3) {

        
        lista_inimigos[i].nivel_ameaca = lista_inimigos[i].hp + lista_inimigos[i].atk;
        i++;
    }

    
    fclose(arquivo);
    
    
    int inimigos_lidos = i; 

    
    printf("\n## Inimigos de Elite (Nivel de Ameaca >= %.1f) ##\n", LIMITE_ELITE);
    int elite_encontrados = 0;

    for (i = 0; i < inimigos_lidos; i++) {
        if (lista_inimigos[i].nivel_ameaca >= LIMITE_ELITE) {
            printf("%s: %.1f\n", lista_inimigos[i].nome, lista_inimigos[i].nivel_ameaca);
            elite_encontrados++;
        }
    }

    if (elite_encontrados == 0) {
        printf("Nenhum inimigo de elite encontrado.\n");
    }
    
    printf("\nAnalise concluida.\n");

    return 0;
}