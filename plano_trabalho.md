# Plano de Trabalho - Sistema de Gerenciamento de Pets

## 1. Modelagem do Banco de Dados
- [ ] 1.1. Criar arquivo schema.sql com:
  - [ ] Criação da tabela Pessoa (CREATE TABLE)
  - [ ] Criação da tabela Tipo_Pet (CREATE TABLE)
  - [ ] Criação da tabela Pet (CREATE TABLE)
  - [ ] Definição das chaves primárias
  - [ ] Definição das chaves estrangeiras
  - [ ] Definição das constraints de campos obrigatórios
  - [ ] Definição das constraints de unicidade
- [ ] 1.2. Documentar estrutura do banco
- [ ] 1.3. Criar queries de exemplo para testes

## 2. Configuração Inicial
- [ ] 2.1. Criar estrutura de diretórios do projeto
- [ ] 2.2. Configurar arquivo makefile
- [ ] 2.3. Criar arquivos de cabeçalho (.h) iniciais
- [ ] 2.4. Configurar .gitignore (se usar git)

## 3. Implementação das Estruturas Básicas
### 3.1. Estruturas de Dados
- [ ] Definir struct Pessoa (pessoa.h)
- [ ] Definir struct Tipo_Pet (tipo_pet.h)
- [ ] Definir struct Pet (pet.h)
- [ ] Definir struct Comando (comando.h)

### 3.2. Lista Duplamente Encadeada
- [ ] Implementar estrutura base da lista
- [ ] Implementar funções de inserção
- [ ] Implementar funções de remoção
- [ ] Implementar funções de busca
- [ ] Implementar funções de ordenação

## 4. Sistema de Persistência
- [ ] 4.1. Implementar funções de leitura de arquivo para Pessoa
- [ ] 4.2. Implementar funções de escrita de arquivo para Pessoa
- [ ] 4.3. Implementar funções de leitura de arquivo para Tipo_Pet
- [ ] 4.4. Implementar funções de escrita de arquivo para Tipo_Pet
- [ ] 4.5. Implementar funções de leitura de arquivo para Pet
- [ ] 4.6. Implementar funções de escrita de arquivo para Pet

## 5. Processamento de Comandos
### 5.1. Parser de Comandos
- [ ] Implementar função de parsing de comandos SQL
- [ ] Implementar validação de sintaxe
- [ ] Implementar extração de parâmetros

### 5.2. Filas de Comandos
- [ ] Implementar fila geral de comandos
- [ ] Implementar fila específica para Pessoa
- [ ] Implementar fila específica para Tipo_Pet
- [ ] Implementar fila específica para Pet
- [ ] Implementar distribuidor de comandos para filas específicas

## 6. Operações CRUD
### 6.1. Pessoa
- [ ] Implementar INSERT
- [ ] Implementar SELECT
- [ ] Implementar UPDATE
- [ ] Implementar DELETE
- [ ] Implementar validações específicas

### 6.2. Tipo_Pet
- [ ] Implementar INSERT
- [ ] Implementar SELECT
- [ ] Implementar UPDATE
- [ ] Implementar DELETE
- [ ] Implementar validações específicas

### 6.3. Pet
- [ ] Implementar INSERT
- [ ] Implementar SELECT
- [ ] Implementar UPDATE
- [ ] Implementar DELETE
- [ ] Implementar validações específicas

## 7. Estruturas de Dados Auxiliares
- [ ] 7.1. Implementar Árvore Binária para ordenação
- [ ] 7.2. Implementar funções de balanceamento
- [ ] 7.3. Implementar funções de travessia

## 8. Validações e Regras de Negócio
- [ ] 8.1. Implementar validação de códigos únicos
- [ ] 8.2. Implementar validação de referências (foreign keys)
- [ ] 8.3. Implementar regras de remoção de Pessoa com Pets
- [ ] 8.4. Implementar validação de campos obrigatórios

## 9. Interface com Usuário
- [ ] 9.1. Implementar leitura de comandos via arquivo
- [ ] 9.2. Implementar leitura de comandos via entrada do usuário
- [ ] 9.3. Implementar formatação de saída para SELECT
- [ ] 9.4. Implementar mensagens de erro amigáveis

## 10. Testes
- [ ] 10.1. Criar casos de teste para cada operação CRUD
- [ ] 10.2. Criar casos de teste para validações
- [ ] 10.3. Criar casos de teste para persistência
- [ ] 10.4. Testar casos de erro

## 11. Documentação
- [ ] 11.1. Documentar funções e estruturas
- [ ] 11.2. Criar README com instruções de compilação
- [ ] 11.3. Documentar formato dos arquivos de persistência
- [ ] 11.4. Criar exemplos de uso

## Ordem Sugerida de Desenvolvimento
1. Começar com as estruturas básicas (3.1)
2. Implementar lista duplamente encadeada (3.2)
3. Desenvolver sistema de persistência (4)
4. Implementar parser de comandos (5.1)
5. Desenvolver filas de comandos (5.2)
6. Implementar operações CRUD (6)
7. Adicionar estruturas auxiliares (7)
8. Implementar validações (8)
9. Desenvolver interface com usuário (9)
10. Realizar testes (10)
11. Finalizar documentação (11)

## Notas Importantes
- Manter testes durante todo o desenvolvimento
- Implementar validações junto com cada funcionalidade
- Documentar código durante o desenvolvimento
- Testar persistência frequentemente para evitar perda de dados
