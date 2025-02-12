# Trabalho de Estrutura de Dados

**Instituição:** IFCE - Campus Fortaleza  
**Disciplina:** Estrutura de Dados  
**Professor:** Ajalmar Rocha Neto, Dr.  
**Aluno:** Jorge Lucas Silva de Carvalho  

## Descrição
Sistema de gerenciamento de pets que utiliza fila para processar comandos SQL e árvore binária para ordenação de resultados.

## Estruturas de Dados
1. **Fila de Comandos**: Para processar comandos SQL
2. **Árvore Binária**: Para ordenação nos comandos SELECT
3. **Estruturas Auxiliares**:
   - Pessoa (código, nome, fone, endereço, data_nasc)
   - TipoPet (código, descrição)
   - Pet (código, código_pes, nome, código_tipo)

## Comandos SQL Suportados
```sql
insert into tabela(campos) values(valores);
update tabela set campo = valor where condição;
delete from tabela where condição;
select * from tabela where condição order by campo;
```

## Funcionalidades
1. Leitura de comandos via arquivo ou entrada do usuário
2. Processamento de comandos usando fila
3. Ordenação de resultados usando árvore binária
4. Validações de integridade (códigos únicos e referências)
5. Persistência dos dados em arquivo
