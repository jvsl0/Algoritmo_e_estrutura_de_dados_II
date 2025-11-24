#include <stdio.h>
#include <stdlib.h> 


#define ARQUIVO_LOG "game_log.txt"
#define MAX_EVENTO 100


int main() {
    int opcao;
    char evento[MAX_EVENTO];
    FILE *arquivo;

    printf("--- Sistema de Log de Eventos ---\n");
    
    
    while (1) {
        printf("\nMenu:\n");
        printf("1 - Registrar novo evento\n");
        printf("2 - Sair\n");
        printf("Escolha uma opcao: ");

        
        if (scanf("%d", &opcao) != 1) {
            printf("\nERRO: Entrada invalida. Por favor, digite 1 ou 2.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (opcao == 1) {
            
            
            arquivo = fopen(ARQUIVO_LOG, "a");

            if (arquivo == NULL) {
                perror("ERRO: Nao foi possivel abrir o arquivo de log");
                return EXIT_FAILURE;
            }

            printf("\nDigite o evento (sem espacos): ");
            if (scanf("%s", evento) != 1) {
                printf("Erro na leitura do evento.\n");
                fclose(arquivo);
                continue;
            }
            
            
            fprintf(arquivo, "%s\n", evento);
            
            
            fclose(arquivo);
            
            printf("Evento registrado com sucesso em '%s'.\n", ARQUIVO_LOG);

        } else if (opcao == 2) {
            printf("\nSistema de log encerrado. Adeus!\n");
            break; 

        } else {
            printf("\nOpcao invalida. Por favor, digite 1 ou 2.\n");
        }
    }

    return EXIT_SUCCESS;
}