#include "combate.h"


int calcular_ataque_total(int ataque_base, int bonus_arma) {
    
    return ataque_base + bonus_arma;
}


int aplicar_dano(int vida_atual, int dano_sofrido) {
    int vida_restante = vida_atual - dano_sofrido;

    
    if (vida_restante < 0) {
        return 0;
    } else {
        return vida_restante;
    }
}