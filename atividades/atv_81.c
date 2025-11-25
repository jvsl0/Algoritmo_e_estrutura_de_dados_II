#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[50];
} Movimento;


typedef struct No {
    Movimento dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca;
} Lista;


void inicializar_lista(Lista *lista) {
    if (lista != NULL) {
        lista->cabeca = NULL;
    }
}


No* criar_no(Movimento novo_movimento) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo movimento");
        return NULL;
    }
    novo_no->dados = novo_movimento;
    novo_no->proximo = NULL;
    return novo_no;
}


void inserir_no_inicio(Lista *lista, Movimento novo_movimento) {
    if (lista == NULL) {
        printf("Erro: Lista nao inicializada.\n");
        return;
    }

    No *novo_no = criar_no(novo_movimento);
    if (novo_no == NULL) {
        return; 
    }

   
    novo_no->proximo = lista->cabeca;
    
    
    lista->cabeca = novo_no;

    printf("\n[SUCESSO] Movimento '%s' (ID: %d) adicionado ao inicio do combo.\n", 
           novo_movimento.nome, novo_movimento.id);
}


void liberar_lista(Lista *lista) {
    No *atual = lista->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    lista->cabeca = NULL; 
    printf("Memoria de todos os movimentos do combo liberada.\n");
}


void processar_insercao(Lista *combo) {
    Movimento m;
    char buffer[100]; 

    printf("\n--- Novo Movimento (Ataque) ---\n");
    printf("Digite o ID do movimento (inteiro): ");
    
    
    if (scanf("%d", &m.id) != 1) {
        fprintf(stderr, "Erro de entrada. Por favor, digite um número.\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do movimento (max. 49 caracteres): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    
        buffer[strcspn(buffer, "\n")] = 0;
        
        strncpy(m.nome, buffer, sizeof(m.nome) - 1);
        m.nome[sizeof(m.nome) - 1] = '\0'; 
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return;
    }

    
    inserir_no_inicio(combo, m);
}


int main() {
    Lista combo;
    inicializar_lista(&combo);

    int opcao;
    
    printf("===========================================\n");
    printf("    SISTEMA DE LOG DE COMBO (Jogo de Luta)\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Inserir novo movimento no inicio do combo\n");
        printf("2: Sair e Limpar Memoria\n");
        printf("Escolha a opcao: ");

        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
        }
        
        switch (opcao) {
            case 1:
                processar_insercao(&combo);
                break;
            case 2:
                printf("\nEncerrando o sistema de combo...\n");
                break;
            default:
                printf("\nOpção invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 2);

    liberar_lista(&combo);
    printf("Programa finalizado.\n");

    return 0;
}