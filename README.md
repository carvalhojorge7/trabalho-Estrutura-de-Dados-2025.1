# Interpretador de Comandos SQL

Este projeto implementa um interpretador de comandos SQL que manipula três tabelas específicas usando arquivos binários:

## Tabelas do Sistema

1. **Pessoas**
   - ID (inteiro)
   - Nome (texto)
   - CPF (texto)
   - Idade (inteiro)

2. **Pet**
   - ID (inteiro)
   - Nome (texto)
   - ID_Tipo (inteiro, referência para Tipo_Pet)
   - ID_Pessoa (inteiro, referência para Pessoas)

3. **Tipo_Pet**
   - ID (inteiro)
   - Descrição (texto)

## Comandos SQL Suportados

### 1. INSERT
```sql
INSERT INTO pessoas (id=1, nome=João Silva, cpf=123.456.789-00, idade=30);
INSERT INTO pet (id=1, nome=Rex, id_tipo=1, id_pessoa=1);
INSERT INTO tipo_pet (id=1, descricao=Cachorro);
```

### 2. SELECT
```sql
SELECT * FROM pessoas;
SELECT * FROM pessoas WHERE id=1;
SELECT * FROM pet WHERE id_pessoa=1;
```

### 3. UPDATE
```sql
UPDATE pessoas SET idade=31 WHERE id=1;
UPDATE pet SET nome=Max WHERE id=1;
```

### 4. DELETE
```sql
DELETE FROM pessoas WHERE id=1;
DELETE FROM pet WHERE id_pessoa=1;
```

## Estrutura dos Arquivos

O sistema utiliza três arquivos binários para armazenar os dados:
- `pessoas.bin`: Armazena registros da tabela Pessoas
- `pet.bin`: Armazena registros da tabela Pet
- `tipo_pet.bin`: Armazena registros da tabela Tipo_Pet

## Como Usar

1. Crie um arquivo de texto com os comandos SQL (ex: `comandos.txt`)
2. Execute o programa informando o nome do arquivo
3. O programa processará cada comando e mostrará os resultados
4. Os dados serão salvos nos arquivos .bin correspondentes

## Observações

- Os comandos devem seguir exatamente o formato especificado
- Cada linha deve conter apenas um comando
- Comentários podem ser feitos usando # no início da linha
- Os IDs são únicos em cada tabela
- Existe integridade referencial entre as tabelas (Pet referencia Pessoas e Tipo_Pet)
