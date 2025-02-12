# Sistema de Gerenciamento de Pets 

Trabalho desenvolvido para a disciplina de Estrutura de Dados do curso de Engenharia da Computação do IFCE - Campus Fortaleza.

## Informações do Projeto

**Instituição:** Instituto Federal do Ceará - Campus Fortaleza  
**Departamento:** Telemática  
**Curso:** Engenharia da Computação  
**Disciplina:** Estrutura de Dados  
**Professor:** Ajalmar Rocha Neto, Dr.  
**Trabalho:** 2ª etapa (em dupla)  
**Aluno:** Jorge Lucas Silva de Carvalho  

## Descrição do Projeto

Sistema de processamento de comandos SQL para gerenciamento de pets utilizando estruturas de dados avançadas em C. O sistema implementa uma fila de comandos para processamento sequencial e uma árvore binária para ordenação dos resultados.

## Estruturas de Dados Implementadas

### 1. Fila de Comandos
```c
// Nó da fila de comandos
struct NoComando {
    char comando[500];        // Comando SQL a ser executado
    struct NoComando *prox;   // Próximo comando na fila
};

// Fila de comandos
struct FilaComandos {
    struct NoComando *inicio;  // Início da fila
    struct NoComando *fim;     // Fim da fila
    int tamanho;              // Quantidade de comandos na fila
};
```

### 2. Árvore Binária para Ordenação
```c
// Nó da árvore binária
struct NoArvore {
    void *dados;              // Dados (Pessoa, Pet ou TipoPet)
    struct NoArvore *esq;     // Filho esquerdo
    struct NoArvore *dir;     // Filho direito
    int altura;               // Para balanceamento AVL
};
```

### 3. Estruturas de Dados Auxiliares
```c
// Estrutura para pessoa
struct Pessoa {
    int codigo;           
    char nome[100];       
    char fone[20];        
    char endereco[200];   
    char data_nasc[11];   
};

// Estrutura para tipo de pet
struct TipoPet {
    int codigo;           
    char descricao[100];  
};

// Estrutura para pet
struct Pet {
    int codigo;           
    int codigo_pes;       
    char nome[100];       
    int codigo_tipo;      
};
```

## Funcionamento do Sistema

1. **Processamento de Comandos**
   - Os comandos SQL são lidos do arquivo ou entrada do usuário
   - Cada comando é inserido na fila de comandos
   - Os comandos são processados em ordem FIFO (First In, First Out)
   - Comandos inválidos são descartados durante a validação

2. **Filas Específicas**
   - Após validação, os comandos são distribuídos em filas específicas:
     - Fila de comandos para Pessoa
     - Fila de comandos para TipoPet
     - Fila de comandos para Pet

3. **Ordenação com Árvore Binária**
   - Comandos SELECT com ORDER BY utilizam uma árvore binária
   - A árvore mantém os elementos ordenados automaticamente
   - Travessia in-ordem para obter resultados ordenados

## Comandos SQL Suportados

```sql
-- Inserção
insert into tabela1(campo1, campo2, campo3) values(valor1, valor2, valor3);

-- Atualização
update tabela1 set campo2 = valor2, campo3 = valor3 where campo1 = valor1;

-- Remoção
delete from tabela1 where campo1 = valor1;

-- Consulta com ordenação (usa árvore binária)
select * from tabela1 where campo1 = valor1 order by campo2;
```

## Como Executar

1. Clone o repositório
2. Compile o projeto usando o Makefile:
   ```bash
   make
   ```
3. Execute o programa:
   ```bash
   ./pet_system
   ```

## Organização do Código

- `src/`
  - `fila.c` - Implementação da fila de comandos
  - `arvore.c` - Implementação da árvore binária
  - `parser.c` - Processamento dos comandos SQL
  - `main.c` - Programa principal
- `include/`
  - `fila.h` - Definições da fila
  - `arvore.h` - Definições da árvore
  - `estruturas.h` - Estruturas auxiliares
- `data/` - Arquivos de dados
- `docs/` - Documentação adicional

## Licença

Este projeto é para fins educacionais.
