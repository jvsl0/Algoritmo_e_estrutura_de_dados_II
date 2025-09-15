//exercicio da aula 2

#include <stdio.h>

int main(){
    
    int a, b, c, d, dif;
    int *pa = &a;
    int *pb = &b;
    int *pc = &c;
    int *pd = &d;
    int *pdif = &dif;
    printf("digite os valores de A , B , C e D: ");
    scanf("%d %d %d %d", pa, pb, pc, pd);
    
    *pdif = (*pa * *pb)-(*pc * *pd);
    printf("diferenca = %d", *pdif);
    
    return 0;
}