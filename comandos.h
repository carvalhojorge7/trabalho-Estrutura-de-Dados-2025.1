#ifndef COMANDOS_H
#define COMANDOS_H

#include "estruturas.h"

// Enum para identificar o tipo de estrutura
typedef enum {
    TIPO_PESSOA,
    TIPO_PET,
    TIPO_TIPO_PET
} TipoRegistro;

// Funções auxiliares
char* extrair_campo(const char *comando, const char *campo);
int extrair_id(const char *comando);
int extrair_id_ref(const char *comando, const char *campo);

// Função genérica para verificar existência de registro
int verificar_registro_existe(void *lista, int codigo, int tipo);

// Funções para processamento de comandos
void processar_comando_pessoa(const char *comando, Pessoa **lista);
void processar_comando_pet(const char *comando, Pet **lista, Pessoa *lista_pessoas, TipoPet *lista_tipos);
void processar_comando_tipo_pet(const char *comando, TipoPet **lista);

#endif
