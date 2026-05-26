#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "estatisticas.h"
#include "ranking.h"
#include "utils.h"

int main() {
    srand(time(NULL));
    int op;

    printf("\033[2J\033[H");
    printf("=== RANDON-WITCH: Jogo de Adivinhacao ===\n");

    do {
        printf("\n1 - Jogar\n2 - Analisar historico\n3 - Ranking\n4 - Sair\n");
        op = ler_inteiro("Opcao: ", 1, 4);

        if (op == 1) jogar();
        else if (op == 2) analisar_historico();
        else if (op == 3) mostrar_ranking();
        else printf("Ate mais!\n");

    } while (op != 4);

    return 0;
}
