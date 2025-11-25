#include "spellbook.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    Spellbook* meuGrimorio = create_spellbook();
    printf("Grimorio criado.\n");

    
    add_spell(meuGrimorio, 1, "Bola de Fogo", 15);
    add_spell(meuGrimorio, 2, "Escudo Arcana", 10);
    add_spell(meuGrimorio, 3, "Curar Ferimentos", 25);
    add_spell(meuGrimorio, 4, "Teletransporte Rapido", 30);

    
    display_spellbook(meuGrimorio);

    
    destroy_spellbook(meuGrimorio);
    
    
    meuGrimorio = NULL; 

    return 0;
}