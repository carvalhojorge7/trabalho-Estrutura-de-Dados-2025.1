#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

Fila* criar_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void inserir_comando(Fila *f, const char *descricao, char tipo) {
    NoComando *no = (NoComando*) malloc(sizeof(NoComando));
    strcpy(no->descricao, descricao);
    no->tipo = tipo;
    no->prox = NULL;
    
    if (f->fim == NULL) {
        f->inicio = f->fim = no;
    } else {
        f->fim->prox = no;
        f->fim = no;
    }
    f->tamanho++;
}

NoComando* remover_comando(Fila *f) {
    if (f->inicio == NULL) return NULL;
    
    NoComando *temp = f->inicio;
    f->inicio = f->inicio->prox;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    f->tamanho--;
    return temp;
}

int fila_vazia(Fila *f) {
    return (f->inicio == NULL);
}

void liberar_fila(Fila *f) {
    while (!fila_vazia(f)) {
        NoComando *no = remover_comando(f);
        free(no);
    }
    free(f);
}
