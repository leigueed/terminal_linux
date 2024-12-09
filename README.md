# Interface de Shell em C 📟

Projeto acadêmico que implementa uma interface de shell básica em linguagem C que aceita comandos do usuário, criando um processo separado para executar cada comando. Este projeto teve como escolhido o sistema *Linux* para executá-lo.

## Descrição:

O projeto é dividido em duas partes principais:

1. **Criação de Processos Filhos e Execução de Comandos**: A interface de shell recebe comandos do usuário, criando um processo-filho para executá-los usando `fork()` e `execvp()`, com os argumentos armazenados em um *array* de strings.

2. **Implementação do Histórico de Comandos**: O shell armazena até 10 comandos recentes, exibíveis com `history`. Comandos anteriores podem ser executados usando `!!` (último comando) ou `!N` (comando específico).

## Estrutura do Projeto

## Execução

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install foobar.

```bash
pip install foobar
```

## Exemplo de Uso

```python
import foobar

# returns 'words'
foobar.pluralize('word')

# returns 'geese'
foobar.pluralize('goose')

# returns 'phenomenon'
foobar.singularize('phenomena')
```

## Comandos Implementados

## Tratamento de Erros

## Colaboradores 👨🏻‍💻

<div align="center" style="display: block;">
  
Estudantes de Análise e Desenvolvimento de Sistema do Instituto Federal de Rondônia (IFRO):

<em>[Eduarda Leigue](https://github.com/leigueed)</em>
<em>[João do Monte](https://github.com/joaomonteandrade)</em>
<em>[Matheus Henrique](https://github.com/Modheus)</em>
<em>[Paulo Ximenes](https://github.com/PauloAlbqrq)</em>
<em>[Luiz Guilherme](https://github.com/usuario-colaborador2)</em>

<img align= "center" src="programing.gif" width="600"/>
</div>
