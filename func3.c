#include "shell.h"

/**
 * _putchar - Write a character to standrd output.
 * @ch: The character to print.
 * Return: 1 on success, -1 on error (errno is set).
 */

int _putchar(char ch)
{
	return (write(1, &ch, 1));
}

/**
 * c_strncpy - Copy a string with a specified length
 * @destination: The destination character array.
 * @source: The source character array.
 * @length: The maximum number of characters to copy.
 * Return: A pointer to the destination character array.
 */
char *c_strncpy(char *destination, char *source, int length)
{
	int i;

	for (i = 0; i < length && *(source + i); i++)
	{
		*(destination + i) = *(source + i);
	}

	for (; i < length; i++)
	{
		*(destination + i) = '\0';
	}

	return (destination);
}

/**
 * str_lenght - Calculate the length of a string.
 * @str: The input string.
 * Return: The length of the string as an integer.
 */
int str_lenght(char *str)
{
	int length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}


/**
 * c_atoi - convert to a int
 * @s:string
 * Return:int
 */
int c_atoi(char *s)
{
int i, j, n, x;

	i = n = 0;
	x = 1;
	while ((s[i] < '0' || s[i] > '9') && (s[i] != '\0'))
	{
		if (s[i] == '-')
			x *= -1;
		i++;
	}
	j = i;
	while ((s[j] >= '0') && (s[j] <= '9'))
	{
		n = (n * 10) + x * ((s[j]) - '0');
		j++;
	}
	return (n);
}

/**
 * c_puts - Print a string followed by a newline.
 * @string: Pointer to a character string.
 * Return: void
 */
void c_puts(char *string)
{
	int index = 0;

	while (string[index] != '\0')
	{
		_putchar(string[index]);
		index++;
	}
	_putchar('\n');
}
