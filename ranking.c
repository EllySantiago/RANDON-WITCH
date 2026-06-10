#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ranking.h"
#include "loja.h"

void ordenar_ranking(Jogador lista[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            int trocar = 0;
            if (lista[j].acertos < lista[j+1].acertos) {
                trocar = 1;
            } else if (lista[j].acertos == lista[j+1].acertos) {
                if (lista[j].tentativas > lista[j+1].tentativas)
                    trocar = 1;
            }
            if (trocar) {
                Jogador temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void atualizar_ranking(char *nome, int novas_tentativas, const char *data) {
    Jogador lista[MAX_JOGADORES];
    int total = 0;
    int encontrado = 0;

    FILE *f = fopen("ranking.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%49s %d %d %29s",
                      lista[total].nome,
                      &lista[total].acertos,
                      &lista[total].tentativas,
                      lista[total].ultima_data) == 4) {
            if (strcmp(lista[total].nome, nome) == 0) {
                lista[total].acertos += 1;
                lista[total].tentativas += novas_tentativas;
                strncpy(lista[total].ultima_data, data, 29);
                encontrado = 1;
            }
            total++;
        }
        fclose(f);
    }

    if (!encontrado && total < MAX_JOGADORES) {
        strcpy(lista[total].nome, nome);
        lista[total].acertos = 1;
        lista[total].tentativas = novas_tentativas;
        strncpy(lista[total].ultima_data, data, 29);
        total++;
    }

    ordenar_ranking(lista, total);

    f = fopen("ranking.txt", "w");
    for (int i = 0; i < total; i++)
        fprintf(f, "%s %d %d %s\n",
                lista[i].nome, lista[i].acertos,
                lista[i].tentativas, lista[i].ultima_data);
    fclose(f);
}

void mostrar_ranking() {
    printf("\033[2J\033[H");
    FILE *f = fopen("ranking.txt", "r");
    Jogador j;

    printf("\n--- RANKING (Mestres da Logica) ---\n");

    if (!f) {
        printf("Nenhuma partida registrada ainda. Jogue uma partida para aparecer no ranking!\n");
        return;
    }

    printf("%-4s %-15s %-8s %-12s %-8s %-12s\n", "Pos", "Jogador", "Acertos", "Tent. Totais", "Moedas", "Ultimo Acerto");
    printf("--------------------------------------------------------------------------\n");

    int pos = 1;
    while (fscanf(f, "%49s %d %d %29s", j.nome, &j.acertos, &j.tentativas, j.ultima_data) == 4) {
        int moedas = carregar_moedas(j.nome);
        printf("%-4d %-15s %-8d %-12d %-8d %-12s\n", pos++, j.nome, j.acertos, j.tentativas, moedas, j.ultima_data);
    }
    fclose(f);
}
