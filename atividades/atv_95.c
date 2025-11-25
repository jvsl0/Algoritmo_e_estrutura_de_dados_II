#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Inimigo {
    int id;
    char tipo[50];
    struct Inimigo *prox;
} Inimigo;

typedef struct {
    Inimigo *inicio;
} Lista;

void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
}

void liberar_lista(Lista *lista) {
    Inimigo *atual = lista->inicio;
    Inimigo *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
}

void inserir_fim(Lista *lista, int id, char tipo[]) {
    Inimigo *novo_inimigo = (Inimigo *)malloc(sizeof(Inimigo));
    if (novo_inimigo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novo_inimigo->id = id;
    strcpy(novo_inimigo->tipo, tipo);
    novo_inimigo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo_inimigo;
    } else {
        Inimigo *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_inimigo;
    }
}

void mostrar_lista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nCampo de Batalha: Vazio (Aguardando proxima onda).\n");
        return;
    }

    printf("\nALVOS ATIVOS (ONDA ATUAL)\n");
    Inimigo *atual = lista->inicio;
    int contador = 1;
    while (atual != NULL) {
        printf("%d. ID: %d | Tipo: %s\n", contador, atual->id, atual->tipo);
        atual = atual->prox;
        contador++;
    }
    printf("------------------------------------------\n");
}

Lista criar_lista(int n) {
    Lista nova_onda;
    inicializar_lista(&nova_onda);
    int i;
    int id_inimigo;
    char tipo_inimigo[50];

    printf("\n--- Leitura dos %d Inimigos da Nova Onda ---\n", n);
    
    for (i = 0; i < n; i++) {
        printf("\nInimigo %d:\n", i + 1);
        
        printf("  ID: ");
        if (scanf("%d", &id_inimigo) != 1) {
             printf("ID invalido. Insercao interrompida.\n");
             liberar_lista(&nova_onda);
             inicializar_lista(&nova_onda);
             return nova_onda;
        }
        while (getchar() != '\n');
        
        printf("  Tipo: ");
        if (fgets(tipo_inimigo, 50, stdin) == NULL) {
             printf("Tipo invalido. Insercao interrompida.\n");
             liberar_lista(&nova_onda);
             inicializar_lista(&nova_onda);
             return nova_onda;
        }
        tipo_inimigo[strcspn(tipo_inimigo, "\n")] = 0;

        inserir_fim(&nova_onda, id_inimigo, tipo_inimigo);
    }
    printf("\n--- Nova Onda de %d Inimigos Criada com Sucesso ---\n", n);
    return nova_onda;
}

int main() {
    Lista alvos_ativos;
    inicializar_lista(&alvos_ativos);
    int escolha;
    int num_inimigos;

    printf("Inicializando o Jogo de Defesa de Torre...\n");

    do {
        printf("\n==================================\n");
        printf("       GERENCIAMENTO DE ONDA\n");
        printf("==================================\n");
        printf("1. Iniciar Nova Onda\n");
        printf("2. Mostrar Alvos Ativos\n");
        printf("3. Sair do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: {
                printf("\nQuantos inimigos a nova onda tera? ");
                if (scanf("%d", &num_inimigos) != 1 || num_inimigos <= 0) {
                    printf("Numero de inimigos invalido.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                liberar_lista(&alvos_ativos);
                
                alvos_ativos = criar_lista(num_inimigos);
                
                mostrar_lista(&alvos_ativos);
                break;
            }
            case 2:
                mostrar_lista(&alvos_ativos);
                break;
            case 3:
                printf("\nEncerrando o jogo. Liberando todos os recursos...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 3);

    liberar_lista(&alvos_ativos);

    return 0;
}