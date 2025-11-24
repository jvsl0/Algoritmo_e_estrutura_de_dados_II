#include <stdio.h>
#include "combate.h" 

int main() {
    int ataque_base_heroi;
    int bonus_espada;
    int vida_inimigo_inicial;

    printf("--- Simulador de Ataque de RPG ---\n\n");

    
    printf("Digite o ataque base do Heroi: ");
    if (scanf("%d", &ataque_base_heroi) != 1) return 1;

    printf("Digite o bonus da Espada: ");
    if (scanf("%d", &bonus_espada) != 1) return 1;

    
    printf("Digite a vida inicial do Inimigo: ");
    if (scanf("%d", &vida_inimigo_inicial) != 1) return 1;

    printf("\n------------------------------------------------------\n");

    
    int dano_causado = calcular_ataque_total(ataque_base_heroi, bonus_espada);

    
    int vida_inimigo_final = aplicar_dano(vida_inimigo_inicial, dano_causado);

    
    printf("Estatisticas:\n");
    printf("  Ataque Base do Heroi: %d\n", ataque_base_heroi);
    printf("  Bônus da Espada:      %d\n", bonus_espada);
    printf("  Vida Inicial do Inimigo: %d\n", vida_inimigo_inicial);
    printf("\n");

    printf("Resultado do Combate:\n");
    printf("  Poder de Ataque Total do Heroi: %d\n", dano_causado);
    printf("  Dano Causado: %d\n", dano_causado);
    printf("  Vida Restante do Inimigo: %d\n", vida_inimigo_final);
    
    if (vida_inimigo_final == 0) {
        printf("  Inimigo Derrotado!\n");
    } else {
        printf("  O Inimigo sobreviveu ao ataque.\n");
    }

    printf("------------------------------------------------------\n");

    return 0;
}