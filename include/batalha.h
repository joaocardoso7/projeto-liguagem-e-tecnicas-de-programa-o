#ifndef BATALHA_H
#define BATALHA_H

#include "pokemon.h"

// Resultados possiveis de uma batalha
#define BATALHA_DERROTA   0
#define BATALHA_VITORIA   1
#define BATALHA_CAPTURA   2
#define BATALHA_FUGA      3

// Quanto de vida a pocao recupera
#define CURA_POCAO 20

// Retorna o multiplicador de vantagem de tipo (2.0, 1.0 ou 0.5)
float multiplicador_tipo(char tipo_ataque[], char tipo_defensor[]);

// Calcula o dano que um golpe causa no defensor
int calcular_dano(Pokemon *atacante, Pokemon *defensor, Ataque *golpe);

// Tira vida do Pokemon (nunca deixa a vida ficar negativa)
void aplicar_dano(Pokemon *p, int dano);

// Usa uma pocao no Pokemon (nunca passa da vida maxima)
// Retorna 1 se usou, 0 se nao foi possivel
int usar_pocao(Treinador *t, Pokemon *p);

// Tenta capturar o Pokemon selvagem
// Retorna 1 se capturou, 0 se nao capturou
int tentar_captura(Treinador *t, Pokemon *selvagem);

// Executa uma batalha completa contra um Pokemon selvagem
// Retorna uma das constantes BATALHA_*
int iniciar_batalha(Treinador *t, Pokemon selvagem);

#endif
