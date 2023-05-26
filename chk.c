#include "main.h"

/**
 * add_bin_prefix - function that adds bin prefix to argv
 * @argv: array of arguments
 * @new_arg: new argument
 * Return: void.
 */
void add_bin_prefix(char *argv[], char *new_arg)
{
	char *pathes = "/bin/";
	size_t lenth;
	size_t arg_len;

	if (argv[0] == NULL)
	{
		return;
	}

	lenth = _strlen(pathes);
	arg_len = _strlen(argv[0]);
	if (_strcmp(argv[0], pathes) == 0 ||
			_strcmp(argv[0], "./") == 0 ||
			_strcmp(argv[0], "../") == 0)
	{
		return;
	}

	_strncpy(new_arg, pathes, lenth);
	_strncpy(new_arg + lenth, argv[0], arg_len);
	new_arg[lenth + arg_len] = '\0';

	argv[0] = new_arg;
}
