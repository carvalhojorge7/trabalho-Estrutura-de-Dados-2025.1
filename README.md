# Sistema de Gerenciamento de Pets 🐾

Trabalho desenvolvido para a disciplina de Estrutura de Dados do curso de Engenharia da Computação do IFCE - Campus Fortaleza.

## 📋 Informações do Projeto

**Instituição:** Instituto Federal do Ceará - Campus Fortaleza  
**Departamento:** Telemática  
**Curso:** Engenharia da Computação  
**Disciplina:** Estrutura de Dados  
**Professor:** Ajalmar Rocha Neto, Dr.  
**Trabalho:** 2ª etapa (em dupla)  
**Aluno:** Jorge Lucas Silva de Carvalho  

## 📝 Descrição do Projeto

Sistema de gerenciamento de pets que implementa operações CRUD (Create, Read, Update, Delete) utilizando estruturas de dados em C. O sistema utiliza uma sintaxe similar a SQL para manipulação dos dados e implementa estruturas como listas duplamente encadeadas, filas e árvores binárias.

## 🏗️ Estruturas de Dados

### Pessoa
```c
struct Pessoa {
    int codigo;           // * Chave primária, único
    char nome[100];       // * Obrigatório
    char fone[20];        
    char endereco[200];   
    char data_nasc[11];   // * Formato: dd/mm/yyyy
};
```

### Tipo de Pet
```c
struct TipoPet {
    int codigo;           // * Chave primária, único
    char descricao[100];  // * Obrigatório
};
```

### Pet
```c
struct Pet {
    int codigo;           // * Chave primária, único
    int codigo_pes;       // * Chave estrangeira (Pessoa)
    char nome[100];       // * Obrigatório
    int codigo_tipo;      // * Chave estrangeira (TipoPet)
};
```

**Nota:** Campos marcados com * são obrigatórios.

## 🔍 Comandos Suportados

O sistema suporta os seguintes comandos SQL:

```sql
-- Inserção
insert into tabela1(campo1, campo2, campo3) values(valor1, valor2, valor3);

-- Atualização
update tabela1 set campo2 = valor2, campo3 = valor3 where campo1 = valor1;

-- Remoção
delete from tabela1 where campo1 = valor1;

-- Consulta
select * from tabela1 where campo1 = valor1 order by campo2;
```

### Exemplo de Script
```sql
insert into tipo_pet(codigo, descricao) values(1, 'cachorro');
insert into tipo_pet(codigo, descricao) values(2, 'gato');
insert into pessoa(codigo, nome, fone) values(1, 'joão', '859995566');
insert into pessoa(codigo, nome, fone, endereco) values(2, 'maria', '859996677', 'rua b, nr 202');
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(1,1, 'bilu', 2);
select * from pet where codigo = 3;
```

## ⚙️ Funcionalidades

1. **Entrada de Dados**
   - Leitura de comandos via arquivo
   - Leitura de comandos via entrada do usuário

2. **Validações**
   - Códigos únicos para pessoas, pets e tipos de pets
   - Integridade referencial entre tabelas
   - Campos obrigatórios
   - Regras de remoção para pessoas com pets

3. **Estruturas de Dados Utilizadas**
   - Listas duplamente encadeadas
   - Filas para processamento de comandos
   - Árvore binária para ordenação de resultados

4. **Persistência**
   - Armazenamento em arquivos
   - Consistência entre memória e arquivo

## 🚀 Como Executar

1. Clone o repositório
2. Compile o projeto usando o Makefile:
   ```bash
   make
   ```
3. Execute o programa:
   ```bash
   ./pet_system
   ```

## 📁 Organização do Código

- `src/` - Arquivos fonte (.c)
- `include/` - Arquivos de cabeçalho (.h)
- `data/` - Arquivos de dados
- `docs/` - Documentação adicional
- `schema.sql` - Estrutura do banco de dados

## 🤝 Contribuição

Este é um projeto acadêmico desenvolvido como parte da disciplina de Estrutura de Dados. Contribuições são bem-vindas através de pull requests.

## 📄 Licença

Este projeto é para fins educacionais.
