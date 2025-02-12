#ifndef REGISTROS_H
#define REGISTROS_H

#include "estruturas.h"

// Funções para manipulação do "banco de dados" (.bin)
void salvar_registro(const char *tabela, Registro *reg);
void buscar_registros(const char *tabela, const char *campo, const char *valor, 
                     void (*callback)(const char *dados));
int atualizar_registro(const char *tabela, const char *campo_busca, const char *valor_busca,
                      const char *campo_atualizar, const char *valor_novo);
int remover_registro(const char *tabela, const char *campo, const char *valor);

// Funções auxiliares
int registro_atende_condicao(const char *dados, const char *campo, const char *valor);
void marcar_como_deletado(FILE *arquivo, long posicao);
void reorganizar_arquivo(const char *tabela);

#endif
