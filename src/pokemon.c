#include <stdio.h>
#include <string.h>
#include "../include/pokemon.h"


void mostrar_pokemon(Pokemon *pokemon) {
    printf("\n===== POKEMON =====\n");
    printf("Nome: %s\n", pokemon->nome);
    printf("Tipo: %s\n", pokemon->tipo);
    printf("Nivel: %d\n", pokemon->nivel);
    printf("Vida: %d/%d\n", pokemon->vida_atual, pokemon->vida_max);
    printf("Ataque: %d\n", pokemon->ataque);
    printf("Defesa: %d\n", pokemon->defesa);
}
