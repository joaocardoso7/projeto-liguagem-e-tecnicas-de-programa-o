#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/batalha.h"

float multiplicador_tipo(const char *tipo_golpe, const char *tipo_defensor) {
    if (strcmp(tipo_golpe, "Fogo") == 0) {
        if (strcmp(tipo_defensor, "Planta") == 0) return 2.0f;
        if (strcmp(tipo_defensor, "Agua") == 0)   return 0.5f;
    } else if (strcmp(tipo_golpe, "Agua") == 0) {
        if (strcmp(tipo_defensor, "Fogo") == 0)   return 2.0f;
        if (strcmp(tipo_defensor, "Planta") == 0) return 0.5f;
    } else if (strcmp(tipo_golpe, "Planta") == 0) {
        if (strcmp(tipo_defensor, "Agua") == 0)   return 2.0f;
        if (strcmp(tipo_defensor, "Fogo") == 0)   return 0.5f;
    }
    return 1.0f;
}

// Formula baseada no nivel: com nivel 5, ataque 10, defesa 10 e poder 40
// o dano normal e 5 (10 com vantagem de tipo).
int calcular_dano(Pokemon *atacante, Pokemon *defensor, Ataque *golpe) {
    int defesa = defensor->defesa > 0 ? defensor->defesa : 1;
    int base = (2 * atacante->nivel / 5 + 2) * golpe->poder * atacante->ataque / defesa / 50 + 2;
    int dano = (int)(base * multiplicador_tipo(golpe->tipo, defensor->tipo));
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
