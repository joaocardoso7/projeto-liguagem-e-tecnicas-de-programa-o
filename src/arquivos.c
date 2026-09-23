#include <stdio.h>
#include <stdlib.h>
#include "../include/arquivos.h"

int verificar_ou_criar_save(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("[AVISO] Arquivo de progresso '%s' nao encontrado.\n", caminho);
        printf("[SISTEMA] Criando novo arquivo de dados padrao...\n");

        arquivo = fopen(caminho, "w");
        if (arquivo == NULL) {
            printf("[ERRO CRITICO] Falha ao criar o arquivo no disco!\n");
            return 0; // falha
        }

        // escreve cabecalho 
        fprintf(arquivo, "# SAVE POKEMON RPG\n");
        fclose(arquivo);
        printf("[SISTEMA] Arquivo base criado com sucesso!\n");
        return 1;
    }

    printf("[SISTEMA] Arquivo '%s' carregado com integridade.\n", caminho);
    fclose(arquivo);
    return 1;
}
