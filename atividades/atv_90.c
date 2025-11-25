#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
} Ward;

typedef struct No {
    Ward dados;
    struct No *proximo;
} No;

typedef struct {
    No *cabeca;
    No *cauda;
} WardsAtivos;


void inicializar_wards(WardsAtivos *lista) {
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->cauda = NULL;
    }
}

No* criar_no(Ward novo_ward) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo ward");
        return NULL;
    }
    novo_no->dados = novo_ward;
    novo_no->proximo = NULL;
    return novo_no;
}

void liberar_wards(WardsAtivos *lista) {
    No *atual = lista->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
    lista->cauda = NULL;
    printf("\nMemoria da lista de wards liberada.\n");
}

int ler_dados_ward(Ward *ward) {
    char buffer[150];

    printf("\nDigite o ID do Ward (inteiro): ");
    if (scanf("%d", &ward->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do Ward (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(ward->nome, buffer, sizeof(ward->nome) - 1);
        ward->nome[sizeof(ward->nome) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return 0;
    }
    
    return 1;
}

void adicionar_ward_fim(WardsAtivos *lista, Ward novo_ward) {
    No *novo_no = criar_no(novo_ward);
    if (novo_no == NULL) return; 

    if (lista->cabeca == NULL) {
        
        lista->cabeca = novo_no;
        lista->cauda = novo_no;
    } 
    else {
        
        lista->cauda->proximo = novo_no;
        
        lista->cauda = novo_no;
    }

    printf("\n[SUCESSO] Ward '%s' (ID: %d) adicionado a sequencia.\n", 
           novo_ward.nome, novo_ward.id);
}


void deletar_apos(WardsAtivos *lista, int id_referencia) {
    
    if (lista->cabeca == NULL) {
        printf("\n[ATENCAO] Nao ha wards ativos. 'Ward Shatter' falhou.\n");
        return;
    }

    No *atual = lista->cabeca;

    
    while (atual != NULL && atual->dados.id != id_referencia) {
        atual = atual->proximo;
    }

    
    if (atual == NULL) {
        printf("\n[ERRO] Ward de referencia com ID %d nao encontrado. 'Ward Shatter' falhou.\n", id_referencia);
        return;
    }
    
    if (atual->proximo == NULL) {
        printf("\n[ATENCAO] Ward '%s' (ID: %d) e o ultimo na sequencia. Nao ha ward para destruir apos ele.\n", 
               atual->dados.nome, id_referencia);
        return;
    }


    No *no_a_remover = atual->proximo;
    Ward ward_removido = no_a_remover->dados;

    
    atual->proximo = no_a_remover->proximo;
    
   
    if (no_a_remover == lista->cauda) {
        lista->cauda = atual; 
    }

    free(no_a_remover); 

    printf("\n[WARD SHATTER SUCESSO] Ward '%s' (ID: %d) destruiu o Ward '%s' (ID: %d) da sequencia.\n", 
           atual->dados.nome, id_referencia, ward_removido.nome, ward_removido.id);
}


void mostrar_wards(const WardsAtivos *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        printf("\n-- Nao ha wards ativos. --\n");
        return;
    }

    printf("\n--- SEQUENCIA DE WARDS ATIVOS ---\n");
    printf(" ORDEM | ID  | NOME\n");
    printf("-------|-----|-----------------------------------\n");

    No *atual = lista->cabeca;
    int ordem = 1;
    while (atual != NULL) {
        printf(" %5d | %3d | %s\n", 
               ordem++, 
               atual->dados.id, 
               atual->dados.nome);

        atual = atual->proximo; 
    }
    printf("---------------------------------------\n");
}


int main() {
    WardsAtivos lista_wards;
    inicializar_wards(&lista_wards);

    int opcao;
    Ward novo_ward;
    int id_referencia_shatter;
    
    printf("===========================================\n");
    printf("  SISTEMA DE GERENCIAMENTO DE WARDS MAGICOS\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU DE FEITICOS ---\n");
        printf("1: Adicionar Ward (fim da lista)\n");
        printf("2: Lancar 'Ward Shatter' (Deletar apos ID)\n");
        printf("3: Mostrar Wards Ativos\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_ward(&novo_ward)) {
                    adicionar_ward_fim(&lista_wards, novo_ward);
                }
                break;
            case 2:
                printf("\n--- WARD SHATTER ---\n");
                printf("Digite o ID do Ward de referencia (o Ward que sera o alvo): ");
                if (scanf("%d", &id_referencia_shatter) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                deletar_apos(&lista_wards, id_referencia_shatter);
                mostrar_wards(&lista_wards); 
                break;
            case 3:
                mostrar_wards(&lista_wards);
                break;
            case 4:
                printf("\nFechando o sistema de wards...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_wards(&lista_wards);
    printf("Programa finalizado.\n");

    return 0;
}