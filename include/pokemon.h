#ifndef POKEMON_H
#define POKEMON_H

#define MAX_ATAQUES 4
#define MAX_TIME 6

// Representação de uma habilidade/golpe
typedef struct {
    char nome[30];
    int poder;
    char tipo[15]; // "Fogo", "Agua", "Planta", "Normal"
} Ataque;

// Representação de uma criatura
typedef struct {
    char nome[30];
    char tipo[15];
    int vida_max;
    int vida_atual;
    int nivel;
    int ataque;
    int defesa;
    Ataque ataques[MAX_ATAQUES]; // Vetor homogêneo de structs
} Pokemon;

// Representação do Jogador / Treinador
typedef struct {
    char nome[50];
    Pokemon time[MAX_TIME];
    int qtd_pokemon;
    int pokebolas;
    int pocoes;
} Treinador;

#endif
