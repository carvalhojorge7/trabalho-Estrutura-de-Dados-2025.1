#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
#include <ctype.h>

// Funções auxiliares para extrair informações dos comandos
int extrair_id(const char *comando) {
    const char *pos = strstr(comando, "codigo=");
    if (pos) {
        pos += 7; // Pula "codigo="
        return atoi(pos);
    }
    return -1;
}

// Extrai o ID de referência (após o =)
int extrair_id_ref(const char *comando, const char *campo) {
    char busca[50];
    sprintf(busca, "%s=", campo);
    const char *pos = strstr(comando, busca);
    if (pos) {
        pos += strlen(busca);
        return atoi(pos);
    }
    return -1;
}

// Extrai um campo específico do comando
char *extrair_campo(const char *comando, const char *campo) {
    static char valor[100];
    char busca[50];
    sprintf(busca, "%s=", campo);
    
    const char *inicio = strstr(comando, busca);
    if (inicio) {
        inicio += strlen(busca);
        
        // Se o valor começa com aspas, procura o fechamento
        if (*inicio == '"') {
            inicio++;
            const char *fim = strchr(inicio, '"');
            if (fim) {
                strncpy(valor, inicio, fim - inicio);
                valor[fim - inicio] = '\0';
                return valor;
            }
        }
        
        // Se o valor começa com parênteses, procura o fechamento
        if (*inicio == '(') {
            const char *fim = strchr(inicio, ')');
            if (fim) {
                // Se há mais conteúdo após o parêntese (como em (85)99999-9999)
                if (*(fim + 1) != ',' && *(fim + 1) != ';') {
                    fim = strpbrk(fim, ",;");
                    if (!fim) fim = inicio + strlen(inicio);
                }
                strncpy(valor, inicio, fim - inicio);
                valor[fim - inicio] = '\0';
                return valor;
            }
        }
        
        // Caso contrário, copia até a vírgula ou parêntese de fechamento
        const char *fim = strpbrk(inicio, ",);");
        if (fim) {
            strncpy(valor, inicio, fim - inicio);
            valor[fim - inicio] = '\0';
        } else {
            strcpy(valor, inicio);
        }
        return valor;
    }
    return "";
}

// Extrai campo e valor de um comando UPDATE
int extrair_campo_valor(const char *comando, char *campo, char *valor) {
    const char *set = strcasestr(comando, "SET");
    if (!set) return -1;
    
    const char *where = strcasestr(comando, "WHERE");
    if (!where) return -1;
    
    // Pula o SET e espaços
    set += 3;
    while (*set == ' ') set++;
    
    // Copia o campo até o =
    const char *igual = strchr(set, '=');
    if (!igual) return -1;
    
    strncpy(campo, set, igual - set);
    campo[igual - set] = '\0';
    
    // Remove espaços do final do campo
    char *fim = campo + strlen(campo) - 1;
    while (fim > campo && *fim == ' ') fim--;
    *(fim + 1) = '\0';
    
    // Pula o = e espaços
    igual++;
    while (*igual == ' ') igual++;
    
    // Copia o valor até o WHERE
    strncpy(valor, igual, where - igual);
    valor[where - igual] = '\0';
    
    // Remove espaços do final do valor
    fim = valor + strlen(valor) - 1;
    while (fim > valor && *fim == ' ') fim--;
    *(fim + 1) = '\0';
    
    return 0;
}

// Função auxiliar para comparação case-insensitive
char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    
    for (; *haystack; haystack++) {
        if (toupper(*haystack) == toupper(*needle)) {
            const char *h = haystack, *n = needle;
            while (*h && *n && toupper(*h) == toupper(*n)) {
                h++;
                n++;
            }
            if (!*n) return (char*)haystack;
        }
    }
    return NULL;
}

// Funções de busca
Pessoa *buscar_pessoa(Pessoa *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

Pet *buscar_pet(Pet *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

TipoPet *buscar_tipo_pet(TipoPet *lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo)
            return lista;
        lista = lista->prox;
    }
    return NULL;
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
                inserir_pessoa(&arvore, p);
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
                printf("Codigo: %d, Nome: %s, Fone: %s, Endereco: %s, Data Nasc.: %s\n",
                       p->codigo, p->nome, p->fone, p->endereco, p->data_nasc);
                p = p->prox;
            }
        }
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        processar_update(comando, (void **)lista, 1);
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

// Processamento de comandos para TipoPet
void processar_comando_tipo_pet(const char *comando, TipoPet **lista) {
    if (strncasecmp(comando, "INSERT", 6) == 0) {
        TipoPet *novo = (TipoPet*)malloc(sizeof(TipoPet));
        novo->codigo = extrair_id(comando);
        
        // Verifica se o código já existe
        if (verificar_registro_existe(*lista, novo->codigo, 3)) {
            printf("ERRO: Ja existe um tipo de pet com o codigo %d\n", novo->codigo);
            free(novo);
            return;
        }
        
        strcpy(novo->nome, extrair_campo(comando, "nome"));
        
        // Validações
        if (strlen(novo->nome) == 0) {
            printf("ERRO: O nome e obrigatorio\n");
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
                inserir_tipo_pet(&arvore, t);
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
                printf("Codigo: %d, Nome: %s\n",
                       t->codigo, t->nome);
                t = t->prox;
            }
        }
        printf("=== Fim da consulta ===\n");
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        processar_update(comando, (void **)lista, 3);
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
                    printf("ERRO: Nao e possivel excluir o tipo de pet pois existem pets associados a ele\n");
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
            printf("ERRO: Tipo de pet com codigo %d nao encontrado\n", codigo);
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
            printf("ERRO: Ja existe um pet com o codigo %d\n", novo->codigo);
            free(novo);
            return;
        }
        
        strcpy(novo->nome, extrair_campo(comando, "nome"));
        novo->codigo_tipo = extrair_id_ref(comando, "codigo_tipo");
        novo->codigo_pes = extrair_id_ref(comando, "codigo_pes");
        
        // Validações
        if (strlen(novo->nome) == 0) {
            printf("ERRO: O nome e obrigatorio\n");
            free(novo);
            return;
        }
        
        // Verifica integridade referencial
        if (!verificar_registro_existe(lista_pessoas, novo->codigo_pes, 1)) {
            printf("ERRO: Pessoa com codigo %d nao encontrada\n", novo->codigo_pes);
            free(novo);
            return;
        }
        if (!verificar_registro_existe(lista_tipos, novo->codigo_tipo, 3)) {
            printf("ERRO: Tipo de pet com codigo %d nao encontrado\n", novo->codigo_tipo);
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
                inserir_pet(&arvore, p);
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
                printf("Codigo: %d, Nome: %s, Codigo Tipo: %d, Codigo Pessoa: %d\n",
                       p->codigo, p->nome, p->codigo_tipo, p->codigo_pes);
                p = p->prox;
            }
        }
        printf("=== Fim da consulta ===\n");
    }
    else if (strncasecmp(comando, "UPDATE", 6) == 0) {
        processar_update(comando, (void **)lista, 2);
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
            printf("ERRO: Pet com codigo %d nao encontrado\n", codigo);
        }
    }
}

// Processa comando UPDATE
void processar_update(const char *comando, void **lista, int tipo) {
    char campo[100], valor[200];
    int codigo;
    
    // Extrai o código
    codigo = extrair_id(comando);
    if (codigo == -1) {
        printf("ERRO: Codigo invalido no comando UPDATE\n");
        return;
    }
    
    // Extrai o campo e valor
    if (extrair_campo_valor(comando, campo, valor) != 0) {
        printf("ERRO: Formato invalido no comando UPDATE\n");
        return;
    }
    
    // Remove aspas do valor se existirem
    if (valor[0] == '"') {
        memmove(valor, valor + 1, strlen(valor));
        if (valor[strlen(valor) - 1] == '"') {
            valor[strlen(valor) - 1] = '\0';
        }
    }
    
    if (tipo == 1) {  // Pessoa
        Pessoa *p = buscar_pessoa(*lista, codigo);
        if (!p) {
            printf("ERRO: Pessoa com codigo %d nao encontrada\n", codigo);
            return;
        }
        if (strcmp(campo, "nome") == 0)
            strcpy(p->nome, valor);
        else if (strcmp(campo, "fone") == 0)
            strcpy(p->fone, valor);
        else if (strcmp(campo, "endereco") == 0)
            strcpy(p->endereco, valor);
        else if (strcmp(campo, "data_nasc") == 0)
            strcpy(p->data_nasc, valor);
        else {
            printf("ERRO: Campo invalido para UPDATE em pessoa\n");
            return;
        }
        salvar_pessoas(*lista);
    }
    else if (tipo == 2) {  // Pet
        Pet *p = buscar_pet(*lista, codigo);
        if (!p) {
            printf("ERRO: Pet com codigo %d nao encontrado\n", codigo);
            return;
        }
        if (strcmp(campo, "nome") == 0)
            strcpy(p->nome, valor);
        else if (strcmp(campo, "codigo_tipo") == 0)
            p->codigo_tipo = atoi(valor);
        else if (strcmp(campo, "codigo_pes") == 0)
            p->codigo_pes = atoi(valor);
        else {
            printf("ERRO: Campo invalido para UPDATE em pet\n");
            return;
        }
        salvar_pets(*lista);
    }
    else if (tipo == 3) {  // TipoPet
        TipoPet *t = buscar_tipo_pet(*lista, codigo);
        if (!t) {
            printf("ERRO: Tipo de pet com codigo %d nao encontrado\n", codigo);
            return;
        }
        if (strcmp(campo, "nome") == 0)
            strcpy(t->nome, valor);
        else {
            printf("ERRO: Campo invalido para UPDATE em tipo_pet\n");
            return;
        }
        salvar_tipos(*lista);
    }
}

// Processa comando INSERT para pessoas
void processar_insert_pessoa(const char *comando, NoArvore **raiz) {
    Pessoa *p = extrair_dados_pessoa(comando);
    if (p != NULL) {
        Pessoa *lista_temp = arvore_para_lista_pessoas(*raiz);
        if (buscar_pessoa(lista_temp, p->codigo) != NULL) {
            printf("ERRO: Ja existe uma pessoa com o codigo %d\n", p->codigo);
            free(p);
            return;
        }
        inserir_pessoa(raiz, p);
        printf("Pessoa inserida com sucesso!\n");
        lista_temp = arvore_para_lista_pessoas(*raiz);
        salvar_pessoas(lista_temp);
    }
}

// Processa comando INSERT para pets
void processar_insert_pet(const char *comando, NoArvore **raiz, NoArvore *pessoas) {
    Pet *p = extrair_dados_pet(comando);
    if (p != NULL) {
        // Verifica se já existe um pet com o mesmo código
        Pet *lista_temp = arvore_para_lista_pets(*raiz);
        if (buscar_pet(lista_temp, p->codigo) != NULL) {
            printf("ERRO: Ja existe um pet com o codigo %d\n", p->codigo);
            free(p);
            return;
        }
        // Verifica se a pessoa existe
        Pessoa *lista_pessoas_temp = arvore_para_lista_pessoas(pessoas);
        if (buscar_pessoa(lista_pessoas_temp, p->codigo_pes) == NULL) {
            printf("ERRO: Pessoa com codigo %d nao encontrada\n", p->codigo_pes);
            free(p);
            return;
        }
        inserir_pet(raiz, p);
        printf("Pet inserido com sucesso!\n");
        // Converte a árvore em uma lista e salva
        lista_temp = arvore_para_lista_pets(*raiz);
        salvar_pets(lista_temp);
    }
}

// Processa comando INSERT para tipos de pet
void processar_insert_tipo_pet(const char *comando, NoArvore **raiz) {
    TipoPet *t = extrair_dados_tipo_pet(comando);
    if (t != NULL) {
        // Verifica se já existe um tipo de pet com o mesmo código
        TipoPet *lista_temp = arvore_para_lista_tipos(*raiz);
        if (buscar_tipo_pet(lista_temp, t->codigo) != NULL) {
            printf("ERRO: Ja existe um tipo de pet com o codigo %d\n", t->codigo);
            free(t);
            return;
        }
        inserir_tipo_pet(raiz, t);
        printf("Tipo de pet inserido com sucesso!\n");
        // Converte a árvore em uma lista e salva
        lista_temp = arvore_para_lista_tipos(*raiz);
        salvar_tipos(lista_temp);
    }
}

// Funções para extrair dados dos comandos
Pessoa *extrair_dados_pessoa(const char *comando) {
    Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
    p->codigo = extrair_id(comando);
    strcpy(p->nome, extrair_campo(comando, "nome"));
    strcpy(p->fone, extrair_campo(comando, "fone"));
    strcpy(p->endereco, extrair_campo(comando, "endereco"));
    strcpy(p->data_nasc, extrair_campo(comando, "data_nasc"));
    return p;
}

Pet *extrair_dados_pet(const char *comando) {
    Pet *p = (Pet*)malloc(sizeof(Pet));
    p->codigo = extrair_id(comando);
    strcpy(p->nome, extrair_campo(comando, "nome"));
    p->codigo_tipo = extrair_id_ref(comando, "codigo_tipo");
    p->codigo_pes = extrair_id_ref(comando, "codigo_pes");
    return p;
}

TipoPet *extrair_dados_tipo_pet(const char *comando) {
    TipoPet *t = (TipoPet*)malloc(sizeof(TipoPet));
    t->codigo = extrair_id(comando);
    strcpy(t->nome, extrair_campo(comando, "nome"));
    return t;
}
