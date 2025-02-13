#ifndef COMANDOS_H
#define COMANDOS_H

#include "estruturas.h"

// Enum para identificar o tipo de estrutura
typedef enum {
    TIPO_PESSOA,
    TIPO_PET,
    TIPO_TIPO_PET
} TipoRegistro;

// Funções para processar comandos
void processar_comando_pessoa(const char *comando, Pessoa **lista);
void processar_comando_tipo_pet(const char *comando, TipoPet **lista);
void processar_comando_pet(const char *comando, Pet **lista, Pessoa *lista_pessoas, TipoPet *lista_tipos);

// Funções auxiliares
int extrair_id(const char *comando);
char *extrair_campo(const char *comando, const char *nome_campo);
int extrair_campo_valor(const char *comando, char *campo, char *valor);
int verificar_registro_existe(void *lista, int codigo, int tipo);
void processar_update(const char *comando, void **lista, int tipo);

// Funções de busca
Pessoa *buscar_pessoa(Pessoa *lista, int codigo);
Pet *buscar_pet(Pet *lista, int codigo);
TipoPet *buscar_tipo_pet(TipoPet *lista, int codigo);

// Função auxiliar para comparação case-insensitive
char *strcasestr(const char *haystack, const char *needle);

// Funções para extrair dados
Pessoa *extrair_dados_pessoa(const char *comando);
Pet *extrair_dados_pet(const char *comando);
TipoPet *extrair_dados_tipo_pet(const char *comando);

#endif
