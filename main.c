#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_JOGADORES 100
#define MAX_PALPITES 100
#define MAX_SESSOES 200

// estrutura do jogador pro ranking
typedef struct {
    char nome[50];
    int acertos;
    int tentativas;
} Jogador;

// guarda os dados de uma partida
typedef struct {
    char timestamp[30];
    char nome[50];
    int numero_alvo;
    int total_tentativas;
    int palpites_baixo;
    int palpites_alto;
    int sequencia[MAX_PALPITES];
} Sessao;

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

// recursao pra calcular a media
double media_recursiva(Sessao sessoes[], int n) {
    if (n == 1) return sessoes[0].total_tentativas;
    return (media_recursiva(sessoes, n - 1) * (n - 1) + sessoes[n - 1].total_tentativas) / n;
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

void analisar_historico() {
    printf("\033[2J\033[H");
    Sessao sessoes[MAX_SESSOES];
    int total = carregar_historico(sessoes, MAX_SESSOES);

    printf("\n=== ANALISE DO HISTORICO ===\n");

    if (total == 0) {
        printf("Nenhuma sessao encontrada. Jogue primeiro!\n");
        return;
    }

    double media = media_recursiva(sessoes, total);
    int melhor   = minimo_recursivo(sessoes, total);
    int pior     = maximo_recursivo(sessoes, total);
    double desvio = sqrt(soma_quad(sessoes, total, media) / total);

    // calcula o vies do jogador
    double total_baixo = 0, total_alto = 0;
    for (int i = 0; i < total; i++) {
        total_baixo += sessoes[i].palpites_baixo;
        total_alto  += sessoes[i].palpites_alto;
    }
    double tp = total_baixo + total_alto;
    double taxa_baixo = tp > 0 ? (total_baixo / tp) * 100.0 : 0;
    double taxa_alto  = tp > 0 ? (total_alto  / tp) * 100.0 : 0;

    printf("Total de sessoes    : %d\n", total);
    printf("Media de tentativas : %.2f\n", media);
    printf("Melhor sessao       : %d tentativas\n", melhor);
    printf("Pior sessao         : %d tentativas\n", pior);
    printf("Desvio padrao       : %.2f\n", desvio);
    printf("Vies baixo / alto   : %.1f%% / %.1f%%\n", taxa_baixo, taxa_alto);

    printf("\n--- Sugestoes ---\n");
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

// ordena o ranking por acertos, desempata por menos tentativas
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

    // monta e salva a sessao
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
    printf("Progresso salvo!\n");
}

int main() {
    srand(time(NULL));
    int op;

    printf("\033[2J\033[H");
    printf("=== RANDON-WITCH: Jogo de Adivinhacao ===\n");

    do {
        printf("\n1 - Jogar\n2 - Analisar historico\n3 - Ranking\n4 - Sair\n");
        op = ler_inteiro("Opcao: ", 1, 4);

        if (op == 1) jogar();
        else if (op == 2) analisar_historico();
        else if (op == 3) mostrar_ranking();
        else printf("Ate mais!\n");

    } while (op != 4);

    return 0;
}