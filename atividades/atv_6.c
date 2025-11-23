#include<stdio.h>

int main(){
    
    //Crie um vetor de inteiros chamado plataformas e inicialize-o com os seguintes valores de impulso: {10, 20, 5, 15, 30}.
    int plataformas[] = {10, 20, 5, 15, 30};

    //Crie uma variável do tipo "ponteiro para inteiro" chamada ponteiro_plataforma.
    int *ponteiro_plataforma = plataformas;

    //Crie uma variável inteira chamada altura_total e inicialize-a com 0.
    int altura_total = 0;

    //Crie um laço for que itere por todas as plataformas do vetor. Dentro do laço, você deve usar aritmética de ponteiros para acessar o valor de impulso de cada plataforma e somá-lo à variável altura_total. Dica: Em vez de usar plataformas[i], acesse o valor usando a expressão *(plataformas + i).
    for(int i = 0; i < 5; i++){
        altura_total += *(plataformas + i);
    }

    //Após o laço, mostre na tela a altura total alcançada. A saída deve ser exatamente: Altura total do salto: 80 metros!
    printf("Altura total do salto: %d metros\n", altura_total);

    return 0;
}