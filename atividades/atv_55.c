#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


typedef struct {
    int id;
    char nickname[50];
    int reputacao;
} Jogador;


int busca_binaria(const Jogador *lista, int n, int id_busca);

int main() {
    int n; 
    Jogador *jogadores = NULL; 
    int i;
    int opcao;
    
    printf("--- Ferramenta de Gerenciamento de Jogadores (Busca Binaria) ---\n");

    
    printf("Digite o numero total de jogadores a cadastrar: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: Numero de jogadores invalido.\n");
        return EXIT_FAILURE;
    }

    
    jogadores = (Jogador *)malloc(n * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Cadastro dos Jogadores ##\n");
    printf("ATENCAO: IDs devem ser inseridas em ordem crescente para a Busca Binaria funcionar.\n");
    
    for (i = 0; i < n; i++) {
        printf("\nJogador %d:\n", i + 1);
        
        printf("  ID (inteiro, crescente): ");
        if (scanf("%d", &jogadores[i].id) != 1) { goto erro_leitura; }
        
        printf("  Nickname (uma palavra): ");
        if (scanf("%49s", jogadores[i].nickname) != 1) { goto erro_leitura; }
        
        printf("  Reputacao Inicial: ");
        if (scanf("%d", &jogadores[i].reputacao) != 1) { goto erro_leitura; }
    }

    
    while (1) {
        printf("\n======================================================\n");
        printf("Menu do GM:\n");
        printf("1 - Adicionar Reputacao (+100 pontos)\n");
        printf("2 - Sair do Programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
             
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nOpcao invalida. Por favor, digite 1 ou 2.\n");
            continue;
        }

        if (opcao == 2) {
            printf("\nEncerrando Ferramenta de GM. Boa sorte!\n");
            break; 
        } else if (opcao == 1) {
            int id_consulta;
            int indice_encontrado;
            
            printf("Digite o ID do jogador para adicionar reputacao: ");
            if (scanf("%d", &id_consulta) != 1) {
                 
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("ID invalida.\n");
                continue;
            }

            
            indice_encontrado = busca_binaria(jogadores, n, id_consulta);

            if (indice_encontrado != -1) {
                
                jogadores[indice_encontrado].reputacao += 100;
                
                printf("\n--- Reputacao Adicionada ---\n");
                printf("Nickname: %s, Nova Reputacao: %d\n", 
                       jogadores[indice_encontrado].nickname, 
                       jogadores[indice_encontrado].reputacao);
                printf("----------------------------\n");
            } else {
                
                printf("\nJogador com ID %d nao encontrado.\n", id_consulta);
            }
        } else {
            printf("\nOpcao invalida. Por favor, digite 1 ou 2.\n");
        }
    }

    
    free(jogadores);
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(jogadores);
    return EXIT_FAILURE;
}


int busca_binaria(const Jogador *lista, int n, int id_busca) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda <= direita) {
        
        int meio = esquerda + (direita - esquerda) / 2;

        
        if (lista[meio].id == id_busca) {
            return meio; 
        }

        
        if (lista[meio].id < id_busca) {
            esquerda = meio + 1; 
        } 
        
        else {
            direita = meio - 1; 
        }
    }

    return -1; 
}