#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


#define TOK_DELIM " \t\r\n"
#define BUFFER_SIZE 1024

char* read_input();
char** split_input(char*);
int execute(char** list);

int execute(char** list)
{
    int status;
    pid_t pid = fork();

    if (strcmp(list[0], "exit") == 0)
    {
        return 0;
    }
 
    if (strcmp(list[0],"cd") == 0)
    {
        chdir(list[1]);
        waitpid(pid, &status, WUNTRACED);
    }
    else
    {
        if (pid == 0)
        {
            printf("Child proccess\n");
            execvp(list[0], list);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Child proccess PID: %d\n",pid);
            waitpid(pid, &status, WUNTRACED);
        }
    }

    return 1;
}



char** split_input(char* line) {
    char** tokens = malloc(BUFFER_SIZE * sizeof(char*));
    char* token;
    int index = 0;

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[index] = token;
        index++;

        token = strtok(NULL, TOK_DELIM);
    }

    tokens[index] = NULL;

    return tokens;
}

char* read_input() {
    char* buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
    int index = 0;
    char c;
    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[index] = '\0';
            return buffer;
        }
        else
        {
            buffer[index] = c;
        }
        index++;
    }
}

int main() {

    char* input;
    char** argument_list;
    int status = 1;

    while (status)
    {
        printf("$ ");
        input = read_input();
        argument_list = split_input(input);
        status = execute(argument_list);

        free(input);
        free(argument_list);
    }
    return 0;
}