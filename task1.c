#include "main.h"


int remove_newline(char *str);


/**
 * main - a simple shell program
 * Return: 0 on success, 1 on failure
 */


int main(void)
{
	char *line = NULL;
	char *argv[2];
	int status;
	pid_t pid;
	size_t len = MAX_LEN;

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		if (getline(&line, &len, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (line[0] == '\n')
			continue;
		line[remove_newline(line)] = '\0';
		argv[0] = line;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(line, argv, NULL) == -1)
			{
				perror(line);
				exit(1);
			}
		}
		else
			wait(&status);
	}
	free(line);
	return (0);
}

/**
 * remove_newline - removes the newline character from a string
 * @str: the string to modify
 * Return: the index of the newline character or -1 if not found
 */
int remove_newline(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\n')
			return (i);
	}
	return (-1);
}
