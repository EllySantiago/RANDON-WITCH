#ifndef LOJA_H
#define LOJA_H

int  carregar_moedas(const char *nome);
void salvar_moedas(const char *nome, int moedas);
void adicionar_moedas(const char *nome, int quantidade);
void abrir_loja(const char *nome);

int  tem_dica(const char *nome);
void usar_dica(const char *nome);

#endif
