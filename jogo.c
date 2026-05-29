#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "tipos.h"
#include "historico.h"
#include "ranking.h"
#include "utils.h"

static void mensagem_motivacional(int tentativas, int referencia) {
    printf("\n--- Resumo da partida ---\n");
    if (tentativas <= referencia)
        printf("Sensacional! Voce e um mestre da busca binaria!\n");
    else if (tentativas <= referencia + 3)
        printf("Muito bem! Estrategia afiada, continue assim.\n");
    else if (tentativas <= referencia + 6)
        printf("Bom jogo! Com mais pratica voce vai melhorar ainda mais.\n");
    else
        printf("Nao desista! Tente comecar sempre pelo meio e ir dividindo o intervalo.\n");
}

void jogar() {
    printf("\033[2J\033[H");
    char nome[50];
    printf("\nSeu nome (sem espacos): ");
    fflush(stdout);
    scanf("%49s", nome);
    limpar_buffer();

    printf("\nEscolha a dificuldade:\n");
    printf("  1 - Facil   (1 a  50, sem limite de tentativas)\n");
    printf("  2 - Medio   (1 a 100, sem limite de tentativas)\n");
    printf("  3 - Dificil (1 a 200, limite de 10 tentativas)\n");
    int op = ler_inteiro("Dificuldade: ", 1, 3);

    int max_alvo, limite, ref_motivacional;
    Dificuldade dif;
    switch (op) {
        case 1: dif = FACIL;   max_alvo = 50;  limite = 0;  ref_motivacional = 4; break;
        case 3: dif = DIFICIL; max_alvo = 200; limite = 10; ref_motivacional = 9; break;
        default: dif = MEDIO;  max_alvo = 100; limite = 0;  ref_motivacional = 7; break;
    }
    (void)dif;

    int alvo = (rand() % max_alvo) + 1;
    int palpite, tentativas = 0;
    int palpites_baixo = 0, palpites_alto = 0;
    int sequencia[MAX_PALPITES];
    int acertou = 0;

    if (limite > 0)
        printf("\nOk %s! Adivinhe o numero entre 1 e %d. Voce tem %d tentativas!\n", nome, max_alvo, limite);
    else
        printf("\nOk %s! Adivinhe o numero entre 1 e %d.\n", nome, max_alvo);

    while (1) {
        if (limite > 0 && tentativas >= limite) {
            printf("Fim de jogo! O numero era %d. Tente novamente!\n", alvo);
            break;
        }
        if (limite > 0)
            printf("[%d/%d] ", tentativas + 1, limite);
        palpite = ler_inteiro("Palpite: ", 1, max_alvo);
        sequencia[tentativas] = palpite;
        tentativas++;

        if (palpite == alvo) {
            printf("Acertou! O numero era %d. Voce levou %d tentativa(s).\n", alvo, tentativas);
            acertou = 1;
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
    if (acertou) {
        atualizar_ranking(nome, tentativas);
        mensagem_motivacional(tentativas, ref_motivacional);
    }
    printf("Progresso salvo!\n");
}
