#include "main.h"

/**
 * command - parse a command line into a program and arguments
 * @line: the command line
 * Return: an array of strings containing the program and arguments
 */

char **command(char *line)
{
	int i = 0;
	char **argv = malloc(MAX_ARG * sizeof(char *));
	char *token = strtok(line, DELIM);

	if (!argv)

	{
		perror("malloc");
		exit(1);
	}
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
 * exec_c - execute a command with optional pipes
 * @argv: an array of strings containing the command and arguments
 * Return: 0 if no pipes, 1 if pipes
 */

int exec_c(char **argv) /* Changed parameter type to char ** */
{
	pid_t pid;
	int status;
	char *pipe_symbol = NULL; /* Initialized pipe_symbol to NULL */
	char **cmd1 = command(argv[0]);
	char **cmd2 = command(pipe_symbol + 1);
	int pipefd[2];

	if (argv[0] != NULL)      /* Added check for null pointer */
	{
		pipe_symbol = strchr(argv[0], '|');
	}
	if (pipe_symbol != NULL)
	{
		*pipe_symbol = '\0';
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
		close(pipefd[0]); /* Added closing of pipe file descriptors */
		close(pipefd[1]); /* Added closing of pipe file descriptors */
		wait(NULL);       /* Added waiting for child processes */
		wait(NULL);       /* Added waiting for child processes */
		free(cmd1);       /* Added freeing of cmd1 pointer */
		free(cmd2);       /* Added freeing of cmd2 pointer */
		return (1);       /* Added return statement for pipes */
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
		return (0); /* Added return statement for no pipes */
	}
}

int exec_b(char **argv)
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

void code_loop(void)
{
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;
	char **argv;

	while (1)
	{
		printf(PROMPT);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			break;
		}
		line[nread - 1] = '\0';
		argv = command(line);
		if (argv[0] == NULL || strcmp(argv[0], "exit") == 0)
		{
			break;
		}

		if (!exec_b(argv))
		{
			exec_c(argv);
		}
		free(line);
		free(argv);
	}
}
int main(void)
{
	code_loop();
	return (0);
}
