#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define MAX_COMANDO 500

int main() {
    Fila *fila = criar_fila();
    char arquivo[100];
    char comando[MAX_COMANDO];
    
    printf("Digite o nome do arquivo com os comandos SQL: ");
    scanf("%s", arquivo);
    
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return 1;
    }
    
    // Lê e insere todos os comandos na fila
    while (fgets(comando, MAX_COMANDO, f)) {
        comando[strcspn(comando, "\n")] = 0; // Remove \n
        inserir_comando(fila, comando);
    }
    fclose(f);
    
    // Processa os comandos e gera os arquivos .bin
    printf("\nProcessando comandos...\n");
    processar_comandos(fila);
    printf("Arquivos .bin gerados com sucesso!\n");
    
    liberar_fila(fila);
    return 0;
}
