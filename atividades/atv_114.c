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

// Protótipos
void inicializar_fila(Fila *f);
int estaVazia(Fila *f);
void push(Fila *f, Jogador j);
Jogador pop(Fila *f);
Jogador verInicio(Fila *f);
void mostrar(Fila *f);
void salvarFila(Fila *f, const char *nomeArquivo);
void liberar_fila(Fila *f);

// --- Implementação das Funções ---

void inicializar_fila(Fila *f) { f->inicio = NULL; f->fim = NULL; }
int estaVazia(Fila *f) { return (f->inicio == NULL); }

void push(Fila *f, Jogador j) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) { printf("\nERRO: Falha na alocacao de memoria.\n"); return; }
    
    // Evita a mensagem de SUCCESSO para push interno no carregarFila
    int is_loading = (f->inicio == NULL && f->fim == NULL && j.id != 0); 

    novo_no->dados = j;
    novo_no->prox = NULL;
    
    if (estaVazia(f)) { f->inicio = novo_no; f->fim = novo_no; } 
    else { f->fim->prox = novo_no; f->fim = novo_no; }
    
    if (!is_loading) {
        printf("SUCESSO: Jogador ID %d ('%s') adicionado ao final da fila.\n", j.id, j.nickname);
    }
}

Jogador pop(Fila *f) {
    Jogador jogador_removido = {-1, ""};
    if (estaVazia(f)) { return jogador_removido; }

    No *no_a_remover = f->inicio;
    jogador_removido = no_a_remover->dados;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) { f->fim = NULL; }

    free(no_a_remover);
    return jogador_removido;
}

Jogador verInicio(Fila *f) {
    Jogador jogador_consulta = {-1, ""};
    if (estaVazia(f)) { printf("\nAVISO: A fila esta vazia. Nao ha jogador no inicio.\n"); return jogador_consulta; }
    return f->inicio->dados;
}

void mostrar(Fila *f) {
    if (estaVazia(f)) { printf("\nATENCAO: A fila de matchmaking esta vazia.\n"); return; }
    printf("\n*** FILA DE MATCHMAKING (Inicio -> Fim) ***\n");
    printf("--------------------------------------------\n");
    
    No *aux = f->inicio;
    int posicao = 1;
    
    while (aux != NULL) {
        printf("Posicao %d: ID %d | Nickname: %s\n", posicao, aux->dados.id, aux->dados.nickname);
        aux = aux->prox;
        posicao++;
    }
    printf("--------------------------------------------\n");
}

void salvarFila(Fila *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    
    if (arquivo == NULL) {
        printf("\nERRO: Nao foi possivel abrir o arquivo %s para escrita.\n", nomeArquivo);
        return;
    }

    No *atual = f->inicio;
    int contagem = 0;

    while (atual != NULL) {
        fwrite(&(atual->dados), sizeof(Jogador), 1, arquivo);
        atual = atual->prox;
        contagem++;
    }

    fclose(arquivo);
    printf("\n✅ SUCESSO: %d jogadores salvos no arquivo binario: %s\n", contagem, nomeArquivo);
}

// FUNÇÃO PRINCIPAL DA TAREFA: Implementação da operação Carregar Fila de Arquivo Binário
void carregarFila(Fila *f, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    
    // Se o arquivo não existe, inicia com fila vazia e retorna
    if (arquivo == NULL) {
        printf("AVISO: Nenhum arquivo de grimorio '%s' encontrado. Iniciando com fila vazia.\n", nomeArquivo);
        return;
    }

    Jogador jogador_lido;
    int contagem = 0;

    // Leitura: O primeiro item do arquivo e empilhado primeiro (mantendo a ordem FIFO)
    while (fread(&jogador_lido, sizeof(Jogador), 1, arquivo) == 1) {
        // Usa a lógica de inserção para reconstruir a fila
        // A ordem de leitura (FIFO) e a ordem de inserção (na fila) se complementam, 
        // mantendo a ordem original sem a necessidade de inversão.
        push(f, jogador_lido);
        contagem++;
    }

    fclose(arquivo);
    printf("SUCESSO: %d jogadores carregados do arquivo '%s'. Estado restaurado.\n", contagem, nomeArquivo);
}

void liberar_fila(Fila *f) {
    while (!estaVazia(f)) { pop(f); }
}

int main() {
    Fila fila_matchmaking;
    inicializar_fila(&fila_matchmaking);
    const char *nome_arquivo_data = "matchmaking_queue.bin";
    
    // CHAVE DA TAREFA: Carrega o estado anterior da fila na inicialização
    carregarFila(&fila_matchmaking, nome_arquivo_data);

    int escolha;
    Jogador novo_jogador;
    int proximo_id = 101;

    printf("\n--- Simulador de Fila de Matchmaking (FIFO) ---\n");

    do {
        printf("\n==================================\n");
        printf("       MENU DE MATCHMAKING\n");
        printf("==================================\n");
        printf("1. Adicionar Jogador (Enqueue)\n");
        printf("2. Remover Jogador (Dequeue)\n");
        printf("3. Mostrar Fila\n");
        printf("4. Ver proximo da Fila (Peek)\n");
        printf("5. Salvar Fila em Arquivo\n");
        printf("6. Verificar se a Fila esta Vazia\n");
        printf("7. Sair\n");
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
                push(&fila_matchmaking, novo_jogador);
                break;
            }
            case 2: {
                Jogador jogador_alocado = pop(&fila_matchmaking);
                if (jogador_alocado.id != -1) {
                    printf("\n🎉 SUCESSO: O jogador '%s' (ID: %d) foi removido e entrou em uma partida!\n",
                           jogador_alocado.nickname, jogador_alocado.id);
                } else {
                    printf("\nAVISO: A fila esta vazia.\n");
                }
                break;
            }
            case 3:
                mostrar(&fila_matchmaking);
                break;
            case 4: {
                Jogador proximo = verInicio(&fila_matchmaking);
                if (proximo.id != -1) {
                    printf("\n➡️ O proximo jogador a entrar na partida e: '%s' (ID: %d)\n",
                           proximo.nickname, proximo.id);
                }
                break;
            }
            case 5:
                salvarFila(&fila_matchmaking, nome_arquivo_data);
                break;
            case 6:
                if (estaVazia(&fila_matchmaking)) {
                    printf("\n[STATUS]: SIM, a fila esta vazia.\n");
                } else {
                    printf("\n[STATUS]: NAO, a fila contem jogadores.\n");
                }
                break;
            case 7:
                printf("\nEncerrando o sistema de matchmaking.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 7);

    liberar_fila(&fila_matchmaking);
    return 0;
}