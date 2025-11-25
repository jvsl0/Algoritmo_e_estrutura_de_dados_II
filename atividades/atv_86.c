#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[100];
} Heroi;


typedef struct No {
    Heroi dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca;
} Formacao;


void inicializar_formacao(Formacao *formacao) {
    if (formacao != NULL) {
        formacao->cabeca = NULL;
    }
}

No* criar_no(Heroi novo_heroi) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo heroi");
        return NULL;
    }
    novo_no->dados = novo_heroi;
    novo_no->proximo = NULL;
    return novo_no;
}

void liberar_formacao(Formacao *formacao) {
    No *atual = formacao->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    formacao->cabeca = NULL;
    printf("\nMemoria da formacao de batalha liberada.\n");
}

int ler_dados_heroi(Heroi *heroi) {
    char buffer[150];

    printf("\nDigite o ID do Heroi (inteiro): ");
    if (scanf("%d", &heroi->id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do Heroi (max. 99 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(heroi->nome, buffer, sizeof(heroi->nome) - 1);
        heroi->nome[sizeof(heroi->nome) - 1] = '\0';
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return 0;
    }
    
    return 1;
}


void adicionar_heroi_fim(Formacao *formacao, Heroi novo_heroi) {
    No *novo_no = criar_no(novo_heroi);
    if (novo_no == NULL) return; 

    if (formacao->cabeca == NULL) {
        formacao->cabeca = novo_no;
    } 
    else {
        No *atual = formacao->cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }

    printf("\n[SUCESSO] Heroi '%s' (ID: %d) adicionado ao fim da formacao.\n", 
           novo_heroi.nome, novo_heroi.id);
}


void inserir_antes(Formacao *formacao, Heroi guarda_costas, int id_vip) {
    No *novo_no = criar_no(guarda_costas);
    if (novo_no == NULL) return; 

    
    if (formacao->cabeca == NULL) {
        printf("\n[ERRO] A formacao esta vazia. Nao e possivel proteger o VIP com ID %d.\n", id_vip);
        free(novo_no);
        return;
    }

    
    if (formacao->cabeca->dados.id == id_vip) {
        novo_no->proximo = formacao->cabeca;
        formacao->cabeca = novo_no;
        printf("\n[SUCESSO] Guarda-Costas '%s' (ID: %d) inserido ANTES do VIP '%s' (ID: %d), agora ele e o primeiro da formacao.\n", 
               guarda_costas.nome, guarda_costas.id, formacao->cabeca->proximo->dados.nome, id_vip);
        return;
    }

    
    No *anterior = formacao->cabeca;
    No *atual = formacao->cabeca->proximo;
    
    
    while (atual != NULL && atual->dados.id != id_vip) {
        anterior = atual;
        atual = atual->proximo;
    }

    
    if (atual == NULL) {
        printf("\n[ERRO] O VIP com ID %d nao foi encontrado na formacao. Insercao de Guarda-Costas cancelada.\n", id_vip);
        free(novo_no);
        return;
    }
    
    
    novo_no->proximo = atual;
    anterior->proximo = novo_no;

    printf("\n[SUCESSO] Guarda-Costas '%s' (ID: %d) inserido ANTES do VIP '%s' (ID: %d).\n", 
           guarda_costas.nome, guarda_costas.id, atual->dados.nome, id_vip);
}



void mostrar_formacao(const Formacao *formacao) {
    if (formacao == NULL || formacao->cabeca == NULL) {
        printf("\n-- A formacao de batalha esta vazia. --\n");
        return;
    }

    printf("\n--- FORMACAO DE BATALHA ---\n");
    printf(" ORDEM | ID  | NOME\n");
    printf("-------|-----|-----------------------------------\n");

    No *atual = formacao->cabeca;
    int ordem = 1;
    while (atual != NULL) {
        // Exibe o heroi
        printf(" %5d | %3d | %s\n", 
               ordem++, 
               atual->dados.id, 
               atual->dados.nome);

        
        if (ordem == 2) {
            printf("--------------------------------------- (LINHA DE FRENTE)\n");
        }

        atual = atual->proximo; 
    }
    printf("---------------------------------------\n");
}



int main() {
    Formacao formacao;
    inicializar_formacao(&formacao);

    int opcao;
    Heroi novo_heroi;
    int id_vip_alvo;
    
    printf("===========================================\n");
    printf("    GERENCIADOR DE FORMACAO DE BATALHA\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1: Adicionar Heroi no FIM da Formacao\n");
        printf("2: Adicionar Guarda-Costas (Inserir ANTES)\n");
        printf("3: Mostrar Formacao\n");
        printf("4: Sair\n");
        printf("Escolha a opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                if (ler_dados_heroi(&novo_heroi)) {
                    adicionar_heroi_fim(&formacao, novo_heroi);
                }
                break;
            case 2:
                printf("\n--- Inserir Guarda-Costas (Inserir ANTES) ---\n");
                
                
                if (!ler_dados_heroi(&novo_heroi)) {
                    break;
                }
                
                
                printf("Digite o ID do Heroi VIP (existente) que sera protegido (inserir antes): ");
                if (scanf("%d", &id_vip_alvo) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID do VIP invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                
                
                inserir_antes(&formacao, novo_heroi, id_vip_alvo);

                break;
            case 3:
                mostrar_formacao(&formacao);
                break;
            case 4:
                printf("\nEncerrando o gerenciador de formacao...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_formacao(&formacao);
    printf("Programa finalizado.\n");

    return 0;
}