#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} Aventureiro;

typedef struct No {
    Aventureiro dados;
    struct No *proximo;
} No;


typedef struct {
    No *cabeca;
} Grupo;


void inicializar_grupo(Grupo *grupo) {
    if (grupo != NULL) {
        grupo->cabeca = NULL;
    }
}


No* criar_no(Aventureiro novo_aventureiro) {
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL) {
        perror("Erro ao alocar memoria para o novo aventureiro");
        return NULL;
    }
    novo_no->dados = novo_aventureiro;
    novo_no->proximo = NULL;
    return novo_no;
}


void liberar_grupo(Grupo *grupo) {
    No *atual = grupo->cabeca;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual); 
        atual = proximo;
    }
    grupo->cabeca = NULL;
    printf("\nMemoria de todos os aventureiros do grupo liberada.\n");
}


void adicionar_aventureiro(Grupo *grupo, Aventureiro novo_aventureiro) {
    if (grupo == NULL) {
        printf("Erro: Grupo não inicializado.\n");
        return;
    }

    
    No *novo_no = criar_no(novo_aventureiro);
    if (novo_no == NULL) {
        return; 
    }

    
    novo_no->proximo = grupo->cabeca;
    
    grupo->cabeca = novo_no;

    printf("\n[SUCESSO] %s (ID: %d) se juntou ao grupo e assumiu a lideranca.\n", 
           novo_aventureiro.nome, novo_aventureiro.id);
}

void mostrar_grupo(const Grupo *grupo) {
    if (grupo == NULL || grupo->cabeca == NULL) {
        printf("\nO grupo de aventureiros esta vazio no momento.\n");
        return;
    }

    printf("\n--- ROSTER DE AVENTUREIROS ---\n");
    printf(" ORDEM | ID  | NOME\n");
    printf("-------|-----|-----------------------------------\n");

    No *atual = grupo->cabeca;
    int ordem = 1; 

    while (atual != NULL) {
        printf(" %5d | %3d | %s\n", 
               ordem, 
               atual->dados.id, 
               atual->dados.nome);

        atual = atual->proximo; 
        ordem++;
    }
    printf("-----------------------------------------------\n");
}


void ler_e_adicionar_aventureiro(Grupo *grupo) {
    Aventureiro a;
    char buffer[100]; 

    printf("\n--- Adicionar Novo Aventureiro ---\n");
    printf("Digite o ID do aventureiro (inteiro): ");
    
    if (scanf("%d", &a.id) != 1) {
        fprintf(stderr, "Erro: Entrada de ID invalida.\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    printf("Digite o Nome do aventureiro (max. 49 caracteres): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
       
        buffer[strcspn(buffer, "\n")] = 0;
        
        strncpy(a.nome, buffer, sizeof(a.nome) - 1);
        a.nome[sizeof(a.nome) - 1] = '\0'; 
    } else {
        fprintf(stderr, "Erro de leitura do nome.\n");
        return;
    }

    
    adicionar_aventureiro(grupo, a);
}

int main() {
    Grupo grupo_principal;
    inicializar_grupo(&grupo_principal);

    int opcao;
    
    printf("===========================================\n");
    printf("   GERENCIADOR DE GRUPO DE AVENTUREIROS\n");
    printf("===========================================\n");

    do {
        printf("\n--- MENU DE GRUPO ---\n");
        printf("1: Adicionar Novo Aventureiro (Assume a Lideranca)\n");
        printf("2: Mostrar Grupo (Roster)\n");
        printf("3: Sair\n");
        printf("Escolha a opcao: ");

        
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; 
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        switch (opcao) {
            case 1:
                ler_e_adicionar_aventureiro(&grupo_principal);
                break;
            case 2:
                mostrar_grupo(&grupo_principal);
                break;
            case 3:
                printf("\nEncerrando o gerenciador de grupo...\n");
                break;
            default:
                printf("\nOpção invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 3);

    liberar_grupo(&grupo_principal);
    printf("Programa finalizado.\n");

    return 0;
}