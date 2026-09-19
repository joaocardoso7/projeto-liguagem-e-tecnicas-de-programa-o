#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batalha.h"

// ---------------------------------------------------------
// Funcoes auxiliares (so usadas dentro deste arquivo)
// ---------------------------------------------------------

// Limpa o que sobrou no teclado (evita bug no scanf)
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Le um numero entre min e max. Repete ate o usuario digitar certo.
static int ler_opcao(int min, int max) {
    int opcao;
    int ok;

    do {
        ok = scanf("%d", &opcao);
        limpar_buffer();
        if (ok != 1 || opcao < min || opcao > max) {
            printf("Opcao invalida! Digite um numero de %d a %d: ", min, max);
            ok = 0;
        }
    } while (ok != 1);

    return opcao;
}

// Procura o primeiro Pokemon do time que ainda tem vida.
// Retorna a posicao dele ou -1 se todos estiverem desmaiados.
static int primeiro_vivo(Treinador *t) {
    int i;
    for (i = 0; i < t->qtd_pokemon; i++) {
        if (t->time[i].vida_atual > 0) {
            return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------
// Calculo de dano
// ---------------------------------------------------------

float multiplicador_tipo(char tipo_ataque[], char tipo_defensor[]) {
    // Fogo ganha de Planta, Planta ganha de Agua, Agua ganha de Fogo
    if (strcmp(tipo_ataque, "Fogo") == 0) {
        if (strcmp(tipo_defensor, "Planta") == 0) return 2.0;
        if (strcmp(tipo_defensor, "Agua") == 0)   return 0.5;
    }
    if (strcmp(tipo_ataque, "Planta") == 0) {
        if (strcmp(tipo_defensor, "Agua") == 0)   return 2.0;
        if (strcmp(tipo_defensor, "Fogo") == 0)   return 0.5;
    }
    if (strcmp(tipo_ataque, "Agua") == 0) {
        if (strcmp(tipo_defensor, "Fogo") == 0)   return 2.0;
        if (strcmp(tipo_defensor, "Planta") == 0) return 0.5;
    }
    return 1.0; // Normal ou tipos iguais: dano normal
}

int calcular_dano(Pokemon *atacante, Pokemon *defensor, Ataque *golpe) {
    int dano;
    float mult;

    // Formula simples: forca do atacante + poder do golpe - metade da defesa
    dano = atacante->ataque + golpe->poder - (defensor->defesa / 2);

    // Aplica a vantagem/desvantagem de tipo
    mult = multiplicador_tipo(golpe->tipo, defensor->tipo);
    dano = (int)(dano * mult);

    // Todo golpe causa pelo menos 1 de dano
    if (dano < 1) {
        dano = 1;
    }

    return dano;
}

void aplicar_dano(Pokemon *p, int dano) {
    p->vida_atual = p->vida_atual - dano;

    // Trava: vida nunca fica negativa
    if (p->vida_atual < 0) {
        p->vida_atual = 0;
    }
}

// ---------------------------------------------------------
// Pocao
// ---------------------------------------------------------

int usar_pocao(Treinador *t, Pokemon *p) {
    if (t->pocoes <= 0) {
        printf("Voce nao tem pocoes!\n");
        return 0;
    }
    if (p->vida_atual == p->vida_max) {
        printf("%s ja esta com a vida cheia!\n", p->nome);
        return 0;
    }

    p->vida_atual = p->vida_atual + CURA_POCAO;

    // Trava: vida nunca passa da vida maxima
    if (p->vida_atual > p->vida_max) {
        p->vida_atual = p->vida_max;
    }

    t->pocoes--;
    printf("%s recuperou vida! (%d/%d)\n", p->nome, p->vida_atual, p->vida_max);
    return 1;
}

// ---------------------------------------------------------
// Captura
// ---------------------------------------------------------

int tentar_captura(Treinador *t, Pokemon *selvagem) {
    int chance;
    int sorteio;

    if (t->pokebolas <= 0) {
        printf("Voce nao tem pokebolas!\n");
        return 0;
    }
    if (t->qtd_pokemon >= MAX_TIME) {
        printf("Seu time esta cheio!\n");
        return 0;
    }

    t->pokebolas--;
    printf("Voce jogou uma pokebola...\n");

    // Quanto menos vida o Pokemon tem, mais facil capturar.
    // Vida cheia = 30% de chance. Vida quase zero = quase 80%.
    chance = 30 + (100 - (selvagem->vida_atual * 100 / selvagem->vida_max)) / 2;

    sorteio = rand() % 100; // numero de 0 a 99
    if (sorteio < chance) {
        t->time[t->qtd_pokemon] = *selvagem; // copia o Pokemon para o time
        t->qtd_pokemon++;
        printf("Voce capturou %s!\n", selvagem->nome);
        return 1;
    }

    printf("%s escapou da pokebola!\n", selvagem->nome);
    return 0;
}

// ---------------------------------------------------------
// Batalha completa
// ---------------------------------------------------------

int iniciar_batalha(Treinador *t, Pokemon selvagem) {
    int pos;
    int opcao;
    int i;
    int dano;
    int escolha;
    Pokemon *meu;

    printf("\nUm %s selvagem apareceu!\n", selvagem.nome);

    while (1) {
        // Escolhe o Pokemon que vai lutar
        pos = primeiro_vivo(t);
        if (pos == -1) {
            printf("Todos os seus Pokemon desmaiaram...\n");
            return BATALHA_DERROTA;
        }
        meu = &t->time[pos];

        // Mostra o estado da batalha
        printf("\n%s (Nv %d)  HP: %d/%d\n", selvagem.nome, selvagem.nivel,
               selvagem.vida_atual, selvagem.vida_max);
        printf("%s (Nv %d)  HP: %d/%d\n", meu->nome, meu->nivel,
               meu->vida_atual, meu->vida_max);
        printf("\n1 - Atacar\n2 - Usar pocao (%d)\n3 - Jogar pokebola (%d)\n4 - Fugir\n",
               t->pocoes, t->pokebolas);
        printf("Escolha: ");
        opcao = ler_opcao(1, 4);

        // ----- Turno do jogador -----
        if (opcao == 1) {
            printf("\nEscolha o golpe:\n");
            for (i = 0; i < MAX_ATAQUES; i++) {
                printf("%d - %s (poder %d, %s)\n", i + 1, meu->ataques[i].nome,
                       meu->ataques[i].poder, meu->ataques[i].tipo);
            }
            printf("Golpe: ");
            escolha = ler_opcao(1, MAX_ATAQUES) - 1; // -1 porque o vetor comeca em 0

            dano = calcular_dano(meu, &selvagem, &meu->ataques[escolha]);
            aplicar_dano(&selvagem, dano);
            printf("%s usou %s e causou %d de dano!\n", meu->nome,
                   meu->ataques[escolha].nome, dano);

            if (selvagem.vida_atual == 0) {
                printf("%s selvagem desmaiou! Voce venceu!\n", selvagem.nome);
                return BATALHA_VITORIA;
            }
        } else if (opcao == 2) {
            if (usar_pocao(t, meu) == 0) {
                continue; // nao gastou o turno, volta pro menu
            }
        } else if (opcao == 3) {
            if (t->pokebolas <= 0 || t->qtd_pokemon >= MAX_TIME) {
                tentar_captura(t, &selvagem); // so mostra a mensagem de erro
                continue;
            }
            if (tentar_captura(t, &selvagem) == 1) {
                return BATALHA_CAPTURA;
            }
        } else {
            printf("Voce fugiu da batalha!\n");
            return BATALHA_FUGA;
        }

        // ----- Turno do Pokemon selvagem -----
        escolha = rand() % MAX_ATAQUES; // golpe aleatorio
        dano = calcular_dano(&selvagem, meu, &selvagem.ataques[escolha]);
        aplicar_dano(meu, dano);
        printf("%s selvagem usou %s e causou %d de dano!\n", selvagem.nome,
               selvagem.ataques[escolha].nome, dano);

        if (meu->vida_atual == 0) {
            printf("%s desmaiou!\n", meu->nome);
        }
    }
}
