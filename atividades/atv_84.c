#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char titulo[100];
    char status[30]; 
} Missao;


typedef struct No {
    Missao dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca; 
} Diario;



void inicializar_diario(Diario *diario) {
    if (diario != NULL) {
        diario->cabeca = NULL;
    }
}


No* criar_no(Missao nova_missao) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para a nova missao");
        return NULL;
    }
    novo_no->dados = nova_missao;
    novo_no->proximo = NULL;
    return novo_no;
}


void liberar_diario(Diario *diario) {
    No *atual = diario->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    diario->cabeca = NULL;
    printf("\nMemoria do diario de missoes liberada.\n");
}


int ler_dados_missao(Missao *missao) {
    char buffer[150]; 

    printf("\nDigite o ID da Missao (inteiro): ");
    if (scanf("%d", &missao->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Titulo da Missao (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        strncpy(missao->titulo, buffer, sizeof(missao->titulo) - 1);
        missao->titulo[sizeof(missao->titulo) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do titulo.\n");
        return 0;
    }

    
    strcpy(missao->status, "Ativa");
    
    return 1;
}


void adicionar_missao(Diario *diario, Missao nova_missao) {
    No *novo_no = criar_no(nova_missao);
    if (novo_no == NULL) return; 

    
    if (diario->cabeca == NULL) {
        diario->cabeca = novo_no;
    } 
    
    else {
        No *atual = diario->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo; 
        }
        
        atual->proximo = novo_no;
    }

    printf("\n[SUCESSO] Missao '%s' (ID: %d) adicionada ao diario com status '%s'.\n", 
           nova_missao.titulo, nova_missao.id, nova_missao.status);
}


void mostrar_missoes(const Diario *diario) {
    if (diario == NULL || diario->cabeca == NULL) {
        printf("\n-- O diario de missoes esta vazio no momento. --\n");
        return;
    }

    printf("\n--- DIARIO DE MISSOES ATIVAS ---\n");
    printf(" ID  | STATUS    | TITULO\n");
    printf("-----|-----------|-----------------------------------\n");

    No *atual = diario->cabeca;

    
    while (atual != NULL) {
        printf(" %3d | %-9s | %s\n", 
               atual->dados.id, 
               atual->dados.status, 
               atual->dados.titulo);

        atual = atual->proximo; 
    }
    printf("---------------------------------------------------\n");
}


No* pesquisar_missao(const Diario *diario, int id_busca) {
    No *atual = diario->cabeca;

    
    while (atual != NULL) {
        if (atual->dados.id == id_busca) {
            
            return atual;
        }
        atual = atual->proximo; 
    }

    
    return NULL; 
}




int main() {
    Diario quest_log;
    inicializar_diario(&quest_log);

    int opcao;
    Missao nova_missao;
    int id_busca;
    No *missao_encontrada;
    
    printf("===========================================\n");
    printf("       GERENCIADOR DE DIARIO DE MISSOES\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Adicionar Missao\n");
        printf("2: Mostrar Missoes\n");
        printf("3: Buscar Missao por ID\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_missao(&nova_missao)) {
                    adicionar_missao(&quest_log, nova_missao);
                }
                break;
            case 2:
                mostrar_missoes(&quest_log);
                break;
            case 3:
                printf("\n--- Buscar Missao ---\n");
                printf("Digite o ID da Missao que deseja buscar: ");
                if (scanf("%d", &id_busca) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                
                
                int c;
                while ((c = getchar()) != '\n' && c != EOF); 

                missao_encontrada = pesquisar_missao(&quest_log, id_busca);

                if (missao_encontrada != NULL) {
                    printf("\nMissao Encontrada:\n");
                    printf(" ID: %d\n", missao_encontrada->dados.id);
                    printf(" Titulo: %s\n", missao_encontrada->dados.titulo);
                    printf(" Status: %s\n", missao_encontrada->dados.status);
                } else {
                    printf("\nMissao nao encontrada! (ID: %d)\n", id_busca);
                }
                break;
            case 4:
                printf("\nEncerrando o diario de missoes...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_diario(&quest_log);
    printf("Programa finalizado.\n");

    return 0;
}