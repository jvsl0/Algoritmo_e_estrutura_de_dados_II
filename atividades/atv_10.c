#include<stdio.h>

int main(){

    int sala_1[] = {10 ,20,5};
    int sala_2[] = { 50 , 100 };
    int sala_3[] = { 5 , 5 , 5 ,10};
    int *ponteiro_salas[] = {sala_1, sala_2, sala_3};
    int tamanho[]={
        sizeof(sala_1)/sizeof(sala_1[0]),
        sizeof(sala_2)/sizeof(sala_2[0]),
        sizeof(sala_3)/sizeof(sala_3[0])
    };

    for(int i = 0; i < 3; i++){
        printf("Moedas da sala %d: ", i+1);
        for(int j = 0; j < tamanho[i]; j++){
            printf(" %d ", ponteiro_salas[i][j]);
        }
        printf("\n");
    }



    
}

//Requisitos:
//Arrays de Moedas: Crie três vetores de inteiros para representar as moedas em cada sala secreta.
//sala_1 deve conter os valores: {10, 20, 5}
//sala_2 deve conter os valores: {50, 100}
//sala_3 deve conter os valores: {5, 5, 5, 10}
//Vetor de Ponteiros (Gerenciador de Salas): Crie um vetor de ponteiros para inteiros chamado ponteiro_salas com 3 posições. Este vetor atuará como nosso gerenciador.
//Conecte os Ponteiros: Faça com que cada posição do ponteiro_salas aponte para o início de um dos vetores de moedas.
//ponteiro_salas[0] deve apontar para sala_1.
//ponteiro_salas[1] deve apontar para sala_2.
//ponteiro_salas[2] deve apontar para sala_3.
//Acesse e Imprima as Moedas: Usando o vetor de ponteiros ponteiro_salas, acesse os dados e imprima os valores das moedas de cada sala. A saída do seu programa deve ser exatamente assim:
//Moedas na Sala 1: 10 20 5
//Moedas na Sala 2: 50 100
//Moedas na Sala 3: 5 5 5 10
//(Dica: Para imprimir as moedas, crie um loop separado para cada sala. Dentro do loop da Sala 1, você pode obter seu tamanho com sizeof(sala_1) / sizeof(sala_1[0]), e assim por diante para as outras salas. Use o ponteiro_salas para acessar os valores. Caso queira fazer uma solução mais avançada, tente implementar uma forma de imprimir todas as moedas usando um único loop for que itera de 0 a 2)
