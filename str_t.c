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

	if (str != NULL)
	{
		st_P = str;
	}
	while (*st_P && *st_P == ' ')
	{
		st_P++;
	}
	nd_P = st_P;
	while (*st_P != '\0')
	{
		if (*st_P == *delimiter)
		{
			*st_P = '\0';
			while (*(st_P + 1) == ' ')
			{
				st_P++;
			}
			argv[argc++] = nd_P;
			nd_P = st_P + 1;
			if (argc >= 10)
			{
				break;
			}
		}
		st_P++;
	}
	argv[argc++] = nd_P;
	argv[argc] = NULL;
}
