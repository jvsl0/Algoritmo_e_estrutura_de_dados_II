#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int custo_mana;
} Feitico;


typedef struct NoPilha {
    Feitico dados;
    struct NoPilha *prox;
} NoPilha;


typedef struct {
    NoPilha *topo;
} Pilha;

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}


void push(Pilha *p, const char *nome, int custo_mana) {
    // Aloca memoria para o novo no
    NoPilha *novo_no = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro de alocacao de memoria (Stack Overflow simulado).\n");
        return;
    }

    
    strncpy(novo_no->dados.nome, nome, 49);
    novo_no->dados.nome[49] = '\0';
    novo_no->dados.custo_mana = custo_mana;

    
    novo_no->prox = p->topo;

    
    p->topo = novo_no;

    printf("Comando '%s' (Custo: %d) adicionado ao topo da pilha.\n", nome, custo_mana);
}


void mostrar_pilha(Pilha *p) {
    if (p->topo == NULL) {
        printf("\nPilha de comandos vazia.\n");
        return;
    }

    printf("\n*** PILHA DE COMANDOS DO ARCANISTA (Topo -> Base) ***\n");
    NoPilha *atual = p->topo;
    while (atual != NULL) {
        printf("[ID: %d, Feitico: %s]\n", atual->dados.custo_mana, atual->dados.nome);
        atual = atual->prox;
    }
    printf("---------------------------------------------------\n");
}


void liberar_pilha(Pilha *p) {
    NoPilha *atual = p->topo;
    NoPilha *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    p->topo = NULL;
}

int main() {
    Pilha comandos;
    inicializar_pilha(&comandos);
    int escolha;
    char nome_feitico[50];
    int mana_custo;

    printf("Simulador de Pilha de Comandos do Arcanista (LIFO).\n");

    do {
        printf("\n======================================\n");
        printf("       MENU DE COMANDOS DE FEITICO\n");
        printf("======================================\n");
        printf("1: Adicionar novo feitico (PUSH)\n");
        printf("2: Finalizar sequencia de comandos\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0; 
            while (getchar() != '\n'); 
        } else {
            while (getchar() != '\n'); 
        }

        switch (escolha) {
            case 1: {
                printf("\nNome do Feitico: ");
                if (fgets(nome_feitico, 50, stdin) == NULL) break;
                
                nome_feitico[strcspn(nome_feitico, "\n")] = 0; 

                printf("Custo de Mana (inteiro): ");
                if (scanf("%d", &mana_custo) != 1) {
                    printf("Custo invalido. Tente novamente.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                
                
                push(&comandos, nome_feitico, mana_custo);
                mostrar_pilha(&comandos);
                break;
            }
            case 2:
                printf("\nSequencia de comandos finalizada. O Arcanista esta pronto para agir!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    } while (escolha != 2);

    
    liberar_pilha(&comandos);

    return 0;
}