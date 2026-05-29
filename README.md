# RANDON-WITCH — Jogo de Adivinhacao

Projeto Integrador da disciplina de Programacao Imperativa e Funcional (PIF)
Curso de Analise e Desenvolvimento de Sistemas — 2026.1

## Equipe
- Ana Beatriz Bezerra Lopes da Costa
- Claudemir Pereira de Araujo Filho
- Drielly Santiago dos Santos

---

## Sobre o Projeto

Jogo de adivinhacao desenvolvido em linguagem C onde o sistema sorteia um numero dentro de um intervalo definido pela dificuldade escolhida. O jogador tenta descobri-lo atraves de palpites e recebe uma dica a cada tentativa ("Muito baixo" / "Muito alto" / "Acertou"). Toda partida e registrada em arquivo, alimentando um modulo de analise estatistica (com recursao) e um ranking de jogadores.

---

## Funcionalidades

### Modos de Jogo

- **Jogar nova partida** — escolhe a dificuldade, sorteia o numero, recebe palpites com dicas; ao final salva a sessao e atualiza o ranking (se acertou).
- **Analisar historico** — exibe relatorio por partida e estatisticas agregadas, com sugestoes de estrategia. Permite ver todas as partidas ou filtrar por jogador.
- **Ranking** — placar dos jogadores ordenado por desempenho, salvo em arquivo.

### Niveis de Dificuldade (H4 — Sprint 01)

| Nivel   | Intervalo | Limite de Tentativas |
|---------|-----------|----------------------|
| Facil   | 1 a 50    | Sem limite           |
| Medio   | 1 a 100   | Sem limite           |
| Dificil | 1 a 200   | 10 tentativas        |

No modo Dificil, se o jogador esgotar as 10 tentativas sem acertar, o jogo encerra exibindo o numero correto.

### Analise e Estatisticas

- Relatorio individual de cada partida (data, jogador, numero alvo, sequencia de palpites).
- Estatisticas agregadas: total de sessoes, soma e media de tentativas, melhor e pior sessao, desvio padrao e vies baixo/alto.
- Sugestoes textuais de estrategia baseadas no historico (busca pelo meio, busca binaria, equilibrio de vies).

---

## Historias Implementadas — Sprint 01

| Historia | Descricao | Status |
|----------|-----------|--------|
| H1 | Jogar nova partida: sorteio, loop de palpites, dicas e registro da sessao | Concluido |
| H2 | Analisar historico: leitura com `fgets`, recursao, estatisticas e sugestoes | Concluido |
| H3 | Entrada invalida: validacao de intervalo, limpeza de buffer, EOF handling | Concluido |
| H4 | Nivel de dificuldade: Facil/Medio/Dificil com intervalos e limite de tentativas | Concluido |

---

## Requisitos Funcionais (RF)

| Cod. | Descricao |
|------|-----------|
| RF01 | Geracao do numero alvo com `rand()` e `srand()` a cada sessao |
| RF02 | Loop de palpites com validacao de intervalo e dicas: "Muito baixo", "Muito alto", "Acertou" |
| RF03 | Registro da sessao em arquivo texto: timestamp, nome, alvo, tentativas, palpites abaixo/acima e sequencia CSV |
| RF04 | Leitura do historico com `fgets()` e reconstrucao das sessoes para analise |
| RF05 | Calculo de estatisticas: total de sessoes, media, melhor/pior sessao, desvio padrao e vies baixo/alto |
| RF06 | Uso de recursao em soma, minimo, maximo e soma dos quadrados das diferencas |
| RF07 | Sugestoes textuais de estrategia baseadas no historico |
| RF08 | Selecao de nivel de dificuldade com intervalo e limite de tentativas variaveis |

## Requisitos Nao Funcionais

- Multiplataforma: Windows, Linux e macOS
- Compativel com compiladores C11
- Sem dependencias externas (apenas a libm, via `-lm`)
- Persistencia em arquivo texto simples
- Codigo modular, legivel e comentado de forma enxuta

---

## Estrutura do Projeto

```
RANDON-WITCH/
├── main.c              # Menu principal e ponto de entrada
├── jogo.c / .h         # Logica da partida e selecao de dificuldade
├── historico.c / .h    # Escrita e leitura do arquivo de sessoes
├── estatisticas.c / .h # Estatisticas e sugestoes (com recursao)
├── ranking.c / .h      # Registro e exibicao do ranking
├── utils.c / .h        # Leitura validada de entrada, limpeza de buffer e EOF handling
├── tipos.h             # Structs Jogador e Sessao, enum Dificuldade
├── Makefile            # Compilacao e execucao
├── historico.txt       # Arquivo de sessoes (gerado em tempo de execucao)
├── ranking.txt         # Arquivo de ranking (gerado em tempo de execucao)
├── screencast.html     # Screencast interativo da execucao
├── docs/               # Imagens do sprint board e issue tracker
└── README.md
```

---

## Compilacao e Execucao

```bash
make        # compila o executavel "jogo"
make run    # compila e executa
make clean  # remove o executavel
```

---

## Menu Principal

```
=== RANDON-WITCH: Jogo de Adivinhacao ===
1 - Jogar
2 - Analisar historico
3 - Ranking
4 - Sair
```

---

## Formato do Historico

Cada sessao e gravada em `historico.txt` como um bloco de chave=valor:

| Campo            | Descricao                                  |
|------------------|--------------------------------------------|
| timestamp        | Data e hora da partida                     |
| nome             | Nome do jogador                            |
| numero_alvo      | Numero sorteado                            |
| total_tentativas | Total de palpites validos                  |
| palpites_baixo   | Quantidade de palpites abaixo do alvo      |
| palpites_alto    | Quantidade de palpites acima do alvo       |
| sequencia        | Lista de todos os palpites separados por virgula |

---

## Tratamento de Erros

| Situacao                              | Comportamento                                      |
|---------------------------------------|----------------------------------------------------|
| Arquivo de historico inexistente      | Exibe "Nenhuma sessao encontrada" e retorna ao menu |
| Historico nao pode ser aberto p/ escrita | Mensagem de erro no terminal; jogo continua      |
| Entrada nao numerica                  | Buffer limpo; solicita novo valor                  |
| Valor fora do intervalo               | Mensagem de erro; tentativa nao e contabilizada    |
| EOF inesperado (Ctrl+D)               | Programa encerra graciosamente via `exit(0)`       |
| Ranking sem partidas registradas      | Mensagem amigavel; sem travamento                  |
| Modo dificil sem acerto em 10 tents. | Game over com revelacao do numero correto          |

---

## Sprint 01 — Quadro e Backlog

![Quadro da Sprint 01](docs/sprint_board.png)

A Sprint 01 cobre a semana de 25/05 a 28/05/2026 (Entrega 03). As historias H1, H2, H3 e H4 foram implementadas e movidas para **Concluido**. As historias H5 a H9 permanecem no **Backlog** para entregas futuras.

---

## Issue / Bug Tracker

![Issues do Projeto](docs/issues_tracker.png)

O tracker de issues esta disponivel na aba **Issues** do repositorio GitHub. Issues abertos referentes a esta entrega: entrada invalida sem tratamento de EOF (#7), duplicacao no ranking (#6), criacao automatica do historico (#4) e validacao de nome vazio (#5). Issues #2 e #3 foram fechados nesta sprint.

---

## Testes de Sistema

O screencast completo da execucao esta disponivel em [`screencast.html`](screencast.html) — abre direto no navegador e demonstra:

- Selecao do nivel de dificuldade (Facil, Medio, Dificil)
- Entrada invalida nao-numerica (`abc`) com mensagem de erro e continuacao da partida
- Valor fora do intervalo (`150` no modo Medio) rejeitado sem contar tentativa
- Modo Dificil com contador de tentativas `[X/10]` e game over ao esgotar
- Sequencia de palpites com dicas "Muito baixo" / "Muito alto"
- Acerto com exibicao do total de tentativas e registro no historico
- Analise do historico com estatisticas e sugestao de estrategia

---

## Programacao em Par

Esta sprint foi desenvolvida em tres sessoes de pair programming:

| Par | Integrantes | Funcionalidades |
|-----|-------------|-----------------|
| Par 1 | Drielly Santiago + Ana Beatriz | H1 — Jogar nova partida: logica de sorteio, loop de palpites, dicas e registro da sessao em arquivo |
| Par 2 | Drielly Santiago + Claudemir Araujo | H2 — Analisar historico: leitura com `fgets`, reconstrucao de sessoes via recursao, estatisticas agregadas e sugestoes de estrategia |
| Par 3 | Ana Beatriz + Claudemir Araujo | H3 e H4 — Entrada invalida: validacao de intervalo, limpeza de buffer para entradas nao-numericas, EOF handling; Nivel de dificuldade: Facil/Medio/Dificil com intervalos e limite de tentativas no modo Dificil |

A experiencia permitiu identificar em tempo real inconsistencias na validacao de entrada (issue #7) e no comportamento do ranking com multiplas sessoes (issue #6), ambos registrados no tracker.

---

## Funcionalidade Prevista — Loja de Premios

Modulo planejado para uma proxima entrega: troca das recompensas obtidas ao vencer partidas por premios em uma loja. Ainda **nao implementado** no estado atual do projeto.

---

Projeto desenvolvido para a disciplina de Programacao Imperativa e Funcional — PIF 2026.1
