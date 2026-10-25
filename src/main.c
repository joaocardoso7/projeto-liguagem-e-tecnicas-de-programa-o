#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

/* ---------- Utilitarios de entrada ---------- */

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Le um inteiro entre min e max. Repete ate o jogador digitar algo valido.
int lerOpcao(int min, int max) {
    int valor;
    while (1) {
        int lidos = scanf("%d", &valor);
        if (lidos == EOF) {          // entrada encerrada (Ctrl+D / Ctrl+Z)
            printf("\nEntrada encerrada. Ate a proxima!\n");
            exit(0);
        }
        if (lidos != 1) {            // digitou letra ou simbolo
            limparBuffer();
            printf("Entrada invalida! Digite apenas numeros: ");
            continue;
        }
        limparBuffer();
        if (valor >= min && valor <= max) {
            return valor;
        }
        printf("Opcao invalida! Escolha entre %d e %d: ", min, max);
    }
}

/* ---------- Criacao do treinador ---------- */

static void definirAtaque(Ataque *a, const char *nome, int poder, const char *tipo) {
    snprintf(a->nome, sizeof(a->nome), "%s", nome);
    a->poder = poder;
    snprintf(a->tipo, sizeof(a->tipo), "%s", tipo);
}

static void definirPokemonInicial(Pokemon *p, int escolha) {
    memset(p, 0, sizeof(*p));   // zera tudo: nenhum campo fica com lixo

    if (escolha == 1) {
        snprintf(p->nome, sizeof(p->nome), "Charmander");
        snprintf(p->tipo, sizeof(p->tipo), "Fogo");
        definirAtaque(&p->ataques[1], "Brasa", 12, "Fogo");
    } else if (escolha == 2) {
        snprintf(p->nome, sizeof(p->nome), "Bulbasaur");
        snprintf(p->tipo, sizeof(p->tipo), "Planta");
        definirAtaque(&p->ataques[1], "Chicote de Vinha", 12, "Planta");
    } else {
        snprintf(p->nome, sizeof(p->nome), "Squirtle");
        snprintf(p->tipo, sizeof(p->tipo), "Agua");
        definirAtaque(&p->ataques[1], "Jato de Agua", 12, "Agua");
    }
    definirAtaque(&p->ataques[0], "Investida", 8, "Normal");

    p->nivel = 5;
    p->vida_max = 20;
    p->vida_atual = 20;
    p->ataque = 10;
    p->defesa = 10;
}

void criarTreinador(Treinador *t) {
    memset(t, 0, sizeof(*t));   // recomeca do zero, mesmo se jogar duas vezes

    printf("\n--- INICIANDO NOVA JORNADA ---\n");
    printf("Prof. Carvalho: Ola! Qual e o seu nome, treinador?\nNome: ");

    if (fgets(t->nome, sizeof(t->nome), stdin) != NULL) {
        t->nome[strcspn(t->nome, "\n")] = '\0';
    }
    if (t->nome[0] == '\0') {
        snprintf(t->nome, sizeof(t->nome), "Treinador");
    }

    printf("\nMuito bem, %s! Escolha o seu parceiro inicial:\n", t->nome);
    printf("  [1] Charmander (Fogo)\n");
    printf("  [2] Bulbasaur  (Planta)\n");
    printf("  [3] Squirtle   (Agua)\n");
    printf("Escolha (1-3): ");
    int escolhaInicial = lerOpcao(1, 3);

    definirPokemonInicial(&t->time[0], escolhaInicial);
    t->qtd_pokemon = 1;
    t->pokebolas = 5;
    t->pocoes = 3;

    printf("\nParabens! Voce recebeu um %s (Nivel %d)!\n",
           t->time[0].nome, t->time[0].nivel);
    printf("Inventario: %d Pokebolas | %d Pocoes.\n", t->pokebolas, t->pocoes);
}

/* ---------- Mochila ---------- */

void mostrarMochila(const Treinador *t) {
    printf("\n=== MOCHILA DE %s ===\n", t->nome);
    printf("Equipe (%d/%d):\n", t->qtd_pokemon, MAX_TIME);
    for (int i = 0; i < t->qtd_pokemon; i++) {
        printf("  %d. %-12s Nv %-2d  HP %d/%d  (%s)\n",
               i + 1, t->time[i].nome, t->time[i].nivel,
               t->time[i].vida_atual, t->time[i].vida_max, t->time[i].tipo);
    }
    printf("Itens: %d Pokebolas | %d Pocoes\n", t->pokebolas, t->pocoes);
}

/* ---------- Persistencia (a implementar) ---------- */

// Devolve 1 se salvou, 0 se falhou.
int salvarJogo(const Treinador *t) {
    (void)t;
    printf("\n[TODO] Salvar jogo ainda nao implementado.\n");
    return 0;
}

// Devolve 1 se carregou, 0 se falhou (arquivo ausente ou corrompido).
int carregarJogo(Treinador *t) {
    (void)t;
    printf("\n[TODO] Carregar jogo ainda nao implementado.\n");
    return 0;
}

/* ---------- Loop de exploracao ---------- */

// Roda ate o jogador escolher voltar ao menu principal.
void menuExploracao(Treinador *jogador) {
    int voltar = 0;

    while (!voltar) {
        printf("\n=== EXPLORACAO ===\n");
        printf("1. Explorar\n");
        printf("2. Mochila\n");
        printf("3. Salvar jogo\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");

        switch (lerOpcao(1, 4)) {
            case 1:
                printf("\n[TODO] Aqui entra a batalha selvagem (batalha.c).\n");
                break;
            case 2:
                mostrarMochila(jogador);
                break;
            case 3:
                salvarJogo(jogador);
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

        switch (lerOpcao(1, 3)) {
            case 1: {
                Treinador jogador;
                criarTreinador(&jogador);
                menuExploracao(&jogador);
                break;
            }
            case 2: {
                Treinador jogador;
                if (carregarJogo(&jogador)) {
                    menuExploracao(&jogador);
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
