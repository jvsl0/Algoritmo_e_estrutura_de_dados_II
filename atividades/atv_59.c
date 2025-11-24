#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[50];
    int hp;
    int ataque;
} Monstro;


int busca_binaria_recursiva(const Monstro *lista, int id_busca, int esquerda, int direita) {
    
    if (esquerda > direita) {
        return -1; 
    }

    
    int meio = esquerda + (direita - esquerda) / 2;

   
    if (lista[meio].id == id_busca) {
        return meio; 
    }

    
    if (lista[meio].id > id_busca) {
        return busca_binaria_recursiva(lista, id_busca, esquerda, meio - 1);
    }

    
    return busca_binaria_recursiva(lista, id_busca, meio + 1, direita);
}

int main() {
    int n; 
    Monstro *bestiario = NULL; 
    int i;
    
    printf("--- Simulador de Busca Eficiente no Bestiario (Recursivo) ---\n");

    
    printf("Digite o numero total de monstros a catalogar (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: Numero de monstros invalido.\n");
        return EXIT_FAILURE;
    }

    
    bestiario = (Monstro *)malloc(n * sizeof(Monstro));
    if (bestiario == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Catalogando Monstros (IDs DEVE estar em ordem crescente) ##\n");
    for (i = 0; i < n; i++) {
        printf("\nMonstro %d:\n", i + 1);
        
        printf("  ID (inteiro, crescente): ");
        if (scanf("%d", &bestiario[i].id) != 1) { goto erro_leitura; }
        
        printf("  Nome (uma palavra): ");
        if (scanf("%49s", bestiario[i].nome) != 1) { goto erro_leitura; }
        
        printf("  HP (Saude): ");
        if (scanf("%d", &bestiario[i].hp) != 1) { goto erro_leitura; }
        
        printf("  Ataque: ");
        if (scanf("%d", &bestiario[i].ataque) != 1) { goto erro_leitura; }
    }

    
    int id_consulta;
    int indice_encontrado;

    printf("\n=========================================================\n");
    printf("              MODO DE CONSULTA DO BESTIARIO\n");
    printf("  Digite o ID do monstro para buscar (0 para sair).\n");
    printf("=========================================================\n");

    while (1) {
        printf("\nBuscar ID: ");
        if (scanf("%d", &id_consulta) != 1) {
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ID de busca invalido.\n");
            continue;
        }

        if (id_consulta == 0) {
            printf("\nEncerrando Bestiario. Bom jogo!\n");
            break; 
        }
        
        
        indice_encontrado = busca_binaria_recursiva(bestiario, id_consulta, 0, n - 1);

        if (indice_encontrado != -1) {
            
            Monstro m = bestiario[indice_encontrado];
            
            printf("Monstro Encontrado: %s (ID: %d) - HP: %d, Ataque: %d\n", 
                   m.nome, m.id, m.hp, m.ataque);
        } else {
            
            printf("Monstro com ID %d nao encontrado.\n", id_consulta);
        }
    }

    
    free(bestiario);
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(bestiario);
    return EXIT_FAILURE;
}