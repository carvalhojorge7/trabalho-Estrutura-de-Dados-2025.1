#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "registros.h"

// Função para extrair nome da tabela do comando
void extrair_nome_tabela(const char *comando, char *nome_arquivo) {
    const char *into = strstr(comando, "into ");
    const char *from = strstr(comando, "from ");
    const char *update = strstr(comando, "update ");
    const char *delete = strstr(comando, "delete from ");
    
    const char *inicio = NULL;
    if (into) inicio = into + 5;
    else if (from) inicio = from + 5;
    else if (update) inicio = update + 7;
    else if (delete) inicio = delete + 12;
    
    if (!inicio) {
        nome_arquivo[0] = '\0';
        return;
    }
    
    while (*inicio == ' ') inicio++; // Pula espaços extras
    
    // Copia até encontrar espaço ou parênteses
    int i = 0;
    while (inicio[i] && inicio[i] != ' ' && inicio[i] != '(') {
        nome_arquivo[i] = inicio[i];
        i++;
    }
    nome_arquivo[i] = '\0';
}

// Função para extrair os valores entre parênteses
void extrair_valores(const char *comando, char **valores, int *tamanho) {
    const char *inicio = strchr(comando, '(');
    if (!inicio) {
        *valores = NULL;
        return;
    }
    inicio++;
    
    const char *fim = strrchr(comando, ')');
    if (!fim || fim <= inicio) {
        *valores = NULL;
        return;
    }
    
    *tamanho = fim - inicio;
    *valores = (char*)malloc(*tamanho + 1);
    strncpy(*valores, inicio, *tamanho);
    (*valores)[*tamanho] = '\0';
}

// Função para extrair a condição WHERE
void extrair_where(const char *comando, char *campo, char *valor) {
    const char *where = strstr(comando, "where ");
    if (!where) {
        campo[0] = '\0';
        valor[0] = '\0';
        return;
    }
    
    where += 6; // Pula "where "
    while (*where == ' ') where++; // Pula espaços extras
    
    // Procura por "campo = valor"
    sscanf(where, "%[^= ] = %[^;) ]", campo, valor);
}

// Função para extrair SET do UPDATE
void extrair_set(const char *comando, char *campo, char *valor) {
    const char *set = strstr(comando, "set ");
    if (!set) {
        campo[0] = '\0';
        valor[0] = '\0';
        return;
    }
    
    set += 4; // Pula "set "
    while (*set == ' ') set++; // Pula espaços extras
    
    // Procura por "campo = valor"
    sscanf(set, "%[^= ] = %[^ ]", campo, valor);
}

// Callback para exibir resultados do SELECT
void exibir_registro(const char *dados) {
    printf("| %s\n", dados);
}

void processar_select(const char *comando) {
    char tabela[100];
    char campo[100];
    char valor[100];
    
    extrair_nome_tabela(comando, tabela);
    if (tabela[0] == '\0') return;
    
    extrair_where(comando, campo, valor);
    
    printf("\n");
    printf("+===========================================+\n");
    printf("|              CONSULTA SQL                |\n");
    printf("+===========================================+\n");
    printf("Tabela: %s\n", tabela);
    if (campo[0] != '\0') {
        printf("Filtro: %s = %s\n", campo, valor);
    }
    printf("+===========================================+\n");
    printf("\nRegistros:\n");
    printf("-------------------------------------------\n");
    
    buscar_registros(tabela, campo, valor, exibir_registro);
    
    printf("-------------------------------------------+\n\n");
}

void processar_insert(const char *comando) {
    char tabela[100];
    extrair_nome_tabela(comando, tabela);
    if (tabela[0] == '\0') return;
    
    char *valores;
    int tamanho;
    extrair_valores(comando, &valores, &tamanho);
    
    if (!valores) {
        printf("\n");
        printf("+===========================================+\n");
        printf("|               ERRO INSERT                |\n");
        printf("+===========================================+\n");
        printf("Erro ao extrair valores do comando\n");
        printf("+===========================================+\n\n");
        return;
    }
    
    // Cria registro
    Registro reg;
    reg.dados = valores;
    reg.tamanho = tamanho;
    
    printf("\n");
    printf("+===========================================+\n");
    printf("|              INSERT SQL                  |\n");
    printf("+===========================================+\n");
    printf("Tabela: %s\n", tabela);
    printf("Valores: %s\n", valores);
    printf("+===========================================+\n\n");
    
    // Salva no arquivo binário
    salvar_registro(tabela, &reg);
    
    free(valores);
}

void processar_update(const char *comando) {
    char tabela[100];
    char campo_where[100];
    char valor_where[100];
    char campo_set[100];
    char valor_set[100];
    
    extrair_nome_tabela(comando, tabela);
    if (tabela[0] == '\0') return;
    
    extrair_where(comando, campo_where, valor_where);
    if (campo_where[0] == '\0') {
        printf("\n");
        printf("+===========================================+\n");
        printf("|               ERRO UPDATE                |\n");
        printf("+===========================================+\n");
        printf("UPDATE requer cláusula WHERE\n");
        printf("+===========================================+\n\n");
        return;
    }
    
    extrair_set(comando, campo_set, valor_set);
    if (campo_set[0] == '\0') {
        printf("\n");
        printf("+===========================================+\n");
        printf("|               ERRO UPDATE                |\n");
        printf("+===========================================+\n");
        printf("UPDATE requer cláusula SET\n");
        printf("+===========================================+\n\n");
        return;
    }
    
    printf("\n");
    printf("+===========================================+\n");
    printf("|              UPDATE SQL                  |\n");
    printf("+===========================================+\n");
    printf("Tabela: %s\n", tabela);
    printf("SET %s = %s\n", campo_set, valor_set);
    printf("WHERE %s = %s\n", campo_where, valor_where);
    printf("+===========================================+\n\n");
    
    atualizar_registro(tabela, campo_where, valor_where, campo_set, valor_set);
}

void processar_delete(const char *comando) {
    char tabela[100];
    char campo[100];
    char valor[100];
    
    extrair_nome_tabela(comando, tabela);
    if (tabela[0] == '\0') return;
    
    extrair_where(comando, campo, valor);
    if (campo[0] == '\0') {
        printf("\n");
        printf("+===========================================+\n");
        printf("|               ERRO DELETE                |\n");
        printf("+===========================================+\n");
        printf("DELETE requer cláusula WHERE\n");
        printf("+===========================================+\n\n");
        return;
    }
    
    printf("\n");
    printf("+===========================================+\n");
    printf("|              DELETE SQL                  |\n");
    printf("+===========================================+\n");
    printf("Tabela: %s\n", tabela);
    printf("Condição: %s = %s\n", campo, valor);
    printf("+===========================================+\n\n");
    
    remover_registro(tabela, campo, valor);
}

void processar_comandos(Fila *f) {
    NoComando *no;
    int linha = 1;
    
    printf("\n");
    printf("+===========================================+\n");
    printf("|         PROCESSADOR DE COMANDOS          |\n");
    printf("+===========================================+\n\n");
    
    while ((no = remover_comando(f)) != NULL) {
        printf("Linha %d: %s\n", linha++, no->comando);
        
        if (strncasecmp(no->comando, "insert", 6) == 0) {
            processar_insert(no->comando);
        }
        else if (strncasecmp(no->comando, "select", 6) == 0) {
            processar_select(no->comando);
        }
        else if (strncasecmp(no->comando, "update", 6) == 0) {
            processar_update(no->comando);
        }
        else if (strncasecmp(no->comando, "delete", 6) == 0) {
            processar_delete(no->comando);
        }
        else if (strlen(no->comando) > 0 && no->comando[0] != '#') {
            printf("\n");
            printf("+===========================================+\n");
            printf("|                  ERRO                    |\n");
            printf("+===========================================+\n");
            printf("Comando não reconhecido\n");
            printf("+===========================================+\n\n");
        }
        
        free(no);
    }
    
    printf("+===========================================+\n");
    printf("|            FIM DO PROCESSAMENTO          |\n");
    printf("+===========================================+\n\n");
}
