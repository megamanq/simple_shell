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
 * cc_strtok - Tokenizes a String Using Delimiters
 * @str: The input string to tokenize
 * @delim: The delimiter characters
 * Return: A pointer to the next token or NULL if no more tokens are found
 */
char *cc_strtok(char *str, const char *delim)
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
