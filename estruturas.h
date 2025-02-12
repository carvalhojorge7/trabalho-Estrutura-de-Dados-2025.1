#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_COMANDO 500

// Estrutura para armazenar um registro do arquivo binário
typedef struct {
    char *dados;  // Dados do registro
    int tamanho;  // Tamanho dos dados
} Registro;

// Estrutura para a fila de comandos
typedef struct NoComando {
    char comando[MAX_COMANDO];
    struct NoComando *prox;
} NoComando;

typedef struct {
    NoComando *inicio;
    NoComando *fim;
} Fila;

// Funções para manipulação da fila
Fila* criar_fila();
void inserir_comando(Fila *f, const char *comando);
NoComando* remover_comando(Fila *f);
void liberar_fila(Fila *f);

// Funções para processar comandos
void processar_comandos(Fila *f);

#endif
