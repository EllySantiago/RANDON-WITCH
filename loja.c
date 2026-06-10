#include <stdio.h>
#include <string.h>
#include "loja.h"
#include "utils.h"

typedef struct {
    char nome[50];
    char descricao[100];
    int custo;
} Item;

static Item catalogo[] = {
    { "Dica de Intervalo",  "Revela se o alvo esta na metade superior ou inferior do intervalo", 30 },
    { "Palpite Bonus",      "Ganha 3 tentativas extras no modo Dificil",                         50 },
    { "Revelar Dezena",     "Revela o digito das dezenas do numero alvo",                        80 },
};
static int NUM_ITENS = 3;

int carregar_moedas(const char *nome) {
    FILE *f = fopen("moedas.txt", "r");
    if (!f) return 0;

    char n[50];
    int saldo;
    while (fscanf(f, "%49s %d", n, &saldo) == 2) {
        if (strcmp(n, nome) == 0) {
            fclose(f);
            return saldo;
        }
    }
    fclose(f);
    return 0;
}

void salvar_moedas(const char *nome, int moedas) {
    char nomes[100][50];
    int saldos[100];
    int total = 0;
    int encontrado = 0;

    FILE *f = fopen("moedas.txt", "r");
    if (f) {
        while (total < 100 && fscanf(f, "%49s %d", nomes[total], &saldos[total]) == 2) {
            if (strcmp(nomes[total], nome) == 0) {
                saldos[total] = moedas;
                encontrado = 1;
            }
            total++;
        }
        fclose(f);
    }

    if (!encontrado && total < 100) {
        strncpy(nomes[total], nome, 49);
        saldos[total] = moedas;
        total++;
    }

    f = fopen("moedas.txt", "w");
    if (!f) return;
    for (int i = 0; i < total; i++)
        fprintf(f, "%s %d\n", nomes[i], saldos[i]);
    fclose(f);
}

void adicionar_moedas(const char *nome, int quantidade) {
    int atual = carregar_moedas(nome);
    salvar_moedas(nome, atual + quantidade);
    printf("Voce ganhou %d moeda(s) de premio! Saldo: %d moedas.\n", quantidade, atual + quantidade);
}

void abrir_loja(const char *nome) {
    printf("\033[2J\033[H");
    printf("=== LOJA DE PREMIOS ===\n");

    int saldo = carregar_moedas(nome);
    printf("Jogador: %s | Saldo: %d moedas\n\n", nome, saldo);

    for (int i = 0; i < NUM_ITENS; i++)
        printf("%d - %-20s (%d moedas) — %s\n", i + 1, catalogo[i].nome, catalogo[i].custo, catalogo[i].descricao);
    printf("%d - Voltar ao menu\n", NUM_ITENS + 1);

    int op = ler_inteiro("Escolha: ", 1, NUM_ITENS + 1);
    if (op == NUM_ITENS + 1) return;

    Item *item = &catalogo[op - 1];
    if (saldo < item->custo) {
        printf("Saldo insuficiente. Voce tem %d moedas e o item custa %d.\n", saldo, item->custo);
        return;
    }

    salvar_moedas(nome, saldo - item->custo);
    printf("Item '%s' resgatado com sucesso! Saldo restante: %d moedas.\n",
           item->nome, saldo - item->custo);

    if (op == 1) {
        char nomes[100][50];
        int qtds[100];
        int total = 0, encontrado = 0;
        FILE *f = fopen("itens.txt", "r");
        if (f) {
            while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
                if (strcmp(nomes[total], nome) == 0) { qtds[total]++; encontrado = 1; }
                total++;
            }
            fclose(f);
        }
        if (!encontrado && total < 100) {
            strncpy(nomes[total], nome, 49);
            qtds[total] = 1;
            total++;
        }
        f = fopen("itens.txt", "w");
        if (f) {
            for (int i = 0; i < total; i++)
                fprintf(f, "%s %d\n", nomes[i], qtds[i]);
            fclose(f);
        }
        printf("Use a Dica de Intervalo durante a partida digitando 0 no lugar do palpite.\n");
    } else if (op == 2) {
        char nomes[100][50];
        int qtds[100];
        int total = 0, encontrado = 0;
        FILE *f = fopen("bonus.txt", "r");
        if (f) {
            while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
                if (strcmp(nomes[total], nome) == 0) { qtds[total]++; encontrado = 1; }
                total++;
            }
            fclose(f);
        }
        if (!encontrado && total < 100) {
            strncpy(nomes[total], nome, 49);
            qtds[total] = 1;
            total++;
        }
        f = fopen("bonus.txt", "w");
        if (f) {
            for (int i = 0; i < total; i++)
                fprintf(f, "%s %d\n", nomes[i], qtds[i]);
            fclose(f);
        }
        printf("+3 tentativas extras serao aplicadas automaticamente no proximo modo Dificil.\n");
    } else if (op == 3) {
        char nomes[100][50];
        int qtds[100];
        int total = 0, encontrado = 0;
        FILE *f = fopen("dezena.txt", "r");
        if (f) {
            while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
                if (strcmp(nomes[total], nome) == 0) { qtds[total]++; encontrado = 1; }
                total++;
            }
            fclose(f);
        }
        if (!encontrado && total < 100) {
            strncpy(nomes[total], nome, 49);
            qtds[total] = 1;
            total++;
        }
        f = fopen("dezena.txt", "w");
        if (f) {
            for (int i = 0; i < total; i++)
                fprintf(f, "%s %d\n", nomes[i], qtds[i]);
            fclose(f);
        }
        printf("A dezena do numero alvo sera revelada ao iniciar a proxima partida.\n");
    }
}

int tem_dica(const char *nome) {
    FILE *f = fopen("itens.txt", "r");
    if (!f) return 0;
    char n[50]; int qtd;
    while (fscanf(f, "%49s %d", n, &qtd) == 2) {
        if (strcmp(n, nome) == 0) { fclose(f); return qtd; }
    }
    fclose(f);
    return 0;
}

void usar_dica(const char *nome) {
    char nomes[100][50];
    int qtds[100];
    int total = 0;
    FILE *f = fopen("itens.txt", "r");
    if (f) {
        while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
            if (strcmp(nomes[total], nome) == 0 && qtds[total] > 0) qtds[total]--;
            total++;
        }
        fclose(f);
    }
    f = fopen("itens.txt", "w");
    if (f) {
        for (int i = 0; i < total; i++)
            fprintf(f, "%s %d\n", nomes[i], qtds[i]);
        fclose(f);
    }
}

int tem_bonus(const char *nome) {
    FILE *f = fopen("bonus.txt", "r");
    if (!f) return 0;
    char n[50]; int qtd;
    while (fscanf(f, "%49s %d", n, &qtd) == 2) {
        if (strcmp(n, nome) == 0) { fclose(f); return qtd; }
    }
    fclose(f);
    return 0;
}

void usar_bonus(const char *nome) {
    char nomes[100][50];
    int qtds[100];
    int total = 0;
    FILE *f = fopen("bonus.txt", "r");
    if (f) {
        while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
            if (strcmp(nomes[total], nome) == 0 && qtds[total] > 0) qtds[total]--;
            total++;
        }
        fclose(f);
    }
    f = fopen("bonus.txt", "w");
    if (f) {
        for (int i = 0; i < total; i++)
            fprintf(f, "%s %d\n", nomes[i], qtds[i]);
        fclose(f);
    }
}

int tem_dezena(const char *nome) {
    FILE *f = fopen("dezena.txt", "r");
    if (!f) return 0;
    char n[50]; int qtd;
    while (fscanf(f, "%49s %d", n, &qtd) == 2) {
        if (strcmp(n, nome) == 0) { fclose(f); return qtd; }
    }
    fclose(f);
    return 0;
}

void usar_dezena(const char *nome) {
    char nomes[100][50];
    int qtds[100];
    int total = 0;
    FILE *f = fopen("dezena.txt", "r");
    if (f) {
        while (total < 100 && fscanf(f, "%49s %d", nomes[total], &qtds[total]) == 2) {
            if (strcmp(nomes[total], nome) == 0 && qtds[total] > 0) qtds[total]--;
            total++;
        }
        fclose(f);
    }
    f = fopen("dezena.txt", "w");
    if (f) {
        for (int i = 0; i < total; i++)
            fprintf(f, "%s %d\n", nomes[i], qtds[i]);
        fclose(f);
    }
}
