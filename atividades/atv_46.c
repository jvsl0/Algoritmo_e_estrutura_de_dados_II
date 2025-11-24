#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    int nivel;
    int highScore;
} PlayerProfile;


#define MESTRE_SCORE 10000
#define VETERANO_SCORE 5000




void criar_arquivo_teste() {
    FILE *arquivo;
    PlayerProfile perfis[] = {
        {"Alice", 30, 15000},    
        {"Bob", 15, 6000},       
        {"Charlie", 5, 4000},    
    };
    int num_perfis = sizeof(perfis) / sizeof(PlayerProfile);

    arquivo = fopen("profiles.dat", "wb");
    if (arquivo == NULL) {
        perror("ERRO ao criar o arquivo profiles.dat");
        return;
    }
    fwrite(perfis, sizeof(PlayerProfile), num_perfis, arquivo);
    fclose(arquivo);
    printf("Arquivo 'profiles.dat' de teste criado.\n");
}


const char* determinar_rank(int score) {
    if (score > MESTRE_SCORE) {
        return "Mestre do Jogo";
    } else if (score > VETERANO_SCORE) {
        return "Veterano";
    } else {
        return "Aspirante";
    }
}



int main() {
    FILE *arquivo;
    PlayerProfile perfil_atual;

    
    criar_arquivo_teste(); 
    
    printf("\n--- Carregando Perfis de Jogadores ---\n");
    
   
    arquivo = fopen("profiles.dat", "rb");

    if (arquivo == NULL) {
        perror("ERRO: Falha ao abrir profiles.dat");
        return EXIT_FAILURE;
    }

    printf("--------------------------------------------------\n");
    
   
    while (fread(&perfil_atual, sizeof(PlayerProfile), 1, arquivo) == 1) {
        
       
        const char *rank = determinar_rank(perfil_atual.highScore);
        
        printf("Nome: %-15s | Score: %5d | Rank: %s\n",
               perfil_atual.nome,
               perfil_atual.highScore,
               rank);
    }
    
    
    fclose(arquivo);

    printf("--------------------------------------------------\n");
    printf("Carregamento de perfis concluido.\n");

    return EXIT_SUCCESS;
}