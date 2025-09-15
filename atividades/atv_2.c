//atividade da aula 2

#include <stdio.h>

int main(){
    
    //Crie uma variável inteira chamada tesouro_local e inicialize-a com o valor 0.
    int tesouro_local = 0;
    
    //Crie uma variável do tipo "ponteiro para inteiro" chamada plataforma_secreta.
    int *plataforma_secreta;
    
    //Faça com que o ponteiro plataforma_secreta armazene o endereço de memória da variável tesouro_local.
    plataforma_secreta = &tesouro_local;
    
    //Antes de qualquer ação, imprima o valor de tesouro_local para mostrar que o tesouro ainda não está ativo. A saída deve ser: "O tesouro ainda nao apareceu. Valor: 0"
    printf("O tesouro ainda nao apareceu. Valor: %d\n", tesouro_local);
    
    //Utilizando apenas o ponteiro plataforma_secreta e o operador de indireção (*), modifique o valor no endereço de memória para 1 (simulando que o tesouro apareceu). Você não deve usar a variável tesouro_local diretamente nesta etapa.
    *plataforma_secreta = 1;
    
    //Após a ativação, imprima novamente o valor da variável tesouro_local para confirmar que ela foi alterada através do ponteiro. A saída deve ser: "O personagem pisou na plataforma secreta! O tesouro apareceu! Valor: 1"
    printf("O personagem pisou na plataforma secreta! Valor: %d", tesouro_local);
    
    return 0;
}