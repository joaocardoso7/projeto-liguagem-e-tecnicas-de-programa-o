#ifndef BATALHA_H
#define BATALHA_H

#include "pokemon.h"

int calcular_dano(Pokemon *atacante, Pokemon *defensor, Ataque *golpe);
void aplicar_dano(Pokemon *p, int dano);
int tentar_captura(Treinador *t, Pokemon *selvagem);

#endif
