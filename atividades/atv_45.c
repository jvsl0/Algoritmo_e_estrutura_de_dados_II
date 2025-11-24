#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int nivel;
    float vida;
    float mana;
} Personagem;


void criar_novo_personagem();

int main() {
    int opcao;

    printf("--- Sistema de Save Game Binario ---\n");

    while (1) {
        printf("\nMenu Principal:\n");
        printf("1 - Criar Novo Personagem\n");
        printf("2 - Sair\n");
        printf("Escolha uma opcao: ");

        
        if (scanf("%d", &opcao) != 1) {
            printf("\nERRO: Entrada invalida.\n");
            
            while (getchar() != '\n'); 
            continue;
        }

        if (opcao == 1) {
            criar_novo_personagem();
        } else if (opcao == 2) {
            printf("\nSistema de save game encerrado. Progresso salvo em 'savegame.sav'.\n");
            break; 
        } else {
            printf("\nOpcao invalida. Digite 1 ou 2.\n");
        }
    }

    return EXIT_SUCCESS;
}


void criar_novo_personagem() {
    FILE *arquivo;
    Personagem novo_personagem;
    
    printf("\n## Cadastro de Novo Personagem ##\n");

    
    printf("Nome (max 49 caracteres): ");
    if (scanf("%49s", novo_personagem.nome) != 1) return;

    
    printf("Nivel: ");
    if (scanf("%d", &novo_personagem.nivel) != 1) return;

    
    printf("Vida (HP): ");
    if (scanf("%f", &novo_personagem.vida) != 1) return;

    
    printf("Mana (MP): ");
    if (scanf("%f", &novo_personagem.mana) != 1) return;

    

    
    arquivo = fopen("savegame.sav", "ab");

    if (arquivo == NULL) {
        perror("\nERRO: Nao foi possivel abrir o arquivo savegame.sav");
        return;
    }

    
    size_t itens_escritos = fwrite(&novo_personagem, sizeof(Personagem), 1, arquivo);

    
    if (itens_escritos == 1) {
        printf("\nPersonagem '%s' (Nv %d) salvo com sucesso!\n", novo_personagem.nome, novo_personagem.nivel);
    } else {
        printf("\nERRO: Falha ao escrever os dados no arquivo binario.\n");
    }

    
    if (fclose(arquivo) == EOF) {
        perror("ERRO: Falha ao fechar o arquivo.");
    }
}