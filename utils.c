#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_inteiro(const char *msg, int min, int max) {
    int valor;
    while (1) {
        printf("%s", msg);
        fflush(stdout);
        int r = scanf("%d", &valor);
        if (r == EOF) exit(0);
        if (r != 1) {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero entre %d e %d.\n", min, max);
            continue;
        }
        limpar_buffer();
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo. Digite entre %d e %d.\n", min, max);
            continue;
        }
        return valor;
    }
}
