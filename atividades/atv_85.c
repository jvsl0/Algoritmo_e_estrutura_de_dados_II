#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[100];
} Item;


typedef struct No {
    Item dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca; 
} Inventario;



void inicializar_inventario(Inventario *inventario) {
    if (inventario != NULL) {
        inventario->cabeca = NULL;
    }
}


No* criar_no(Item novo_item) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo item");
        return NULL;
    }
    novo_no->dados = novo_item;
    novo_no->proximo = NULL;
    return novo_no;
}

void liberar_inventario(Inventario *inventario) {
    No *atual = inventario->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    inventario->cabeca = NULL;
    printf("\nMemoria do inventario liberada.\n");
}


int ler_dados_item(Item *item) {
    char buffer[150]; 

    printf("\nDigite o ID do Item (inteiro): ");
    if (scanf("%d", &item->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
    
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do Item (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        strncpy(item->nome, buffer, sizeof(item->nome) - 1);
        item->nome[sizeof(item->nome) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return 0;
    }
    
    return 1;
}


No* pesquisar_item(const Inventario *inventario, int id_busca) {
    No *atual = inventario->cabeca;
    while (atual != NULL) {
        if (atual->dados.id == id_busca) {
            return atual; 
        }
        atual = atual->proximo;
    }
    return NULL; 
}


void inserir_inicio(Inventario *inventario, Item novo_item) {
    No *novo_no = criar_no(novo_item);
    if (novo_no == NULL) return; 

    novo_no->proximo = inventario->cabeca;
    inventario->cabeca = novo_no;

    printf("\n[SUCESSO] '%s' (ID: %d) adicionado ao inicio do inventário.\n", 
           novo_item.nome, novo_item.id);
}


void inserir_fim(Inventario *inventario, Item novo_item) {
    No *novo_no = criar_no(novo_item);
    if (novo_no == NULL) return; 

    
    if (inventario->cabeca == NULL) {
        inventario->cabeca = novo_no;
    } 
    
    else {
        No *atual = inventario->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }

    printf("\n[SUCESSO] '%s' (ID: %d) adicionado ao final do inventário.\n", 
           novo_item.nome, novo_item.id);
}


void inserir_apos_id(Inventario *inventario, Item novo_item, int id_fragmento) {
    // 1. Encontra o no alvo (o fragmento)
    No *no_fragmento = pesquisar_item(inventario, id_fragmento);

    if (no_fragmento == NULL) {
        printf("\n[ERRO] O item com ID %d (fragmento) nao foi encontrado. Insercao de '%s' cancelada.\n", 
               id_fragmento, novo_item.nome);
        return;
    }

    
    No *novo_no = criar_no(novo_item);
    if (novo_no == NULL) return;

    
    novo_no->proximo = no_fragmento->proximo;
    
    
    no_fragmento->proximo = novo_no;

    printf("\n[SUCESSO] '%s' (ID: %d) inserido APOS o fragmento '%s' (ID: %d).\n", 
           novo_item.nome, novo_item.id, no_fragmento->dados.nome, id_fragmento);
}

void mostrar_inventario(const Inventario *inventario) {
    if (inventario == NULL || inventario->cabeca == NULL) {
        printf("\n-- O inventário de missoes esta vazio. --\n");
        return;
    }

    printf("\n--- INVENTARIO DE ITENS DE MISSAO ---\n");
    printf(" ID  | NOME\n");
    printf("-----|-----------------------------------\n");

    No *atual = inventario->cabeca;
    while (atual != NULL) {
        printf(" %3d | %s\n", 
               atual->dados.id, 
               atual->dados.nome);

        atual = atual->proximo; 
    }
    printf("---------------------------------------\n");
}


int main() {
    Inventario inventario;
    inicializar_inventario(&inventario);

    int opcao;
    Item novo_item;
    int id_fragmento_alvo;
    
    printf("===========================================\n");
    printf("      REGISTRO DE ITENS DE MISSAO (RPG)\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Inserir item no INICIO (Comum)\n");
        printf("2: Inserir item no FIM (Comum)\n");
        printf("3: Inserir CATALISADOR APOS um Fragmento (por ID)\n");
        printf("4: Mostrar Inventario\n");
        printf("5: Sair\n");
        printf("Escolha a opcao: ");

        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_item(&novo_item)) {
                    inserir_inicio(&inventario, novo_item);
                }
                break;
            case 2:
                if (ler_dados_item(&novo_item)) {
                    inserir_fim(&inventario, novo_item);
                }
                break;
            case 3:
                printf("\n--- Inserir Catalisador Apos Fragmento ---\n");
                
                
                if (!ler_dados_item(&novo_item)) {
                    break;
                }
                
                
                printf("Digite o ID do Fragmento de Poder (item existente) apos o qual inserir o catalisador: ");
                if (scanf("%d", &id_fragmento_alvo) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID de Fragmento invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                
                
                inserir_apos_id(&inventario, novo_item, id_fragmento_alvo);

                break;
            case 4:
                mostrar_inventario(&inventario);
                break;
            case 5:
                printf("\nEncerrando o registro de itens...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 5);

    liberar_inventario(&inventario);
    printf("Programa finalizado.\n");

    return 0;
}