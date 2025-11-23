#include<stdio.h>

int main(){
    int moedas_coletadas[] = {10,50,20,5,100};
    int pontuacao_total = 0;
    int *ponteiro_moeda = moedas_coletadas;

    for(int i = 0; ponteiro_moeda <= (moedas_coletadas + 4); i++){
        pontuacao_total += *ponteiro_moeda;
        ponteiro_moeda++;
    }

    printf("Pontuacao total do nivel: %d", pontuacao_total);
}

//Requisitos:
//Vetor de Moedas: Crie um vetor de inteiros chamado moedas_coletadas e inicialize-o com os seguintes valores, que representam o valor de cada moeda: {10, 50, 20, 5, 100}.
//Variável de Pontuação: Crie uma variável inteira pontuacao_total e inicialize-a com 0.
//Ponteiro para Moedas: Crie um ponteiro para inteiro chamado ponteiro_moeda.
//Apontar para o Início: Faça com que ponteiro_moeda aponte para o endereço do primeiro elemento do vetor moedas_coletadas.
//Loop com Ponteiro: Crie um laço for ou while que percorra todos os 5 elementos do vetor. A condição de parada do laço deve comparar o endereço do ponteiro atual com o endereço final do vetor. A cada iteração, você deve:
//- Usar o operador de indireção (*) para obter o valor da moeda atual e somá-lo à pontuacao_total.
//- Incrementar o ponteiro_moeda (ponteiro_moeda++) para que ele aponte para a próxima moeda.
//Imprimir o Resultado: Após o laço terminar, imprima a pontuação final. A saída deve ser exatamente: Pontuação total do nível: 185
