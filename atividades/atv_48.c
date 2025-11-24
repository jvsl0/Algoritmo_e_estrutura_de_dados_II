#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_CAMPEOES 3


typedef struct {
    char nome[50];
    int vida;
    int ataque;
} Campeao;


void criar_arquivo_teste();


int main() {
    FILE *arquivo;
    Campeao esquadrao[NUM_CAMPEOES]; 
    int i;
    
    printf("--- Carregando Esquadrao de Campeoes ---\n");

    
    criar_arquivo_teste(); 
    
    
    arquivo = fopen("squad.dat", "rb");

    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo squad.dat");
        return EXIT_FAILURE;
    }

    
    size_t itens_lidos = fread(esquadrao, sizeof(Campeao), NUM_CAMPEOES, arquivo);

    
    if (itens_lidos != NUM_CAMPEOES) {
        printf("ERRO: Apenas %zu de %d campeoes foram lidos. Verifique a criacao do arquivo.\n", itens_lidos, NUM_CAMPEOES);
        fclose(arquivo);
        return EXIT_FAILURE;
    }

    
    fclose(arquivo);

    

    
    Campeao tanque_candidato = esquadrao[0]; 

    
    for (i = 1; i < NUM_CAMPEOES; i++) {
        if (esquadrao[i].vida > tanque_candidato.vida) {
            tanque_candidato = esquadrao[i]; 
        }
    }
    
    printf("\nCarregamento completo. Campeoes prontos para a batalha.\n");
    
    
    printf("O Tanque do esquadrao e: %s\n", tanque_candidato.nome);
    printf("%s: Tanque do esquadrao.\n", tanque_candidato.nome);

    return EXIT_SUCCESS;
}


void criar_arquivo_teste() {
    FILE *arquivo;
    
    Campeao dados_teste[] = {
        {"Garen", 620, 69},
        {"Lux", 530, 55},
        {"Ashe", 590, 61}
    };
    
    arquivo = fopen("squad.dat", "wb"); 
    if (arquivo == NULL) {
        perror("ERRO FATAL: Nao foi possivel criar o arquivo squad.dat para teste");
        exit(EXIT_FAILURE);
    }
    
    
    if (fwrite(dados_teste, sizeof(Campeao), NUM_CAMPEOES, arquivo) != NUM_CAMPEOES) {
        printf("ERRO FATAL: Falha ao escrever todos os 3 campeoes no arquivo de teste.\n");
    } else {
        printf("Arquivo 'squad.dat' de teste criado com sucesso (3 registros).\n");
    }
    
    fclose(arquivo);
}