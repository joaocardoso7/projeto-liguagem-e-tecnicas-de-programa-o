#include <stdio.h>
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

void mostrar_inventario(Treinador *treinador) {
    printf("\n===== INVENTARIO =====\n");
    printf("Pokebolas: %d\n", treinador->pokebolas);
    printf("Pocoes: %d\n", treinador->pocoes);
}

void inicializar_treinador(Treinador *treinador, const char *nome) {
    snprintf(treinador->nome, sizeof(treinador->nome), "%s", nome);

    treinador->qtd_pokemon = 0;
    treinador->pokebolas = 5;
    treinador->pocoes = 3;
}
