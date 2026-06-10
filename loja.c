#include <stdio.h>
#include <string.h>
#include "loja.h"
#include "utils.h"

// itens disponiveis na loja
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

// le o saldo de moedas do jogador no arquivo moedas.txt
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

// salva o saldo atualizado do jogador
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

// adiciona moedas ao saldo do jogador (chamado apos vitoria)
void adicionar_moedas(const char *nome, int quantidade) {
    int atual = carregar_moedas(nome);
    salvar_moedas(nome, atual + quantidade);
    printf("Voce ganhou %d moeda(s) de premio! Saldo: %d moedas.\n", quantidade, atual + quantidade);
}

// exibe o menu da loja e processa compras
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

    // itens 2 e 3 ainda nao disponiveis
    if (op == 2 || op == 3) {
        printf("Este item estara disponivel em breve!\n");
        return;
    }

    Item *item = &catalogo[op - 1];
    if (saldo < item->custo) {
        printf("Saldo insuficiente. Voce tem %d moedas e o item custa %d.\n", saldo, item->custo);
        return;
    }

    salvar_moedas(nome, saldo - item->custo);
    printf("Item '%s' resgatado com sucesso! Saldo restante: %d moedas.\n",
           item->nome, saldo - item->custo);

    // registra a dica de intervalo em itens.txt
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
    } else {
        printf("(Item sera aplicado na sua proxima partida.)\n");
    }
}

// retorna quantas dicas o jogador tem disponiveis
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

// decrementa uma dica do jogador
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
