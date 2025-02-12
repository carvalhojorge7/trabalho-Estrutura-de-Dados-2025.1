#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "fila.h"
#include "arvore.h"
#include "comandos.h"

#define MAX_COMANDO 500

int main() {
    // Criar filas para cada tipo
    Fila *fila_pessoa = criar_fila();
    Fila *fila_pet = criar_fila();
    Fila *fila_tipo = criar_fila();
    
    // Criar árvore para ordenação
    Arvore *arvore = criar_arvore();
    
    char comando[MAX_COMANDO];
    int opcao;
    
    do {
        printf("\n=== Sistema de Gerenciamento de Pets ===\n");
        printf("1. Ler comando do teclado\n");
        printf("2. Ler comandos de arquivo\n");
        printf("3. Processar comandos\n");
        printf("0. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        
        switch(opcao) {
            case 1:
                printf("Digite o comando SQL: ");
                fgets(comando, MAX_COMANDO, stdin);
                comando[strcspn(comando, "\n")] = 0; // Remove \n
                processar_comando(comando, fila_pessoa, fila_pet, fila_tipo);
                break;
                
            case 2:
                printf("Nome do arquivo: ");
                char arquivo[100];
                fgets(arquivo, 100, stdin);
                arquivo[strcspn(arquivo, "\n")] = 0;
                
                FILE *f = fopen(arquivo, "r");
                if (f == NULL) {
                    printf("Erro ao abrir arquivo\n");
                    break;
                }
                
                while (fgets(comando, MAX_COMANDO, f)) {
                    comando[strcspn(comando, "\n")] = 0;
                    processar_comando(comando, fila_pessoa, fila_pet, fila_tipo);
                }
                fclose(f);
                break;
                
            case 3:
                // Processar comandos das filas
                printf("\nProcessando comandos...\n");
                NoComando *cmd;
                
                while ((cmd = remover_comando(fila_pessoa)) != NULL) {
                    executar_insert(cmd->descricao, cmd->tipo);
                    free(cmd);
                }
                
                while ((cmd = remover_comando(fila_pet)) != NULL) {
                    executar_insert(cmd->descricao, cmd->tipo);
                    free(cmd);
                }
                
                while ((cmd = remover_comando(fila_tipo)) != NULL) {
                    executar_insert(cmd->descricao, cmd->tipo);
                    free(cmd);
                }
                break;
        }
    } while (opcao != 0);
    
    // Liberar memória
    liberar_fila(fila_pessoa);
    liberar_fila(fila_pet);
    liberar_fila(fila_tipo);
    liberar_arvore(arvore);
    
    return 0;
}
