#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "estruturas.h"
#include "comandos.h"

#define MAX_COMANDO 500

int main() {
    // Configura o locale para português do Brasil
    setlocale(LC_ALL,"");
    
    char nome_arquivo[100];
    
    printf("Digite o nome do arquivo de comandos (ex: comandos.txt): ");
    scanf("%s", nome_arquivo);
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');

    // Abre o arquivo de comandos
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("\nERRO: Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
        printf("Verifique se o arquivo existe e se o nome esta correto.\n\n");
        system("pause");
        return 1;
    }

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
    
    // Lê os comandos do arquivo
    char linha[MAX_COMANDO];
    printf("\n=== Lendo comandos do arquivo ===\n\n");
    while (fgets(linha, MAX_COMANDO, arquivo)) {
        // Remove o \n do final da linha
        linha[strcspn(linha, "\n")] = 0;
        if (linha[0] != '#' && linha[0] != '\0') {  // Ignora comentários e linhas vazias
            printf("Lendo comando: %s\n", linha);
            inserir_comando(comandos, linha);
        }
    }
    printf("\n=== Separando comandos por tipo ===\n\n");
    separar_comandos(comandos, fila_pessoas, fila_pets, fila_tipos);

    // Processa os comandos
    NoComando *cmd;
    
    printf("\n=== Processando comandos para TIPO_PET ===\n\n");
    while ((cmd = remover_comando(fila_tipos)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        processar_comando_tipo_pet(cmd->comando, &lista_tipos);
        printf("\n");
        free(cmd);
    }

    printf("\n=== Processando comandos para PESSOAS ===\n\n");
    while ((cmd = remover_comando(fila_pessoas)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        processar_comando_pessoa(cmd->comando, &lista_pessoas);
        printf("\n");
        free(cmd);
    }

    printf("\n=== Processando comandos para PET ===\n\n");
    while ((cmd = remover_comando(fila_pets)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        processar_comando_pet(cmd->comando, &lista_pets, lista_pessoas, lista_tipos);
        printf("\n");
        free(cmd);
    }

    // Salvar alterações nos arquivos
    salvar_pessoas(lista_pessoas);
    salvar_tipos(lista_tipos);
    salvar_pets(lista_pets);
    
    // Libera a memória
    liberar_fila(comandos);
    liberar_fila(fila_pessoas);
    liberar_fila(fila_pets);
    liberar_fila(fila_tipos);

    // Fecha o arquivo
    fclose(arquivo);

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

    printf("\nProcessamento concluido!\n");
    printf("Pressione qualquer tecla para sair...");
    system("pause");

    return 0;
}
