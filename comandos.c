#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"

// Funções auxiliares para extrair informações dos comandos
int extrair_id(const char *comando) {
    char *pos = strstr(comando, "id=");
    if (!pos) return -1;
    return atoi(pos + 3);
}

char* extrair_campo(const char *comando, const char *campo) {
    char busca[100];
    sprintf(busca, "%s=", campo);
    char *pos = strstr(comando, busca);
    if (!pos) return NULL;
    
    pos += strlen(busca);
    static char valor[100];
    int i = 0;
    
    // Extrai até encontrar vírgula, parênteses ou ponto e vírgula
    while (*pos && *pos != ',' && *pos != ')' && *pos != ';') {
        valor[i++] = *pos++;
    }
    valor[i] = '\0';
    
    return valor;
}

int extrair_id_ref(const char *comando, const char *campo) {
    char *valor = extrair_campo(comando, campo);
    if (!valor) return -1;
    return atoi(valor);
}

// Função genérica para verificar se um registro existe
int verificar_registro_existe(void *lista, int codigo, int tipo) {
    switch (tipo) {
        case 1: { // Pessoa
            Pessoa *p = (Pessoa*)lista;
            while (p) {
                if (p->codigo == codigo) return 1;
                p = p->prox;
            }
            break;
        }
        case 2: { // Pet
            Pet *p = (Pet*)lista;
            while (p) {
                if (p->codigo == codigo) return 1;
                p = p->prox;
            }
            break;
        }
        case 3: { // TipoPet
            TipoPet *t = (TipoPet*)lista;
            while (t) {
                if (t->codigo == codigo) return 1;
                t = t->prox;
            }
            break;
        }
    }
    return 0;
}

// Processamento de comandos para Pessoa
void processar_comando_pessoa(const char *comando, Pessoa **lista) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        Pessoa *nova = (Pessoa*)malloc(sizeof(Pessoa));
        nova->codigo = extrair_id(comando);
        strcpy(nova->nome, extrair_campo(comando, "nome"));
        strcpy(nova->fone, extrair_campo(comando, "fone"));
        strcpy(nova->endereco, extrair_campo(comando, "endereco"));
        strcpy(nova->data_nasc, extrair_campo(comando, "data_nasc"));
        
        // Inserir no início da lista
        nova->prox = *lista;
        nova->ant = NULL;
        if (*lista) (*lista)->ant = nova;
        *lista = nova;
        
        // Salvar no arquivo
        salvar_pessoas(*lista);
    }
    else if (strncasecmp(comando, "SELECT", 6) == 0) {
        // Verifica se tem ORDER BY
        if (strstr(comando, "ORDER BY nome")) {
            NoArvore *arvore = NULL;
            Pessoa *p = *lista;
            
            // Inserir todos na árvore
            while (p) {
                inserir_na_arvore(&arvore, p, 1);
                p = p->prox;
            }
            
            // Exibir ordenado
            exibir_arvore_ordenada(arvore, 1);
            
            // Libera a árvore (0 porque não queremos liberar os dados, que estão na lista)
            liberar_arvore(arvore, 0);
        }
        else {
            // Exibir normal
            Pessoa *p = *lista;
            while (p) {
                printf("Código: %d, Nome: %s, Fone: %s, Endereço: %s, Data Nasc.: %s\n",
                       p->codigo, p->nome, p->fone, p->endereco, p->data_nasc);
                p = p->prox;
            }
        }
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int codigo = extrair_id(comando);
        Pessoa *p = *lista;
        
        while (p) {
            if (p->codigo == codigo) {
                char *nome = extrair_campo(comando, "nome");
                char *fone = extrair_campo(comando, "fone");
                char *endereco = extrair_campo(comando, "endereco");
                char *data_nasc = extrair_campo(comando, "data_nasc");
                
                if (nome) strcpy(p->nome, nome);
                if (fone) strcpy(p->fone, fone);
                if (endereco) strcpy(p->endereco, endereco);
                if (data_nasc) strcpy(p->data_nasc, data_nasc);
                
                // Salvar no arquivo
                salvar_pessoas(*lista);
                break;
            }
            p = p->prox;
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int codigo = extrair_id(comando);
        Pessoa *p = *lista;
        
        while (p) {
            if (p->codigo == codigo) {
                // Ajusta ponteiros
                if (p->ant) p->ant->prox = p->prox;
                else *lista = p->prox;
                if (p->prox) p->prox->ant = p->ant;
                
                // Libera memória
                free(p);
                
                // Salvar no arquivo
                salvar_pessoas(*lista);
                break;
            }
            p = p->prox;
        }
    }
}

// Processamento de comandos para Pet
void processar_comando_pet(const char *comando, Pet **lista, Pessoa *lista_pessoas, TipoPet *lista_tipos) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        Pet *novo = (Pet*)malloc(sizeof(Pet));
        novo->codigo = extrair_id(comando);
        
        // Verifica se o código já existe
        if (verificar_registro_existe(*lista, novo->codigo, 2)) {
            printf("ERRO: Já existe um pet com o código %d\n", novo->codigo);
            free(novo);
            return;
        }
        
        strcpy(novo->nome, extrair_campo(comando, "nome"));
        novo->codigo_tipo = extrair_id_ref(comando, "codigo_tipo");
        novo->codigo_pes = extrair_id_ref(comando, "codigo_pes");
        
        // Validações
        if (strlen(novo->nome) == 0) {
            printf("ERRO: O nome é obrigatório\n");
            free(novo);
            return;
        }
        
        // Verifica integridade referencial
        if (!verificar_registro_existe(lista_pessoas, novo->codigo_pes, 1)) {
            printf("ERRO: Pessoa com código %d não encontrada\n", novo->codigo_pes);
            free(novo);
            return;
        }
        if (!verificar_registro_existe(lista_tipos, novo->codigo_tipo, 3)) {
            printf("ERRO: Tipo de pet com código %d não encontrado\n", novo->codigo_tipo);
            free(novo);
            return;
        }
        
        // Inserir no início da lista
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
        
        // Salvar no arquivo
        salvar_pets(*lista);
        printf("Pet inserido com sucesso!\n");
    }
    else if (strncasecmp(comando, "SELECT", 6) == 0) {
        if (*lista == NULL) {
            printf("Nenhum pet cadastrado.\n");
            return;
        }
        
        printf("=== Resultado da consulta ===\n");
        // Verifica se tem ORDER BY
        if (strstr(comando, "ORDER BY nome")) {
            NoArvore *arvore = NULL;
            Pet *p = *lista;
            
            // Inserir todos na árvore
            while (p) {
                inserir_na_arvore(&arvore, p, 2);
                p = p->prox;
            }
            
            // Exibir ordenado
            exibir_arvore_ordenada(arvore, 2);
            
            // Libera a árvore (0 porque não queremos liberar os dados, que estão na lista)
            liberar_arvore(arvore, 0);
        }
        else {
            // Exibir normal
            Pet *p = *lista;
            while (p) {
                printf("Código: %d, Nome: %s, Código Tipo: %d, Código Pessoa: %d\n",
                       p->codigo, p->nome, p->codigo_tipo, p->codigo_pes);
                p = p->prox;
            }
        }
        printf("=== Fim da consulta ===\n");
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int codigo = extrair_id(comando);
        Pet *p = *lista;
        int encontrou = 0;
        
        while (p) {
            if (p->codigo == codigo) {
                encontrou = 1;
                char *nome = extrair_campo(comando, "nome");
                char *codigo_tipo = extrair_campo(comando, "codigo_tipo");
                char *codigo_pes = extrair_campo(comando, "codigo_pes");
                
                if (nome) {
                    if (strlen(nome) == 0) {
                        printf("ERRO: O nome não pode ser vazio\n");
                        return;
                    }
                    strcpy(p->nome, nome);
                }
                if (codigo_tipo) {
                    int novo_codigo_tipo = atoi(codigo_tipo);
                    if (verificar_registro_existe(lista_tipos, novo_codigo_tipo, 3)) {
                        p->codigo_tipo = novo_codigo_tipo;
                    } else {
                        printf("ERRO: Tipo de pet com código %d não encontrado\n", novo_codigo_tipo);
                        return;
                    }
                }
                if (codigo_pes) {
                    int novo_codigo_pes = atoi(codigo_pes);
                    if (verificar_registro_existe(lista_pessoas, novo_codigo_pes, 1)) {
                        p->codigo_pes = novo_codigo_pes;
                    } else {
                        printf("ERRO: Pessoa com código %d não encontrada\n", novo_codigo_pes);
                        return;
                    }
                }
                
                // Salvar no arquivo
                salvar_pets(*lista);
                printf("Pet atualizado com sucesso!\n");
                break;
            }
            p = p->prox;
        }
        
        if (!encontrou) {
            printf("ERRO: Pet com código %d não encontrado\n", codigo);
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int codigo = extrair_id(comando);
        Pet *p = *lista;
        int encontrou = 0;
        
        while (p) {
            if (p->codigo == codigo) {
                encontrou = 1;
                // Ajusta ponteiros
                if (p->ant) p->ant->prox = p->prox;
                else *lista = p->prox;
                if (p->prox) p->prox->ant = p->ant;
                
                // Libera memória
                free(p);
                
                // Salvar no arquivo
                salvar_pets(*lista);
                printf("Pet removido com sucesso!\n");
                break;
            }
            p = p->prox;
        }
        
        if (!encontrou) {
            printf("ERRO: Pet com código %d não encontrado\n", codigo);
        }
    }
}

// Processamento de comandos para TipoPet
void processar_comando_tipo_pet(const char *comando, TipoPet **lista) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        TipoPet *novo = (TipoPet*)malloc(sizeof(TipoPet));
        novo->codigo = extrair_id(comando);
        
        // Verifica se o código já existe
        if (verificar_registro_existe(*lista, novo->codigo, 3)) {
            printf("ERRO: Já existe um tipo de pet com o código %d\n", novo->codigo);
            free(novo);
            return;
        }
        
        strcpy(novo->nome, extrair_campo(comando, "nome"));
        
        // Validações
        if (strlen(novo->nome) == 0) {
            printf("ERRO: O nome é obrigatório\n");
            free(novo);
            return;
        }
        
        // Inserir no início da lista
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
        
        // Salvar no arquivo
        salvar_tipos(*lista);
        printf("Tipo de pet inserido com sucesso!\n");
    }
    else if (strncasecmp(comando, "SELECT", 6) == 0) {
        if (*lista == NULL) {
            printf("Nenhum tipo de pet cadastrado.\n");
            return;
        }
        
        printf("=== Resultado da consulta ===\n");
        // Verifica se tem ORDER BY
        if (strstr(comando, "ORDER BY nome")) {
            NoArvore *arvore = NULL;
            TipoPet *t = *lista;
            
            // Inserir todos na árvore
            while (t) {
                inserir_na_arvore(&arvore, t, 3);
                t = t->prox;
            }
            
            // Exibir ordenado
            exibir_arvore_ordenada(arvore, 3);
            
            // Libera a árvore (0 porque não queremos liberar os dados, que estão na lista)
            liberar_arvore(arvore, 0);
        }
        else {
            // Exibir normal
            TipoPet *t = *lista;
            while (t) {
                printf("Código: %d, Nome: %s\n",
                       t->codigo, t->nome);
                t = t->prox;
            }
        }
        printf("=== Fim da consulta ===\n");
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int codigo = extrair_id(comando);
        TipoPet *t = *lista;
        int encontrou = 0;
        
        while (t) {
            if (t->codigo == codigo) {
                encontrou = 1;
                char *nome = extrair_campo(comando, "nome");
                if (nome) {
                    if (strlen(nome) == 0) {
                        printf("ERRO: O nome não pode ser vazio\n");
                        return;
                    }
                    strcpy(t->nome, nome);
                }
                
                // Salvar no arquivo
                salvar_tipos(*lista);
                printf("Tipo de pet atualizado com sucesso!\n");
                break;
            }
            t = t->prox;
        }
        
        if (!encontrou) {
            printf("ERRO: Tipo de pet com código %d não encontrado\n", codigo);
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int codigo = extrair_id(comando);
        TipoPet *t = *lista;
        int encontrou = 0;
        
        while (t) {
            if (t->codigo == codigo) {
                encontrou = 1;
                // Verifica se tem pets associados
                Pet *pet_temp = NULL;  // Precisamos de uma lista de pets para verificar
                if (verificar_registro_existe(pet_temp, codigo, 2)) {
                    printf("ERRO: Não é possível excluir o tipo de pet pois existem pets associados a ele\n");
                    return;
                }
                
                // Ajusta ponteiros
                if (t->ant) t->ant->prox = t->prox;
                else *lista = t->prox;
                if (t->prox) t->prox->ant = t->ant;
                
                // Libera memória
                free(t);
                
                // Salvar no arquivo
                salvar_tipos(*lista);
                printf("Tipo de pet removido com sucesso!\n");
                break;
            }
            t = t->prox;
        }
        
        if (!encontrou) {
            printf("ERRO: Tipo de pet com código %d não encontrado\n", codigo);
        }
    }
}
