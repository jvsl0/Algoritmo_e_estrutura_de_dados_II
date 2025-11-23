#include<stdio.h>

void ler_cenario(int n, int *cenario){
    for(int i = 0; i < n; i++){
        scanf("%d", cenario + i);
    }
}

int main(){
    int n;
    printf("digite o numero de blocos no cenario:");
    scanf("%d", &n);
    int cenario[n];
    ler_cenario(n, cenario);
    for(int i = 0; i < n; i++){
        if(cenario[i] == 1)
        cenario[i] = 2;
        break;
    }

    for(int i = 0; i < n; i++){
        printf("%d ", cenario[i]);
    }
    printf("\n");

    return 0;
}

//Requisitos:
//1. Função ler_cenario:
//Crie uma função chamada ler_cenario que não retorna nada (void).
//Ela deve receber dois parâmetros: um inteiro n (o tamanho da fileira) e um ponteiro para inteiro cenario (que aponta para o início do vetor do cenário).
//Dentro desta função, use um laço for para ler n valores inteiros (0 ou 1) do usuário.
//Para a leitura de cada valor com scanf, você deve usar aritmética de ponteiros (ex: cenario + i) para indicar o endereço de memória de cada posição do vetor.
//2. Função main:
//Peça ao usuário para digitar o número de blocos no cenário (n).
//Declare um vetor de inteiros chamado cenario com tamanho n.
//Chame a função ler_cenario para preencher o vetor.
//Após a leitura, percorra o vetor cenario. Encontre o primeiro bloco que seja uma plataforma (1) e mude seu valor para 2 (o power-up). Interrompa a busca assim que encontrar o primeiro.
//Imprima na tela o vetor do cenário já modificado, com os números separados por um espaço.