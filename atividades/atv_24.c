#include <stdio.h>
#include <stdlib.h> // Para malloc e free

int main() {
    int linhas, colunas;
    int **mapa = NULL;
    int blocos_tijolo = 0;


    printf("--- Construcao Simplificada do Mapa ---\n");
    printf("Digite o numero de **linhas** (altura): ");
    if (scanf("%d", &linhas) != 1 || linhas <= 0) return 1;
    
    printf("Digite o número de **colunas** (largura): ");
    if (scanf("%d", &colunas) != 1 || colunas <= 0) return 1;


    mapa = (int **)malloc(linhas * sizeof(int *));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para as linhas.\n");
        return 1;
    }


    for (int i = 0; i < linhas; i++) {
        mapa[i] = (int *)malloc(colunas * sizeof(int));
        if (mapa[i] == NULL) {
            printf("Erro ao alocar memoria na linha %d. Liberando memoria e encerrando.\n", i);

            for (int k = 0; k < i; k++) {
                free(mapa[k]);
            }
            free(mapa);
            return 1;
        }
    }


    printf("\n--- Preenchimento do Mapa (0:Vazio, 1:Tijolo, 2:Moeda) ---\n");
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int valor;
            printf("Celula [%d][%d]: ", i, j);
            if (scanf("%d", &valor) != 1) {
                
                break; 
            }
            
            mapa[i][j] = valor;
            
            
            if (valor == 1) {
                blocos_tijolo++;
            }
        }
    }
    
    
    printf("\n--- Mapa Final ---\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }

    
    printf("\n--- Resultado ---\n");
    printf("O mapa possui **%d blocos de tijolo**.\n", blocos_tijolo);

   
    
    
    for (int i = 0; i < linhas; i++) {
        free(mapa[i]);
    }
    
    
    free(mapa);
    printf("Memoria do mapa liberada.\n");

    return 0;
}