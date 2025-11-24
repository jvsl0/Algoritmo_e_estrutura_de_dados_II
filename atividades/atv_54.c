#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


typedef struct {
    int id;
    char nome[50];
    int forca;
    int agilidade;
    int inteligencia;
} Personagem;


int buscar_personagem(const Personagem *lista, int n, int id_busca);

int main() {
    int n; 
    Personagem *campanha = NULL; 
    int i;
    int opcao;
    
    printf("--- Ferramenta de Consulta de Personagens para Mestre de Jogo ---\n");

    
    printf("Digite o numero total de personagens na campanha: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: Numero de personagens invalido.\n");
        return EXIT_FAILURE;
    }

    
    campanha = (Personagem *)malloc(n * sizeof(Personagem));
    if (campanha == NULL) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return EXIT_FAILURE;
    }

    
    printf("\n## Cadastro dos Personagens ##\n");
    for (i = 0; i < n; i++) {
        printf("\nPersonagem %d:\n", i + 1);
        printf("  ID (inteiro): ");
        if (scanf("%d", &campanha[i].id) != 1) { goto erro_leitura; }
        
        printf("  Nome (uma palavra): ");
        if (scanf("%49s", campanha[i].nome) != 1) { goto erro_leitura; }
        
        printf("  Forca: ");
        if (scanf("%d", &campanha[i].forca) != 1) { goto erro_leitura; }
        
        printf("  Agilidade: ");
        if (scanf("%d", &campanha[i].agilidade) != 1) { goto erro_leitura; }
        
        printf("  Inteligencia: ");
        if (scanf("%d", &campanha[i].inteligencia) != 1) { goto erro_leitura; }
    }

    
    while (1) {
        printf("\n======================================================\n");
        printf("Menu do Mestre:\n");
        printf("1 - Consultar Personagem por ID\n");
        printf("2 - Sair do Programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
             
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\nOpcao invalida. Por favor, digite 1 ou 2.\n");
            continue;
        }

        if (opcao == 2) {
            printf("\nEncerrando Ferramenta de Consulta. Bom jogo!\n");
            break; 
        } else if (opcao == 1) {
            int id_consulta;
            int indice_encontrado;
            
            printf("Digite a ID do personagem para consulta: ");
            if (scanf("%d", &id_consulta) != 1) {
                 
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("ID invalida.\n");
                continue;
            }

            // Busca linear
            indice_encontrado = buscar_personagem(campanha, n, id_consulta);

            if (indice_encontrado != -1) {
                
                Personagem p = campanha[indice_encontrado];
                
                
                float media = (float)(p.forca + p.agilidade + p.inteligencia) / 3.0f;
                
                printf("\n--- Detalhes do Personagem Encontrado ---\n");
                printf("Nome: %s (ID: %d)\n", p.nome, p.id);
                printf("Atributos (For %d, Agi %d, Int %d)\n", p.forca, p.agilidade, p.inteligencia);
                printf("Media de Atributos: %.2f\n", media);
                printf("-----------------------------------------\n");
            } else {
                
                printf("\nPersonagem com ID %d nao encontrado na campanha.\n", id_consulta);
            }
        } else {
            printf("\nOpcao invalida. Por favor, digite 1 ou 2.\n");
        }
    }

    
    free(campanha);
    return EXIT_SUCCESS;

erro_leitura:
    printf("\nErro durante a leitura dos dados. Encerrando programa.\n");
    free(campanha);
    return EXIT_FAILURE;
}


int buscar_personagem(const Personagem *lista, int n, int id_busca) {
    int i;
    
    for (i = 0; i < n; i++) {
        if (lista[i].id == id_busca) {
            return i; 
        }
    }
    return -1; 
}