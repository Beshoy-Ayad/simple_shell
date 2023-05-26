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
