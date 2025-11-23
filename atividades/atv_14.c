#include<stdio.h>
#include<string.h>

int main(){

    char frase_inicio_luta[]={"Voce nunca saira daqui com vida!"};
    char caixa_dialogo[100]={"(Silencio)"};
    printf("Chefe antes da luta: %s\n", caixa_dialogo);

    strcpy(caixa_dialogo, frase_inicio_luta);
    printf("%s", frase_inicio_luta);

    return 0;
}