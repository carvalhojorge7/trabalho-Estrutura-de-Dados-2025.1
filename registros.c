#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// Salva um registro no arquivo binário
void salvar_registro(const char *tabela, Registro *reg) {
    char filename[100]; // Nome do arquivo
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "ab");
    if (f) {
        // Salva tamanho e dados
        fwrite(&reg->tamanho, sizeof(int), 1, f);
        fwrite(reg->dados, 1, reg->tamanho, f);
        fclose(f);
        printf("Registro salvo em %s\n", filename);
    } else {
        printf("Erro ao abrir arquivo %s\n", filename);
    }
}

// Busca um registro no arquivo binário
Registro* buscar_registro(const char *tabela, const char *campo, const char *valor) {
    char filename[100];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Arquivo %s não encontrado\n", filename);
        return NULL;
    }
    
    Registro *reg = NULL;
    int tamanho;
    
    // Lê registros até encontrar o procurado
    while (fread(&tamanho, sizeof(int), 1, f) == 1) {
        reg = malloc(sizeof(Registro));
        reg->tamanho = tamanho;
        reg->dados = malloc(tamanho);
        
        fread(reg->dados, 1, tamanho, f);
        
        // Verifica se é o registro procurado
        // TODO: implementar busca por campo/valor
        
        // Se não for o registro procurado, libera e continua
        free(reg->dados);
        free(reg);
        reg = NULL;
    }
    
    fclose(f);
    return reg;
}

// Atualiza um registro no arquivo binário
void atualizar_registro(const char *tabela, const char *campo, const char *valor, 
                       const char *novo_campo, const char *novo_valor) {
    // TODO: implementar atualização
    printf("Atualização não implementada ainda\n");
}

// Remove um registro do arquivo binário (remoção lógica)
void remover_registro(const char *tabela, const char *campo, const char *valor) {
    // TODO: implementar remoção lógica
    printf("Remoção não implementada ainda\n");
}

// Libera a memória de um registro
void liberar_registro(Registro *reg) {
    if (reg) {
        if (reg->dados) free(reg->dados);
        free(reg);
    }
}
