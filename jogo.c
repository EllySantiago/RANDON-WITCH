#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "tipos.h"
#include "historico.h"
#include "ranking.h"
#include "utils.h"

// mensagem motivacional baseada no desempenho da partida
static void mensagem_motivacional(int tentativas) {
    printf("\n--- Resumo da partida ---\n");
    if (tentativas <= 5)
        printf("Sensacional! Voce e um mestre da busca binaria!\n");
    else if (tentativas <= 8)
        printf("Muito bem! Estrategia afiada, continue assim.\n");
    else if (tentativas <= 12)
        printf("Bom jogo! Com mais pratica voce vai melhorar ainda mais.\n");
    else
        printf("Nao desista! Tente comecar sempre pelo meio (50) e ir dividindo o intervalo.\n");
}

void jogar() {
    printf("\033[2J\033[H");
    char nome[50];
    printf("\nSeu nome (sem espacos): ");
    scanf("%49s", nome);
    limpar_buffer();

    int alvo = (rand() % 100) + 1;
    int palpite, tentativas = 0;
    int palpites_baixo = 0, palpites_alto = 0;
    int sequencia[MAX_PALPITES];

    printf("\nOk %s! Adivinhe o numero entre 1 e 100.\n", nome);

    while (1) {
        palpite = ler_inteiro("Palpite: ", 1, 100);
        sequencia[tentativas] = palpite;
        tentativas++;

        if (palpite == alvo) {
            printf("Acertou! O numero era %d. Voce levou %d tentativa(s).\n", alvo, tentativas);
            break;
        } else if (palpite < alvo) {
            printf("Muito baixo!\n");
            palpites_baixo++;
        } else {
            printf("Muito alto!\n");
            palpites_alto++;
        }
    }

    Sessao s;
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(s.timestamp, sizeof(s.timestamp), "%Y-%m-%d %H:%M:%S", t);
    strncpy(s.nome, nome, 49);
    s.numero_alvo = alvo;
    s.total_tentativas = tentativas;
    s.palpites_baixo = palpites_baixo;
    s.palpites_alto = palpites_alto;
    memcpy(s.sequencia, sequencia, sizeof(int) * tentativas);

    salvar_historico(&s);
    atualizar_ranking(nome, tentativas);
    mensagem_motivacional(tentativas);
    printf("Progresso salvo!\n");
}
