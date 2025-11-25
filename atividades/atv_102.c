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
    NoPilha *novo_no = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    strncpy(novo_no->dados.nome, nome, 49);
    novo_no->dados.nome[49] = '\0';
    novo_no->dados.custo_mana = custo_mana;

    novo_no->prox = p->topo;

    p->topo = novo_no;

    printf("Comando '%s' (Custo: %d) adicionado ao topo da pilha.\n", nome, custo_mana);
}


Feitico pop(Pilha *p) {
    
    Feitico feitico_removido = {"", -1};

    if (p->topo == NULL) {
        printf("A pilha de comandos esta vazia! Nada para lancar.\n");
        return feitico_removido;
    }

    NoPilha *no_a_remover = p->topo;
    
    
    feitico_removido = no_a_remover->dados;

    
    p->topo = no_a_remover->prox;

    
    free(no_a_remover);

    return feitico_removido;
}


void mostrar_pilha(Pilha *p) {
    if (p->topo == NULL) {
        printf("\nA pilha de comandos esta vazia.\n");
        return;
    }

    printf("\n*** PILHA DE COMANDOS DO ARCANISTA (Topo -> Base) ***\n");
    printf("   (Ultimo comando sera o PRIMEIRO a ser executado)\n");
    
    NoPilha *atual = p->topo;
    int indice = 1;
    while (atual != NULL) {
        printf("%d. Feitico: %s | Custo de Mana: %d\n", indice, atual->dados.nome, atual->dados.custo_mana);
        atual = atual->prox;
        indice++;
    }
    printf("---------------------------------------------------\n");
}


void liberar_pilha(Pilha *p) {
   
    while (p->topo != NULL) {
        pop(p); 
    }
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
        printf("2: Lancar Proximo Feitico (POP)\n");
        printf("3: Mostrar Pilha de Comandos\n");
        printf("4: Finalizar e Sair\n");
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
                break;
            }
            case 2: {
                Feitico feitico_lancado = pop(&comandos);
                
                
                if (feitico_lancado.custo_mana != -1) {
                    printf("\nFeitico '%s' (Custo: %d) lancado com sucesso!\n", 
                           feitico_lancado.nome, 
                           feitico_lancado.custo_mana);
                }
                break;
            }
            case 3:
                mostrar_pilha(&comandos);
                break;
            case 4:
                printf("\nSequencia de acoes encerrada.\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    } while (escolha != 4);


    printf("\nLiberando memoria restante da pilha de comandos...\n");
    liberar_pilha(&comandos);

    return 0;
}