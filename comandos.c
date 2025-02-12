#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "comandos.h"

// Identifica o tipo de tabela do comando
char identificar_tipo_comando(const char *comando) {
    if (strstr(comando, "pessoa")) return 'P';
    if (strstr(comando, "pet")) return 'E';
    if (strstr(comando, "tipo_pet")) return 'T';
    return 0;
}

// Valida sintaxe básica do comando SQL
int validar_comando(const char *comando) {
    // Verifica se comando termina com ;
    if (comando[strlen(comando)-1] != ';') return 0;
    
    // Verifica se é um dos comandos válidos
    if (strstr(comando, "insert into") ||
        strstr(comando, "select") ||
        strstr(comando, "delete from") ||
        strstr(comando, "update")) {
        return 1;
    }
    
    return 0;
}

// Processa e distribui o comando para a fila apropriada
int processar_comando(const char *comando, Fila *fila_pessoa, Fila *fila_pet, Fila *fila_tipo) {
    if (!validar_comando(comando)) {
        printf("Comando inválido: %s\n", comando);
        return 0;
    }
    
    char tipo = identificar_tipo_comando(comando);
    if (!tipo) {
        printf("Tabela não identificada no comando: %s\n", comando);
        return 0;
    }
    
    // Distribui para a fila apropriada
    switch(tipo) {
        case 'P':
            inserir_comando(fila_pessoa, comando, tipo);
            break;
        case 'E':
            inserir_comando(fila_pet, comando, tipo);
            break;
        case 'T':
            inserir_comando(fila_tipo, comando, tipo);
            break;
    }
    
    return 1;
}

// Funções básicas para executar comandos
int executar_insert(const char *comando, char tipo) {
    // Implementação básica do INSERT
    printf("Executando INSERT: %s\n", comando);
    return 1;
}

int executar_select(const char *comando, char tipo, Arvore *arvore) {
    // Implementação básica do SELECT
    printf("Executando SELECT: %s\n", comando);
    return 1;
}

int executar_delete(const char *comando, char tipo) {
    // Implementação básica do DELETE
    printf("Executando DELETE: %s\n", comando);
    return 1;
}

int executar_update(const char *comando, char tipo) {
    // Implementação básica do UPDATE
    printf("Executando UPDATE: %s\n", comando);
    return 1;
}
