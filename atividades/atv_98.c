#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Membro {
    int id;
    char nome[100];
    int nivel;
    struct Membro *prox;
} Membro;

typedef struct {
    Membro *inicio;
} Lista;


typedef struct DadosMembro {
    int id;
    char nome[100];
    int nivel;
} DadosMembro;


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

void inserir_fim(Lista *lista, int id, char nome[], int nivel) {
    Membro *novo_membro = (Membro *)malloc(sizeof(Membro));
    if (novo_membro == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novo_membro->id = id;
    strcpy(novo_membro->nome, nome);
    novo_membro->nivel = nivel;
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
}

void mostrar_guilda(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nRegistro da Guilda: Vazio.\n");
        return;
    }

    printf("\n*** DADOS DA GUILDA CARREGADOS ***\n");
    printf("ID | Nivel | Nome do Membro\n");
    printf("--------------------------------\n");
    Membro *atual = lista->inicio;
    while (atual != NULL) {
        printf("%2d | %5d | %s\n", atual->id, atual->nivel, atual->nome);
        atual = atual->prox;
    }
    printf("--------------------------------\n");
}


void salvar_guilda_teste() {
    FILE *arquivo = fopen("guild_roster.b", "wb");
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo de teste.\n");
        return;
    }

    DadosMembro membros_teste[] = {
        {101, "Ariel, A Lider", 85},
        {102, "Kael, o Tank", 72},
        {103, "Lina, a Curandeira", 68}
    };
    int num_membros = sizeof(membros_teste) / sizeof(DadosMembro);

    fwrite(membros_teste, sizeof(DadosMembro), num_membros, arquivo);

    fclose(arquivo);
    printf("Arquivo 'guild_roster.b' criado com sucesso para o teste.\n");
}


Lista carregar_guilda() {
    Lista nova_lista;
    inicializar_lista(&nova_lista);
    FILE *arquivo = fopen("guild_roster.b", "rb");

    if (arquivo == NULL) {
        printf("\nERRO: Arquivo 'guild_roster.b' nao encontrado. Impossivel carregar o save.\n");
        return nova_lista;
    }

    DadosMembro dados_lidos;


    while (fread(&dados_lidos, sizeof(DadosMembro), 1, arquivo) == 1) {
        
        inserir_fim(&nova_lista, dados_lidos.id, dados_lidos.nome, dados_lidos.nivel);
    }

    fclose(arquivo);
    printf("\nSUCESSO: Dados da guilda carregados de 'guild_roster.b'.\n");
    return nova_lista;
}

int main() {
    Lista guilda_carregada;
    

    salvar_guilda_teste();


    guilda_carregada = carregar_guilda();


    mostrar_guilda(&guilda_carregada);


    liberar_lista(&guilda_carregada);

    return 0;
}