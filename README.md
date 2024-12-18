  
# Interface de Shell em C 📟
Projeto acadêmico de uma interface de shell simples programado em `linguagem C`, permitindo que o usuário insira comandos, gerando um processo separado para executar cada um deles. Desenvolvido para o ambiente `Linux`, o shell suporta funções como execução de comandos em segundo plano, histórico de comandos e reexecução de comandos anteriores.

<div align="center" style="display: block;">
   <img align= "center" src="programing.gif" width="600"/>
</div>

## Estrutura do Código

Nesta seção, mostraremos o código e nele explicamos a estrutura e as principais funções do shell, como histórico de comandos, execução de processos e controle de segundo plano.

`Bibliotecas`:
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
```

`Definições de constantes`:
```c
// O tamanho máximo de uma linha de comando que o shell pode processar.
#define MAX_LINE 80
// Define o número máximo de comandos armazenados no histórico.
#define MAX_HISTORY 10
```

`Declarações de variáveis`:
```c
char *args[MAX_LINE / 2 + 1]; 
char input[MAX_LINE]; // Define o número máximo de comandos armazenados no histórico.
int should_run = 1; // Flag (bandeira) para determinar quando encerrar o programa.
int background = 0; // Indica se o comando deve ser executado em segundo plano.

char *history[MAX_HISTORY];
int history_count = 0; // Um contador que conta quantos comandos foram armazenados no histórico.
```

`Declarações de funções`:
```c
void execute_command(char* in);
void execute_history_command(int n);
```

### Função **`main`**:
```c
// O programa entra em um loop enquanto a "should_run" for verdadeiro.
// Ele exibe o "osh>", lê a entrada do usuário e chama a função "execute_command" para processar e executar o comando inserido.

int main(void) {
    while (should_run) {
      // Essas duas linhas servem só para mostrar "osh>" na tela.
        printf("osh> ");
        fflush(stdout);

        // Lê a entrada do usuário e coloca na variável "input".
        fgets(input, MAX_LINE, stdin);
        execute_command(input);
    }
    return 0;
}
```
    
### Função **`execute_command`**:

Este shell suporta os principais comandos:

1. Comandos padrão do Linux.
2. Histórico de comandos com `history`.
3. Reexecução de comandos com `!!` e `!n`.
4. Execução em segundo plano com `&`.
5. Finalização com `exit`.
   
```c
// Função principal que executa comandos escritos pelo usuário.

void execute_command(char* in){
    // Remove a nova linha no final da string.
        in[strcspn(in, "\n")] = 0;

        // Se o usuário digitar "history" vai ser imprimido o histórico completo.
        if (strcmp(in, "history") == 0) {
            print_history();
            return;
        }
        // Verifica se o comando é 'exit' para encerrar o shell.
        if (strcmp(in, "exit") == 0) {
            should_run = 0;
            return;
        }
        // Se o usuário escrever "!!" vai ser executado o comando mais recente do histórico.
        if (in[0] == '!' && in[1] == '!') {
            if (history_count > 0) {
                execute_history_command(history_count);
            } else {
                printf("Nenhum comando no histórico\n");
            }
            return;
        }
        // Se o usuário escrever "!" antes de um número, vai ser executado o comando correspondente à posição do número no histórico.
        if (in[0] == '!' && in[1] != '\0') {
            int n = atoi(&in[1]);
            execute_history_command(n);
            return;
        }
        // Se o comando terminar com &, marca o comando para ser executado em segundo plano.
        background = 0;
        if (input[strlen(in) - 1] == '&') {
            background = 1;
            input[strlen(in) - 1] = 0; // Remove o '&' da string.
        }
    
        // Adiciona o comando ao histórico.
        add_to_history(in);

        // Divide o comando em tokens (palavras separadas por espaço) e coloca dentro da variavel "args".
        char *token = strtok(in, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // O último argumento precisa ser "NULL" para a função "execvp".

        // Usa "fork()" para criar um novo processo.
        pid_t pid = fork();
    
        // Verifica se deu algum erro.
        if (pid < 0) {
            perror("Fork falhou");
            exit(1);
        }
    
        // Se for o processo filho, executa o comando com "execvp()".
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Execvp falhou");
                exit(1);
            }
        } else {
            // Se for o processo pai, espera o término do filho com "wait(NULL)".
            // A menos que o comando seja em segundo plano, onde NÃO ESPERA.
            if (!background) {
                wait(NULL);
            }
        }
}
```

### Função **`Gerenciamento do histórico`**:
```c
// Declaração
char *history[MAX_HISTORY];
int history_count = 0; // Um contador que conta quantos comandos foram armazenados no histórico.

// Define o número máximo de comandos armazenados no histórico.
#define MAX_HISTORY 10

// Adiciona o comando ao histórico.
        add_to_history(in);

// Função para adicionar um comando na lista do histórico.
void add_to_history(char *command) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(command);
    } else {
        // Se o histórico estiver cheio, remove o comando mais antigo.
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        // Adiciona o novo comando no final do histórico.
        history[MAX_HISTORY - 1] = strdup(command);
    }
}
```

### Função **`print_history`**:
```c

if (strcmp(in, "history") == 0) {
    print_history();
    return;
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}
```

### Função **`execute_history_command`**:
```c
// Função que executa um comando do histórico baseado no número fornecido (n), referente a um comando anterior no histórico.
// Se o (n) não for válido, é exibido uma mensagem de erro.

void execute_history_command(int n) {
    if (n > 0 && n <= history_count) {
        printf("%s\n", history[n - 1]);
        execute_command(history[n - 1]);
    } else {
        printf("Nenhum comando correspondente no histórico.\n");
    }
}
```

## Colaboradores 👨🏻‍💻
Este projeto acadêmico é desenvolvido por estudantes do Curso Superior de Tecnologia Análise e Desenvolvimento de Sistema do IFRO:

<em>[Eduarda Leigue](https://github.com/leigueed)</em> -
<em>[João do Monte](https://github.com/joaomonteandrade)</em> -
<em>[Matheus Henrique](https://github.com/Modheus)</em> -
<em>[Paulo Ximenes](https://github.com/PauloAlbqrq)</em> -
<em>[Luiz Guilherme](https://github.com/usuario-colaborador2)</em>
