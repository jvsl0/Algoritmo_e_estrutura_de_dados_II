#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definicão da struct Jogador (Dados a serem armazenados)
typedef struct {
    int id;
    char nickname[50];
} Jogador;

// 2. Definicão do Nó da Fila
typedef struct No {
    Jogador dados;
    struct No *prox;
} No;

// 3. Definicão da Fila (Contem os ponteiros inicio e fim)
typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Inicializa a fila, garantindo que esteja vazia
void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Implementacao da operacao INSERIR (Enqueue)
void inserir(Fila *f, Jogador j) {
    // 1. Aloca e preenche o novo no
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("\nERRO: Falha na alocacao de memoria para novo jogador.\n");
        return;
    }

    novo_no->dados = j;
    novo_no->prox = NULL; // Novo elemento sempre sera o ultimo

    // 2. Trata os dois casos de insercao
    if (f->inicio == NULL) {
        // Caso 1: Fila vazia
        f->inicio = novo_no;
        f->fim = novo_no;
    } else {
        // Caso 2: Fila nao vazia (Adiciona apos o ultimo e atualiza o ponteiro fim)
        f->fim->prox = novo_no;
        f->fim = novo_no;
    }

    printf("SUCESSO: Jogador ID %d ('%s') adicionado ao final da fila.\n", j.id, j.nickname);
}

// Funcao auxiliar para liberar memoria ao sair
void liberar_fila(Fila *f) {
    No *atual = f->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    f->inicio = NULL;
    f->fim = NULL;
}

int main() {
    Fila fila_matchmaking;
    inicializar_fila(&fila_matchmaking);
    int escolha;
    Jogador novo_jogador;
    int proximo_id = 1;

    printf("--- Simulador de Fila de Matchmaking (FIFO) ---\n");

    do {
        printf("\n==================================\n");
        printf("       MENU DE MATCHMAKING\n");
        printf("==================================\n");
        printf("1. Adicionar Novo Jogador (INSERIR)\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0; // Opcao invalida
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
        }

        switch (escolha) {
            case 1: {
                novo_jogador.id = proximo_id++;
                
                printf("Nickname do Jogador (ID %d): ", novo_jogador.id);
                if (fgets(novo_jogador.nickname, 50, stdin) == NULL) break;
                // Remove a quebra de linha
                novo_jogador.nickname[strcspn(novo_jogador.nickname, "\n")] = 0; 
                
                inserir(&fila_matchmaking, novo_jogador);
                break;
            }
            case 2:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 2);

    liberar_fila(&fila_matchmaking);
    return 0;
}