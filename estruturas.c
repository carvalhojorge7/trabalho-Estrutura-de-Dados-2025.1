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
            nome_a = ((TipoPet*)a)->nome;
            nome_b = ((TipoPet*)b)->nome;
            break;
        default:
            return 0;
    }
    
    return strcmp(nome_a, nome_b);
}

NoArvore* inserir_no(NoArvore *raiz, void *dados, int tipo) {
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore*)malloc(sizeof(NoArvore));
        novo->dados = dados;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    
    // Verifica se já existe um registro com o mesmo código
    int codigo_novo, codigo_atual;
    if (tipo == 1) {
        codigo_novo = ((Pessoa*)dados)->codigo;
        codigo_atual = ((Pessoa*)raiz->dados)->codigo;
    } else if (tipo == 2) {
        codigo_novo = ((Pet*)dados)->codigo;
        codigo_atual = ((Pet*)raiz->dados)->codigo;
    } else {
        codigo_novo = ((TipoPet*)dados)->codigo;
        codigo_atual = ((TipoPet*)raiz->dados)->codigo;
    }
    
    if (codigo_novo == codigo_atual) {
        return raiz;  // Não permite duplicatas
    }
    
    if (codigo_novo < codigo_atual) {
        raiz->esq = inserir_no(raiz->esq, dados, tipo);
    } else {
        raiz->dir = inserir_no(raiz->dir, dados, tipo);
    }
    
    return raiz;
}

void exibir_dados(void *dados, int tipo) {
    if (tipo == 1) {  // Pessoa
        Pessoa *p = (Pessoa*)dados;
        printf("Codigo: %d, Nome: %s, Fone: %s, Endereco: %s, Data Nasc.: %s\n",
               p->codigo, p->nome, p->fone, p->endereco, p->data_nasc);
    }
    else if (tipo == 2) {  // Pet
        Pet *p = (Pet*)dados;
        printf("Codigo: %d, Nome: %s, Codigo Tipo: %d, Codigo Pessoa: %d\n",
               p->codigo, p->nome, p->codigo_tipo, p->codigo_pes);
    }
    else if (tipo == 3) {  // TipoPet
        TipoPet *t = (TipoPet*)dados;
        printf("Codigo: %d, Nome: %s\n",
               t->codigo, t->nome);
    }
}

void exibir_arvore_ordenada(NoArvore *raiz, int tipo) {
    static int *codigos_exibidos = NULL;
    static int num_exibidos = 0;
    static int capacidade = 0;
    
    if (raiz == NULL) {
        // Limpa o array quando terminar de exibir a árvore inteira
        if (codigos_exibidos) {
            free(codigos_exibidos);
            codigos_exibidos = NULL;
            num_exibidos = 0;
            capacidade = 0;
        }
        return;
    }
    
    if (!codigos_exibidos) {
        capacidade = 100;
        codigos_exibidos = (int*)malloc(capacidade * sizeof(int));
        num_exibidos = 0;
    }
    
    exibir_arvore_ordenada(raiz->esq, tipo);
    
    // Verifica se o código já foi exibido
    int codigo;
    if (tipo == 1) {
        codigo = ((Pessoa*)raiz->dados)->codigo;
    } else if (tipo == 2) {
        codigo = ((Pet*)raiz->dados)->codigo;
    } else {
        codigo = ((TipoPet*)raiz->dados)->codigo;
    }
    
    int ja_exibido = 0;
    for (int i = 0; i < num_exibidos; i++) {
        if (codigos_exibidos[i] == codigo) {
            ja_exibido = 1;
            break;
        }
    }
    
    if (!ja_exibido) {
        exibir_dados(raiz->dados, tipo);
        if (num_exibidos < capacidade) {
            codigos_exibidos[num_exibidos++] = codigo;
        }
    }
    
    exibir_arvore_ordenada(raiz->dir, tipo);
}

// Insere uma pessoa na árvore
void inserir_pessoa(NoArvore **raiz, Pessoa *p) {
    *raiz = inserir_no(*raiz, p, 1);
}

// Insere um pet na árvore
void inserir_pet(NoArvore **raiz, Pet *p) {
    *raiz = inserir_no(*raiz, p, 2);
}

// Insere um tipo de pet na árvore
void inserir_tipo_pet(NoArvore **raiz, TipoPet *t) {
    *raiz = inserir_no(*raiz, t, 3);
}

// Funções para converter árvore em lista
TipoPet* arvore_para_lista_tipos(NoArvore *raiz) {
    if (raiz == NULL) return NULL;
    
    // Primeiro converte a subárvore esquerda
    TipoPet *lista = arvore_para_lista_tipos(raiz->esq);
    
    // Adiciona o nó atual
    TipoPet *atual = (TipoPet*)raiz->dados;
    atual->prox = NULL;
    atual->ant = NULL;
    
    // Se a lista está vazia, retorna o nó atual
    if (lista == NULL) {
        return atual;
    }
    
    // Senão, encontra o último elemento e adiciona o atual
    TipoPet *ultimo = lista;
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = atual;
    atual->ant = ultimo;
    
    // Converte a subárvore direita e a conecta
    TipoPet *direita = arvore_para_lista_tipos(raiz->dir);
    if (direita != NULL) {
        atual->prox = direita;
        direita->ant = atual;
    }
    
    return lista;
}

Pet* arvore_para_lista_pets(NoArvore *raiz) {
    if (raiz == NULL) return NULL;
    
    Pet *lista = arvore_para_lista_pets(raiz->esq);
    
    Pet *atual = (Pet*)raiz->dados;
    atual->prox = NULL;
    atual->ant = NULL;
    
    if (lista == NULL) {
        return atual;
    }
    
    Pet *ultimo = lista;
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = atual;
    atual->ant = ultimo;
    
    Pet *direita = arvore_para_lista_pets(raiz->dir);
    if (direita != NULL) {
        atual->prox = direita;
        direita->ant = atual;
    }
    
    return lista;
}

Pessoa* arvore_para_lista_pessoas(NoArvore *raiz) {
    if (raiz == NULL) return NULL;
    
    Pessoa *lista = arvore_para_lista_pessoas(raiz->esq);
    
    Pessoa *atual = (Pessoa*)raiz->dados;
    atual->prox = NULL;
    atual->ant = NULL;
    
    if (lista == NULL) {
        return atual;
    }
    
    Pessoa *ultimo = lista;
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = atual;
    atual->ant = ultimo;
    
    Pessoa *direita = arvore_para_lista_pessoas(raiz->dir);
    if (direita != NULL) {
        atual->prox = direita;
        direita->ant = atual;
    }
    
    return lista;
}