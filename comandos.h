#ifndef COMANDOS_H
#define COMANDOS_H

#include "estruturas.h"
#include "fila.h"

// Funções para processar comandos
int processar_comando(const char *comando, Fila *fila_pessoa, Fila *fila_pet, Fila *fila_tipo);
int validar_comando(const char *comando);
char identificar_tipo_comando(const char *comando);

// Funções para executar comandos
int executar_insert(const char *comando, char tipo);
int executar_select(const char *comando, char tipo, Arvore *arvore);
int executar_delete(const char *comando, char tipo);
int executar_update(const char *comando, char tipo);

#endif
