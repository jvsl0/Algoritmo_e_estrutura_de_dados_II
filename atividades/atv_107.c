#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicoes de Estruturas
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

// Protótipos de Funcoes
void inicializar_pilha(Pilha *p);
int vazia(Pilha *p);
void push(Pilha *p, const char *nome, int custo_mana);
Feitico pop(Pilha *p);
Feitico top(Pilha *p);
void inverter_pilha(Pilha *p);
void mostrar_pilha(Pilha *p);
void salvar_pilha_em_arquivo(Pilha *p, const char* nome_arquivo);
void liberar_pilha(Pilha *p);

// Implementacao da operacao PUSH
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
}

// Implementacao da operacao POP
Feitico pop(Pilha *p) {
    Feitico feitico_removido = {"", -1};
    if (vazia(p)) return feitico_removido;

    NoPilha *no_a_remover = p->topo;
    feitico_removido = no_a_remover->dados;
    p->topo = no_a_remover->prox;
    free(no_a_remover);

    return feitico_removido;
}

// Implementacao da funcao INVERTER PILHA
void inverter_pilha(Pilha *p) {
    if (vazia(p)) return;

    Pilha auxiliar;
    inicializar_pilha(&auxiliar);
    Feitico feitico_aux;

    // 1. Original -> Auxiliar (Inverte a ordem)
    while (!vazia(p)) {
        feitico_aux = pop(p);
        push(&auxiliar, feitico_aux.nome, feitico_aux.custo_mana);
    }
    
    // 2. Auxiliar -> Original (Inverte de volta, restaurando a ordem original)
    while (!vazia(&auxiliar)) {
        feitico_aux = pop(&auxiliar);
        push(p, feitico_aux.nome, feitico_aux.custo_mana);
    }
}

// Implementacao da funcao SALVAR PILHA
void salvar_pilha_em_arquivo(Pilha *p, const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("\nERRO: Nao foi possivel abrir o arquivo %s para escrita.\n", nome_arquivo);
        return;
    }

    NoPilha *atual = p->topo;
    int contagem = 0;

    while (atual != NULL) {
        fwrite(&(atual->dados), sizeof(Feitico), 1, arquivo);
        atual = atual->prox;
        contagem++;
    }

    fclose(arquivo);
    printf("\nSUCESSO: Sequencia de %d feiticos salva no grimorio magico (%s).\n", contagem, nome_arquivo);
}

// FUNCAO PRINCIPAL DA TAREFA: Carregar a pilha de arquivo binario
void carregar_pilha_de_arquivo(Pilha *p, const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");

    // Requisito 1: Se o arquivo nao existe, retorna e inicializa a pilha vazia
    if (arquivo == NULL) {
        printf("\nNenhum grimorio encontrado (%s), iniciando com uma pilha vazia.\n", nome_arquivo);
        return;
    }

    Feitico feitico_lido;
    int contagem_lida = 0;
    
    // Leitura: O primeiro item do arquivo e empilhado primeiro (vira a base)
    while (fread(&feitico_lido, sizeof(Feitico), 1, arquivo) == 1) {
        push(p, feitico_lido.nome, feitico_lido.custo_mana);
        contagem_lida++;
    }
    
    fclose(arquivo);

    if (contagem_lida > 0) {
        // Ponto Critico: Inverte a pilha para restaurar a ordem Topo->Base correta
        inverter_pilha(p);
        printf("\nGrimorio carregado com sucesso! %d feiticos restaurados.\n", contagem_lida);
    } else {
        printf("\nGrimorio carregado, mas estava vazio.\n");
    }
}


// Funcoes Auxiliares
void inicializar_pilha(Pilha *p) { p->topo = NULL; }
int vazia(Pilha *p) { return (p->topo == NULL); }
Feitico top(Pilha *p) {
    Feitico feitico_consulta = {"", -1};
    if (vazia(p)) {
        printf("A pilha de comandos esta vazia! Nao ha feiticos para consultar.\n");
        return feitico_consulta;
    }
    return p->topo->dados;
}
void mostrar_pilha(Pilha *p) {
    if (vazia(p)) {
        printf("\nA pilha de comandos esta vazia.\n");
        return;
    }
    printf("\n*** PILHA DE COMANDOS DO ARCANISTA (Topo -> Base) ***\n");
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
    while (!vazia(p)) {
        pop(p); 
    }
}

int main() {
    Pilha comandos;
    inicializar_pilha(&comandos);
    const char *nome_arquivo_save = "grimorio.bin";
    
    // CHAVE DA TAREFA: Carrega o estado anterior da pilha
    carregar_pilha_de_arquivo(&comandos, nome_arquivo_save);

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
        printf("5: Salvar Sequencia no Grimorio\n");
        printf("6: Verificar Status da Pilha\n");
        printf("7: Inverter Ordem dos Feiticos (REVERTER ESTRATEGIA)\n");
        printf("8: Finalizar e Sair\n");
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
                salvar_pilha_em_arquivo(&comandos, nome_arquivo_save);
                break;
            case 6:
                if (vazia(&comandos)) {
                    printf("\n[STATUS]: A pilha de comandos esta VAZIA.\n");
                } else {
                    printf("\n[STATUS]: A pilha de comandos possui feiticos PENDENTES.\n");
                }
                break;
            case 7:
                inverter_pilha(&comandos);
                printf("\nOrdem dos feiticos invertida!\n");
                break;
            case 8:
                printf("\nSequencia de acoes encerrada. Ate a proxima aventura!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    } while (escolha != 8);

    liberar_pilha(&comandos);

    return 0;
}