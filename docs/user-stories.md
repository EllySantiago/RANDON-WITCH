# User Stories — RANDON-WITCH

> Formato: Como [papel], quero [ação], para [benefício].  
> Critérios de aceitação definidos no padrão 3Cs (Cartão, Conversa, Confirmação).

---

## H1 — Jogar nova partida

**Como** jogador, **quero** iniciar uma partida e receber dicas a cada palpite, **para** descobrir o número secreto.

**Critérios de aceitação:**
- O sistema sorteia um número no intervalo da dificuldade escolhida
- A cada palpite válido, exibe "Muito baixo", "Muito alto" ou "Acertou"
- Ao acertar, exibe o total de tentativas e salva a sessão no histórico

**Status:** ✅ Concluído (Sprint 01)

---

## H2 — Analisar histórico de partidas

**Como** jogador, **quero** visualizar estatísticas das minhas partidas anteriores, **para** entender meu desempenho e melhorar minha estratégia.

**Critérios de aceitação:**
- Exibe relatório individual de cada partida (data, jogador, alvo, sequência)
- Calcula e exibe: total de sessões, média, melhor, pior, desvio padrão e viés
- Exibe sugestões textuais de estratégia baseadas no histórico
- Permite filtrar partidas por nome de jogador

**Status:** ✅ Concluído (Sprint 01)

---

## H3 — Entrada inválida no palpite

**Como** jogador, **quero** que o sistema rejeite entradas inválidas sem travar, **para** continuar jogando normalmente após errar a digitação.

**Critérios de aceitação:**
- Entradas não numéricas exibem mensagem de erro e limpam o buffer
- Valores fora do intervalo exibem mensagem e não contabilizam tentativa
- EOF (Ctrl+D) encerra o programa graciosamente

**Status:** ✅ Concluído (Sprint 01)

---

## H4 — Nível de dificuldade

**Como** jogador, **quero** escolher a dificuldade antes de jogar, **para** adaptar o desafio ao meu nível.

**Critérios de aceitação:**
- Fácil: intervalo 1–50, sem limite de tentativas
- Médio: intervalo 1–100, sem limite de tentativas
- Difícil: intervalo 1–200, limite de 10 tentativas com contador visível
- No modo Difícil, ao esgotar tentativas, revela o número correto

**Status:** ✅ Concluído (Sprint 01)

---

## H5 — Sistema de moedas de prêmio

**Como** jogador, **quero** ganhar moedas ao acertar o número, **para** acumular saldo e resgatar itens na loja.

**Critérios de aceitação:**
- Ao acertar, o jogador recebe moedas proporcionais à eficiência (menos tentativas = mais moedas)
- O saldo é salvo em arquivo e persiste entre sessões
- O saldo atual é exibido ao acessar a loja

**Status:** ✅ Concluído (Sprint 02)

---

## H6 — Loja de prêmios

**Como** jogador, **quero** acessar uma loja para trocar moedas por itens, **para** obter vantagens nas partidas.

**Critérios de aceitação:**
- Menu de loja exibe itens com nome, descrição e custo em moedas
- Compra só é permitida se o saldo for suficiente
- Saldo é debitado e atualizado após a compra
- Itens disponíveis: Dica de Intervalo (30), Palpite Bônus (50), Revelar Dezena (80)

**Status:** ✅ Concluído (Sprint 02)

---

## H7 — Ranking de jogadores

**Como** jogador, **quero** ver um ranking com os melhores jogadores, **para** comparar meu desempenho com outros.

**Critérios de aceitação:**
- Exibe lista ordenada por número de acertos (decrescente)
- Em caso de empate, ordena por menor total de tentativas
- Registra nome, acertos, total de tentativas e data do último acerto
- Salvo em arquivo e atualizado a cada vitória

**Status:** ✅ Concluído (Sprint 01/02)

---

## H8 — Relatório individual por sessão

**Como** jogador, **quero** ver o detalhamento de cada partida no histórico, **para** analisar minha sequência de palpites.

**Critérios de aceitação:**
- Exibe data, jogador, número alvo, total de tentativas e sequência completa de palpites
- Exibe avaliação textual do desempenho (excelente, mediano, pode melhorar)
- Permite ver todas as partidas ou filtrar por jogador

**Status:** ✅ Concluído (Sprint 01)

---

## H9 — Sugestões de estratégia baseadas no histórico

**Como** jogador, **quero** receber sugestões automáticas baseadas no meu histórico, **para** melhorar minha técnica de busca.

**Critérios de aceitação:**
- Se a média de tentativas for alta, sugere começar pelo meio do intervalo
- Se o viés for maior que 60% para um lado, alerta sobre o desequilíbrio
- Se o desvio padrão for alto, alerta sobre inconsistência de estratégia

**Status:** ✅ Concluído (Sprint 01)

---

## H10 — Persistência e criação automática de arquivos

**Como** sistema, **quero** criar os arquivos de histórico e ranking automaticamente, **para** que o jogador não precise configurar nada manualmente.

**Critérios de aceitação:**
- `historico.txt` é criado automaticamente na primeira partida
- `ranking.txt` é criado automaticamente na primeira vitória
- `moedas.txt` é criado automaticamente no primeiro acesso à loja
- Ausência de arquivos não causa travamento ou erro fatal

**Status:** ✅ Concluído (Sprint 01/02)
