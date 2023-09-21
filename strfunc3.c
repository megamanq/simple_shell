#include "shell.h"

/**
 * isDelimiter - Checks if a character matches any character in a string.
 * @character: The character to check.
 * @string: The string to check.
 *
 * Return: 1 if a match is found, 0 if no match is found.
 */
unsigned int isDelimiter(char character, const char *string)
{
	unsigned int index = 0;

	while (string[index] != '\0')
	{
		if (character == string[index])
			return (1);
		index++;
	}
	return (0);
}

/**
 * handle_sharp - Remove all after sharp
 * @input: Input string;
 * Return: void
 */
void handle_sharp(char *input)
{
	int index = 0;
	int is_whitespace = 1;	/* Initialize to true */

	while (input[index] != '\0')
	{
		if (input[index] == ' ')
		{
			is_whitespace = 1;
		}
		else if (is_whitespace && input[index] == '#')
		{
			input[index] = '\0';
			break;
		}
		else
		{
			is_whitespace = 0;
		}
		index++;
	}
}
/**
 * c_strncmp - Compare a specified number of characters in two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * @numb: The number of characters to compare.
 *
 * Return: 1 if the strings don't match, otherwise 0.
 */

int c_strncmp(const char *str1, const char *str2, size_t numb)
{
	size_t index;

	if (str1 == NULL)
		return (-1);
	index = 0;
	while (index < numb && str2[index])
	{
		if (str1[index] != str2[index])
		{
			return (1);
		}
		index++;
	}
	return (0);
}
