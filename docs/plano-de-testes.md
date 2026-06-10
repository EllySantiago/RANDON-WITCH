# Plano de Testes — RANDON-WITCH

---

## Objetivo

Validar o comportamento do sistema em cenários funcionais e de borda, garantindo que todos os requisitos funcionais (RF01–RF07) e histórias de usuário (H1–H10) estejam implementados e funcionando corretamente.

---

## Ambiente de teste

- Sistema operacional: macOS / Linux / Windows (WSL)
- Compilador: GCC com flags `-Wall -std=c11 -lm`
- Comando de compilação: `make`
- Execução: `make run` ou `./jogo`

---

## Casos de teste

### CT01 — Fluxo completo de uma partida (H1, RF01, RF02, RF03)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | Executável compilado |
| Entrada | Nome: `Teste`, Dificuldade: Médio (2), palpites até acertar |
| Ação | Jogar partida completa até acertar |
| Resultado esperado | Exibe dicas corretas; ao acertar exibe total de tentativas; `historico.txt` é atualizado com a sessão |
| Status | ✅ Aprovado |

---

### CT02 — Entrada não numérica (H3, RF02)

| Campo | Descrição |
|-------|-----------|
| Entrada | Digitar `abc` quando solicitado o palpite |
| Resultado esperado | Mensagem de erro exibida; buffer limpo; nova solicitação sem contar tentativa |
| Status | ✅ Aprovado |

---

### CT03 — Valor fora do intervalo (H3, RF02)

| Campo | Descrição |
|-------|-----------|
| Entrada | Dificuldade Médio; digitar `150` como palpite |
| Resultado esperado | Mensagem "Valor fora do intervalo"; tentativa não contabilizada |
| Status | ✅ Aprovado |

---

### CT04 — Modo Difícil com esgotamento de tentativas (H4)

| Campo | Descrição |
|-------|-----------|
| Entrada | Dificuldade Difícil (3); errar 10 vezes consecutivas |
| Resultado esperado | Contador `[X/10]` atualizado a cada tentativa; ao esgotar, exibe "Fim de jogo" e o número correto |
| Status | ✅ Aprovado |

---

### CT05 — Análise do histórico sem filtro (H2, RF04, RF05)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | `historico.txt` com pelo menos 5 sessões |
| Ação | Menu → Analisar histórico → Ver todas as partidas |
| Resultado esperado | Exibe relatório de cada partida e estatísticas agregadas (média, melhor, pior, desvio, viés) |
| Status | ✅ Aprovado |

---

### CT06 — Análise do histórico com filtro por jogador (H2, RF04)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | `historico.txt` com sessões de múltiplos jogadores |
| Entrada | Filtrar por nome existente |
| Resultado esperado | Exibe apenas as partidas do jogador filtrado com estatísticas corretas |
| Status | ✅ Aprovado |

---

### CT07 — Análise com filtro por jogador inexistente (H2)

| Campo | Descrição |
|-------|-----------|
| Entrada | Filtrar por nome que não existe no histórico |
| Resultado esperado | Mensagem "Nenhuma partida encontrada" sem travamento |
| Status | ✅ Aprovado |

---

### CT08 — Sugestões de estratégia (H9, RF07)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | `historico.txt` com 10+ sessões com média > 10 tentativas |
| Resultado esperado | Sugestão de começar pelo meio do intervalo exibida |
| Status | ✅ Aprovado |

---

### CT09 — Ranking após múltiplas vitórias (H7, RF)

| Campo | Descrição |
|-------|-----------|
| Ação | Jogar e acertar com dois nomes diferentes; acessar ranking |
| Resultado esperado | Ranking exibe ambos os jogadores ordenados por acertos decrescentes; inclui data do último acerto |
| Status | ✅ Aprovado |

---

### CT10 — Loja: saldo insuficiente (H6)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | Jogador com 0 moedas |
| Ação | Acessar loja e tentar comprar qualquer item |
| Resultado esperado | Mensagem "Saldo insuficiente" sem débito ou travamento |
| Status | ✅ Aprovado |

---

### CT11 — Loja: compra bem-sucedida (H5, H6)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | Jogador com saldo suficiente (acertar partidas para acumular moedas) |
| Ação | Acessar loja e comprar item com saldo suficiente |
| Resultado esperado | Saldo debitado corretamente; confirmação de resgate exibida; `moedas.txt` atualizado |
| Status | ✅ Aprovado |

---

### CT12 — EOF inesperado (H3)

| Campo | Descrição |
|-------|-----------|
| Ação | Pressionar Ctrl+D durante qualquer leitura de entrada |
| Resultado esperado | Programa encerra sem mensagem de erro ou crash |
| Status | ✅ Aprovado |

---

### CT13 — Ausência de historico.txt (H10)

| Campo | Descrição |
|-------|-----------|
| Pré-condição | Remover `historico.txt` |
| Ação | Acessar "Analisar histórico" |
| Resultado esperado | Mensagem "Nenhuma sessão encontrada" sem travamento |
| Status | ✅ Aprovado |

---

### CT14 — Recursão em estatísticas (RF06)

| Campo | Descrição |
|-------|-----------|
| Verificação | Inspeção de código: funções `soma_recursiva`, `minimo_recursivo`, `maximo_recursivo`, `soma_quad` em `estatisticas.c` |
| Resultado esperado | Todas as funções usam recursão sem loops; compilam sem warnings |
| Status | ✅ Aprovado |

---

## Resultado geral

| Total de casos | Aprovados | Reprovados | Pendentes |
|----------------|-----------|------------|-----------|
| 14 | 14 | 0 | 0 |
