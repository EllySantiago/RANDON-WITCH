#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "estatisticas.h"
#include "historico.h"
#include "utils.h"

// recursao pra calcular a soma
int soma_recursiva(Sessao sessoes[], int n) {
    if (n == 1) return sessoes[0].total_tentativas;
    return soma_recursiva(sessoes, n - 1) + sessoes[n - 1].total_tentativas;
}

// recursao pra achar o minimo
int minimo_recursivo(Sessao sessoes[], int n) {
    if (n == 1) return sessoes[0].total_tentativas;
    int resto = minimo_recursivo(sessoes, n - 1);
    return sessoes[n - 1].total_tentativas < resto ? sessoes[n - 1].total_tentativas : resto;
}

// recursao pra achar o maximo
int maximo_recursivo(Sessao sessoes[], int n) {
    if (n == 1) return sessoes[0].total_tentativas;
    int resto = maximo_recursivo(sessoes, n - 1);
    return sessoes[n - 1].total_tentativas > resto ? sessoes[n - 1].total_tentativas : resto;
}

// soma dos quadrados pra calcular desvio padrao
double soma_quad(Sessao sessoes[], int n, double media) {
    if (n == 1) return pow(sessoes[0].total_tentativas - media, 2);
    return soma_quad(sessoes, n - 1, media) + pow(sessoes[n - 1].total_tentativas - media, 2);
}

// mostra o relatorio de uma sessao individual
static void exibir_sessao(Sessao *s, int numero) {
    printf("\n--- Partida #%d ---\n", numero);
    printf("Data: %s\n", s->timestamp);
    printf("Jogador: %s\n", s->nome);
    printf("Numero alvo: %d\n", s->numero_alvo);
    printf("Tentativas: %d\n", s->total_tentativas);
    printf("Palpites abaixo: %d | acima: %d\n", s->palpites_baixo, s->palpites_alto);
    printf("Sequencia: ");
    for (int i = 0; i < s->total_tentativas; i++) {
        printf("%d", s->sequencia[i]);
        if (i < s->total_tentativas - 1) printf(" -> ");
    }
    printf("\n");

    if (s->total_tentativas <= 7)
        printf("Avaliacao: excelente desempenho!\n");
    else if (s->total_tentativas <= 12)
        printf("Avaliacao: desempenho mediano.\n");
    else
        printf("Avaliacao: pode melhorar a estrategia.\n");
}

void analisar_historico() {
    printf("\033[2J\033[H");
    Sessao sessoes[MAX_SESSOES];
    int total = carregar_historico(sessoes, MAX_SESSOES);

    printf("\n=== ANALISE DO HISTORICO ===\n");

    if (total == 0) {
        printf("Nenhuma sessao encontrada. Jogue primeiro!\n");
        return;
    }

    printf("\n1 - Ver todas as partidas\n");
    printf("2 - Filtrar por jogador\n");
    int op = ler_inteiro("Opcao: ", 1, 2);

    char filtro[50] = "";
    if (op == 2) {
        // coleta jogadores unicos do historico
        char jogadores[MAX_SESSOES][50];
        int njog = 0;
        for (int i = 0; i < total; i++) {
            int ja_existe = 0;
            for (int j = 0; j < njog; j++) {
                if (strcmp(jogadores[j], sessoes[i].nome) == 0) { ja_existe = 1; break; }
            }
            if (!ja_existe) strncpy(jogadores[njog++], sessoes[i].nome, 49);
        }
        printf("\nJogadores no historico:\n");
        for (int i = 0; i < njog; i++)
            printf("  %d - %s\n", i + 1, jogadores[i]);
        printf("\nEscolha o numero ou digite o nome: ");
        char entrada[50];
        scanf("%49s", entrada);
        limpar_buffer();
        // verifica se e numero
        int escolha = atoi(entrada);
        if (escolha >= 1 && escolha <= njog)
            strncpy(filtro, jogadores[escolha - 1], 49);
        else
            strncpy(filtro, entrada, 49);
    }

    Sessao filtradas[MAX_SESSOES];
    int qtd = 0;
    for (int i = 0; i < total; i++) {
        if (op == 1 || strcmp(sessoes[i].nome, filtro) == 0) {
            filtradas[qtd++] = sessoes[i];
        }
    }

    if (qtd == 0) {
        printf("\nNenhuma partida encontrada para '%s'.\n", filtro);
        return;
    }

    printf("\n=== RELATORIO POR PARTIDA ===\n");
    printf("(Exibindo as ultimas 10 de %d partidas)\n", qtd);
    int inicio = qtd > 10 ? qtd - 10 : 0;
    for (int i = inicio; i < qtd; i++)
        exibir_sessao(&filtradas[i], i + 1);

    // estatisticas agregadas usando recursao
    int soma_total = soma_recursiva(filtradas, qtd);
    double media   = (double)soma_total / qtd;
    int melhor     = minimo_recursivo(filtradas, qtd);
    int pior       = maximo_recursivo(filtradas, qtd);
    double desvio  = sqrt(soma_quad(filtradas, qtd, media) / qtd);

    double total_baixo = 0, total_alto = 0;
    for (int i = 0; i < qtd; i++) {
        total_baixo += filtradas[i].palpites_baixo;
        total_alto  += filtradas[i].palpites_alto;
    }
    double tp = total_baixo + total_alto;
    double taxa_baixo = tp > 0 ? (total_baixo / tp) * 100.0 : 0;
    double taxa_alto  = tp > 0 ? (total_alto  / tp) * 100.0 : 0;

    printf("\n=== ESTATISTICAS AGREGADAS ===\n");
    printf("Total de sessoes    : %d\n", qtd);
    printf("Soma de tentativas  : %d\n", soma_total);
    printf("Media de tentativas : %.2f\n", media);
    printf("Melhor sessao       : %d tentativas\n", melhor);
    printf("Pior sessao         : %d tentativas\n", pior);
    printf("Desvio padrao       : %.2f\n", desvio);
    printf("Vies baixo / alto   : %.1f%% / %.1f%%\n", taxa_baixo, taxa_alto);

    printf("\n--- Sugestoes de Estrategia ---\n");
    if (media > 10)
        printf("Voce usa muitas tentativas. Tente comecar sempre pelo meio (50).\n");
    else if (media <= 7)
        printf("Boa estrategia! Voce esta perto de uma busca binaria otimizada.\n");

    if (taxa_baixo > 60)
        printf("Voce chuta muito baixo. Tente comecar com valores mais altos.\n");
    else if (taxa_alto > 60)
        printf("Voce chuta muito alto. Tente comecar com valores mais baixos.\n");
    else
        printf("Seu vies esta equilibrado, continue assim!\n");

    if (desvio > 5)
        printf("Sua consistencia esta baixa. Tente usar sempre a mesma estrategia.\n");
}
