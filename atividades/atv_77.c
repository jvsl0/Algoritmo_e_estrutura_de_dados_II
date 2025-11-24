#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int pontuacao;
} Jogador;


void troca(Jogador *a, Jogador *b) {
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}


int particao(Jogador v[], int inicio, int fim) {
    
    int pivo_pontuacao = v[fim].pontuacao;
    int i = inicio - 1; 
    
    for (int j = inicio; j <= fim - 1; j++) {
        
        if (v[j].pontuacao >= pivo_pontuacao) {
            
            i++;
            
            troca(&v[i], &v[j]);
        }
    }

    
    troca(&v[i + 1], &v[fim]);

    
    return (i + 1);
}


void quickSort(Jogador v[], int inicio, int fim) {
    if (inicio < fim) {
        
        int pi = particao(v, inicio, fim);

        
        quickSort(v, inicio, pi - 1);

       
        quickSort(v, pi + 1, fim);
    }
}

int main() {
    int n; 
    int i;

    printf("--- Quick Sort Decrescente para Placar de Jogadores ---\n\n");

    
    printf("Digite a quantidade de jogadores (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: N deve ser um inteiro positivo.\n");
        return EXIT_FAILURE;
    }

    
    Jogador *placar = (Jogador *)malloc(n * sizeof(Jogador));
    if (placar == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    printf("Digite o ID e a pontuacao de cada um dos %d jogadores:\n", n);
    for (i = 0; i < n; i++) {
        printf("Jogador %d (ID Pontuacao): ", i + 1);
        if (scanf("%d %d", &placar[i].id, &placar[i].pontuacao) != 2) {
            printf("Erro na leitura dos dados.\n");
            free(placar);
            return EXIT_FAILURE;
        }
    }

    
    quickSort(placar, 0, n - 1);

    
    printf("\n============================================\n");
    printf("Placar Final Ordenado (Decrescente):\n");
    printf("RANK | ID do Jogador | Pontuacao\n");
    printf("--------------------------------------------\n");
    for (i = 0; i < n; i++) {
        
        printf("%4d | %13d | %9d\n", i + 1, placar[i].id, placar[i].pontuacao);
    }
    printf("============================================\n");

    
    free(placar);

    return EXIT_SUCCESS;
}