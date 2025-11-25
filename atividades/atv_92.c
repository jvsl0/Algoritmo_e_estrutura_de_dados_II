#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[100];
} Mercenario;


typedef struct No {
    Mercenario dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca;
    No *cauda;
} Companhia;


void inicializar_companhia(Companhia *lista) {
    if (lista != NULL) {
        lista->cabeca = NULL;
        lista->cauda = NULL;
    }
}

No* criar_no(Mercenario novo_mercenario) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo mercenario");
        return NULL;
    }
    novo_no->dados = novo_mercenario;
    novo_no->proximo = NULL;
    return novo_no;
}

void demitir_todos_mercenarios(Companhia *lista) {
    if (lista->cabeca == NULL) {
        printf("\n[ATENCAO] A companhia ja esta dissolvida.\n");
        return;
    }
    
    No *atual = lista->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabeca = NULL;
    lista->cauda = NULL;
    printf("\n===========================================\n");
    printf("  [SUCESSO] COMPANHIA DISSOLVIDA! Falencia declarada.\n");
    printf("  Todos os registros de mercenarios foram limpos (memoria liberada).\n");
    printf("===========================================\n");
}

int ler_dados_mercenario(Mercenario *mercenario) {
    char buffer[150];

    printf("\nDigite o ID do Mercenario (inteiro): ");
    if (scanf("%d", &mercenario->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do Mercenario (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(mercenario->nome, buffer, sizeof(mercenario->nome) - 1);
        mercenario->nome[sizeof(mercenario->nome) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return 0;
    }
    
    return 1;
}


void contratar_mercenario(Companhia *lista, Mercenario novo_mercenario) {
    No *novo_no = criar_no(novo_mercenario);
    if (novo_no == NULL) return; 

    if (lista->cabeca == NULL) {
        
        lista->cabeca = novo_no;
        lista->cauda = novo_no;
    } 
    else {
        
        lista->cauda->proximo = novo_no;
        
        lista->cauda = novo_no;
    }

    printf("\n[SUCESSO] Mercenario '%s' (ID: %d) contratado para a companhia.\n", 
           novo_mercenario.nome, novo_mercenario.id);
}


void exibir_companhia(const Companhia *lista) {
    if (lista == NULL || lista->cabeca == NULL) {
        printf("\n-- A companhia esta vazia ou dissolvida. --\n");
        return;
    }

    printf("\n--- COMPANHIA DE MERCENARIOS ATIVA ---\n");
    printf(" POSICAO | ID  | NOME\n");
    printf("---------|-----|-----------------------------------\n");

    No *atual = lista->cabeca;
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
    Companhia companhia;
    inicializar_companhia(&companhia);

    int opcao;
    Mercenario novo_mercenario;
    
    printf("===========================================\n");
    printf(" GERENCIADOR DE COMPANHIA DE MERCENARIOS\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU DE GERENCIAMENTO ---\n");
        printf("1: Contratar Mercenario (inserir no fim)\n");
        printf("2: Exibir Companhia\n");
        printf("3: Declarar Falencia (Deletar lista inteira)\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_mercenario(&novo_mercenario)) {
                    contratar_mercenario(&companhia, novo_mercenario);
                }
                break;
            case 2:
                exibir_companhia(&companhia);
                break;
            case 3:
                demitir_todos_mercenarios(&companhia);
                exibir_companhia(&companhia); 
                break;
            case 4:
                printf("\nFechando o gerenciador. A memoria sera liberada.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    
    if (companhia.cabeca != NULL) {
        demitir_todos_mercenarios(&companhia);
    }
    printf("Programa finalizado.\n");

    return 0;
}