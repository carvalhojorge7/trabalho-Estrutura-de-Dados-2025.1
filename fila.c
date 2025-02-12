#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

Fila* criar_fila() {
    Fila *f = malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void inserir_comando(Fila *f, const char *comando) {
    NoComando *no = malloc(sizeof(NoComando));
    strcpy(no->comando, comando);
    no->prox = NULL;
    
    if (f->fim) {
        f->fim->prox = no;
        f->fim = no;
    } else {
        f->inicio = f->fim = no;
    }
}

NoComando* remover_comando(Fila *f) {
    if (!f->inicio) return NULL;
    
    NoComando *no = f->inicio;
    f->inicio = no->prox;
    
    if (!f->inicio) f->fim = NULL;
    
    no->prox = NULL;
    return no;
}

void liberar_fila(Fila *f) {
    NoComando *atual = f->inicio;
    while (atual) {
        NoComando *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}
