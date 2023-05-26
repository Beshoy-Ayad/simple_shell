#include "main.h"


/**
 * main - Simple shell program.
 * Return: Always 0.
 * **/

int main(void)
{
	pid_t id = 0;
	ssize_t bytes = 0;
	char in[MAX_INPUT_LENGTH];
	char new[50];
	char *argv_Bu[MAXARGS];

	if (isatty(STDIN_FILENO))
	{
		interactive_mode(bytes, id, in, argv_Bu, new);
	}
	else
	{
		non_interactive_mode(in, argv_Bu, new);
	}
	return (0);
}

/**
 * commands - is built-in command.
 * @argv: arguments.
 * Return: 0 or 1.
 **/
int commands(char **argv)
{
	char **envp;
	int exit_status;

	if (_strcmp(argv[0], "exit") == 0)
	{
		exit_status = argv[1] ? _atoi(argv[1]) : EXIT_SUCCESS;
		if (exit_status < 0)
			exit(EXIT_FAILURE);
		exit(exit_status);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
		envp = environ;
		while (*envp)
		{
			write(STDOUT_FILENO, *envp, _strlen(*envp));
			write(STDOUT_FILENO, "\n", 1);
			envp++;
		}
		return (1);
	}
	return (0);
}
