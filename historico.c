#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "historico.h"

// salva a sessao no historico.txt
void salvar_historico(Sessao *s) {
    FILE *f = fopen("historico.txt", "a");
    if (!f) {
        printf("Erro ao abrir historico.txt\n");
        return;
    }

    fprintf(f, "SESSAO\n");
    fprintf(f, "timestamp=%s\n", s->timestamp);
    fprintf(f, "nome=%s\n", s->nome);
    fprintf(f, "numero_alvo=%d\n", s->numero_alvo);
    fprintf(f, "total_tentativas=%d\n", s->total_tentativas);
    fprintf(f, "palpites_baixo=%d\n", s->palpites_baixo);
    fprintf(f, "palpites_alto=%d\n", s->palpites_alto);
    fprintf(f, "sequencia=");
    for (int i = 0; i < s->total_tentativas; i++) {
        fprintf(f, "%d", s->sequencia[i]);
        if (i < s->total_tentativas - 1) fprintf(f, ",");
    }
    fprintf(f, "\nFIM\n");
    fclose(f);
}

// le o historico.txt e reconstroi as sessoes
int carregar_historico(Sessao sessoes[], int max) {
    FILE *f = fopen("historico.txt", "r");
    if (!f) return 0;

    int total = 0;
    char linha[512];

    while (total < max && fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strcmp(linha, "SESSAO") != 0) continue;

        Sessao *s = &sessoes[total];
        memset(s, 0, sizeof(Sessao));

        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = 0;
            if (strcmp(linha, "FIM") == 0) break;

            char *eq = strchr(linha, '=');
            if (!eq) continue;
            *eq = '\0';
            char *chave = linha;
            char *valor = eq + 1;

            if (strcmp(chave, "timestamp") == 0)
                strncpy(s->timestamp, valor, 29);
            else if (strcmp(chave, "nome") == 0)
                strncpy(s->nome, valor, 49);
            else if (strcmp(chave, "numero_alvo") == 0)
                s->numero_alvo = atoi(valor);
            else if (strcmp(chave, "total_tentativas") == 0)
                s->total_tentativas = atoi(valor);
            else if (strcmp(chave, "palpites_baixo") == 0)
                s->palpites_baixo = atoi(valor);
            else if (strcmp(chave, "palpites_alto") == 0)
                s->palpites_alto = atoi(valor);
            else if (strcmp(chave, "sequencia") == 0) {
                char copia[512];
                strncpy(copia, valor, 511);
                char *tok = strtok(copia, ",");
                int idx = 0;
                while (tok && idx < MAX_PALPITES) {
                    s->sequencia[idx++] = atoi(tok);
                    tok = strtok(NULL, ",");
                }
            }
        }
        total++;
    }
    fclose(f);
    return total;
}
