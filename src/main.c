#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pokemon.h"

/* ---------- Entrada ---------- */

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Le um inteiro entre min e max. Repete ate o jogador digitar algo valido.
int ler_opcao(int min, int max) {
    int valor;
    while (1) {
        int lidos = scanf("%d", &valor);
        if (lidos == EOF) {          // entrada encerrada (Ctrl+D / Ctrl+Z)
            printf("\nEntrada encerrada. Ate a proxima!\n");
            exit(0);
        }
        if (lidos != 1) {            // digitou letra ou simbolo
            limpar_buffer();
            printf("Entrada invalida! Digite apenas numeros: ");
            continue;
        }
        limpar_buffer();
        if (valor >= min && valor <= max) {
            return valor;
        }
        printf("Opcao invalida! Escolha entre %d e %d: ", min, max);
    }
}

/* ---------- Novo jogo ---------- */

static void definir_ataque(Ataque *a, const char *nome, int poder, const char *tipo) {
    snprintf(a->nome, sizeof(a->nome), "%s", nome);
    a->poder = poder;
    snprintf(a->tipo, sizeof(a->tipo), "%s", tipo);
}

static void definir_pokemon_inicial(Pokemon *p, int escolha) {
    memset(p, 0, sizeof(*p));

    if (escolha == 1) {
        snprintf(p->nome, sizeof(p->nome), "Charmander");
        snprintf(p->tipo, sizeof(p->tipo), "Fogo");
        definir_ataque(&p->ataques[1], "Brasa", 12, "Fogo");
    } else if (escolha == 2) {
        snprintf(p->nome, sizeof(p->nome), "Bulbasaur");
        snprintf(p->tipo, sizeof(p->tipo), "Planta");
        definir_ataque(&p->ataques[1], "Chicote de Vinha", 12, "Planta");
    } else {
        snprintf(p->nome, sizeof(p->nome), "Squirtle");
        snprintf(p->tipo, sizeof(p->tipo), "Agua");
        definir_ataque(&p->ataques[1], "Jato de Agua", 12, "Agua");
    }
    definir_ataque(&p->ataques[0], "Investida", 8, "Normal");

    p->nivel = 5;
    p->vida_max = 20;
    p->vida_atual = 20;
    p->ataque = 10;
    p->defesa = 10;
}

void novo_jogo(Treinador *jogador) {
    char nome[50];

    printf("\n--- INICIANDO NOVA JORNADA ---\n");
    printf("Prof. Carvalho: Ola! Qual e o seu nome, treinador?\nNome: ");

    if (fgets(nome, sizeof(nome), stdin) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';
    } else {
        nome[0] = '\0';
    }
    if (nome[0] == '\0') {
        snprintf(nome, sizeof(nome), "Treinador");
    }

    inicializar_treinador(jogador, nome);   // zera tudo e define pokebolas/pocoes

    printf("\nMuito bem, %s! Escolha o seu parceiro inicial:\n", jogador->nome);
    printf("  [1] Charmander (Fogo)\n");
    printf("  [2] Bulbasaur  (Planta)\n");
    printf("  [3] Squirtle   (Agua)\n");
    printf("Escolha (1-3): ");
    int escolha = ler_opcao(1, 3);

    definir_pokemon_inicial(&jogador->time[0], escolha);
    jogador->qtd_pokemon = 1;

    printf("\nParabens! Voce recebeu um %s!\n", jogador->time[0].nome);
    mostrar_pokemon(&jogador->time[0]);
    mostrar_inventario(jogador);
}

/* ---------- Persistencia (a implementar) ---------- */

// Devolve 1 se salvou, 0 se falhou.
int salvar_jogo(const Treinador *jogador) {
    (void)jogador;
    printf("\n[TODO] Salvar jogo ainda nao implementado.\n");
    return 0;
}

// Devolve 1 se carregou, 0 se falhou (arquivo ausente ou corrompido).
int carregar_jogo(Treinador *jogador) {
    (void)jogador;
    printf("\n[TODO] Carregar jogo ainda nao implementado.\n");
    return 0;
}

/* ---------- Loop de exploracao ---------- */

// Roda ate o jogador escolher voltar ao menu principal.
void menu_exploracao(Treinador *jogador) {
    int voltar = 0;

    while (!voltar) {
        printf("\n=== EXPLORACAO ===\n");
        printf("1. Explorar\n");
        printf("2. Mochila\n");
        printf("3. Salvar jogo\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");

        switch (ler_opcao(1, 4)) {
            case 1:
                printf("\n[TODO] Aqui entra a batalha selvagem (batalha.c).\n");
                break;
            case 2:
                mostrar_time(jogador);
                mostrar_inventario(jogador);
                break;
            case 3:
                salvar_jogo(jogador);
                break;
            case 4:
                voltar = 1;
                break;
        }
    }
}

/* ---------- Programa principal ---------- */

int main(void) {
    int rodando = 1;

    while (rodando) {
        printf("\n=== RPG POKEMON ===\n");
        printf("1. Novo Jogo\n");
        printf("2. Carregar Jogo\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");

        switch (ler_opcao(1, 3)) {
            case 1: {
                Treinador jogador;
                novo_jogo(&jogador);
                menu_exploracao(&jogador);
                break;
            }
            case 2: {
                Treinador jogador;
                if (carregar_jogo(&jogador)) {
                    menu_exploracao(&jogador);
                }
                break;
            }
            case 3:
                printf("\nEncerrando o programa. Ate a proxima!\n");
                rodando = 0;
                break;
        }
    }

    return 0;
}
