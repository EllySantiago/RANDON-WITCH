#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "tipos.h"

int soma_recursiva(Sessao sessoes[], int n);
int minimo_recursivo(Sessao sessoes[], int n);
int maximo_recursivo(Sessao sessoes[], int n);
double soma_quad(Sessao sessoes[], int n, double media);
void analisar_historico();

#endif
