#include<stdio.h>
#include<stdlib.h>

int main(){

    float *ponteiro_altura_salto_duplo = NULL;

    printf("Jogador ainda nao possui o Salto Duplo.\n");

    ponteiro_altura_salto_duplo = malloc(sizeof(float));

    if(ponteiro_altura_salto_duplo == NULL){
        printf("alocacao de memoria falhou");
        return 1;
    }

    free(ponteiro_altura_salto_duplo);//Em um jogo real, esta linha seria usada para liberar a memória 
                                      //(e o *power-up* desativado) quando ele não fosse mais necessário,
                                      // evitando vazamento de memória (memory leak).

    *ponteiro_altura_salto_duplo = 15.5;

    printf("Pena Dourada coletada! Altura do Salto Duplo: %.2f\n", *ponteiro_altura_salto_duplo);

    return 0; 
}