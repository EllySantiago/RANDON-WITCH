# Guia de Contribuição — RANDON-WITCH

Obrigado por contribuir com o projeto! Siga as instruções abaixo para configurar o ambiente e enviar suas alterações.

---

## Pré-requisitos

| Ferramenta | Versão mínima | Verificação |
|------------|---------------|-------------|
| GCC        | 11.x          | `gcc --version` |
| Make       | 4.x           | `make --version` |
| Git        | 2.x           | `git --version` |

O projeto usa apenas a biblioteca padrão C11 e `libm`. Nenhuma dependência externa precisa ser instalada.

---

## Configuração do ambiente local

```bash
# 1. Clone o repositório
git clone https://github.com/EllySantiago/RANDON-WITCH.git
cd RANDON-WITCH

# 2. Compile o projeto
make

# 3. Execute
make run
```

O executável gerado é `jogo`. Os arquivos `historico.txt` e `ranking.txt` são criados automaticamente na primeira execução.

### Limpeza

```bash
make clean   # remove o executável compilado
```

---

## Estrutura do projeto

```
RANDON-WITCH/
├── main.c              # Ponto de entrada e menu principal
├── jogo.c / .h         # Lógica de partida e seleção de dificuldade
├── historico.c / .h    # Gravação e leitura do histórico em .txt
├── estatisticas.c / .h # Estatísticas e sugestões (com recursão)
├── ranking.c / .h      # Registro e exibição do ranking
├── utils.c / .h        # Leitura validada de entrada e limpeza de buffer
├── tipos.h             # Structs e enums compartilhados
├── Makefile            # Compilação (C11, -Wall, -lm)
└── docs/               # Imagens do sprint board e issue tracker
```

---

## Como contribuir

### 1. Crie uma branch a partir de `main`

```bash
git checkout main
git pull origin main
git checkout -b feat/nome-da-funcionalidade
```

Convenção de nomes: `feat/`, `fix/`, `docs/` seguido de uma descrição curta em kebab-case.

### 2. Faça suas alterações

- Siga o estilo já adotado no projeto: funções em snake_case, comentários em português, arquivos separados por módulo (`.c` + `.h`).
- Adicione ou atualize comentários nas funções alteradas.
- Não inclua binários compilados (`jogo`, `*.o`) no commit — o `.gitignore` já os exclui.

### 3. Compile e teste antes de fazer push

```bash
make clean && make
make run
```

Verifique manualmente os cenários principais:
- Jogar uma partida completa (Fácil, Médio e Difícil)
- Analisar histórico com e sem filtro por jogador
- Inserir entradas inválidas (texto, número fora do intervalo)
- Verificar ranking após múltiplas partidas

### 4. Abra um Pull Request

- Título em português, descrevendo o que foi feito.
- Descreva as funcionalidades implementadas, os testes realizados e qualquer issue resolvida.
- Referencie as issues relacionadas com `Closes #N` na descrição.

---

## Registro de issues e bugs

Use a aba **Issues** do repositório GitHub para reportar bugs ou sugerir melhorias. Ao abrir uma issue:

1. Descreva o comportamento observado e o esperado.
2. Inclua os passos para reproduzir o problema.
3. Informe o sistema operacional e a versão do GCC utilizada.

---

## Dúvidas

Entre em contato com qualquer membro da equipe listado no `README.md`.
