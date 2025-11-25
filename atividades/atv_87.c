#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
} Jogador;

typedef struct No {
    Jogador dados;
    struct No *proximo;
} No;

typedef struct {
    No *cabeca;
    No *cauda;
} FilaMatchmaking;


void inicializar_fila(FilaMatchmaking *fila) {
    if (fila != NULL) {
        fila->cabeca = NULL;
        fila->cauda = NULL;
    }
}

No* criar_no(Jogador novo_jogador) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo jogador");
        return NULL;
    }
    novo_no->dados = novo_jogador;
    novo_no->proximo = NULL;
    return novo_no;
}

void liberar_fila(FilaMatchmaking *fila) {
    No *atual = fila->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    fila->cabeca = NULL;
    fila->cauda = NULL;
    printf("\nMemoria da fila de espera liberada.\n");
}

int ler_dados_jogador(Jogador *jogador) {
    char buffer[150];

    printf("\nDigite o ID do Jogador (inteiro): ");
    if (scanf("%d", &jogador->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do Jogador (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(jogador->nome, buffer, sizeof(jogador->nome) - 1);
        jogador->nome[sizeof(jogador->nome) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return 0;
    }
    
    return 1;
}


void adicionar_jogador_fim(FilaMatchmaking *fila, Jogador novo_jogador) {
    No *novo_no = criar_no(novo_jogador);
    if (novo_no == NULL) return; 

    if (fila->cabeca == NULL) {
        
        fila->cabeca = novo_no;
        fila->cauda = novo_no;
    } 
    else {
        
        fila->cauda->proximo = novo_no;
        
        fila->cauda = novo_no;
    }

    printf("\n[SUCESSO] Jogador '%s' (ID: %d) adicionado ao fim da fila.\n", 
           novo_jogador.nome, novo_jogador.id);
}


void deletar_primeiro(FilaMatchmaking *fila) {
    if (fila->cabeca == NULL) {
        printf("\n[ATENCAO] Nao ha jogadores na fila de espera para iniciar uma partida.\n");
        return;
    }

    No *no_a_remover = fila->cabeca;
    Jogador jogador_removido = no_a_remover->dados;

    
    fila->cabeca = fila->cabeca->proximo;

    
    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }

    free(no_a_remover);

    printf("\n[PARTIDA INICIADA] Jogador '%s' (ID: %d) removido do inicio da fila.\n", 
           jogador_removido.nome, jogador_removido.id);
}


void mostrar_fila(const FilaMatchmaking *fila) {
    if (fila == NULL || fila->cabeca == NULL) {
        printf("\n-- A fila de matchmaking esta vazia. --\n");
        return;
    }

    printf("\n--- FILA DE ESPERA ---\n");
    printf(" POSICAO | ID  | NOME\n");
    printf("---------|-----|-----------------------------------\n");

    No *atual = fila->cabeca;
    int posicao = 1;
    while (atual != NULL) {
        printf(" %7d | %3d | %s\n", 
               posicao++, 
               atual->dados.id, 
               atual->dados.nome);

        atual = atual->proximo; 
    }
    printf("---------------------------------------\n");
}




int main() {
    FilaMatchmaking fila;
    inicializar_fila(&fila);

    int opcao;
    Jogador novo_jogador;
    
    printf("===========================================\n");
    printf("    SISTEMA DE FILA DE MATCHMAKING (FIFO)\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Adicionar jogador ao fim da fila\n");
        printf("2: Iniciar partida (Deletar o primeiro)\n");
        printf("3: Mostrar fila de espera\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_jogador(&novo_jogador)) {
                    adicionar_jogador_fim(&fila, novo_jogador);
                }
                break;
            case 2:
                deletar_primeiro(&fila);
                break;
            case 3:
                mostrar_fila(&fila);
                break;
            case 4:
                printf("\nEncerrando o sistema de matchmaking...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_fila(&fila);
    printf("Programa finalizado.\n");

    return 0;
}