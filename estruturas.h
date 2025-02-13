#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estruturas para os dados
typedef struct Pessoa {
    int codigo;
    char nome[100];
    char fone[20];
    char endereco[200];
    char data_nasc[11];
    struct Pessoa *prox;
    struct Pessoa *ant;
} Pessoa;

typedef struct TipoPet {
    int codigo;
    char nome[100];
    struct TipoPet *prox;
    struct TipoPet *ant;
} TipoPet;

typedef struct Pet {
    int codigo;
    char nome[100];
    int codigo_tipo;
    int codigo_pes;
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

// Funções de manipulação da árvore
NoArvore* inserir_no(NoArvore *raiz, void *dados, int tipo);
void inserir_pessoa(NoArvore **raiz, Pessoa *p);
void inserir_pet(NoArvore **raiz, Pet *p);
void inserir_tipo_pet(NoArvore **raiz, TipoPet *t);
void exibir_arvore_ordenada(NoArvore *raiz, int tipo);
void exibir_dados(void *dados, int tipo);

// Remove um nó da árvore
NoArvore* remover_no(NoArvore *raiz, int codigo, int tipo);

// Funções para árvore binária
NoArvore* criar_arvore();
void liberar_arvore(NoArvore *raiz, int liberar_dados);

// Funções para converter árvore em lista
TipoPet* arvore_para_lista_tipos(NoArvore *raiz);
Pet* arvore_para_lista_pets(NoArvore *raiz);
Pessoa* arvore_para_lista_pessoas(NoArvore *raiz);

#endif
