#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estruturas básicas para os dados
typedef struct {
    int codigo;
    char nome[100];
    char fone[20];
    char endereco[200];
    char data_nasc[11];
} Pessoa;

typedef struct {
    int codigo;
    char descricao[100];
} TipoPet;

typedef struct {
    int codigo;
    int codigo_pes;
    char nome[100];
    int codigo_tipo;
} Pet;

// Estrutura da fila de comandos
typedef struct NoComando {
    char comando[500];
    struct NoComando *prox;
} NoComando;

typedef struct {
    NoComando *inicio;
    NoComando *fim;
} Fila;

// Estrutura da árvore para ordenação
typedef struct NoArvore {
    void *dados;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} Arvore;

#endif
