#ifndef FILA_H
#define FILA_H

#include "estruturas.h"

// Funções básicas da fila
Fila* criar_fila();
void inserir_comando(Fila *f, const char *descricao, char tipo);
NoComando* remover_comando(Fila *f);
int fila_vazia(Fila *f);
void liberar_fila(Fila *f);

#endif
