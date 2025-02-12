#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

Arvore* criar_arvore() {
    Arvore *a = (Arvore*) malloc(sizeof(Arvore));
    a->raiz = NULL;
    return a;
}

NoArvore* criar_no(void *dados, char tipo) {
    NoArvore *no = (NoArvore*) malloc(sizeof(NoArvore));
    no->dados = dados;
    no->tipo = tipo;
    no->esq = no->dir = NULL;
    return no;
}

NoArvore* inserir_no(NoArvore *raiz, void *dados, char tipo, int (*compara)(void*, void*)) {
    if (raiz == NULL) {
        return criar_no(dados, tipo);
    }
    
    if (compara(dados, raiz->dados) < 0) {
        raiz->esq = inserir_no(raiz->esq, dados, tipo, compara);
    } else {
        raiz->dir = inserir_no(raiz->dir, dados, tipo, compara);
    }
    
    return raiz;
}

NoArvore* inserir(Arvore *a, void *dados, char tipo, int (*compara)(void*, void*)) {
    a->raiz = inserir_no(a->raiz, dados, tipo, compara);
    return a->raiz;
}

void percorrer_em_ordem_rec(NoArvore *raiz, void (*visita)(void*)) {
    if (raiz != NULL) {
        percorrer_em_ordem_rec(raiz->esq, visita);
        visita(raiz->dados);
        percorrer_em_ordem_rec(raiz->dir, visita);
    }
}

void percorrer_em_ordem(NoArvore *raiz, void (*visita)(void*)) {
    percorrer_em_ordem_rec(raiz, visita);
}

void liberar_no(NoArvore *no) {
    if (no != NULL) {
        liberar_no(no->esq);
        liberar_no(no->dir);
        free(no);
    }
}

void liberar_arvore(Arvore *a) {
    liberar_no(a->raiz);
    free(a);
}
