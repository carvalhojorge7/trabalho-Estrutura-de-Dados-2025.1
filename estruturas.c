#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// Funções para manipulação de filas
Fila* criar_fila() {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void inserir_comando(Fila *f, const char *comando) {
    NoComando *no = (NoComando*)malloc(sizeof(NoComando));
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
    NoComando *no;
    while ((no = remover_comando(f)) != NULL) {
        free(no);
    }
    free(f);
}

// Função para validar comandos
int validar_comando(const char *comando) {
    // Ignora comentários e linhas vazias
    if (comando[0] == '#' || comando[0] == '\0') return 0;
    
    // Verifica se é um comando SQL válido
    if (strncasecmp(comando, "insert", 6) == 0 ||
        strncasecmp(comando, "select", 6) == 0 ||
        strncasecmp(comando, "update", 6) == 0 ||
        strncasecmp(comando, "delete", 6) == 0) {
        
        // Verifica se contém as tabelas válidas
        if (strstr(comando, "pessoas") ||
            strstr(comando, "pet") ||
            strstr(comando, "tipo_pet")) {
            return 1;
        }
    }
    
    return 0;
}

// Função para separar comandos em filas específicas
void separar_comandos(Fila *comandos, Fila *pessoas, Fila *pets, Fila *tipos) {
    NoComando *no;
    while ((no = remover_comando(comandos)) != NULL) {
        if (!validar_comando(no->comando)) {
            free(no);
            continue;
        }
        
        // Determina a qual fila pertence
        if (strstr(no->comando, "pessoas")) {
            inserir_comando(pessoas, no->comando);
        }
        else if (strstr(no->comando, "pet") && !strstr(no->comando, "tipo_pet")) {
            inserir_comando(pets, no->comando);
        }
        else if (strstr(no->comando, "tipo_pet")) {
            inserir_comando(tipos, no->comando);
        }
        
        free(no);
    }
}

// Funções para manipulação de listas
Pessoa* criar_lista_pessoas() {
    return NULL;
}

TipoPet* criar_lista_tipos() {
    return NULL;
}

Pet* criar_lista_pets() {
    return NULL;
}

// Funções para carregar dados dos arquivos
void carregar_pessoas(Pessoa **lista) {
    FILE *f = fopen("pessoas.bin", "rb");
    if (!f) return;
    
    Pessoa pessoa;
    while (fread(&pessoa, sizeof(Pessoa), 1, f) == 1) {
        Pessoa *nova = (Pessoa*)malloc(sizeof(Pessoa));
        *nova = pessoa;
        nova->prox = *lista;
        nova->ant = NULL;
        if (*lista) (*lista)->ant = nova;
        *lista = nova;
    }
    
    fclose(f);
}

void carregar_tipos(TipoPet **lista) {
    FILE *f = fopen("tipo_pet.bin", "rb");
    if (!f) return;
    
    TipoPet tipo;
    while (fread(&tipo, sizeof(TipoPet), 1, f) == 1) {
        TipoPet *novo = (TipoPet*)malloc(sizeof(TipoPet));
        *novo = tipo;
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
    }
    
    fclose(f);
}

void carregar_pets(Pet **lista) {
    FILE *f = fopen("pet.bin", "rb");
    if (!f) return;
    
    Pet pet;
    while (fread(&pet, sizeof(Pet), 1, f) == 1) {
        Pet *novo = (Pet*)malloc(sizeof(Pet));
        *novo = pet;
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
    }
    
    fclose(f);
}

// Funções para salvar dados nos arquivos
void salvar_pessoas(Pessoa *lista) {
    FILE *f = fopen("pessoas.bin", "wb");
    if (!f) return;
    
    Pessoa *p = lista;
    while (p) {
        fwrite(p, sizeof(Pessoa), 1, f);
        p = p->prox;
    }
    
    fclose(f);
}

void salvar_tipos(TipoPet *lista) {
    FILE *f = fopen("tipo_pet.bin", "wb");
    if (!f) return;
    
    TipoPet *t = lista;
    while (t) {
        fwrite(t, sizeof(TipoPet), 1, f);
        t = t->prox;
    }
    
    fclose(f);
}

void salvar_pets(Pet *lista) {
    FILE *f = fopen("pet.bin", "wb");
    if (!f) return;
    
    Pet *p = lista;
    while (p) {
        fwrite(p, sizeof(Pet), 1, f);
        p = p->prox;
    }
    
    fclose(f);
}

// Funções para árvore binária
NoArvore* criar_arvore() {
    return NULL;
}

void liberar_arvore(NoArvore *raiz, int liberar_dados) {
    if (!raiz) return;
    
    // Libera recursivamente as subárvores
    liberar_arvore(raiz->esq, liberar_dados);
    liberar_arvore(raiz->dir, liberar_dados);
    
    // Se liberar_dados for 1, libera também os dados (só usado quando os dados são alocados dinamicamente)
    if (liberar_dados) {
        free(raiz->dados);
    }
    
    // Libera o nó
    free(raiz);
}

int comparar_nomes(void *a, void *b, int tipo) {
    char *nome_a, *nome_b;
    
    switch (tipo) {
        case 1: // Pessoa
            nome_a = ((Pessoa*)a)->nome;
            nome_b = ((Pessoa*)b)->nome;
            break;
        case 2: // Pet
            nome_a = ((Pet*)a)->nome;
            nome_b = ((Pet*)b)->nome;
            break;
        case 3: // TipoPet
            nome_a = ((TipoPet*)a)->descricao;
            nome_b = ((TipoPet*)b)->descricao;
            break;
        default:
            return 0;
    }
    
    return strcmp(nome_a, nome_b);
}

void inserir_na_arvore(NoArvore **raiz, void *dados, int tipo) {
    if (!*raiz) {
        *raiz = (NoArvore*)malloc(sizeof(NoArvore));
        (*raiz)->dados = dados;
        (*raiz)->esq = (*raiz)->dir = NULL;
        return;
    }
    
    int cmp = comparar_nomes(dados, (*raiz)->dados, tipo);
    if (cmp < 0)
        inserir_na_arvore(&(*raiz)->esq, dados, tipo);
    else
        inserir_na_arvore(&(*raiz)->dir, dados, tipo);
}

void exibir_dados(void *dados, int tipo) {
    switch (tipo) {
        case 1: { // Pessoa
            Pessoa *p = (Pessoa*)dados;
            printf("ID: %d, Nome: %s, CPF: %s, Idade: %d\n",
                   p->id, p->nome, p->cpf, p->idade);
            break;
        }
        case 2: { // Pet
            Pet *p = (Pet*)dados;
            printf("ID: %d, Nome: %s, ID_Tipo: %d, ID_Pessoa: %d\n",
                   p->id, p->nome, p->id_tipo, p->id_pessoa);
            break;
        }
        case 3: { // TipoPet
            TipoPet *t = (TipoPet*)dados;
            printf("ID: %d, Descrição: %s\n",
                   t->id, t->descricao);
            break;
        }
    }
}

void exibir_arvore_ordenada(NoArvore *raiz, int tipo) {
    if (!raiz) return;
    
    exibir_arvore_ordenada(raiz->esq, tipo);
    exibir_dados(raiz->dados, tipo);
    exibir_arvore_ordenada(raiz->dir, tipo);
}

struct Pessoa {
    int id;
    char nome[100];
    char cpf[20];
    int idade;
    struct Pessoa* prox;
    struct Pessoa* ant;
};

struct Tipo_Pet {
    int id;
    char descricao[100];
    struct Tipo_Pet* prox;
    struct Tipo_Pet* ant;
};

struct Pet {
    int id;
    int id_pessoa;
    int id_tipo;
    char nome[100];
    struct Pet* prox;
    struct Pet* ant;
};

struct Comando {
    char descricao[255];
    struct Comando* prox;
}; // FILA

struct Ordem {
    char campo[255];
    struct Ordem *direita;
    struct Ordem *esquerda;
}; // ARVORE

struct NoComando {
    char comando[255];
    struct NoComando* prox;
};

struct Fila {
    struct NoComando* inicio;
    struct NoComando* fim;
};

struct NoArvore {
    void* dados;
    struct NoArvore* esq;
    struct NoArvore* dir;
};