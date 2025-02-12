# Interpretador de Comandos SQL para Arquivos Binários

Este projeto implementa um interpretador de comandos SQL que lê instruções de um arquivo texto e manipula arquivos binários correspondentes.

## Comandos Suportados

O sistema suporta as quatro operações básicas (CRUD):

1. **CREATE** - Inserção de dados:
```sql
insert into tabela values(valor1, valor2, ...);
```

2. **READ** - Consulta de dados:
```sql
select * from tabela;
select * from tabela where campo = valor;
```

3. **UPDATE** - Atualização de dados:
```sql
update tabela set campo = valor where campo = valor;
```

4. **DELETE** - Remoção de dados:
```sql
delete from tabela where campo = valor;
```

## Funcionamento

1. O programa recebe como entrada um arquivo `.txt` contendo comandos SQL
2. Para cada comando:
   - **INSERT**: Cria novo registro no arquivo binário
   - **SELECT**: Lê e exibe registros do arquivo binário
   - **UPDATE**: Modifica registros existentes
   - **DELETE**: Remove registros do arquivo

3. Formato do arquivo binário:
   - Para cada registro:
     * Tamanho dos dados (inteiro)
     * Dados brutos (bytes)
     * Flag de registro ativo/removido

## Exemplo

Arquivo `comandos.txt`:
```sql
insert into vinho values(1, 'Cabernet', 2020, 89.90);
select * from vinho where ano = 2020;
update vinho set preco = 99.90 where id = 1;
delete from vinho where id = 1;
```

## Compilação e Execução

1. Compile o projeto:
```bash
make
```

2. Execute o programa:
```bash
./programa
```

3. Digite o nome do arquivo de comandos quando solicitado:
```
Digite o nome do arquivo de comandos (.txt): comandos.txt
```

## Estrutura do Projeto

- `main.c`: Programa principal
- `estruturas.h`: Definição das estruturas de dados
- `comandos.c`: Processamento dos comandos SQL
- `registros.c`: Manipulação dos arquivos binários
- `comandos.txt`: Arquivo de exemplo com comandos SQL
