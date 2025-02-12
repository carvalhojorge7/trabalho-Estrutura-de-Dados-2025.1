#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estruturas para os dados
typedef struct Pessoa {
    int id;
    char nome[100];
    char cpf[15];
    int idade;
    struct Pessoa *prox;
    struct Pessoa *ant;
} Pessoa;

typedef struct TipoPet {
    int id;
    char descricao[100];
    struct TipoPet *prox;
    struct TipoPet *ant;
} TipoPet;

typedef struct Pet {
    int id;
    char nome[100];
    int id_tipo;
    int id_pessoa;
    struct Pet *prox;
    struct Pet *ant;
} Pet;

// Estrutura para os comandos
typedef struct NoComando {
    char comando[500];
    struct NoComando *prox;
} NoComando;

// Estrutura para as filas
typedef struct {
    NoComando *inicio;
    NoComando *fim;
} Fila;

// Estrutura para árvore binária (para SELECT ORDER BY)
typedef struct NoArvore {
    void *dados;  // Ponteiro genérico para Pessoa, Pet ou TipoPet
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

// Funções para manipulação de filas
Fila* criar_fila();
void inserir_comando(Fila *f, const char *comando);
NoComando* remover_comando(Fila *f);
void liberar_fila(Fila *f);

// Funções para validação de comandos
int validar_comando(const char *comando);
void separar_comandos(Fila *comandos, Fila *pessoas, Fila *pets, Fila *tipos);

// Funções para manipulação de listas
Pessoa* criar_lista_pessoas();
TipoPet* criar_lista_tipos();
Pet* criar_lista_pets();

// Funções para carregar dados dos arquivos
void carregar_pessoas(Pessoa **lista);
void carregar_tipos(TipoPet **lista);
void carregar_pets(Pet **lista);

// Funções para salvar dados nos arquivos
void salvar_pessoas(Pessoa *lista);
void salvar_tipos(TipoPet *lista);
void salvar_pets(Pet *lista);

// Funções para árvore binária
NoArvore* criar_arvore();
void inserir_na_arvore(NoArvore **raiz, void *dados, int tipo);
void exibir_arvore_ordenada(NoArvore *raiz, int tipo);

#endif
