
#ifndef HEROI_H
#define HEROI_H


typedef struct Heroi Heroi;


Heroi* alocar_roster(int quantidade);

void ler_roster(Heroi* roster, int quantidade);


void imprimir_roster(const Heroi* roster, int quantidade);



#endif