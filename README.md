# Interface de Shell em C 📟

Projeto acadêmico que implementa uma interface de shell básica em linguagem C que aceita comandos do usuário, criando um processo separado para executar cada comando. Este projeto teve como escolhido o sistema *Linux* para executá-lo.

## 📌 Funcionalidades  

**Execução de Comandos**:
   
  - Aceita comandos do usuário e os executa usando `fork()` e `execvp()`.  
  - Permite execução em segundo plano ao adicionar `&` ao final do comando.  

**Histórico de Comandos**:
  - Armazena até 10 comandos recentes.  
  - Comandos podem ser acessados por:
    
    `history` = exibe o histórico completo.  
    `!!` = executa o último comando.  
    `!N` = executa o comando correspondente ao índice **N** no histórico.

## Estrutura do Código 
O projeto está organizado em uma única estrutura de código com funções específicas para cada tarefa:  

1. **Função `main`**  
   - Gerencia o loop principal do shell.  
   - Lê entradas do usuário e as encaminha para execução.  

2. **Função `execute_command`**  
   - Processa e executa o comando inserido pelo usuário.  
   - Divide o comando em tokens, cria processos-filhos e chama `execvp`.  

3. **Função `add_to_history`**  
   - Adiciona comandos ao histórico.  
   - Implementa um sistema de substituição quando o limite de 10 comandos é alcançado.  

4. **Função `print_history`**  
   - Exibe os últimos 10 comandos armazenados no histórico.  

5. **Função `execute_history_command`**  
   - Executa comandos previamente armazenados no histórico com base no índice especificado.

## Exemplo de Uso
**Comandos Suportados**

- Comandos básicos do Linux, como `ls`, `pwd`, `mkdir`, etc.
- Histórico e execução:
  
  `history`: Exibe os 10 últimos comandos.
  
  `!!`: Reexecuta o último comando.
  
  `!3`: Executa o terceiro comando do histórico.

**Interação com o Shell**
```bash
osh> ls  
arquivo1.txt arquivo2.txt  

osh> mkdir pasta_teste  

osh> history  
1 ls  
2 mkdir pasta_teste  

osh> !1  
arquivo1.txt arquivo2.txt  
```

## Colaboradores 👨🏻‍💻

<div align="center" style="display: block;">
  
Este projeto foi desenvolvido por estudantes do curso de Análise e Desenvolvimento de Sistema do Instituto Federal de Rondônia (IFRO):

<em>[Eduarda Leigue](https://github.com/leigueed)</em> -
<em>[João do Monte](https://github.com/joaomonteandrade)</em> -
<em>[Matheus Henrique](https://github.com/Modheus)</em>
<br>
<em>[Paulo Ximenes](https://github.com/PauloAlbqrq)</em> -
<em>[Luiz Guilherme](https://github.com/usuario-colaborador2)</em>

<img align= "center" src="programing.gif" width="600"/>
</div>
