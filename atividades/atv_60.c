#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int hp;
} Monstro;


int encontrar_alvo_mais_fraco(const Monstro *horda, int n);

int main() {
    int n; 
    Monstro *horda = NULL; 
    int i;
    int indice_alvo;

    printf("--- Identificador de Alvo Mais Fraco (RPG Tatico) ---\n");

    
    printf("Digite a quantidade de monstros na horda (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: A quantidade de monstros deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    horda = (Monstro *)malloc(n * sizeof(Monstro));
    if (horda == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Cadastro dos Monstros ##\n");
    for (i = 0; i < n; i++) {
        printf("\nMonstro %d:\n", i + 1);
        
        printf("  Nome (uma palavra): ");
        if (scanf("%49s", horda[i].nome) != 1) { goto erro_leitura; }
        
        printf("  HP (Pontos de Vida): ");
        if (scanf("%d", &horda[i].hp) != 1 || horda[i].hp < 0) { 
            printf("HP deve ser um numero nao-negativo.\n");
            goto erro_leitura; 
        }
    }

    
    indice_alvo = encontrar_alvo_mais_fraco(horda, n);

    
    printf("\n============================================\n");
    
    if (n > 0 && indice_alvo != -1) {
        printf("Alvo prioritario: %s (%d HP)\n", 
               horda[indice_alvo].nome, horda[indice_alvo].hp);
    } else if (n > 0) {
        
        printf("Erro: Nao foi possivel identificar o alvo mais fraco.\n");
    } else {
        printf("Nao ha monstros na horda.\n");
    }

    printf("============================================\n");

    
    free(horda);
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(horda);
    return EXIT_FAILURE;
}


int encontrar_alvo_mais_fraco(const Monstro *horda, int n) {
    
    if (n <= 0) {
        return -1;
    }

    int indice_min = 0; 
    int menor_hp = horda[0].hp;

    
    for (int i = 1; i < n; i++) {
        
        if (horda[i].hp < menor_hp) {
            menor_hp = horda[i].hp;
            indice_min = i;
        }
    }

    return indice_min;
}