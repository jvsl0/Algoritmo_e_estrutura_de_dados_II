#include<stdio.h>

int main(){
    //Crie uma variável inteira chamada pontuacao e inicialize-a com o valor 0.
    int pontuacao = 0;

    //Crie uma variável do tipo "ponteiro para inteiro" chamada ponteiro_pontuacao.
    int *ponteiro_pontuacao;

    //Faça com que ponteiro_pontuacao aponte para o endereço de memória da variável pontuacao.
    ponteiro_pontuacao = &pontuacao;

    //Mostre na tela a pontuação do jogador antes de coletar qualquer moeda. A saída deve ser: "Pontuacao inicial: 0"
    printf("Pontuacao inicial: %d\n", *ponteiro_pontuacao);

    //Usando o ponteiro_pontuacao, adicione 10 pontos à pontuação do jogador. Repita este processo 3 vezes para simular a coleta de 3 moedas. (Dica: você pode fazer isso em 3 linhas separadas ou usar um laço for).
    for(int i = 0; i < 3; i++){
        *ponteiro_pontuacao += 10;
    }

    //Após simular a coleta das 3 moedas, mostre na tela a pontuação final. A saída deve ser: "Pontuacao final apos coletar 3 moedas: 30"
    printf("Pontuacao final apos coletar 3 moedas: %d\n", *ponteiro_pontuacao);

    return 0;
}