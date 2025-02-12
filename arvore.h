#ifndef ARVORE_H
#define ARVORE_H

#include "estruturas.h"

// Funções básicas da árvore
Arvore* criar_arvore();
NoArvore* inserir(Arvore *a, void *dados, char tipo, int (*compara)(void*, void*));
void percorrer_em_ordem(NoArvore *raiz, void (*visita)(void*));
void liberar_arvore(Arvore *a);

#endif
