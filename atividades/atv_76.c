#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void selecionarPivoAleatorio(int v[], int inicio, int fim) {
    
    int indice_aleatorio = inicio + (rand() % (fim - inicio + 1));

    
    troca(&v[indice_aleatorio], &v[fim]);
}


int particao(int v[], int inicio, int fim) {
    
    int pivo = v[fim];
    int i = inicio - 1; 

    for (int j = inicio; j <= fim - 1; j++) {
        if (v[j] <= pivo) {
            i++;
            troca(&v[i], &v[j]);
        }
    }

    
    troca(&v[i + 1], &v[fim]);
    return (i + 1);
}

void quickSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        
        selecionarPivoAleatorio(v, inicio, fim);

        
        int pi = particao(v, inicio, fim);

        // 3. Chamadas recursivas
        quickSort(v, inicio, pi - 1); 
        quickSort(v, pi + 1, fim);   
    }
}

int main() {
    
    srand(time(NULL));

    int n; 
    int i;

    printf("--- Quick Sort Robusto para Leaderboards (Pivo Aleatorio) ---\n\n");

    
    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    int *pontuacoes = (int *)malloc(n * sizeof(int));
    if (pontuacoes == NULL) {
        printf("Erro: Falha na alocacao de memoria para as pontuacoes.\n");
        return EXIT_FAILURE;
    }

    printf("Digite a pontuacao de cada um dos %d jogadores:\n", n);
    for (i = 0; i < n; i++) {
        printf("Jogador %d Pontuacao: ", i + 1);
        if (scanf("%d", &pontuacoes[i]) != 1 || pontuacoes[i] < 0) {
            printf("Erro na leitura ou pontuacao invalida.\n");
            free(pontuacoes);
            return EXIT_FAILURE;
        }
    }

    
    printf("\nIniciando Quick Sort com estrategia de Pivo Aleatorio...\n");
    quickSort(pontuacoes, 0, n - 1);

    
    printf("\n========================================================\n");
    printf("Leaderboard Final (Pontuacoes Ordenadas):\n");
    for (i = 0; i < n; i++) {
        printf("%d", pontuacoes[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n========================================================\n");

    
    free(pontuacoes);

    return EXIT_SUCCESS;
}