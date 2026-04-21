# RANDON-WITCH

alunos: Drielly Santiago dos Santos

links uteis:
docs com diagramas e historias de usuario:
https://docs.google.com/document/d/1Onn0zreH8-ji0cUPtdZGIiET4_C9ct-UDlEsmH9ZOP0/edit?usp=sharing
click up/ trello



DME.md

Copiar
        # Jogo de Adivinhacao — PIF 2026.1

> Projeto Integrador da disciplina de **Programacao Imperativa e Funcional (PIF)**  
> Curso de Analise e Desenvolvimento de Sistemas — 2026.1

---

## Sobre o Projeto

Jogo de adivinhacao desenvolvido em linguagem C onde o sistema sorteia um numero entre 1 e 100, o jogador tenta descobri-lo atraves de palpites e recebe dicas a cada tentativa. O jogo conta com personagens iniciais, sistema de apostas com moedas, loja de premios e ranking de jogadores.

---

## Funcionalidades Principais

### Modos de Jogo

-   **Jogar nova partida** — sorteia numero, recebe palpites e retorna dicas
-   **Analisar historico** — exibe estatisticas e sugestoes de estrategia com base nas partidas salvas

### Diferenciais do Projeto

-   **3 personagens iniciais** (estilo escolha inicial):
    -   **Sorte** — aplica +5 ou -5 no resultado automaticamente se isso garantir a vitoria
    -   **Rico** — inicia com 160 moedas (o padrao e 100)
    -   **Random** — aplica penalidade oculta de -2; vence e ganha premio so quem souber burla-lo
-   **Sistema de moedas** — apostas com moedas comuns que se convertem em moedas de premio ao vencer
-   **Loja de premios** — troca de moedas de premio por recompensas
-   **Ranking** — placar com nome do jogador e total de acertos, salvo em arquivo

---

## Requisitos Funcionais (RF)

| Cod. | Descricao |
| --- | --- |
| RF01 | Geracao do numero alvo com `rand()` e `srand()` a cada sessao |
| RF02 | Loop de palpites com validacao de intervalo (1–100) e dicas: "Muito baixo", "Muito alto", "Acertou" |
| RF03 | Registro da sessao em arquivo texto: timestamp, alvo, tentativas, palpites abaixo/acima e lista CSV |
| RF04 | Leitura do historico com `fgets()` e reconstrucao das sessoes para analise |
| RF05 | Calculo de estatisticas: total de sessoes, media, melhor/pior sessao, desvio padrao e vies baixo/alto |
| RF06 | Uso de recursao em soma, minimo, maximo e soma dos quadrados das diferencas |
| RF07 | Sugestoes textuais de estrategia baseadas no historico (vies, busca linear, busca binaria) |

---

## Requisitos Nao Funcionais

-   Multiplataforma: Windows, Linux e macOS
-   Compativel com compiladores C11
-   Sem dependencias externas
-   Persistencia em arquivo texto simples
-   Codigo modular, legivel e comentado de forma enxuta

---

## Estrutura do Projeto

```
jogo-adivinhacao/
├── src/
│   ├── main.c           # Menu principal e ponto de entrada
│   ├── jogo.c / .h      # Logica da partida e personagens
│   ├── historico.c / .h # Escrita e leitura do arquivo de sessoes
│   ├── analise.c / .h   # Estatisticas e sugestoes (com recursao)
│   ├── moedas.c / .h    # Sistema de apostas e moedas de premio
│   ├── loja.c / .h      # Loja de premios
│   └── ranking.c / .h   # Registro e exibicao do ranking
├── historico.txt        # Arquivo de sessoes (gerado em tempo de execucao)
├── ranking.txt          # Arquivo de ranking (gerado em tempo de execucao)
└── README.md

```

---

## Formato do Arquivo de Historico

Cada sessao e gravada em uma unica linha no formato:

```
timestamp;alvo;tentativas;baixos;altos;palpites_csv

```

**Exemplo:**

```
2026-03-31 16:35:10;42;7;4;2;10,80,50,40,45,43,42

```

| Campo | Descricao |
| --- | --- |
| timestamp | Data e hora da partida |
| alvo | Numero sorteado |
| tentativas | Total de palpites validos |
| baixos | Quantidade de palpites abaixo do alvo |
| altos | Quantidade de palpites acima do alvo |
| palpites\_csv | Lista de todos os palpites separados por virgula |

---

## Como Compilar e Executar

### Pre-requisitos

-   GCC com suporte a C11
-   Biblioteca `math.h` (flag `-lm`)

### Compilacao

```bash
gcc -std=c11 -Wall -o jogo src/*.c -lm

```

### Execucao

```bash
./jogo

```

### Menu Principal

```
=== JOGO DE ADIVINHACAO ===
1. Jogar nova partida
2. Analisar historico
3. Ver ranking
4. Loja de premios
5. Sair

```

---

## Logica de Recursao

As seguintes funcoes utilizam recursao (modulo `analise.c`):

-   `soma_tentativas()` — soma total de tentativas entre sessoes
-   `minimo_tentativas()` — melhor sessao (menor numero de tentativas)
-   `maximo_tentativas()` — pior sessao (maior numero de tentativas)
-   `soma_quadrados_diferencas()` — calculo da variancia para desvio padrao
-   `contar_monotonicos()` — detecta sequencias monotônicas nos palpites

---

## Formulas Analiticas

**Media de tentativas:**

```
media = soma(tentativas) / total_sessoes

```

**Desvio padrao populacional:**

```
sigma = sqrt( soma((xi - media)^2) / n )

```

**Vies por sessao:**

```
vies_baixo = palpites_abaixo / total_tentativas
vies_alto  = palpites_acima  / total_tentativas

```

---

## Heuristicas de Estrategia

| Condicao Detectada | Sugestao Exibida |
| --- | --- |
| Primeiros palpites muito distantes do alvo | "Tendencia a comecar muito longe do alvo" |
| Muitas sequencias monotônicas | "Voce usa busca linear — tente busca binaria" |
| Media alta com desvio baixo | "Estrategia repetitiva pouco eficiente" |
| Media proxima de log2(100) ou menos | "Boa aproximacao de busca binaria!" |

---

## Personagens

| Personagem | Efeito |
| --- | --- |
| **Sorte** | Aplica +5 ou -5 automaticamente se garantir a vitoria naquela rodada |
| **Rico** | Inicia com 160 moedas comuns (padrao: 100) |
| **Random** | Aplica sempre -2 no resultado; premio da loja liberado ao quem souber compensar |

---

## Sistema de Moedas

-   **Moedas comuns** — usadas para apostar antes de cada partida (saldo inicial: 100 ou 160 com Rico)
-   **Moedas de premio** — obtidas ao vencer apostas; usadas exclusivamente na loja
-   Aposta perdida: debita moedas comuns sem gerar moedas de premio
-   Aposta vencida: converte moedas apostadas em moedas de premio

---

## Tratamento de Erros

| Situacao | Comportamento |
| --- | --- |
| Arquivo historico inexistente | Exibe "Sem dados registrados" e retorna ao menu |
| Arquivo nao pode ser aberto para escrita | Partida continua normalmente; erro exibido no terminal |
| Entrada nao numerica | Buffer limpo; solicita novo valor |
| Valor fora do intervalo 1–100 | Mensagem de erro; tentativa nao e contabilizada |
| Aposta acima do saldo | Operacao bloqueada com mensagem de saldo insuficiente |
| Ranking sem partidas registradas | Mensagem amigavel; sem travamento |

---

## Cronograma de Entregas

| Semana | Data | Entrega |
| --- | --- | --- |
| 1 | 21/04/2026 | Estrutura basica e geracao RNG |
| 2 | 28/04/2026 | Loop de jogo, persistencia e carregamento de historico |
| 3 | 05/05/2026 | **Capstone 1** — Jogo funcional + historico basico |
| 4 | 12/05/2026 | Recursao: soma, minimo e maximo |
| 5 | 19/05/2026 | Recursao: desvio padrao e soma dos quadrados |
| 6 | 26/05/2026 | **Capstone 2** — Analise completa com sugestoes |
| 7 | 02/06/2026 | Integracao completa do menu e testes |
| 8 | 09/06/2026 | **Capstone 3** — Projeto polido e documentado |
| 9 | 16/06/2026 | **MVP Final** — Versao de producao (entrega final) |

---

## Entrega

-   Repositorio no **GitHub** com commits de todos os integrantes
-   Professor adicionado como colaborador: `mr-costaalencar`
-   Demonstracao funcional em sala de aula na entrega final

---

## Dicas de Desenvolvimento

-   Compilar e testar apos cada modulo: `gcc -std=c11 -Wall -o jogo src/*.c -lm`
-   Testar com 10+ sessoes antes de cada capstone
-   Usar recursao apenas onde for didatico (soma, min, max, quadrados) — nao no loop principal
-   Manter arquivo historico legivel e no formato `timestamp;alvo;tentativas;baixos;altos;csv`
-   Cada modulo deve ser testavel de forma isolada

---

## Extensoes Sugeridas (Opcionais)

-   Gerar 100+ sessoes para testar o modulo analitico
-   Comparar desempenho humano com busca binaria simulada
-   Adicionar modo treino com sugestao do proximo palpite
-   Implementar GUI com raylib, NCurses ou ImTui

---

_Projeto desenvolvido para a disciplina de Programacao Imperativa e Funcional — PIF 2026.1_
