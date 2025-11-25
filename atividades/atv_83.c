#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int matricula;
    char nome[50];
} Jogador;


typedef struct No {
    Jogador dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca; 
    No *cauda;  
} Fila;



void inicializar_fila(Fila *fila) {
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


void liberar_fila(Fila *fila) {
    No *atual = fila->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    fila->cabeca = NULL;
    fila->cauda = NULL;
    printf("\nMemoria da fila liberada.\n");
}



void inserir_inicio(Fila *fila, Jogador novo_jogador) {
    No *novo_no = criar_no(novo_jogador);
    if (novo_no == NULL) return; 
    // Caso 1: Fila vazia
    if (fila->cabeca == NULL) {
        fila->cabeca = novo_no;
        fila->cauda = novo_no;
    } 
    
    else {
        novo_no->proximo = fila->cabeca;
        fila->cabeca = novo_no;
    }

    printf("\n[SUCESSO] %s (Matricula: %d) adicionado com PRIORIDADE ao inicio da fila.\n", 
           novo_jogador.nome, novo_jogador.matricula);
}


void inserir_fim(Fila *fila, Jogador novo_jogador) {
    No *novo_no = criar_no(novo_jogador);
    if (novo_no == NULL) return; 

    
    if (fila->cauda == NULL) {
        fila->cabeca = novo_no;
        fila->cauda = novo_no;
    } 
    
    else {
        
        fila->cauda->proximo = novo_no;
        
        fila->cauda = novo_no;
    }

    printf("\n[SUCESSO] %s (Matricula: %d) adicionado ao final da fila.\n", 
           novo_jogador.nome, novo_jogador.matricula);
}


void mostrar_fila(const Fila *fila) {
    if (fila == NULL || fila->cabeca == NULL) {
        printf("\n-- A fila de batalha esta vazia no momento. --\n");
        return;
    }

    printf("\n--- FILA DE BATALHA (Ordem de Matchmaking) ---\n");
    printf(" POSICAO | MATRICULA | NOME\n");
    printf("---------|-----------|-----------------------------------\n");

    No *atual = fila->cabeca;
    int posicao = 1; 

    
    while (atual != NULL) {
        printf(" %7d | %9d | %s\n", 
               posicao, 
               atual->dados.matricula, 
               atual->dados.nome);

        atual = atual->proximo; 
        posicao++;
    }
    printf("---------------------------------------------------\n");
}


int ler_dados_jogador(Jogador *jogador) {
    char buffer[100]; 

    printf("\nDigite a Matricula do jogador (inteiro): ");
    
    if (scanf("%d", &jogador->matricula) != 1) {
        fprintf(stderr, "Erro: Entrada de Matricula invalida.\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do jogador (max. 49 caracteres): ");
    
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


int main() {
    Fila fila_batalha;
    inicializar_fila(&fila_batalha);

    int opcao;
    Jogador novo_jogador;
    
    printf("===========================================\n");
    printf("       GERENCIADOR DE FILA DE BATALHA\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Adicionar jogador no INICIO (Prioridade)\n");
        printf("2: Adicionar jogador no FIM (Ordem de Chegada)\n");
        printf("3: Mostrar Fila\n");
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
                    inserir_inicio(&fila_batalha, novo_jogador);
                }
                break;
            case 2:
                if (ler_dados_jogador(&novo_jogador)) {
                    inserir_fim(&fila_batalha, novo_jogador);
                }
                break;
            case 3:
                mostrar_fila(&fila_batalha);
                break;
            case 4:
                printf("\nEncerrando o sistema de fila...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_fila(&fila_batalha);
    printf("Programa finalizado.\n");

    return 0;
}