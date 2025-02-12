#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "comandos.h"

#define MAX_COMANDO 500

int main() {
    // Criar filas para os comandos
    Fila *comandos = criar_fila();
    Fila *fila_pessoas = criar_fila();
    Fila *fila_pets = criar_fila();
    Fila *fila_tipos = criar_fila();
    
    // Criar listas duplamente encadeadas
    Pessoa *lista_pessoas = criar_lista_pessoas();
    TipoPet *lista_tipos = criar_lista_tipos();
    Pet *lista_pets = criar_lista_pets();
    
    // Carregar dados dos arquivos
    carregar_pessoas(&lista_pessoas);
    carregar_tipos(&lista_tipos);
    carregar_pets(&lista_pets);
    
    // Ler comandos do arquivo
    char arquivo[100];
    printf("Digite o nome do arquivo de comandos: ");
    scanf("%s", arquivo);
    
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo de comandos!\n");
        return 1;
    }
    
    char linha[MAX_COMANDO];
    while (fgets(linha, MAX_COMANDO, f)) {
        // Remove \n do final
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) > 0) {
            inserir_comando(comandos, linha);
        }
    }
    fclose(f);
    
    // Separar comandos em filas específicas
    separar_comandos(comandos, fila_pessoas, fila_pets, fila_tipos);
    
    // Processar comandos de cada fila
    NoComando *cmd;
    
    // Processar comandos de pessoas
    printf("\nProcessando comandos de pessoas:\n");
    while ((cmd = remover_comando(fila_pessoas)) != NULL) {
        printf("\nComando: %s\n", cmd->comando);
        processar_comando_pessoa(cmd->comando, &lista_pessoas);
        free(cmd);
    }
    
    // Processar comandos de pets
    printf("\nProcessando comandos de pets:\n");
    while ((cmd = remover_comando(fila_pets)) != NULL) {
        printf("\nComando: %s\n", cmd->comando);
        processar_comando_pet(cmd->comando, &lista_pets, lista_pessoas, lista_tipos);
        free(cmd);
    }
    
    // Processar comandos de tipos de pet
    printf("\nProcessando comandos de tipos de pet:\n");
    while ((cmd = remover_comando(fila_tipos)) != NULL) {
        printf("\nComando: %s\n", cmd->comando);
        processar_comando_tipo_pet(cmd->comando, &lista_tipos);
        free(cmd);
    }
    
    // Salvar alterações nos arquivos
    salvar_pessoas(lista_pessoas);
    salvar_tipos(lista_tipos);
    salvar_pets(lista_pets);
    
    // Liberar memória
    liberar_fila(comandos);
    liberar_fila(fila_pessoas);
    liberar_fila(fila_pets);
    liberar_fila(fila_tipos);
    
    // Liberar listas encadeadas
    while (lista_pessoas) {
        Pessoa *p = lista_pessoas;
        lista_pessoas = lista_pessoas->prox;
        free(p);
    }
    
    while (lista_tipos) {
        TipoPet *t = lista_tipos;
        lista_tipos = lista_tipos->prox;
        free(t);
    }
    
    while (lista_pets) {
        Pet *p = lista_pets;
        lista_pets = lista_pets->prox;
        free(p);
    }
    
    return 0;
}
