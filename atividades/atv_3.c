//atividade da aula 3
#include<stdio.h>

int main(){
    //!showMemory(start=65520)
    //Crie uma variável do tipo float chamada coordenada_x para armazenar a posição do portal no eixo X.
    float coordenada_x;
    
    //Crie uma variável do tipo "ponteiro para float" chamada ponteiro_x e Faça com que ponteiro_x aponte para o endereço de memória da variável coordenada_x..
    float *ponteiro_x = &coordenada_x;
    
    //Peça ao usuário para digitar a coordenada X do portal e armazene o valor na variável coordenada_x.
    printf("digite a coordenada x do portal:\n");
    scanf("%f", ponteiro_x);
    
    //Mostre na tela a coordenada X do portal que foi digitada. A saída deve ser: "Posicao do portal no eixo X: [valor]" (use o especificador de formato %f).
    printf("posicao do portal no eixo X: %f\n", *ponteiro_x);
    
    //Mostre na tela o endereço de memória onde a coordenada está armazenada, simulando como o sistema de teletransporte "encontraria" o portal. A saída deve ser: "Endereco do portal para teletransporte: [endereco]" (use o especificador de formato %p).
    printf("Endereco do portal para teletransporte:%p", ponteiro_x);
    
    return 0;
}