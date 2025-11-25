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
    printf("\nMemoria da lista de jogadores liberada.\n");
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

    printf("\n[SUCESSO] Jogador '%s' (ID: %d) adicionado ao fim do grupo.\n", 
           novo_jogador.nome, novo_jogador.id);
}


void deletar_primeiro(FilaMatchmaking *fila) {
    if (fila->cabeca == NULL) {
        printf("\n[ATENCAO] Nao ha jogadores na lista para remover do inicio.\n");
        return;
    }

    No *no_a_remover = fila->cabeca;
    Jogador jogador_removido = no_a_remover->dados;

    
    fila->cabeca = fila->cabeca->proximo;

    
    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }

    free(no_a_remover);

    printf("\n[REMOVIDO] Jogador '%s' (ID: %d) removido do inicio da lista (Lider da Party).\n", 
           jogador_removido.nome, jogador_removido.id);
}


void deletar_fim(FilaMatchmaking *fila) {
    if (fila->cabeca == NULL) {
        printf("\n[ATENCAO] A lista de jogadores esta vazia. Nao e possivel remover.\n");
        return;
    }

    
    if (fila->cabeca == fila->cauda) {
        Jogador jogador_removido = fila->cabeca->dados;
        free(fila->cabeca);
        fila->cabeca = NULL;
        fila->cauda = NULL;
        printf("\n[REMOVIDO] Jogador '%s' (ID: %d) removido (a lista esta agora vazia).\n", 
               jogador_removido.nome, jogador_removido.id);
        return;
    }

    
    No *atual = fila->cabeca;
    
    
    while (atual->proximo != fila->cauda) {
        atual = atual->proximo;
    }
    
    
    No *no_a_remover = fila->cauda;
    Jogador jogador_removido = no_a_remover->dados;

    
    fila->cauda = atual;
    fila->cauda->proximo = NULL; 

    free(no_a_remover);

    printf("\n[REMOVIDO] Jogador '%s' (ID: %d) removido do final da lista (Ultimo Membro).\n", 
           jogador_removido.nome, jogador_removido.id);
}


void mostrar_fila(const FilaMatchmaking *fila) {
    if (fila == NULL || fila->cabeca == NULL) {
        printf("\n-- A lista de jogadores esta vazia. --\n");
        return;
    }

    printf("\n--- GRUPO DE JOGADORES ---\n");
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
    printf("      GERENCIADOR DE GRUPO DE JOGADORES\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Adicionar jogador ao fim do grupo\n");
        printf("2: Deletar o primeiro (Lider da Party)\n");
        printf("3: Mostrar grupo\n");
        printf("4: Sair\n");
        printf("5: Remover o ultimo membro (Deletar do fim)\n"); 
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
                printf("\nEncerrando o gerenciador de grupo...\n");
                break;
            case 5:
                deletar_fim(&fila); 
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