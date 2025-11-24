#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 


typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Unidade;

void liberar_memoria(Unidade *ptr) {
    if (ptr != NULL) {
        free(ptr);
        printf("\nMemoria alocada dinamicamente liberada com sucesso.\n");
    }
}

int main() {
    int n; 
    Unidade *esquadrao = NULL; 
    int i;
    
    printf("--- Salvando um Esquadrao em Jogo de Estrategia ---\n");

    
    printf("Quantas unidades terao no esquadrao (n)? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: O numero de unidades deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    
    esquadrao = (Unidade *)malloc(n * sizeof(Unidade)); 
    if (esquadrao == NULL) {
        printf("Erro: Falha na alocacao de memoria para o esquadrao.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Cadastro das Unidades ##\n");
    for (i = 0; i < n; i++) {
        char nome_temp[50];
        
        printf("Unidade %d:\n", i + 1);
        printf("  Nome: ");
        if (scanf("%49s", nome_temp) != 1) { 
            liberar_memoria(esquadrao);
            return EXIT_FAILURE;
        }
        
        strcpy(esquadrao[i].nome, nome_temp);

        printf("  Vida (HP): ");
        if (scanf("%d", &esquadrao[i].vida) != 1) { 
            liberar_memoria(esquadrao);
            return EXIT_FAILURE;
        }

        printf("  Ataque (ATK): ");
        if (scanf("%d", &esquadrao[i].ataque) != 1) { 
            liberar_memoria(esquadrao);
            return EXIT_FAILURE;
        }
    }

    
    FILE *arquivo;
    
    arquivo = fopen("squad.dat", "wb");

    if (arquivo == NULL) {
        perror("\nERRO: Nao foi possivel abrir o arquivo squad.dat para escrita");
        liberar_memoria(esquadrao);
        return EXIT_FAILURE;
    }

    
    size_t itens_escritos = fwrite(esquadrao, sizeof(Unidade), n, arquivo);

    if (itens_escritos == n) {
        printf("\nSucesso! %zu unidades salvas em 'squad.dat'.\n", itens_escritos);
    } else {
        printf("\nERRO: Apenas %zu de %d unidades foram salvas. Dados incompletos.\n", itens_escritos, n);
    }

    
    fclose(arquivo);

    
    Unidade maior_ataque = esquadrao[0]; 

    for (i = 1; i < n; i++) {
        if (esquadrao[i].ataque > maior_ataque.ataque) {
            maior_ataque = esquadrao[i]; 
        }
    }
    

    printf("\n>>> Maior Ameaca no Esquadrao: %s (ATK: %d)\n", maior_ataque.nome, maior_ataque.ataque);

    
    liberar_memoria(esquadrao);

    return EXIT_SUCCESS;
}