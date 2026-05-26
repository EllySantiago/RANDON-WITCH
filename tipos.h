#ifndef TIPOS_H
#define TIPOS_H

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

#endif
