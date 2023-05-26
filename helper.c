#include "main.h"


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
 * @s: string
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
	return (num);
}
