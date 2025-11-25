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

// Funções Auxiliares
void inicializar_fila(Fila *f) { f->inicio = NULL; f->fim = NULL; }
int estaVazia(Fila *f) { return (f->inicio == NULL); }

// Implementacao da operacao INSERIR (Enqueue)
void inserir(Fila *f, Jogador j) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("\nERRO: Falha na alocacao de memoria.\n");
        return;
    }

    novo_no->dados = j;
    novo_no->prox = NULL;

    if (estaVazia(f)) {
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

    if (estaVazia(f)) {
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

// FUNCAO PRINCIPAL DA TAREFA: Implementacao da operacao VER INICIO (Peek/Front)
Jogador verInicio(Fila *f) {
    // Jogador de falha (ID = -1)
    Jogador jogador_consulta = {-1, ""};

    // 1. Lida com fila vazia
    if (estaVazia(f)) {
        printf("\nAVISO: A fila esta vazia. Nao ha jogador no inicio.\n");
        return jogador_consulta;
    }

    // 2. Retorna os dados do nó de inicio sem modificar a fila
    return f->inicio->dados;
}

// Implementacao da operacao MOSTRAR (Travessia)
void mostrar(Fila *f) {
    if (estaVazia(f)) {
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
        printf("4. Ver quem e o proximo da Fila\n"); // Nova opção
        printf("5. Verificar se a Fila esta Vazia\n");
        printf("6. Sair\n"); // Opção de sair reenumerada
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
                    printf("\n SUCESSO: O jogador '%s' (ID: %d) foi removido e entrou em uma partida!\n",
                           jogador_alocado.nickname, jogador_alocado.id);
                }
                break;
            }
            case 3:
                mostrar(&fila_matchmaking);
                break;
            case 4: {
                Jogador proximo = verInicio(&fila_matchmaking);
                
                if (proximo.id != -1) {
                    printf("\n O proximo jogador a entrar na partida e: '%s' (ID: %d)\n",
                           proximo.nickname, proximo.id);
                }
                break;
            }
            case 5:
                if (estaVazia(&fila_matchmaking)) {
                    printf("\n[STATUS]: SIM, a fila esta vazia.\n");
                } else {
                    printf("\n[STATUS]: NAO, a fila contem jogadores.\n");
                }
                break;
            case 6:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 6);

    liberar_fila(&fila_matchmaking);
    return 0;
}