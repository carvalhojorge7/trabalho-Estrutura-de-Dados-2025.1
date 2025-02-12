# Plano de Trabalho

## Objetivo
Implementar um interpretador de comandos SQL que manipule três tabelas específicas (Pessoas, Pet e Tipo_Pet) usando arquivos binários.

## Etapas do Desenvolvimento

### 1. Estruturas de Dados
- [x] Definir estrutura para Pessoas (id, nome, cpf, idade)
- [x] Definir estrutura para Pet (id, nome, id_tipo, id_pessoa)
- [x] Definir estrutura para Tipo_Pet (id, descricao)
- [x] Definir estrutura para comandos SQL

### 2. Processamento de Comandos
- [ ] Implementar parser para comandos INSERT
  - [ ] Extrair nome da tabela
  - [ ] Extrair campos e valores
  - [ ] Validar campos obrigatórios
  - [ ] Validar tipos de dados

- [ ] Implementar parser para comandos SELECT
  - [ ] Extrair nome da tabela
  - [ ] Extrair condições WHERE
  - [ ] Suportar SELECT *
  - [ ] Formatar saída dos dados

- [ ] Implementar parser para comandos UPDATE
  - [ ] Extrair nome da tabela
  - [ ] Extrair campos e valores do SET
  - [ ] Extrair condições WHERE
  - [ ] Validar campos existentes

- [ ] Implementar parser para comandos DELETE
  - [ ] Extrair nome da tabela
  - [ ] Extrair condições WHERE
  - [ ] Validar integridade referencial

### 3. Manipulação de Arquivos Binários
- [ ] Implementar gravação de registros
  - [ ] Criar arquivo se não existir
  - [ ] Adicionar novo registro ao final
  - [ ] Validar IDs únicos

- [ ] Implementar leitura de registros
  - [ ] Ler registro por registro
  - [ ] Aplicar filtros WHERE
  - [ ] Ignorar registros deletados

- [ ] Implementar atualização de registros
  - [ ] Localizar registro pelo ID
  - [ ] Atualizar campos específicos
  - [ ] Manter outros campos inalterados

- [ ] Implementar remoção de registros
  - [ ] Marcar registro como deletado
  - [ ] Verificar referências antes de deletar
  - [ ] Manter integridade referencial

### 4. Interface com Usuário
- [ ] Implementar menu principal
- [ ] Ler arquivo de comandos
- [ ] Exibir resultados formatados
- [ ] Tratar erros e exceções

### 5. Testes e Documentação
- [ ] Criar arquivo de comandos de teste
- [ ] Testar todas as operações CRUD
- [ ] Testar integridade referencial
- [ ] Documentar formato dos comandos

## Próximos Passos
1. Implementar estruturas de dados básicas
2. Criar função de leitura do arquivo de comandos
3. Implementar parser de comandos INSERT
4. Implementar gravação em arquivo binário
