# Instituto Federal do Ceará - Campus Fortaleza
## Departamento de Telemática
### Curso: Engenharia da Computação
### Disciplina: Estrutura de Dados
### Professor: Ajalmar Rocha Neto, Dr.
### Trabalho 2 – 2ª etapa (em dupla)
### Aluno: Jorge Lucas Silva de Carvalho

## Descrição do Trabalho

### Estruturas de Dados

Considere as seguintes estruturas:

1. **Struct Pessoa**
   - Campos: código, nome, fone, data_nascimento, endereco
   - Exemplo: `(1, 'joão', '85 999 55 66', '04/10/2002')`

2. **Struct Tipo_de_Pet**
   - Campos: código e descricao
   - Exemplo: `(1, 'cachorro')`

3. **Struct Pet**
   - Campos: código, código_cli, nome, código_tipo
   - Exemplo: `(1, 1, 'bilu', 'gato')` ou `(2, 1, 'brother', 1)`

### Comandos

A fila de comandos utiliza nós do tipo `struct comando` (contendo pelo menos o campo descrição). Os comandos seguem o formato:

```sql
insert into tabela1(campo1, campo1, campo1) values(valor1, valor2, valor3);
update tabela1 set campo2 = valor2, campo3 = valor3 where campo1 = valor1;
delete from tabela1 where campo1 = valor1;
select * from tabela1 where campo1 = valor1 order by campo2;
```

### Exemplo de Script

```sql
insert into tipo_pet(codigo, descricao) values(1, 'cachorro');
insert into tipo_pet(codigo, descricao) values(2, 'gato');
insert into pessoa(codigo, nome, fone) values(1, 'joão', '859995566');
insert into pessoa(codigo, nome, fone, endereco) values(2, 'maria', '859996677', 'rua b, nr 202');
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(1,1, 'bilu', 2);
insert into pessoa(codigo, nome, fone, data_nascimento) values(3, josé, '859997788', '04/10/2001');
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(2,1, 'brother', 1);
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(3,2, 'minie', 1);
select * from pet where codigo = 3;
delete from pet where codigo = 3;
select * from pet order by nome;
```

## Requisitos do Programa

### Estruturas de Dados Requeridas

#### Pessoa
- código* (único)
- nome*
- fone
- endereço
- data nascimento* (dd/mm/yyyy)

#### Tipo_Pet
- código* (único)
- nome*

#### Pet
- código* (único)
- código_pes* (deve ser um código válido de pessoa)
- nome*
- codigo_tipo*

**Nota:** Campos marcados com * são obrigatórios.

### Funcionalidades Obrigatórias

1. Leitura do script via arquivo ou entrada do usuário
2. Validações:
   - Códigos únicos para pessoas, pets e tipos de pets
   - Código_pes deve referenciar uma pessoa cadastrada
   - Código_tipo deve referenciar um tipo_pet cadastrado
   - Pessoa com pet não pode ser removida sem tratar seus pets

3. Organização do Código:
   - Funcionalidades de pessoa em arquivos .c e .h separados
   - Funcionalidades de tipo_pet e pet em arquivos separados
   - Arquivo principal (main.c) para integração

4. Processamento:
   - Validação de comandos
   - Separação em filas específicas
   - Uso de listas duplamente encadeadas
   - Persistência em arquivos
   - Árvore binária para comandos select com order by