#include "shell.h"

/**
 * int_length - Calculate the length of an integer.
 * @number: The integer to determine the length of.
 *
 * Return: The length of the integer.
 */
int int_length(int number)
{
	int length = 0;

	for (; number != 0; length++)
	{
		number /= 10;
	}

	return (length);
}

/**
 * str_cpy - Copies the contents of one string to another.
 * @destination: The destination buffer to store the copied string.
 * @source: The source string to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *str_cpy(char *destination, char *source)
{
	int ind;

	for (ind = 0; source[ind]; ind++)
	{
		destination[ind] = source[ind];
	}
	destination[ind] = '\0';
	return (destination);
}

/**
 * c_strtok - Tokenizes a String Using Delimiters
 * @str: The input string to tokenize
 * @delim: The delimiter characters
 * Return: A pointer to the next token or NULL if no more tokens are found
 */
char *c_strtok(char *str, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int index;

	if (str != NULL)
		next_token = str;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	index = 0;
	while (token_start[index] != '\0')
	{
		if (isDelimiter(token_start[index], delim) == 0)
			break;
		index++;
	}
	if (next_token[index] == '\0' || next_token[index] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + index;
	next_token = token_start;
	index = 0;
	while (next_token[index] != '\0')
	{
		if (isDelimiter(next_token[index], delim) == 1)
			break;
		index++;
	}
	if (next_token[index] == '\0')
		next_token = NULL;
	else
	{
		next_token[index] = '\0';
		next_token = next_token + index + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
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
