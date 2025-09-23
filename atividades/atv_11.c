#include<stdio.h>

int main(){
    int balas[2] = {30, 30};
    int granadas[2] = {5, 5};
    int foguetes[2] = {2, 2};
    int *inventario[3] = {
        balas, granadas, foguetes
    };

    printf("Inventario inicial:\n");
    printf("Balas: %d\n", *(inventario[0]+0));
    printf("granadas: %d\n", *(inventario[1]+0)); 
    printf("foguetes: %d\n", *(inventario[2]+0));

    for(int i = 0; i < 3; i++){
        *(inventario[i]+0) -= 1;
    }

    printf("Estado final:\n");
    printf("Balas: %d\n", *(inventario[0]+0));
    printf("granadas: %d\n", *(inventario[1]+0)); 
    printf("foguetes: %d\n", *(inventario[2]+0));

    return 0;
}

//Requisitos:
//Vetores de Munição: Crie três vetores de inteiros de tamanho 2 para cada tipo de munição: balas, granadas e foguetes. O primeiro elemento (índice 0) deve ser a quantidade atual e o segundo (índice 1) a capacidade máxima. Inicialize-os com os valores do contexto.
//Vetor de Ponteiros (Inventário): Crie um vetor de ponteiros para inteiros chamado inventario com 3 posições.
//Conecte o Inventário: Faça com que cada posição do inventario aponte para o vetor de munição correspondente (posição 0 para balas, 1 para granadas, 2 para foguetes).
//Imprima o Estado Inicial: Mostre na tela a quantidade de cada munição antes do uso. A saída deve ser:
//Inventario Inicial:
//Balas: 30
//Granadas: 5
//Foguetes: 2
//Simule o Uso com Aritmética de Ponteiros: Crie um laço de repetição (for) que percorra o inventario. Dentro do laço, use aritmética de ponteiros e o operador de indireção (*) para decrementar em 1 a quantidade atual (o primeiro elemento) de cada tipo de munição.
//Imprima o Estado Final: Mostre na tela a quantidade de cada munição após o uso, para confirmar que a alteração foi bem-sucedida. A saída deve ser:
//Inventario Apos o Uso:
//Balas: 29
//Granadas: 4
//Foguetes: 1