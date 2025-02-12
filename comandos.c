#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// Função para extrair nome da tabela do comando
void extrair_nome_tabela(const char *comando, char *nome_arquivo) {
    const char *into = strstr(comando, "into ");
    if (!into) return;
    
    into += 5; // Pula "into "
    while (*into == ' ') into++; // Pula espaços extras
    
    // Copia até encontrar espaço ou parênteses
    int i = 0;
    while (into[i] && into[i] != ' ' && into[i] != '(') {
        nome_arquivo[i] = into[i];
        i++;
    }
    nome_arquivo[i] = '\0';
    
    // Adiciona extensão .bin
    strcat(nome_arquivo, ".bin");
}

// Função para extrair os valores entre parênteses
void extrair_valores(const char *comando, char **valores, int *tamanho) {
    const char *inicio = strchr(comando, '(');
    if (!inicio) return;
    inicio++;
    
    const char *fim = strrchr(comando, ')');
    if (!fim || fim <= inicio) return;
    
    *tamanho = fim - inicio;
    *valores = (char*)malloc(*tamanho + 1);
    strncpy(*valores, inicio, *tamanho);
    (*valores)[*tamanho] = '\0';
}

void processar_insert(const char *comando) {
    // Extrai nome da tabela e cria nome do arquivo
    char nome_arquivo[100];
    extrair_nome_tabela(comando, nome_arquivo);
    
    // Extrai valores
    char *valores;
    int tamanho;
    extrair_valores(comando, &valores, &tamanho);
    
    if (!valores) {
        printf("Erro ao extrair valores do comando\n");
        return;
    }
    
    // Cria registro
    Registro reg;
    reg.dados = valores;
    reg.tamanho = tamanho;
    
    // Salva no arquivo binário
    FILE *f = fopen(nome_arquivo, "ab");
    if (f) {
        fwrite(&reg.tamanho, sizeof(int), 1, f);
        fwrite(reg.dados, 1, reg.tamanho, f);
        fclose(f);
        printf("Dados salvos em %s\n", nome_arquivo);
    } else {
        printf("Erro ao criar arquivo %s\n", nome_arquivo);
    }
    
    free(valores);
}

void processar_comandos(Fila *f) {
    NoComando *no;
    int linha = 1;
    
    while ((no = remover_comando(f)) != NULL) {
        printf("\nProcessando linha %d: %s\n", linha++, no->comando);
        
        if (strncasecmp(no->comando, "insert", 6) == 0) {
            processar_insert(no->comando);
        }
        
        free(no);
    }
}
