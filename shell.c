#include "main.h"

/**
 * main - Simple shell program.
 * Return: Always 0.
 * **/

int main(void)
{
	char In_bu[MAX_INPUT_LENGTH];
	/*char arg[50];*/
	/*char *argv[MAXARGS];*/
	/*int status = 0;*/

	while (1)
	{
		write(STDOUT_FILENO, "P)> ", 2);
		read_input(In_bu);
	}
	return (0);
}

/**
 * read_input - Reads the user input from stdin.
 * @In_bu: The buffer to store the input.
 * Return: The number of bytes read, or -1 on error.
 * **/

ssize_t read_input(char *In_bu)
{
	ssize_t bytes = 0;

	bytes = read(STDIN_FILENO, In_bu, MAX_INPUT_LENGTH);
	if (bytes == -1)
	{
		perror("Error Kindly contact support");
		return (-1);
	}
	else if (bytes == 0)
	{
		write(STDOUT_FILENO, "End of Input\n", 15);
		exit(0);
	}
	if (In_bu[bytes - 1] == '\n')
	{
		In_bu[bytes - 1] = '\0';
	}
	return (bytes);
}

/**
 * parse_input - Parses the user input into arguments.
 * @In_bu: The buffer that contains the input.
 * @delim: The delimiter to split the input by.
 * @argv: The array to store the arguments.
 * Return: Nothing.
 * **/
void parse_input(char *In_bu, char *delim, char **argv)
{
	int i = 0;
	char *token = NULL;

	token = strtok(In_bu, delim);

	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
}

/**
 * execute_command - Executes the command given by the user.
 * @argv: The array that contains the command and arguments.
 * Return: Nothing.
 * **/
void execute_command(char **argv)
{
	pid_t id;
	int status = 0;

	id = fork();

	if (id == -1)
	{
		perror("Fail to fork");
		exit(EXIT_FAILURE);
	}
	else if (id == 0)
	{
		if (access(argv[0], X_OK) == 0)
		{
			execve(argv[0], argv, NULL);
		}
		perror("Fail to run this command");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);
}
