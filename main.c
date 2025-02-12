#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define MAX_COMANDO 500

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    printf("\n");
    printf("+===========================================+\n");
    printf("|     INTERPRETADOR DE COMANDOS SQL        |\n");
    printf("+===========================================+\n");
    
    Fila *fila = criar_fila();
    char arquivo[100];
    char comando[MAX_COMANDO];
    char opcao;
    
    do {
        printf("\nDigite o nome do arquivo de comandos (.txt): ");
        scanf("%s", arquivo);
        
        // Verifica se o arquivo termina com .txt
        char *ext = strrchr(arquivo, '.');
        if (!ext || strcmp(ext, ".txt") != 0) {
            strcat(arquivo, ".txt");
        }
        
        FILE *f = fopen(arquivo, "r");
        if (!f) {
            printf("\n");
            printf("+===========================================+\n");
            printf("|                  ERRO                    |\n");
            printf("+===========================================+\n");
            printf("Erro ao abrir arquivo %s\n", arquivo);
            printf("+===========================================+\n\n");
        } else {
            printf("\nLendo comandos do arquivo %s...\n", arquivo);
            
            // Lê e insere todos os comandos na fila
            while (fgets(comando, MAX_COMANDO, f)) {
                comando[strcspn(comando, "\n")] = 0; // Remove \n
                if (strlen(comando) > 0) { // Ignora linhas vazias
                    inserir_comando(fila, comando);
                }
            }
            fclose(f);
            
            // Processa os comandos
            printf("\nProcessando comandos...\n");
            processar_comandos(fila);
            printf("Arquivos .bin gerados com sucesso!\n");
            
            liberar_fila(fila);
            fila = criar_fila(); // Cria nova fila para próximo uso
        }
        
        limpar_buffer();
        printf("\nDeseja processar outro arquivo? (S/N): ");
        scanf("%c", &opcao);
        
    } while (opcao == 'S' || opcao == 's');
    
    printf("\nObrigado por usar o programa!\n");
    system("pause");
    return 0;
}
