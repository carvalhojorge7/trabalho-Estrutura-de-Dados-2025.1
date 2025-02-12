# Plano de Trabalho

## Objetivo
Desenvolver um interpretador de comandos SQL que lê instruções de um arquivo texto e manipula arquivos binários, suportando todas as operações CRUD (Create, Read, Update, Delete).

## Etapas Concluídas

### 1. Estruturas Básicas
- [x] Definição da estrutura Registro (dados + tamanho)
- [x] Definição das estruturas de fila para comandos
- [x] Implementação das funções de manipulação da fila

### 2. Processamento de Comandos
- [x] Leitura de arquivo .txt
- [x] Parser para comandos SQL
  - [x] INSERT (Create)
  - [x] SELECT (Read)
  - [x] UPDATE (Update)
  - [x] DELETE (Delete)
- [x] Extração de nome da tabela
- [x] Extração de valores e condições

### 3. Manipulação de Arquivos
- [x] Criação de arquivos binários
- [x] Salvamento de registros
- [x] Formato binário otimizado (tamanho + dados + flag)
- [x] Busca de registros por condição
- [x] Atualização de registros existentes
- [x] Remoção lógica de registros
