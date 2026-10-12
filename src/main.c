#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ATAQUES 4
#define MAX_TIME 6

// 1. Estruturas baseadas na modelagem do projeto
typedef struct {
    char nome[30];
    int poder;
    char tipo[15]; 
} Ataque;

typedef struct {
    char nome[30];
    char tipo[15];
    int vida_max;
    int vida_atual;
    int nivel;
    int ataque;
    int defesa;
    Ataque ataques[MAX_ATAQUES]; 
} Pokemon;

typedef struct {
    char nome[50];
    Pokemon time[MAX_TIME];
    int qtd_pokemon;
    int pokebolas;
    int pocoes;
} Treinador;


void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int opcao;
    int rodando = 1; 
    Treinador jogador; 

    while (rodando) {
        printf("\n=== RPG POKEMON ===\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Carregar Jogo\n");
        printf("3. Configuracoes\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");

        // Validação defensiva do scanf
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite apenas numeros.\n");
            limparBuffer();
            continue; 
        }
        limparBuffer(); // consome o \n deixado pelo scanf

        switch (opcao) {
            case 1:
                printf("\n--- INICIANDO NOVA JORNADA ---\n");
                printf("Prof. Carvalho: Ola! Qual e o teu nome, treinador? \nNome: ");
                
                // Leitura segura de strings (permite nomes com espaços)
                if (fgets(jogador.nome, sizeof(jogador.nome), stdin) != NULL) {
                    jogador.nome[strcspn(jogador.nome, "\n")] = '\0'; 
                }

                printf("\nMuito bem, %s! Escolhe o teu parceiro inicial:\n", jogador.nome);
                printf("  [1] Charmander (Fogo)\n");
                printf("  [2] Bulbasaur  (Planta)\n");
                printf("  [3] Squirtle   (Agua)\n");
                
                int escolhaInicial = 0;
                do {
                    printf("Escolha (1-3): ");
                    if (scanf("%d", &escolhaInicial) != 1) {
                        limparBuffer();
                        continue;
                    }
                    limparBuffer();
                } while (escolhaInicial < 1 || escolhaInicial > 3);

                // Atribuição de dados iniciais ao inventário
                jogador.qtd_pokemon = 1;
                jogador.pokebolas = 5;
                jogador.pocoes = 3;

                // Configuração do Pokémon escolhido
                if (escolhaInicial == 1) {
                    strcpy(jogador.time[0].nome, "Charmander");
                    strcpy(jogador.time[0].tipo, "Fogo");
                } else if (escolhaInicial == 2) {
                    strcpy(jogador.time[0].nome, "Bulbasaur");
                    strcpy(jogador.time[0].tipo, "Planta");
                } else {
                    strcpy(jogador.time[0].nome, "Squirtle");
                    strcpy(jogador.time[0].tipo, "Agua");
                }
                
                jogador.time[0].nivel = 5;
                jogador.time[0].vida_max = 20;
                jogador.time[0].vida_atual = 20;
                jogador.time[0].ataque = 10;
                jogador.time[0].defesa = 10;

                printf("\nParabens! Recebeste um %s (Nivel %d)!\n", jogador.time[0].nome, jogador.time[0].nivel);
                printf("Inventario atualizado: %d Pokebolas | %d Pocoes.\n", jogador.pokebolas, jogador.pocoes);
                
                // Futura implementação: Loop de Exploração (Menu do Mundo)
                break;

            case 2:
                printf("\nCarregando jogo...\n");
                // Futura implementação: LerArquivo()
                break;

            case 3:
                printf("\nAbrindo configuracoes...\n");
                break;

            case 4:
                printf("\nEncerrando o programa. Ate a proxima!\n");
                rodando = 0; // Altera a condição e encerra o while
                break;

            default:
                printf("\nOpcao invalida! Escolha entre 1 e 4.\n");
        }
    }

    return 0;
}
