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
    No *cauda;
} Guilda;


void inicializar_guilda(Guilda *guilda) {
    if (guilda != NULL) {
        guilda->cabeca = NULL;
        guilda->cauda = NULL;
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

void liberar_guilda(Guilda *guilda) {
    No *atual = guilda->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    guilda->cabeca = NULL;
    guilda->cauda = NULL;
    printf("\nMemoria da lista de herois liberada.\n");
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


void adicionar_heroi_fim(Guilda *guilda, Heroi novo_heroi) {
    No *novo_no = criar_no(novo_heroi);
    if (novo_no == NULL) return; 

    if (guilda->cabeca == NULL) {
        
        guilda->cabeca = novo_no;
        guilda->cauda = novo_no;
    } 
    else {
        
        guilda->cauda->proximo = novo_no;
        
        guilda->cauda = novo_no;
    }

    printf("\n[SUCESSO] Heroi '%s' (ID: %d) registrado na guilda.\n", 
           novo_heroi.nome, novo_heroi.id);
}



void dispensar_heroi(Guilda *guilda, int id_dispensa) {
    
    if (guilda->cabeca == NULL) {
        printf("\n[ATENCAO] A guilda esta vazia. Nao ha herois para dispensar.\n");
        return;
    }

    No *atual = guilda->cabeca;
    No *anterior = NULL;

    
    while (atual != NULL && atual->dados.id != id_dispensa) {
        anterior = atual;
        atual = atual->proximo;
    }

    
    if (atual == NULL) {
        printf("\n[ERRO] Heroi com ID %d nao encontrado na guilda. Nenhuma dispensa realizada.\n", id_dispensa);
        return;
    }

    
    Heroi heroi_dispensado = atual->dados;

    
    if (anterior == NULL) {
        guilda->cabeca = atual->proximo;
        
        
        if (guilda->cabeca == NULL) {
            guilda->cauda = NULL;
        }
    } 
    
    else {
        anterior->proximo = atual->proximo;
        
        
        if (atual == guilda->cauda) {
            guilda->cauda = anterior;
        }
    }

    free(atual); 
    printf("\n[DISPENSA CONCLUIDA] Heroi '%s' (ID: %d) foi dispensado da guilda.\n", 
           heroi_dispensado.nome, heroi_dispensado.id);
}


void mostrar_herois(const Guilda *guilda) {
    if (guilda == NULL || guilda->cabeca == NULL) {
        printf("\n-- A guilda esta vazia. Nao ha herois registrados. --\n");
        return;
    }

    printf("\n--- REGISTRO DE HEROIS DA GUILDA ---\n");
    printf(" POSICAO | ID  | NOME\n");
    printf("---------|-----|-----------------------------------\n");

    No *atual = guilda->cabeca;
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
    Guilda guilda;
    inicializar_guilda(&guilda);

    int opcao;
    Heroi novo_heroi;
    int id_dispensar;
    
    printf("===========================================\n");
    printf("      GERENCIADOR DE GUILDA DE HEROIS\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU DA GUILDA ---\n");
        printf("1: Adicionar novo heroi (fim da lista)\n");
        printf("2: Mostrar todos os herois\n");
        printf("3: Dispensar heroi por ID\n");
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
                    adicionar_heroi_fim(&guilda, novo_heroi);
                }
                break;
            case 2:
                mostrar_herois(&guilda);
                break;
            case 3:
                printf("\n--- DISPENSAR HEROI ---\n");
                printf("Digite o ID do heroi a ser dispensado: ");
                if (scanf("%d", &id_dispensar) != 1) {
                    fprintf(stderr, "Erro: Entrada de ID invalida.\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                dispensar_heroi(&guilda, id_dispensar);
                mostrar_herois(&guilda); 
                break;
            case 4:
                printf("\nFechando o salao da guilda...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    liberar_guilda(&guilda);
    printf("Programa finalizado.\n");

    return 0;
}