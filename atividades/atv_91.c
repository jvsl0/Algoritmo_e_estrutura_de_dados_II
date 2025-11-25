#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char descricao[100];
} Etapa;


typedef struct No {
    Etapa dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca;
    No *cauda;
} DiarioMissao;


void inicializar_missao(DiarioMissao *lista) {
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->cauda = NULL;
    }
}

No* criar_no(Etapa nova_etapa) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para a nova etapa");
        return NULL;
    }
    novo_no->dados = nova_etapa;
    novo_no->proximo = NULL;
    return novo_no;
}

void liberar_missao(DiarioMissao *lista) {
    No *atual = lista->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
    lista->cauda = NULL;
    printf("\nMemoria do diario de missao liberada.\n");
}

int ler_dados_etapa(Etapa *etapa) {
    char buffer[150];

    printf("\nDigite o ID da Etapa (inteiro): ");
    if (scanf("%d", &etapa->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite a Descricao da Etapa (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(etapa->descricao, buffer, sizeof(etapa->descricao) - 1);
        etapa->descricao[sizeof(etapa->descricao) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura da descricao.\n");
        return 0;
    }
    
    return 1;
}


void adicionar_etapa_fim(DiarioMissao *lista, Etapa nova_etapa) {
    No *novo_no = criar_no(nova_etapa);
    if (novo_no == NULL) return; 

    if (lista->cabeca == NULL) {
        
        lista->cabeca = novo_no;
        lista->cauda = novo_no;
    } 
    else {
        
        lista->cauda->proximo = novo_no;
        
        lista->cauda = novo_no;
    }

    printf("\n[SUCESSO] Etapa '%s' (ID: %d) adicionada ao fim da missao.\n", 
           nova_etapa.descricao, nova_etapa.id);
}


void deletar_antes(DiarioMissao *lista, int id_referencia) {
    // Caso 1: Lista vazia
    if (lista->cabeca == NULL) {
        printf("\n[ATENCAO] O diario de missao esta vazio. Nenhuma etapa deletada.\n");
        return;
    }

    
    if (lista->cabeca->dados.id == id_referencia) {
        printf("\n[ATENCAO] Etapa '%s' (ID: %d) e a primeira. Nao ha etapa anterior para deletar.\n", 
               lista->cabeca->dados.descricao, id_referencia);
        return;
    }

    
    No *avo = NULL; 
    No *anterior = lista->cabeca; 
    No *atual = lista->cabeca->proximo; 
    
    
    while (atual != NULL && atual->dados.id != id_referencia) {
        avo = anterior;
        anterior = atual;
        atual = atual->proximo;
    }

    
    if (atual == NULL) {
        printf("\n[ERRO] Etapa de referencia com ID %d nao encontrada no diario de missao.\n", id_referencia);
        return;
    }
    
    
    
    Etapa etapa_removida = anterior->dados;

    
    if (avo == NULL) {
        
        lista->cabeca = atual;
    }
    
    else {
        
        avo->proximo = atual;
        
    }

    free(anterior); 
    
    printf("\n[ATALHO ENCONTRADO] Etapa ANTERIOR '%s' (ID: %d) foi removida, liberando o caminho para '%s'.\n", 
           etapa_removida.descricao, etapa_removida.id, atual->dados.descricao);
}

void mostrar_etapas(const DiarioMissao *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        printf("\n-- O diario de missao esta vazio. Nao ha etapas ativas. --\n");
        return;
    }

    printf("\n--- SEQUENCIA DE ETAPAS DA MISSAO ---\n");
    printf(" ORDEM | ID  | DESCRICAO\n");
    printf("-------|-----|-----------------------------------\n");

    No *atual = lista->cabeca;
    int ordem = 1;
    while (atual != NULL) {
        printf(" %5d | %3d | %s\n", 
               ordem++, 
               atual->dados.id, 
               atual->dados.descricao);

        atual = atual->proximo; 
    }
    printf("---------------------------------------\n");
}



int main() {
    DiarioMissao diario;
    inicializar_missao(&diario);

    int opcao;
    Etapa nova_etapa;
    int id_referencia_deletar_antes;
    
    printf("===========================================\n");
    printf("   GERENCIADOR DE ETAPAS DE MISSAO (RPG)\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU DE MISSAO ---\n");
        printf("1: Adicionar Etapa (fim da lista)\n");
        printf("2: Mostrar Etapas Ativas\n");
        printf("3: Deletar Etapa ANTES de um ID especifico\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_etapa(&nova_etapa)) {
                    adicionar_etapa_fim(&diario, nova_etapa);
                }
                break;
            case 2:
                mostrar_etapas(&diario);
                break;
            case 3:
                printf("\n--- DELETAR ETAPA ANTERIOR ---\n");
                printf("Digite o ID da Etapa de referencia (a etapa que sera MANTIDA): ");
                if (scanf("%d", &id_referencia_deletar_antes) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                deletar_antes(&diario, id_referencia_deletar_antes);
                mostrar_etapas(&diario); 
                break;
            case 4:
                printf("\nFechando o diario de missao...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_missao(&diario);
    printf("Programa finalizado.\n");

    return 0;
}