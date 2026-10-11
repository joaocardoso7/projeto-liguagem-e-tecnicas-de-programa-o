//main.c do rpg textual de pokemon

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int opcao;

    printf("=== RPG POKEMON ===\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Carregar Jogo\n");
    printf("3. Configuracoes\n");
    printf("4. Sair\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 4) {
        printf("Opção invalida! Por favor, escolha uma opcao entre 1 e 4.\n");
        return 1; // Retorna um código de erro
    }

    switch (opcao) {
        case 1:
            printf("Iniciando nova jornada pokemon!\n");
            break;
        case 2:
            printf("Carregando jogo...\n");
            break;
        case 3:
            printf("Abrindo configuracoes...\n");
            break;
        case 4:
            printf("Saindo do jogo, obrigado por jogar!\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }



    return 0;
}
