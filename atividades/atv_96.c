#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Monstro {
    int id; 
    char nome[100];
    struct Monstro *prox;
} Monstro;

typedef struct {
    Monstro *inicio;
} Lista;

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
}


void liberarLista(Lista *lista) {
    Monstro *atual = lista->inicio;
    Monstro *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
}

void adicionarMonstro(Lista *lista, int id, char nome[]) {
    Monstro *novoMonstro = (Monstro *)malloc(sizeof(Monstro));
    if (novoMonstro == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novoMonstro->id = id;
    strcpy(novoMonstro->nome, nome);
    novoMonstro->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novoMonstro;
    } else {
        Monstro *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoMonstro;
    }
    printf("Monstro '%s' (Ameaca: %d) adicionado ao bestiario.\n", nome, id);
}

void mostrarBestiario(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("\nBestiario: Vazio.\n");
        return;
    }

    printf("\n*** REGISTRO DO BESTIARIO ***\n");
    printf("Ameaça | Nome do Monstro\n");
    printf("--------------------------------\n");
    Monstro *atual = lista->inicio;
    while (atual != NULL) {
        printf("  %4d | %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("--------------------------------\n");
}

void ordenarBestiario(Lista *lista) {
    if (lista->inicio == NULL || lista->inicio->prox == NULL) {
        printf("\nA lista esta vazia ou tem apenas um elemento. Nenhuma ordenacao necessaria.\n");
        return;
    }

    int trocado;
    Monstro *ptr1;
    Monstro *lptr = NULL; 
    
    
    do {
        trocado = 0;
        ptr1 = lista->inicio;

        while (ptr1->prox != lptr) {
            
            if (ptr1->id > ptr1->prox->id) {
                
                
                
                int temp_id = ptr1->id;
                ptr1->id = ptr1->prox->id;
                ptr1->prox->id = temp_id;

                // Troca do Nome
                char temp_nome[100];
                strcpy(temp_nome, ptr1->nome);
                strcpy(ptr1->nome, ptr1->prox->nome);
                strcpy(ptr1->prox->nome, temp_nome);
                
                trocado = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    } while (trocado);
    
    printf("\n✅ Bestiario ordenado com sucesso (Ordem Crescente de Nivel de Ameaça).\n");
}

int main() {
    Lista bestiario;
    inicializarLista(&bestiario);
    int escolha;
    int id_monstro;
    char nome_monstro[100];

    // Monstros iniciais
    adicionarMonstro(&bestiario, 5, "Goblin Patrulheiro");
    adicionarMonstro(&bestiario, 20, "Dragao Espectral");
    adicionarMonstro(&bestiario, 12, "Troll das Cavernas");

    do {
        printf("\n==================================\n");
        printf("       MENU DO BESTIARIO\n");
        printf("==================================\n");
        printf("1. Adicionar Monstro\n");
        printf("2. Mostrar Bestiario\n");
        printf("3. Ordenar Bestiario (Bubble Sort)\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: {
                printf("\n--- Adicionar Novo Monstro ---\n");
                printf("Nivel de Ameaça (ID inteiro): ");
                if (scanf("%d", &id_monstro) != 1) break; 
                while (getchar() != '\n');
                
                printf("Nome do Monstro: ");
                if (fgets(nome_monstro, 100, stdin) == NULL) break;
                nome_monstro[strcspn(nome_monstro, "\n")] = 0; 

                adicionarMonstro(&bestiario, id_monstro, nome_monstro);
                break;
            }
            case 2:
                mostrarBestiario(&bestiario);
                break;
            case 3:
                ordenarBestiario(&bestiario);
                mostrarBestiario(&bestiario);
                break;
            case 4:
                printf("\nFechando o Bestiario. Adeus!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (escolha != 4);

    liberarLista(&bestiario);

    return 0;
}