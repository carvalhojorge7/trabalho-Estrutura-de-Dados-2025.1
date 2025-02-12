#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estruturas de dados
typedef struct {
    int codigo;
    char nome[100];
    char fone[20];
    char endereco[200];
    char data_nasc[11];
} Pessoa;

typedef struct {
    int codigo;
    char nome[100];
} TipoPet;

typedef struct {
    int codigo;
    int codigo_pes;
    char nome[100];
    int codigo_tipo;
} Pet;

// Estrutura para comandos SQL
typedef struct NoComando {
    char comando[500];
    struct NoComando *prox;
} NoComando;

typedef struct {
    NoComando *inicio;
    NoComando *fim;
} Fila;

// Funções para manipulação de arquivos
void salvar_pessoa(Pessoa p);
void salvar_tipo_pet(TipoPet t);
void salvar_pet(Pet p);
Pessoa* buscar_pessoa(int codigo);
TipoPet* buscar_tipo_pet(int codigo);
Pet* buscar_pet(int codigo);

// Funções da fila
Fila* criar_fila();
void inserir_comando(Fila *f, char *comando);
NoComando* remover_comando(Fila *f);
void processar_comandos(Fila *f);

#endif
