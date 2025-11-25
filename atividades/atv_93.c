#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Membro {
    int id;
    char nome[100];
    struct Membro *prox;
} Membro;

typedef struct {
    Membro *inicio;
} Lista;


void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
}

void inserir_fim(Lista *lista, int id, char nome[]) {
    Membro *novo_membro = (Membro *)malloc(sizeof(Membro));
    if (novo_membro == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    novo_membro->id = id;
    strcpy(novo_membro->nome, nome);
    novo_membro->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo_membro;
    } else {
        Membro *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_membro;
    }
    printf("Membro ID %d (%s) adicionado à guilda.\n", id, nome);
}

void mostrar_lista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nRegistro da Guilda: Vazio.\n");
        return;
    }

    printf("\nREGISTRO ATUAL DA GUILDA\n");
    Membro *atual = lista->inicio;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("--------------------------------\n");
}

// Funções de Busca e Alteração
Membro *pesquisar(Lista *lista, int id) {
    Membro *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void alterar_nome(Lista *lista, int id, char novo_nome[]) {
    Membro *membro_encontrado = pesquisar(lista, id);

    if (membro_encontrado != NULL) {
        char nome_antigo[100];
        strcpy(nome_antigo, membro_encontrado->nome);

        strcpy(membro_encontrado->nome, novo_nome);

        printf("\nNome do Membro ID %d alterado com sucesso!\n", id);
        printf("   - Nome Antigo: %s\n", nome_antigo);
        printf("   - Novo Nome:   %s\n", novo_nome);
    } else {
        printf("\nERRO: Membro com ID %d não encontrado no registro da guilda.\n", id);
    }
}

// Função Principal
int main() {
    Lista guilda;
    inicializar_lista(&guilda);
    int escolha, id_busca;
    char novo_nome[100];
    
    inserir_fim(&guilda, 101, "Guerreiro");
    inserir_fim(&guilda, 102, "Mago_Arcano");
    inserir_fim(&guilda, 103, "Druida_Verde");

    do {
        printf("\n==================================\n");
        printf("       MENU DA GUILDA\n");
        printf("==================================\n");
        printf("1. Adicionar Novo Membro\n");
        printf("2. Mostrar Registro da Guilda\n");
        printf("3. Alterar Nome de Membro\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: {
                int novo_id;
                char nome_novo_membro[100];
                printf("\nID do novo membro: ");
                if (scanf("%d", &novo_id) != 1) break; 
                while (getchar() != '\n');
                
                printf("Nome do novo membro: ");
                if (fgets(nome_novo_membro, 100, stdin) == NULL) break;
                nome_novo_membro[strcspn(nome_novo_membro, "\n")] = 0; 

                inserir_fim(&guilda, novo_id, nome_novo_membro);
                break;
            }
            case 2:
                mostrar_lista(&guilda);
                break;
            case 3:
                printf("\nDigite o ID do membro para renomear: ");
                if (scanf("%d", &id_busca) != 1) break;
                while (getchar() != '\n');
                
                printf("Digite o NOVO nome: ");
                if (fgets(novo_nome, 100, stdin) == NULL) break;
                novo_nome[strcspn(novo_nome, "\n")] = 0;

                alterar_nome(&guilda, id_busca, novo_nome);
                break;
            case 4:
                printf("\nSaindo do sistema de registro da guilda. Adeus!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (escolha != 4);

    Membro *atual = guilda.inicio;
    Membro *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    guilda.inicio = NULL;

    return 0;
}