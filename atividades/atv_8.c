// Requisitos:
// Vetor da Fase: Crie um vetor de inteiros chamado fase com 10 posições. Inicialize-o com o seguinte layout: {0, 1, 0, 0, 1, 1, 0, 1, 0, 0}.
// Ponteiro do Jogador: Crie uma variável do tipo "ponteiro para inteiro" chamada ponteiro_jogador.
// Contador de Moedas: Crie uma variável inteira chamada moedas_coletadas e inicialize-a com 0.
// Conecte o Ponteiro: Faça com que ponteiro_jogador aponte para o início do vetor fase.
// Percorrendo a Fase: Crie um laço de repetição (um for) que percorra todos os 10 blocos da fase.
// Lógica de Coleta: Dentro do laço, use aritmética de ponteiros para verificar o valor do bloco atual (por exemplo, *(ponteiro_jogador + i)). Se o valor for 1 (uma moeda), incremente a variável moedas_coletadas.
// Imprima o Resultado: Após o laço, mostre na tela o total de moedas coletadas. A saída deve ser: "O jogador coletou um total de 4 moedas!"

#include<stdio.h>

int main(){
    int fase[] = {0, 1, 0, 0, 1, 1, 0, 1, 0, 0};
    int *ponteiro_jogador = fase;
    int moedas_coletadas = 0;
    for (int i = 0; i < 10; i++){
        if(*(ponteiro_jogador + i) == 1){
            moedas_coletadas += 1;
        }
    }
    printf("O jogador coletou um total de %d moedas!", moedas_coletadas);

    return 0;
}





