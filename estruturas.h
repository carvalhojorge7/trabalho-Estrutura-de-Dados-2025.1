#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estruturas básicas para os dados
typedef struct {
    int codigo;           // obrigatório e único
    char nome[100];       // obrigatório
    char fone[20];
    char endereco[200];
    char data_nasc[11];  // obrigatório, formato dd/mm/yyyy
} Pessoa;

typedef struct {
    int codigo;          // obrigatório e único
    char nome[100];      // obrigatório
} TipoPet;

typedef struct {
    int codigo;          // obrigatório e único
    int codigo_pes;      // obrigatório, referencia Pessoa
    char nome[100];      // obrigatório
    int codigo_tipo;     // obrigatório, referencia TipoPet
} Pet;

// Estrutura da fila de comandos
typedef struct NoComando {
    char descricao[500];  // comando SQL
    char tipo;            // P: pessoa, T: tipo_pet, E: pet
    struct NoComando *prox;
} NoComando;

typedef struct {
    NoComando *inicio;
    NoComando *fim;
    int tamanho;
} Fila;

// Estrutura da árvore para ordenação
typedef struct NoArvore {
    void *dados;         // ponteiro genérico para os dados
    char tipo;          // P: pessoa, T: tipo_pet, E: pet
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} Arvore;

#endif
