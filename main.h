#ifndef MAIN_H
#define MAIN_H

#define MAX_INPUT_LENGTH 1024
#define MAXARGS 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>


void string_token(char *str, char *delimiter, char *argv[]);
void add_bin_prefix(char *argv[], char *new_arg);

void eval(char *cmdline);
int builtin_command(char **argv);
char *search_path(char *file);
ssize_t read_input(char *In_bu);
void parse_input(char *In_bu, char *delim, char **argv);
void execute_command(char **argv);
void non_interactive_mode(char *input_buffer,
		char *argv_buffer[], char *new_arg);
void interactive_mode(int bytes, int id,
		char *input_buffer, char *argv_buffer[], char *new_arg);


/**
 * _strlen - function that returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * _strncpy - function that copies a string
 * @dest: input value
 * @src: input value
 * @n: input value
 *
 * Return: dest
 */
void _strncpy(char *dest, char *src, int n)
{
	int a;

	a = 0;
	while (a < n && src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	while (a < n)
	{
		dest[a] = '\0';
		a++;
	}
}

/**
 * _strcmp - compare the string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int a;

	a = 0;
	while (s1[a] != '\0' && s2[a] != '\0')
	{
		if (s1[a] != s2[a])
		{
			return (s1[a] - s2[a]);
		}
		a++;
	}
	return (0);
}

/**
 * _atoi -  convert a string to an integer
 *
 * @s: string
 *
 * Return: num
 */

int _atoi(char *s)
{
	int i, sign, num, digit;

	if (s == NULL)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (sign > 0 && (num > INT_MAX / 10 ||
						(num == INT_MAX / 10 && digit > INT_MAX % 10)))
				return (INT_MAX);
			if (sign < 0 && (num < INT_MIN / 10 ||
						(num == INT_MIN / 10 && digit > -(INT_MIN % 10))))
				return (INT_MIN);
			num = num * 10 + sign * digit;
		}
		else if (num != 0)
			break;
		i++;
	}
	return (num)
}
