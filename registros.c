#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

void salvar_registro(Registro *reg) {
    char filename[MAX_CAMPO + 4]; // +4 para ".bin"
    sprintf(filename, "%s.bin", reg->tabela);
    
    FILE *f = fopen(filename, "ab");
    if (f) {
        // Primeiro salva o número de campos
        fwrite(&reg->num_campos, sizeof(int), 1, f);
        
        // Depois salva cada campo
        for (int i = 0; i < reg->num_campos; i++) {
            fwrite(&reg->campos[i], sizeof(Campo), 1, f);
        }
        
        fclose(f);
    }
}

Registro* buscar_registro(const char *tabela, const char *campo, const char *valor) {
    char filename[MAX_CAMPO + 4];
    sprintf(filename, "%s.bin", tabela);
    
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;
    
    Registro *reg = NULL;
    int num_campos;
    
    // Lê registros até encontrar um que corresponda
    while (fread(&num_campos, sizeof(int), 1, f)) {
        reg = malloc(sizeof(Registro));
        strcpy(reg->tabela, tabela);
        reg->num_campos = num_campos;
        reg->campos = malloc(num_campos * sizeof(Campo));
        
        // Lê todos os campos do registro
        for (int i = 0; i < num_campos; i++) {
            fread(&reg->campos[i], sizeof(Campo), 1, f);
            
            // Se encontrou o campo procurado e o valor corresponde
            if (strcmp(reg->campos[i].nome, campo) == 0 && 
                strcmp(reg->campos[i].valor, valor) == 0) {
                fclose(f);
                return reg;
            }
        }
        
        // Se não encontrou, libera e continua procurando
        liberar_registro(reg);
        reg = NULL;
    }
    
    fclose(f);
    return NULL;
}

void liberar_registro(Registro *reg) {
    if (reg) {
        free(reg->campos);
        free(reg);
    }
}
