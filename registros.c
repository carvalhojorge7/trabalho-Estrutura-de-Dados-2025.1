#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "registros.h"

// Flag para marcar registros deletados
#define DELETADO_FLAG "#DELETADO#"

void salvar_registro(const char *tabela, Registro *reg) {
    char filename[100];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "ab");
    if (f) {
        fwrite(&reg->tamanho, sizeof(int), 1, f);
        fwrite(reg->dados, 1, reg->tamanho, f);
        fclose(f);
        printf("Registro inserido com sucesso!\n");
    } else {
        printf("Erro ao abrir arquivo %s para inserção\n", filename);
    }
}

int registro_atende_condicao(const char *dados, const char *campo, const char *valor) {
    if (!campo || !valor) return 1; // Se não tem condição, retorna todos
    
    // Verifica se o registro está deletado
    if (strstr(dados, DELETADO_FLAG)) return 0;
    
    // Busca campo=valor no registro
    char busca[200];
    sprintf(busca, "%s=%s", campo, valor);
    return strstr(dados, busca) != NULL;
}

void buscar_registros(const char *tabela, const char *campo, const char *valor,
                     void (*callback)(const char *dados)) {
    char filename[100];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Erro ao abrir arquivo %s para leitura\n", filename);
        return;
    }
    
    int tamanho;
    char *dados;
    int encontrou = 0;
    
    while (fread(&tamanho, sizeof(int), 1, f) == 1) {
        dados = malloc(tamanho + 1);
        fread(dados, 1, tamanho, f);
        dados[tamanho] = '\0';
        
        if (registro_atende_condicao(dados, campo, valor)) {
            callback(dados);
            encontrou = 1;
        }
        
        free(dados);
    }
    
    if (!encontrou) {
        printf("Nenhum registro encontrado\n");
    }
    
    fclose(f);
}

void marcar_como_deletado(FILE *arquivo, long posicao) {
    // Volta para o início do registro
    fseek(arquivo, posicao, SEEK_SET);
    
    // Lê o tamanho atual
    int tamanho;
    fread(&tamanho, sizeof(int), 1, arquivo);
    
    // Volta para o início do registro
    fseek(arquivo, posicao, SEEK_SET);
    
    // Marca como deletado
    char *dados = malloc(tamanho + strlen(DELETADO_FLAG) + 1);
    sprintf(dados, "%s%s", DELETADO_FLAG, "registro_deletado");
    
    // Escreve o novo registro
    int novo_tamanho = strlen(dados);
    fwrite(&novo_tamanho, sizeof(int), 1, arquivo);
    fwrite(dados, 1, novo_tamanho, arquivo);
    
    free(dados);
}

int remover_registro(const char *tabela, const char *campo, const char *valor) {
    char filename[100];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "rb+");
    if (!f) {
        printf("Erro ao abrir arquivo %s para remoção\n", filename);
        return 0;
    }
    
    int tamanho;
    char *dados;
    int removidos = 0;
    long posicao;
    
    while (1) {
        posicao = ftell(f);
        if (fread(&tamanho, sizeof(int), 1, f) != 1) break;
        
        dados = malloc(tamanho + 1);
        fread(dados, 1, tamanho, f);
        dados[tamanho] = '\0';
        
        if (registro_atende_condicao(dados, campo, valor)) {
            marcar_como_deletado(f, posicao);
            removidos++;
        }
        
        free(dados);
    }
    
    fclose(f);
    
    if (removidos > 0) {
        printf("%d registro(s) removido(s) com sucesso!\n", removidos);
    } else {
        printf("Nenhum registro encontrado para remoção\n");
    }
    
    return removidos;
}

int atualizar_registro(const char *tabela, const char *campo_busca, const char *valor_busca,
                      const char *campo_atualizar, const char *valor_novo) {
    char filename[100];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "rb+");
    if (!f) {
        printf("Erro ao abrir arquivo %s para atualização\n", filename);
        return 0;
    }
    
    int tamanho;
    char *dados;
    int atualizados = 0;
    long posicao;
    
    while (1) {
        posicao = ftell(f);
        if (fread(&tamanho, sizeof(int), 1, f) != 1) break;
        
        dados = malloc(tamanho + 1);
        fread(dados, 1, tamanho, f);
        dados[tamanho] = '\0';
        
        if (registro_atende_condicao(dados, campo_busca, valor_busca)) {
            // Cria novo registro com o valor atualizado
            char *novo_dados = malloc(tamanho + 100); // Espaço extra para segurança
            sprintf(novo_dados, "%s,%s=%s", dados, campo_atualizar, valor_novo);
            
            // Volta para o início do registro
            fseek(f, posicao, SEEK_SET);
            
            // Escreve o novo registro
            int novo_tamanho = strlen(novo_dados);
            fwrite(&novo_tamanho, sizeof(int), 1, f);
            fwrite(novo_dados, 1, novo_tamanho, f);
            
            free(novo_dados);
            atualizados++;
        }
        
        free(dados);
    }
    
    fclose(f);
    
    if (atualizados > 0) {
        printf("%d registro(s) atualizado(s) com sucesso!\n", atualizados);
    } else {
        printf("Nenhum registro encontrado para atualização\n");
    }
    
    return atualizados;
}
