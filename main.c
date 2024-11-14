#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//Tamanho máximo de comando.
#define MAX_LINE 80
#define MAX_HISTORY 10

char *args[MAX_LINE / 2 + 1]; //Argumentos do comando.
char input[MAX_LINE]; //Linha que o usuario escrever.
int should_run = 1; //Flag (bandeira) para determinar quando encerrar o programa.
int background = 0;

char *history[MAX_HISTORY];
int history_count = 0;
//Função para adicionar um comando na lista do histórico.
void add_to_history(char *command) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(command);
    } else {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(command);
    }
}
//Função para printar o histórico.
void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}
//Executa o comando do histórico na posição da variavel n.
void execute_history_command(int n) {
    if (n > 0 && n <= history_count) {
        printf("%s\n", history[n - 1]);
        execute_command(history[n - 1]);
    } else {
        printf("Nenhum comando correspondente no histórico\n");
    }
}
//Recebe o que o usuário escreveu e executa o comando.
void execute_command(char* in){
//Remove a nova linha no final da string.
in[strcspn(in, "\n")] = 0;
    //Se o usuário digitar "history" vai ser printado o histórico completo.
    if (strcmp(in, "history") == 0) {
        print_history();
        return;
    }
    //Verifica se o comando é 'exit' para encerrar o shell.
    if (strcmp(in, "exit") == 0) {
        should_run = 0;
        return;
    }
    //Se o usuário escrever "!!", será executado o comando mais recente do histórico.
    if (in[0] == '!' && in[1] == '!') {
        if (history_count > 0) {
            execute_history_command(history_count);
        } else {
            printf("Nenhum comando no histórico\n");
        }
        return;
    }
    //Se o usuário escrever "!" antes de um número, será executado o comando correspondente à posição do número no histórico.
    if (in[0] == '!' && in[1] != '\0') {
        int n = atoi(&in[1]);
        execute_history_command(n);
        return;
    }
    //Verifica se o comando foi para rodar em background.
    background = 0;
    if (input[strlen(in) - 1] == '&') {
        background = 1;
        input[strlen(in) - 1] = 0; //Remove o '&'.
    }
    //Adiciona o comando ao histórico.
    add_to_history(in);
    
    //Divide o comando em tokens e coloca dentro da variavel args.
    char *token = strtok(in, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  //O último argumento precisa ser NULL para a função execvp.
    
    //Cria um novo processo para executar o comando.
    pid_t pid = fork();
    //Verifica se houve algum erro.
    if (pid < 0) {
        perror("Fork falhou");
        exit(1);
    }
    if (pid == 0) {
        //Processo filho.
        //Executa o comando e verifica se houve algum erro.
        if (execvp(args[0], args) == -1) {
            perror("Execvp falhou");
            exit(1);
        }
    } else {
        // Processo pai.
        if (!background) {
            wait(NULL);  //Espera o processo filho terminar.
        }
    }
}
int main(void) {
    while (should_run) {
        //Essas duas linhas servem para mostrar "osh>" na tela.
        printf("osh> ");
        fflush(stdout); 
        // Lê a entrada do usuário e coloca na variável input.
        fgets(input, MAX_LINE, stdin);
        execute_command(input);
    }
    return 0;
}
