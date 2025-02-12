# Plano de Trabalho - Sistema de Gerenciamento de Pets

## 1. Implementação das Estruturas de Dados Fundamentais
### 1.1. Fila de Comandos
- [ ] Implementar struct NoComando com:
  - [ ] Campo para armazenar o comando SQL
  - [ ] Ponteiro para próximo comando
- [ ] Implementar struct FilaComandos com:
  - [ ] Ponteiro para início da fila
  - [ ] Ponteiro para fim da fila
  - [ ] Contador de elementos
- [ ] Implementar operações básicas da fila:
  - [ ] Criar fila
  - [ ] Inserir comando (enqueue)
  - [ ] Remover comando (dequeue)
  - [ ] Verificar se está vazia
  - [ ] Liberar fila

### 1.2. Árvore Binária para Ordenação
- [ ] Implementar struct NoArvore com:
  - [ ] Ponteiro para dados (void* para flexibilidade)
  - [ ] Ponteiros para filho esquerdo e direito
  - [ ] Campo para altura (balanceamento)
- [ ] Implementar operações da árvore:
  - [ ] Criar árvore
  - [ ] Inserir nó
  - [ ] Remover nó
  - [ ] Buscar elemento
  - [ ] Percurso em-ordem (para ordenação)
  - [ ] Balanceamento (se necessário)

## 2. Estruturas de Dados Auxiliares
- [ ] Implementar struct Pessoa
- [ ] Implementar struct TipoPet
- [ ] Implementar struct Pet
- [ ] Implementar struct Comando

## 3. Sistema de Processamento de Comandos
### 3.1. Leitura e Validação
- [ ] Implementar leitura de comandos do arquivo
- [ ] Implementar leitura de comandos do usuário
- [ ] Validar sintaxe dos comandos SQL
- [ ] Criar fila geral de comandos

### 3.2. Distribuição de Comandos
- [ ] Criar filas específicas para cada tipo (Pessoa, TipoPet, Pet)
- [ ] Implementar distribuidor de comandos para filas específicas
- [ ] Validar comandos antes da distribuição

## 4. Execução de Comandos
### 4.1. Operações Básicas
- [ ] Implementar INSERT
- [ ] Implementar DELETE
- [ ] Implementar UPDATE
- [ ] Implementar SELECT simples

### 4.2. Operações com Ordenação
- [ ] Implementar SELECT com ORDER BY usando árvore binária
- [ ] Implementar travessia da árvore para exibição ordenada

## 5. Persistência de Dados
- [ ] Implementar salvamento em arquivo para Pessoa
- [ ] Implementar salvamento em arquivo para TipoPet
- [ ] Implementar salvamento em arquivo para Pet
- [ ] Garantir consistência dos dados

## 6. Validações
- [ ] Validar códigos únicos
- [ ] Validar referências entre tabelas
- [ ] Validar campos obrigatórios
- [ ] Implementar regras de remoção de Pessoa com Pets

## 7. Interface com Usuário
- [ ] Implementar menu de opções
- [ ] Formatar saída dos comandos SELECT
- [ ] Implementar mensagens de erro
- [ ] Criar exemplos de uso

## 8. Testes e Documentação
- [ ] Testar operações da fila
- [ ] Testar operações da árvore
- [ ] Testar comandos SQL
- [ ] Documentar código
- [ ] Criar README

## Ordem Sugerida de Desenvolvimento
1. Implementar estrutura da fila de comandos (1.1)
2. Implementar estrutura da árvore binária (1.2)
3. Criar estruturas auxiliares (2)
4. Desenvolver sistema de processamento (3)
5. Implementar execução de comandos (4)
6. Adicionar persistência (5)
7. Implementar validações (6)
8. Desenvolver interface (7)
9. Realizar testes e documentação (8)

## Notas Importantes
- Foco principal nas estruturas de dados (fila e árvore)
- Testar cada estrutura isoladamente antes de integrar
- Manter o código organizado em módulos
- Documentar as funções durante o desenvolvimento
