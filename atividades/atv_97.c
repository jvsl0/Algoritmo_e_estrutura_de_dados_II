#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do no da lista
typedef struct Membro {
    int id;
    char nome[100];
    struct Membro *prox;
} Membro;

// Definição da estrutura de dados para IO Binario (CORRECAO: Movida para escopo global)
typedef struct DadosMembro {
    int id;
    char nome[100];
} DadosMembro;

typedef struct {
    Membro *inicio;
} Lista;

// Funcoes de suporte
void inicializar_lista(Lista *lista) {
    lista->inicio = NULL;
}

void liberar_lista(Lista *lista) {
    Membro *atual = lista->inicio;
    Membro *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
}

void inserir_fim(Lista *lista, int id, char nome[]) {
    Membro *novo_membro = (Membro *)malloc(sizeof(Membro));
    if (novo_membro == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novo_membro->id = id;
    strcpy(novo_membro->nome, nome);
    novo_membro->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo_membro;
    } else {
        Membro *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_membro;
    }
    printf("Membro ID %d (%s) adicionado.\n", id, nome);
}

void mostrar_lista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nRegistro da Guilda: Vazio.\n");
        return;
    }

    printf("\nREGISTRO ATUAL DA GUILDA\n");
    Membro *atual = lista->inicio;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("--------------------------------\n");
}

// FUNCAO PRINCIPAL DA TAREFA: SALVAR EM ARQUIVO BINARIO
void salvar_guild_arquivo(Lista lista) {
    FILE *arquivo = fopen("guild_roster.bin", "wb");
    Membro *atual = lista.inicio;

    if (arquivo == NULL) {
        printf("\nERRO: Nao foi possivel abrir o arquivo guild_roster.bin para escrita.\n");
        return;
    }
    
    // Percorre a lista e salva cada struct de dados no arquivo binario
    while (atual != NULL) {
        // Agora, DadosMembro e um tipo conhecido (global)
        DadosMembro dados_para_salvar;
        dados_para_salvar.id = atual->id;
        strcpy(dados_para_salvar.nome, atual->nome);

        // Escreve apenas os DadosMembro no arquivo
        fwrite(&dados_para_salvar, sizeof(DadosMembro), 1, arquivo);

        atual = atual->prox;
    }

    fclose(arquivo);
    // Usa o tipo DadosMembro corretamente definido no escopo global
    printf("\nSUCESSO: O estado da guilda foi salvo em 'guild_roster.bin'. (%d bytes salvos por membro).\n", (int)sizeof(DadosMembro));
}


int main() {
    Lista guilda;
    inicializar_lista(&guilda);
    int escolha;
    
    printf("--- Simulacao de Gerenciamento de Guilda ---\n");
    inserir_fim(&guilda, 1, "Lider Supremo");
    inserir_fim(&guilda, 2, "Cavaleiro Zero");
    inserir_fim(&guilda, 3, "Mago Arcano");

    do {
        printf("\n==================================\n");
        printf("       MENU DA GUILDA\n");
        printf("==================================\n");
        printf("1. Adicionar Novo Membro\n");
        printf("2. Mostrar Registro da Guilda\n");
        printf("3. SALVAR Guilda em Arquivo Binario\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: {
                int novo_id;
                char nome_novo_membro[100];
                printf("\nID do novo membro: ");
                if (scanf("%d", &novo_id) != 1) break; 
                while (getchar() != '\n');
                
                printf("Nome do novo membro: ");
                if (fgets(nome_novo_membro, 100, stdin) == NULL) break;
                nome_novo_membro[strcspn(nome_novo_membro, "\n")] = 0; 

                inserir_fim(&guilda, novo_id, nome_novo_membro);
                break;
            }
            case 2:
                mostrar_lista(&guilda);
                break;
            case 3:
                salvar_guild_arquivo(guilda);
                break;
            case 4:
                printf("\nSaindo do sistema de registro da guilda. Adeus!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 4);

    liberar_lista(&guilda);

    return 0;
}