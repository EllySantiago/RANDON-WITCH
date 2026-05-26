#include <stdio.h>
#include <string.h>
#include "ranking.h"

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

void atualizar_ranking(char *nome, int novas_tentativas) {
    Jogador lista[MAX_JOGADORES];
    int total = 0;
    int encontrado = 0;

    FILE *f = fopen("ranking.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%49s %d %d", lista[total].nome, &lista[total].acertos, &lista[total].tentativas) == 3) {
            if (strcmp(lista[total].nome, nome) == 0) {
                lista[total].acertos += 1;
                lista[total].tentativas += novas_tentativas;
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
        total++;
    }

    ordenar_ranking(lista, total);

    f = fopen("ranking.txt", "w");
    for (int i = 0; i < total; i++)
        fprintf(f, "%s %d %d\n", lista[i].nome, lista[i].acertos, lista[i].tentativas);
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

    printf("%-4s %-15s %-8s %-10s\n", "Pos", "Jogador", "Acertos", "Tent. Totais");
    printf("------------------------------------------\n");

    int pos = 1;
    while (fscanf(f, "%49s %d %d", j.nome, &j.acertos, &j.tentativas) == 3) {
        printf("%-4d %-15s %-8d %-10d\n", pos++, j.nome, j.acertos, j.tentativas);
    }
    fclose(f);
}
