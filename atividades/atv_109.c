#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicões de Estruturas
typedef struct {
    int id;
    char nickname[50];
} Jogador;

typedef struct No {
    Jogador dados;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Inicializa a fila
void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Implementacao da operacao INSERIR (Enqueue)
void inserir(Fila *f, Jogador j) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("\nERRO: Falha na alocacao de memoria para novo jogador.\n");
        return;
    }

    novo_no->dados = j;
    novo_no->prox = NULL;

    if (f->inicio == NULL) {
        // Fila vazia
        f->inicio = novo_no;
        f->fim = novo_no;
    } else {
        // Fila não vazia
        f->fim->prox = novo_no;
        f->fim = novo_no;
    }

    printf("SUCESSO: Jogador ID %d ('%s') adicionado ao final da fila.\n", j.id, j.nickname);
}

// FUNCAO PRINCIPAL DA TAREFA: Implementacao da operacao MOSTRAR (Travessia)
void mostrar(Fila *f) {
    if (f->inicio == NULL) {
        printf("\nATENCAO: A fila de matchmaking esta vazia.\n");
        return;
    }

    printf("\n*** FILA DE MATCHMAKING (Inicio -> Fim) ***\n");
    printf("   (Primeiro a Entrar sera o Primeiro a Sair)\n");
    printf("--------------------------------------------\n");
    
    // Usa ponteiro auxiliar para percorrer a fila, começando do 'inicio'
    No *aux = f->inicio;
    int posicao = 1;
    
    while (aux != NULL) {
        printf("Posicao %d: ID %d | Nickname: %s\n", 
               posicao, 
               aux->dados.id, 
               aux->dados.nickname);
        aux = aux->prox;
        posicao++;
    }
    printf("--------------------------------------------\n");
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
    int proximo_id = 101; // ID inicial para melhor visualização

    printf("--- Simulador de Fila de Matchmaking (FIFO) ---\n");

    do {
        printf("\n==================================\n");
        printf("       MENU DE MATCHMAKING\n");
        printf("==================================\n");
        printf("1. Adicionar Jogador na Fila\n");
        printf("2. Mostrar Fila\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0;
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
        }

        switch (escolha) {
            case 1: {
                novo_jogador.id = proximo_id++;
                
                printf("Nickname do Jogador (ID %d): ", novo_jogador.id);
                if (fgets(novo_jogador.nickname, 50, stdin) == NULL) break;
                novo_jogador.nickname[strcspn(novo_jogador.nickname, "\n")] = 0; 
                
                inserir(&fila_matchmaking, novo_jogador);
                break;
            }
            case 2:
                // Chamada da nova funcao de exibicao
                mostrar(&fila_matchmaking);
                break;
            case 3:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 3);

    liberar_fila(&fila_matchmaking);
    return 0;
}