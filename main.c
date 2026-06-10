#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "estatisticas.h"
#include "ranking.h"
#include "utils.h"
#include "loja.h"

int main() {
    srand(time(NULL));
    int op;

    printf("\033[2J\033[H");
    printf("=== RANDON-WITCH: Jogo de Adivinhacao ===\n");

    char nome_loja[50] = "";

    do {
        printf("\n1 - Jogar\n2 - Analisar historico\n3 - Ranking\n4 - Loja\n5 - Sair\n");
        op = ler_inteiro("Opcao: ", 1, 5);

        if (op == 1) {
            jogar();
        } else if (op == 2) {
            analisar_historico();
        } else if (op == 3) {
            mostrar_ranking();
        } else if (op == 4) {
            if (nome_loja[0] == '\0') {
                printf("Seu nome para a loja: ");
                fflush(stdout);
                scanf("%49s", nome_loja);
                limpar_buffer();
            }
            abrir_loja(nome_loja);
        } else {
            printf("Ate mais!\n");
        }

    } while (op != 5);

    return 0;
}
