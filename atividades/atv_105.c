#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da struct Feitico (os dados do comando)
typedef struct {
    char nome[50];
    int custo_mana;
} Feitico;

// Definicao do No da Pilha (lista encadeada)
typedef struct NoPilha {
    Feitico dados;
    struct NoPilha *prox;
} NoPilha;

// Definicao da Pilha (o cabecalho)
typedef struct {
    NoPilha *topo;
} Pilha;

// Inicializacao
void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

// Verifica se a pilha esta vazia
int vazia(Pilha *p) {
    return (p->topo == NULL);
}

// Implementacao da operacao PUSH (Adicionar ao Topo da Pilha)
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

// Implementacao da operacao POP (Remover do Topo da Pilha)
Feitico pop(Pilha *p) {
    Feitico feitico_removido = {"", -1};

    if (vazia(p)) {
        // Nao exibe mensagem de erro aqui, pois pop e usado internamente pelo liberar_pilha
        // e pelo inverter_pilha, onde a verificacao de vazio ja foi feita.
        return feitico_removido;
    }

    NoPilha *no_a_remover = p->topo;
    
    feitico_removido = no_a_remover->dados;

    p->topo = no_a_remover->prox;

    free(no_a_remover);

    return feitico_removido;
}

// Implementacao da operacao TOP/PEEK (Consulta o topo da pilha sem remover)
Feitico top(Pilha *p) {
    Feitico feitico_consulta = {"", -1};

    if (vazia(p)) {
        printf("A pilha de comandos esta vazia! Nao ha feiticos para consultar.\n");
        return feitico_consulta;
    }

    return p->topo->dados;
}

// Implementacao da funcao INVERTER PILHA
void inverter_pilha(Pilha *p) {
    if (vazia(p)) {
        printf("\nNao ha feiticos na pilha. Nada para inverter.\n");
        return;
    }

    // 1. Cria e inicializa a pilha auxiliar
    Pilha auxiliar;
    inicializar_pilha(&auxiliar);
    Feitico feitico_aux;

    // 2. Primeira Passagem: Move todos os elementos da Pilha Original para a Auxiliar
    // Isso inverte a ordem: (Topo1, ..., Base1) -> (Base1, ..., Topo1)
    while (!vazia(p)) {
        feitico_aux = pop(p);
        push(&auxiliar, feitico_aux.nome, feitico_aux.custo_mana);
    }
    
    // 3. Segunda Passagem: Move todos os elementos da Pilha Auxiliar de volta para a Original
    // Isso inverte a ordem novamente, resultando na ordem original invertida: (Topo1, ..., Base1)
    while (!vazia(&auxiliar)) {
        feitico_aux = pop(&auxiliar);
        push(p, feitico_aux.nome, feitico_aux.custo_mana);
    }

    printf("\n✅ Ordem dos feiticos invertida com sucesso! O primeiro feitico adicionado agora sera o proximo a ser lancado.\n");
}


// Funcao para exibir a Pilha de Comandos
void mostrar_pilha(Pilha *p) {
    if (vazia(p)) {
        printf("\nA pilha de comandos esta vazia.\n");
        return;
    }

    printf("\n*** PILHA DE COMANDOS DO ARCANISTA (Topo -> Base) ***\n");
    printf("   (O comando no TOPO e o proximo a ser executado)\n");
    
    NoPilha *atual = p->topo;
    int indice = 1;
    while (atual != NULL) {
        printf("%d. Feitico: %s | Custo de Mana: %d\n", indice, atual->dados.nome, atual->dados.custo_mana);
        atual = atual->prox;
        indice++;
    }
    printf("---------------------------------------------------\n");
}

// Funcao para liberar toda a memoria da pilha
void liberar_pilha(Pilha *p) {
    while (!vazia(p)) {
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
        printf("4: Consultar Proximo Feitico (TOP)\n");
        printf("5: Verificar Status da Pilha\n");
        printf("6: Inverter Ordem dos Feiticos (REVERTER ESTRATEGIA)\n");
        printf("7: Finalizar e Sair\n");
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
                } else {
                    printf("\nNao foi possivel lancar o feitico. Pilha vazia.\n");
                }
                break;
            }
            case 3:
                mostrar_pilha(&comandos);
                break;
            case 4: {
                Feitico proximo_feitico = top(&comandos);
                
                if (proximo_feitico.custo_mana != -1) {
                    printf("\n[PROXIMO COMANDO]: Feitico '%s' | Custo de Mana: %d\n", 
                           proximo_feitico.nome, 
                           proximo_feitico.custo_mana);
                }
                break;
            }
            case 5:
                if (vazia(&comandos)) {
                    printf("\n[STATUS]: A pilha de comandos esta VAZIA.\n");
                } else {
                    printf("\n[STATUS]: A pilha de comandos possui feiticos PENDENTES.\n");
                }
                break;
            case 6:
                inverter_pilha(&comandos);
                break;
            case 7:
                printf("\nSequencia de acoes encerrada.\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    } while (escolha != 7);

    printf("\nLiberando memoria restante da pilha de comandos...\n");
    liberar_pilha(&comandos);

    return 0;
}