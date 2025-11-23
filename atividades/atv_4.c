//atividade da aula 4
#include<stdio.h>
//Crie uma função sem retorno (void) com o nome aplicar_powerup_pontuacao_dupla.
void aplicar_powerup_pontuacao_dupla(int *pj){
    *pj = 2 * *pj;
}

int main(){
    
    //!showMemory(start=65520)
    
    //Crie uma variável inteira chamada pontuacao_jogador e inicialize-a com o valor 1500.
    int pontuacao_jogador = 1500;
    int *pj = &pontuacao_jogador;
    //Imprima a pontuação do jogador antes de coletar o power-up. A saída deve ser: "Pontuacao antes do power-up: 1500".
    printf("Pontuacao antes do power-up: %d\n", *pj);
    
    //Chame a função que aplica o power-up (você a criará no próximo passo).
    aplicar_powerup_pontuacao_dupla(pj);
    
    //Imprima a pontuação do jogador após a coleta do power-up para confirmar que o valor foi dobrado. A saída deve ser: "Pontuacao apos o power-up: 3000".
    printf("Pontuacao apos o power-up: %d", *pj);
    return 0;
}