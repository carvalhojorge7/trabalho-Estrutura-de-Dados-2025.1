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

// Função genérica para verificar existência de registro
int verificar_registro_existe(void *lista, int id, TipoRegistro tipo) {
    void *atual = lista;
    
    while (atual) {
        int id_atual;
        void *prox;
        
        switch (tipo) {
            case TIPO_PESSOA:
                id_atual = ((Pessoa*)atual)->id;
                prox = ((Pessoa*)atual)->prox;
                break;
            case TIPO_PET:
                id_atual = ((Pet*)atual)->id;
                prox = ((Pet*)atual)->prox;
                break;
            case TIPO_TIPO_PET:
                id_atual = ((TipoPet*)atual)->id;
                prox = ((TipoPet*)atual)->prox;
                break;
            default:
                return 0;
        }
        
        if (id_atual == id) return 1;
        atual = prox;
    }
    
    return 0;
}

// Processamento de comandos para Pessoa
void processar_comando_pessoa(const char *comando, Pessoa **lista) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        Pessoa *nova = (Pessoa*)malloc(sizeof(Pessoa));
        nova->id = extrair_id(comando);
        strcpy(nova->nome, extrair_campo(comando, "nome"));
        strcpy(nova->cpf, extrair_campo(comando, "cpf"));
        nova->idade = atoi(extrair_campo(comando, "idade"));
        
        // Inserir no início da lista
        nova->prox = *lista;
        nova->ant = NULL;
        if (*lista) (*lista)->ant = nova;
        *lista = nova;
        
        printf("Pessoa inserida com sucesso!\n");
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
            // TODO: Liberar árvore
        }
        else {
            // Exibir normal
            Pessoa *p = *lista;
            while (p) {
                printf("ID: %d, Nome: %s, CPF: %s, Idade: %d\n",
                       p->id, p->nome, p->cpf, p->idade);
                p = p->prox;
            }
        }
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int id = extrair_id(comando);
        Pessoa *p = *lista;
        
        while (p) {
            if (p->id == id) {
                char *nome = extrair_campo(comando, "nome");
                char *cpf = extrair_campo(comando, "cpf");
                char *idade = extrair_campo(comando, "idade");
                
                if (nome) strcpy(p->nome, nome);
                if (cpf) strcpy(p->cpf, cpf);
                if (idade) p->idade = atoi(idade);
                
                printf("Pessoa atualizada com sucesso!\n");
                break;
            }
            p = p->prox;
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int id = extrair_id(comando);
        Pessoa *p = *lista;
        
        while (p) {
            if (p->id == id) {
                // Ajusta ponteiros
                if (p->ant) p->ant->prox = p->prox;
                else *lista = p->prox;
                
                if (p->prox) p->prox->ant = p->ant;
                
                free(p);
                printf("Pessoa removida com sucesso!\n");
                break;
            }
            p = p->prox;
        }
    }
}

// Processamento de comandos para Pet
void processar_comando_pet(const char *comando, Pet **lista, Pessoa *lista_pessoas, TipoPet *lista_tipos) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        int id_pessoa = extrair_id_ref(comando, "id_pessoa");
        int id_tipo = extrair_id_ref(comando, "id_tipo");
        
        // Verifica integridade referencial
        if (!verificar_registro_existe(lista_pessoas, id_pessoa, TIPO_PESSOA)) {
            printf("Erro: Pessoa não encontrada!\n");
            return;
        }
        if (!verificar_registro_existe(lista_tipos, id_tipo, TIPO_TIPO_PET)) {
            printf("Erro: Tipo de pet não encontrado!\n");
            return;
        }
        
        Pet *novo = (Pet*)malloc(sizeof(Pet));
        novo->id = extrair_id(comando);
        strcpy(novo->nome, extrair_campo(comando, "nome"));
        novo->id_tipo = id_tipo;
        novo->id_pessoa = id_pessoa;
        
        // Inserir no início da lista
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
        
        printf("Pet inserido com sucesso!\n");
    }
    else if (strncasecmp(comando, "SELECT", 6) == 0) {
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
            // TODO: Liberar árvore
        }
        else {
            // Exibir normal
            Pet *p = *lista;
            while (p) {
                printf("ID: %d, Nome: %s, ID_Tipo: %d, ID_Pessoa: %d\n",
                       p->id, p->nome, p->id_tipo, p->id_pessoa);
                p = p->prox;
            }
        }
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int id = extrair_id(comando);
        Pet *p = *lista;
        
        while (p) {
            if (p->id == id) {
                char *nome = extrair_campo(comando, "nome");
                char *id_tipo = extrair_campo(comando, "id_tipo");
                char *id_pessoa = extrair_campo(comando, "id_pessoa");
                
                if (nome) strcpy(p->nome, nome);
                if (id_tipo) {
                    int novo_id_tipo = atoi(id_tipo);
                    if (verificar_registro_existe(lista_tipos, novo_id_tipo, TIPO_TIPO_PET)) {
                        p->id_tipo = novo_id_tipo;
                    } else {
                        printf("Erro: Tipo de pet não encontrado!\n");
                    }
                }
                if (id_pessoa) {
                    int novo_id_pessoa = atoi(id_pessoa);
                    if (verificar_registro_existe(lista_pessoas, novo_id_pessoa, TIPO_PESSOA)) {
                        p->id_pessoa = novo_id_pessoa;
                    } else {
                        printf("Erro: Pessoa não encontrada!\n");
                    }
                }
                
                printf("Pet atualizado com sucesso!\n");
                break;
            }
            p = p->prox;
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int id = extrair_id(comando);
        Pet *p = *lista;
        
        while (p) {
            if (p->id == id) {
                // Ajusta ponteiros
                if (p->ant) p->ant->prox = p->prox;
                else *lista = p->prox;
                
                if (p->prox) p->prox->ant = p->ant;
                
                free(p);
                printf("Pet removido com sucesso!\n");
                break;
            }
            p = p->prox;
        }
    }
}

// Processamento de comandos para TipoPet
void processar_comando_tipo_pet(const char *comando, TipoPet **lista) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        TipoPet *novo = (TipoPet*)malloc(sizeof(TipoPet));
        novo->id = extrair_id(comando);
        strcpy(novo->descricao, extrair_campo(comando, "descricao"));
        
        // Inserir no início da lista
        novo->prox = *lista;
        novo->ant = NULL;
        if (*lista) (*lista)->ant = novo;
        *lista = novo;
        
        printf("Tipo de pet inserido com sucesso!\n");
    }
    else if (strncasecmp(comando, "SELECT", 6) == 0) {
        // Verifica se tem ORDER BY
        if (strstr(comando, "ORDER BY descricao")) {
            NoArvore *arvore = NULL;
            TipoPet *t = *lista;
            
            // Inserir todos na árvore
            while (t) {
                inserir_na_arvore(&arvore, t, 3);
                t = t->prox;
            }
            
            // Exibir ordenado
            exibir_arvore_ordenada(arvore, 3);
            // TODO: Liberar árvore
        }
        else {
            // Exibir normal
            TipoPet *t = *lista;
            while (t) {
                printf("ID: %d, Descrição: %s\n",
                       t->id, t->descricao);
                t = t->prox;
            }
        }
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        int id = extrair_id(comando);
        TipoPet *t = *lista;
        
        while (t) {
            if (t->id == id) {
                char *descricao = extrair_campo(comando, "descricao");
                if (descricao) strcpy(t->descricao, descricao);
                
                printf("Tipo de pet atualizado com sucesso!\n");
                break;
            }
            t = t->prox;
        }
    }
    else if (strncasecmp(comando, "DELETE", 6) == 0) {
        int id = extrair_id(comando);
        TipoPet *t = *lista;
        
        while (t) {
            if (t->id == id) {
                // Ajusta ponteiros
                if (t->ant) t->ant->prox = t->prox;
                else *lista = t->prox;
                
                if (t->prox) t->prox->ant = t->ant;
                
                free(t);
                printf("Tipo de pet removido com sucesso!\n");
                break;
            }
            t = t->prox;
        }
    }
}
