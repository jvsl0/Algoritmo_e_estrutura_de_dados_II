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

// FUNCAO PRINCIPAL DA TAREFA: Implementacao da operacao estaVazia
int estaVazia(Fila *f) {
    // Retorna 1 (verdadeiro) se inicio for NULL, 0 (falso) caso contrario.
    return (f->inicio == NULL);
}

// Inicializa a fila
void inicializar_fila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Implementacao da operacao INSERIR (Enqueue)
void inserir(Fila *f, Jogador j) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("\nERRO: Falha na alocacao de memoria.\n");
        return;
    }

    novo_no->dados = j;
    novo_no->prox = NULL;

    if (estaVazia(f)) { // Usa a nova função estaVazia
        f->inicio = novo_no;
        f->fim = novo_no;
    } else {
        f->fim->prox = novo_no;
        f->fim = novo_no;
    }

    printf("SUCESSO: Jogador ID %d ('%s') adicionado ao final da fila.\n", j.id, j.nickname);
}

// Implementacao da operacao REMOVER (Dequeue)
Jogador remover(Fila *f) {
    Jogador jogador_removido = {-1, ""};

    if (estaVazia(f)) { // Usa a nova função estaVazia
        printf("\nAVISO: A fila de matchmaking esta vazia. Nao ha jogadores para remover.\n");
        return jogador_removido;
    }

    No *no_a_remover = f->inicio;
    jogador_removido = no_a_remover->dados;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(no_a_remover);
    return jogador_removido;
}

// Implementacao da operacao MOSTRAR (Travessia)
void mostrar(Fila *f) {
    if (estaVazia(f)) { // Usa a nova função estaVazia
        printf("\nATENCAO: A fila de matchmaking esta vazia.\n");
        return;
    }

    printf("\n*** FILA DE MATCHMAKING (Inicio -> Fim) ***\n");
    printf("--------------------------------------------\n");
    
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

// Funcao auxiliar para liberar toda a memoria ao sair
void liberar_fila(Fila *f) {
    while (!estaVazia(f)) {
        remover(f); 
    }
    f->inicio = NULL;
    f->fim = NULL;
}

int main() {
    Fila fila_matchmaking;
    inicializar_fila(&fila_matchmaking);
    int escolha;
    Jogador novo_jogador;
    int proximo_id = 101;

    printf("--- Simulador de Fila de Matchmaking (FIFO) ---\n");

    do {
        printf("\n==================================\n");
        printf("       MENU DE MATCHMAKING\n");
        printf("==================================\n");
        printf("1. Adicionar Jogador na Fila (Inserir)\n");
        printf("2. Remover Jogador da Fila (Iniciar Partida)\n");
        printf("3. Mostrar Fila\n");
        printf("4. Verificar se a Fila esta Vazia\n");
        printf("5. Sair\n");
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
            case 2: {
                Jogador jogador_alocado = remover(&fila_matchmaking);
                
                if (jogador_alocado.id != -1) {
                    printf("\nSUCESSO: O jogador '%s' (ID: %d) foi removido e entrou em uma partida!\n",
                           jogador_alocado.nickname, jogador_alocado.id);
                }
                break;
            }
            case 3:
                mostrar(&fila_matchmaking);
                break;
            case 4: {
                // Chamada e exibição da nova função
                if (estaVazia(&fila_matchmaking)) {
                    printf("\n[STATUS]: SIM, a fila esta vazia.\n");
                } else {
                    printf("\n[STATUS]: NAO, a fila contem jogadores.\n");
                }
                break;
            }
            case 5:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 5);

    liberar_fila(&fila_matchmaking);
    return 0;
}
