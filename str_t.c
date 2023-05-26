#include "main.h"

/**
 * string_token - function that splits string.
 *
 * @str: string
 * @delimiter: delimiter
 * @argv: array of arguments
 *
 * Return: void.
 */
void string_token(char *str, char *delimiter, char *argv[])
{
	char *st_P = NULL;
	char *nd_P = NULL;
	int argc = 0;
	int len;

	if (str)
	{
		len = _strlen(str);
		while (len > 0 && str[len - 1] == ' ')
			str[--len] = '\0';
	}
	st_P = str;
	while (*st_P == ' ')
		st_P++;
	nd_P = st_P;
	while (*st_P)
	{
		if (_strcmp(st_P, delimiter) == 0)
		{
			*st_P = '\0';
			st_P++;
			while (*st_P == ' ')
				st_P++;
			argv[argc++] = nd_P;
			nd_P = st_P;
			if (argc >= MAXARGS)
				break;
		}
		else
		{
			st_P++;
		}
	}
	argv[argc++] = nd_P;
	argv[argc] = NULL;
}

/**
 * non_interactive_mode - non interactive mode handler .
 * @input_buffer: Input Buffer.
 * @argv_buffer: ARGV Buffer.
 * @new_arg: command Path.
 * Return: void.
 */
void non_interactive_mode(char *input_buffer,
		char *argv_buffer[], char *new_arg)
{
	int id;
	int bytes;
	char *command;
	char *lines[MAXARGS];

	bytes = read(STDIN_FILENO, input_buffer, MAX_INPUT_LENGTH);
	if (bytes > 0 && input_buffer[bytes - 1] == '\n')
		input_buffer[bytes - 1] = '\0';
	string_token(input_buffer, "\n", argv_buffer);
	command = argv_buffer[0];
	while (command)
	{
		string_token(command, " ", lines);
		if (lines[0] && !commands(lines))
		{
			add_bin_prefix(lines, new_arg);
			id = fork();
			if (id == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (id == 0)
			{
				execve(lines[0], lines, NULL);
				perror(lines[0]);
				exit(EXIT_FAILURE);
			}
			else
				wait(NULL);
		}
		command = *(++argv_buffer);
	}
}

/**
 * interactive_mode - function that handles
 * a command from interactive mode.
 *
 * @bytes: number of bytes from reading line.
 * @id: process id.
 * @input_buffer: buffer that save input line.
 * @argv_buffer: buffer that save arguments.
 * @new_arg: full path command.
 *
 * Return: void.
 */
void interactive_mode(int bytes, int id, char
		*input_buffer, char *argv_buffer[], char *new_arg)
{
	while (1)
	{
		write(STDOUT_FILENO, "$$: ", 2);
		bytes = read(STDIN_FILENO, input_buffer, MAX_INPUT_LENGTH);
		if (bytes == -1)
		{
			perror("Error Please contact support");
			continue;
		}
		else if (bytes == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (bytes > 0 && input_buffer[bytes - 1] == '\n')
			input_buffer[bytes - 1] = '\0';
		string_token(input_buffer, " ", argv_buffer);
		if (argv_buffer[0] && !commands(argv_buffer))
		{
			add_bin_prefix(argv_buffer, new_arg);
			id = fork();
			if (id == -1)
			{
				perror("failed try leter");
				exit(EXIT_FAILURE);
			}
			else if (id == 0)
			{
				execve(argv_buffer[0], argv_buffer, NULL);
				perror(argv_buffer[0]);
				exit(EXIT_FAILURE);
			}
			else
				wait(NULL);
		}
	}
}
