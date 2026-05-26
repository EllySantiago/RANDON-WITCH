CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
SRC = main.c jogo.c historico.c estatisticas.c ranking.c utils.c
OUT = jogo

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
