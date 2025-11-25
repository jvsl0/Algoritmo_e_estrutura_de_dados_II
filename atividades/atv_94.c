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
    printf("Mercenário ID %d (%s) adicionado ao registro.\n", id, nome);
}

void mostrar_lista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nRegistro da Guilda: Vazio.\n");
        return;
    }

    printf("\nREGISTRO ATUAL DE MERCENARIOS\n");
    Membro *atual = lista->inicio;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("--------------------------------\n");
}

// Funções de Censo
int tamanho(Lista *lista) {
    int contador = 0;
    Membro *atual = lista->inicio;

    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }

    return contador;
}

// Função Principal
int main() {
    Lista guilda;
    inicializar_lista(&guilda);
    int escolha;
    
    inserir_fim(&guilda, 201, "Aiden");
    inserir_fim(&guilda, 202, "Lira");
    inserir_fim(&guilda, 203, "Kael");

    do {
        printf("\n==================================\n");
        printf("       MENU DA GUILDA\n");
        printf("==================================\n");
        printf("1. Adicionar Novo Mercenario\n");
        printf("2. Mostrar Registro de Mercenarios\n");
        printf("3. Implementar Censo (Contar Membros)\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: {
                int novo_id;
                char nome_novo_membro[100];
                printf("\nID do novo mercenário: ");
                if (scanf("%d", &novo_id) != 1) break; 
                while (getchar() != '\n');
                
                printf("Nome do novo mercenário: ");
                if (fgets(nome_novo_membro, 100, stdin) == NULL) break;
                nome_novo_membro[strcspn(nome_novo_membro, "\n")] = 0; 

                inserir_fim(&guilda, novo_id, nome_novo_membro);
                break;
            }
            case 2:
                mostrar_lista(&guilda);
                break;
            case 3: {
                int tamanho_guilda = tamanho(&guilda);
                printf("\nContagem Atual: A guilda tem um total de **%d** mercenários registrados.\n", tamanho_guilda);
                break;
            }
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
