#include <stdio.h>
#include "utils.h"

// limpa o buffer pra nao bugar na proxima leitura
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// le um inteiro e valida o intervalo
int ler_inteiro(const char *msg, int min, int max) {
    int valor;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &valor) != 1) {
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
