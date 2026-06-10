CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lm
SRC = main.c jogo.c historico.c estatisticas.c ranking.c utils.c loja.c
OUT = jogo

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
