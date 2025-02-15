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
    
    // Criar árvores vazias
    NoArvore *arvore_pessoas = NULL;
    NoArvore *arvore_tipos = NULL;
    NoArvore *arvore_pets = NULL;
    
    // Criar listas temporárias para carregar os dados
    Pessoa *lista_pessoas = NULL;
    TipoPet *lista_tipos = NULL;
    Pet *lista_pets = NULL;
    
    // Carregar dados dos arquivos para as listas
    carregar_pessoas(&lista_pessoas);
    carregar_tipos(&lista_tipos);
    carregar_pets(&lista_pets);
    
    // Converter listas para árvores e liberar as listas
    Pessoa *p = lista_pessoas;
    while (p) {
        Pessoa *prox = p->prox;
        p->prox = p->ant = NULL;
        inserir_pessoa(&arvore_pessoas, p);
        p = prox;
    }
    lista_pessoas = NULL;  // Lista foi convertida para árvore
    
    TipoPet *t = lista_tipos;
    while (t) {
        TipoPet *prox = t->prox;
        t->prox = t->ant = NULL;
        inserir_tipo_pet(&arvore_tipos, t);
        t = prox;
    }
    lista_tipos = NULL;  // Lista foi convertida para árvore
    
    Pet *pet = lista_pets;
    while (pet) {
        Pet *prox = pet->prox;
        pet->prox = pet->ant = NULL;
        inserir_pet(&arvore_pets, pet);
        pet = prox;
    }
    lista_pets = NULL;  // Lista foi convertida para árvore
    
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

    // Processar comandos por tipo
    NoComando *cmd;
    
    printf("\n=== Processando comandos para TIPO_PET ===\n\n");
    while ((cmd = remover_comando(fila_tipos)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        if (strncasecmp(cmd->comando, "SELECT", 6) == 0) {
            if (arvore_tipos == NULL) {
                printf("Nenhum tipo de pet cadastrado.\n");
            } else {
                exibir_arvore_ordenada(arvore_tipos, 3);
            }
        } else if (strncasecmp(cmd->comando, "DELETE", 6) == 0) {
            int codigo = extrair_id(cmd->comando);
            arvore_tipos = remover_no(arvore_tipos, codigo, 3);
            // Atualiza o arquivo com a nova árvore
            TipoPet *lista_temp = arvore_para_lista_tipos(arvore_tipos);
            salvar_tipos(lista_temp);
            // Libera a lista temporária
            while (lista_temp) {
                TipoPet *prox = lista_temp->prox;
                free(lista_temp);
                lista_temp = prox;
            }
        } else if (strncasecmp(cmd->comando, "UPDATE", 6) == 0) {
            char campo[50], valor[100];
            int codigo = extrair_id(cmd->comando);
            if (extrair_campo_valor(cmd->comando, campo, valor)) {
                NoArvore *no = arvore_tipos;
                while (no) {
                    TipoPet *t = (TipoPet*)no->dados;
                    if (t->codigo == codigo) {
                        if (strcmp(campo, "nome") == 0) {
                            strcpy(t->nome, valor);
                        }
                        // Atualiza o arquivo
                        TipoPet *lista_temp = arvore_para_lista_tipos(arvore_tipos);
                        salvar_tipos(lista_temp);
                        // Libera a lista temporária
                        while (lista_temp) {
                            TipoPet *prox = lista_temp->prox;
                            free(lista_temp);
                            lista_temp = prox;
                        }
                        break;
                    }
                    if (codigo < t->codigo) {
                        no = no->esq;
                    } else {
                        no = no->dir;
                    }
                }
            }
        } else {
            TipoPet *lista_temp = NULL;
            processar_comando_tipo_pet(cmd->comando, &lista_temp);
            if (lista_temp) {
                TipoPet *tipo = lista_temp;
                while (tipo) {
                    TipoPet *prox = tipo->prox;
                    tipo->prox = tipo->ant = NULL;
                    inserir_tipo_pet(&arvore_tipos, tipo);
                    tipo = prox;
                }
            }
        }
        printf("\n");
        free(cmd);
    }
    
    printf("\n=== Processando comandos para PESSOAS ===\n\n");
    while ((cmd = remover_comando(fila_pessoas)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        if (strncasecmp(cmd->comando, "SELECT", 6) == 0) {
            if (arvore_pessoas == NULL) {
                printf("Nenhuma pessoa cadastrada.\n");
            } else {
                exibir_arvore_ordenada(arvore_pessoas, 1);
            }
        } else if (strncasecmp(cmd->comando, "DELETE", 6) == 0) {
            int codigo = extrair_id(cmd->comando);
            arvore_pessoas = remover_no(arvore_pessoas, codigo, 1);
            // Atualiza o arquivo com a nova árvore
            Pessoa *lista_temp = arvore_para_lista_pessoas(arvore_pessoas);
            salvar_pessoas(lista_temp);
            // Libera a lista temporária
            while (lista_temp) {
                Pessoa *prox = lista_temp->prox;
                free(lista_temp);
                lista_temp = prox;
            }
        } else if (strncasecmp(cmd->comando, "UPDATE", 6) == 0) {
            char campo[50], valor[100];
            int codigo = extrair_id(cmd->comando);
            if (extrair_campo_valor(cmd->comando, campo, valor)) {
                NoArvore *no = arvore_pessoas;
                while (no) {
                    Pessoa *p = (Pessoa*)no->dados;
                    if (p->codigo == codigo) {
                        if (strcmp(campo, "nome") == 0) {
                            strcpy(p->nome, valor);
                        } else if (strcmp(campo, "fone") == 0) {
                            strcpy(p->fone, valor);
                        } else if (strcmp(campo, "endereco") == 0) {
                            strcpy(p->endereco, valor);
                        } else if (strcmp(campo, "data_nasc") == 0) {
                            strcpy(p->data_nasc, valor);
                        }
                        // Atualiza o arquivo
                        Pessoa *lista_temp = arvore_para_lista_pessoas(arvore_pessoas);
                        salvar_pessoas(lista_temp);
                        // Libera a lista temporária
                        while (lista_temp) {
                            Pessoa *prox = lista_temp->prox;
                            free(lista_temp);
                            lista_temp = prox;
                        }
                        break;
                    }
                    if (codigo < p->codigo) {
                        no = no->esq;
                    } else {
                        no = no->dir;
                    }
                }
            }
        } else {
            Pessoa *lista_temp = NULL;
            processar_comando_pessoa(cmd->comando, &lista_temp);
            if (lista_temp) {
                Pessoa *p = lista_temp;
                while (p) {
                    Pessoa *prox = p->prox;
                    p->prox = p->ant = NULL;
                    inserir_pessoa(&arvore_pessoas, p);
                    p = prox;
                }
            }
        }
        printf("\n");
        free(cmd);
    }
    
    printf("\n=== Processando comandos para PET ===\n\n");
    while ((cmd = remover_comando(fila_pets)) != NULL) {
        printf("Executando: %s\n", cmd->comando);
        if (strncasecmp(cmd->comando, "SELECT", 6) == 0) {
            if (arvore_pets == NULL) {
                printf("Nenhum pet cadastrado.\n");
            } else {
                exibir_arvore_ordenada(arvore_pets, 2);
            }
        } else if (strncasecmp(cmd->comando, "DELETE", 6) == 0) {
            int codigo = extrair_id(cmd->comando);
            arvore_pets = remover_no(arvore_pets, codigo, 2);
            // Atualiza o arquivo com a nova árvore
            Pet *lista_temp = arvore_para_lista_pets(arvore_pets);
            salvar_pets(lista_temp);
            // Libera a lista temporária
            while (lista_temp) {
                Pet *prox = lista_temp->prox;
                free(lista_temp);
                lista_temp = prox;
            }
        } else if (strncasecmp(cmd->comando, "UPDATE", 6) == 0) {
            char campo[50], valor[100];
            int codigo = extrair_id(cmd->comando);
            if (extrair_campo_valor(cmd->comando, campo, valor)) {
                NoArvore *no = arvore_pets;
                while (no) {
                    Pet *p = (Pet*)no->dados;
                    if (p->codigo == codigo) {
                        if (strcmp(campo, "nome") == 0) {
                            strcpy(p->nome, valor);
                        }
                        // Atualiza o arquivo
                        Pet *lista_temp = arvore_para_lista_pets(arvore_pets);
                        salvar_pets(lista_temp);
                        // Libera a lista temporária
                        while (lista_temp) {
                            Pet *prox = lista_temp->prox;
                            free(lista_temp);
                            lista_temp = prox;
                        }
                        break;
                    }
                    if (codigo < p->codigo) {
                        no = no->esq;
                    } else {
                        no = no->dir;
                    }
                }
            }
        } else {
            Pet *lista_temp = NULL;
            Pessoa *pessoas_temp = arvore_para_lista_pessoas(arvore_pessoas);
            TipoPet *tipos_temp = arvore_para_lista_tipos(arvore_tipos);
            processar_comando_pet(cmd->comando, &lista_temp, pessoas_temp, tipos_temp);
            if (lista_temp) {
                Pet *pet = lista_temp;
                while (pet) {
                    Pet *prox = pet->prox;
                    pet->prox = pet->ant = NULL;
                    inserir_pet(&arvore_pets, pet);
                    pet = prox;
                }
            }
            // Libera as listas temporárias
            while (pessoas_temp) {
                Pessoa *prox = pessoas_temp->prox;
                free(pessoas_temp);
                pessoas_temp = prox;
            }
            while (tipos_temp) {
                TipoPet *prox = tipos_temp->prox;
                free(tipos_temp);
                tipos_temp = prox;
            }
        }
        printf("\n");
        free(cmd);
    }

    // Salvar alterações nos arquivos
    Pessoa *pessoas_para_salvar = arvore_para_lista_pessoas(arvore_pessoas);
    TipoPet *tipos_para_salvar = arvore_para_lista_tipos(arvore_tipos);
    Pet *pets_para_salvar = arvore_para_lista_pets(arvore_pets);
    
    salvar_pessoas(pessoas_para_salvar);
    salvar_tipos(tipos_para_salvar);
    salvar_pets(pets_para_salvar);
    
    // Liberar as listas temporárias
    free(pessoas_para_salvar);
    free(tipos_para_salvar);
    free(pets_para_salvar);
    
    // Libera a memória
    liberar_fila(comandos);
    liberar_fila(fila_pessoas);
    liberar_fila(fila_pets);
    liberar_fila(fila_tipos);

    // Fecha o arquivo
    fclose(arquivo);

    // Liberar árvores
    liberar_arvore(arvore_pessoas, 1);
    liberar_arvore(arvore_tipos, 1);
    liberar_arvore(arvore_pets, 1);

    printf("\nProcessamento concluido!\n");
    printf("Pressione qualquer tecla para sair...");
    system("pause");

    return 0;
}
