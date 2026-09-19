#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batalha.h"

int calcular_dano(Pokemon *atacante, Pokemon *defensor, Ataque *golpe) {
    int dano = atacante->ataque + golpe->poder - defensor->defesa / 2;

    // Vantagem de tipo (exemplo: Fogo ganha de Planta)
    if (strcmp(golpe->tipo, "Fogo") == 0 && strcmp(defensor->tipo, "Planta") == 0) {
        dano = dano * 2;
    }
    if (dano < 1) dano = 1;  // dano minimo
    return dano;
}

void aplicar_dano(Pokemon *p, int dano) {
    p->vida_atual = p->vida_atual - dano;
    if (p->vida_atual < 0) p->vida_atual = 0;  // nunca negativa
}

int tentar_captura(Treinador *t, Pokemon *selvagem) {
    if (t->pokebolas <= 0 || t->qtd_pokemon >= MAX_TIME) {
        printf("Nao e possivel capturar agora!\n");
        return 0;
    }
    t->pokebolas--;

    // Quanto menos vida, maior a chance (de 30% ate 80%)
    int chance = 30 + (100 - selvagem->vida_atual * 100 / selvagem->vida_max) / 2;

    if (rand() % 100 < chance) {
        t->time[t->qtd_pokemon] = *selvagem;
        t->qtd_pokemon++;
        printf("Capturou %s!\n", selvagem->nome);
        return 1;
    }
    printf("%s escapou!\n", selvagem->nome);
    return 0;
}
