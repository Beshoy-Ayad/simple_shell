#include "main.h"

/**
 * parse_command - parse a command line into a program and arguments
 * @line: the command line
 * Return: an array of strings containing the program and arguments
 */
char **parse_command(char *line)
{
    char **argv = malloc(MAX_ARG * sizeof(char *));
    if (!argv)
    {
        perror("malloc");
        exit(1);
    }
    int i = 0;
    char *token = strtok(line, DELIM);

    while (token != NULL)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, DELIM);
    }
    argv[i] = NULL;
    return (argv);
}

/**
 * execute_command - execute a command with optional pipes
 * @argv: an array of strings containing the command and arguments
 */
void execute_command(char **argv)
{
    pid_t pid;
    int status;
    char *pipe_symbol = strchr(argv[0], '|');

    if (pipe_symbol != NULL)
    {
        *pipe_symbol = '\0';
        char **cmd1 = parse_command(argv[0]);
        char **cmd2 = parse_command(pipe_symbol + 1);
        int pipefd[2];

        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            if (execve(cmd1[0], cmd1, NULL) == -1)
            {
                perror(cmd1[0]);
                exit(1);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            if (execve(cmd2[0], cmd2, NULL) == -1)
            {
                perror(cmd2[0]);
                exit(1);
            }
        }
        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
    }
    else
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror(argv[0]);
                exit(1);
            }
        }
        else
        {
            wait(&status);
        }
    }
}

/**
 * execute_builtin - check and execute built-in commands
 * @argv: an array of strings containing the command and arguments
 * Return: 1 if the command is built-in, 0 otherwise
 */
int execute_builtin(char **argv)
{
    if (strcmp(argv[0], "cd") == 0)
    {
        if (chdir(argv[1]) != 0)
        {
            perror("cd");
        }
        return (1);
    }
    return (0);
}

/**
 * shell_loop - run a shell loop that reads, parses and executes commands
 */
void shell_loop(void)
{
    char *line;
    char **argv;

    while (1)
    {
        line = readline(PROMPT);
        if (strlen(line) > 0)
        {
            add_history(line);
        }
        argv = parse_command(line);
        if (argv[0] == NULL || strcmp(argv[0], "exit") == 0)
        {
            break;
        }
        if (!execute_builtin(argv))
        {
            execute_command(argv);
        }
        free(line);
        free(argv);
    }
}

/**
 * main - invoke the shell loop
 * Return: 0 on success
 */
int main(void)
{
    shell_loop();
    return (0);
}