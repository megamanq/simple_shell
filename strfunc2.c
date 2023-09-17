#include "shell.h"

/**
 * str_cmp - Compare two strings.
 * @str1: First string.
 * @str2: Second string.
 * Return: 0 if the strings are identical, otherwise the difference.
 */

int str_cmp(char *str1, char *str2)
{
	int difference = 0, index = 0, len1, len2;

	len1 = str_lenght(str1);
	len2 = str_lenght(str2);
	if (str1 == NULL || str2 == NULL)
	{
		return (1);
	}
	if (len1 != len2)
	{
		return (1);
	}
	while (str1[index])
	{
		if (str1[index] != str2[index])
		{
			difference = str1[index] - str2[index];
			break;
		}
		index++;
	}
	return (difference);
}

/**
 * str_findchar - Locate Character In String
 * @str: String to Search In
 * @ch: Character to Search For
 * Return: Pointer to Character or NULL if not found
 */

char *str_findchar(char *str, char ch)
{
	do {
		if (*str == ch)
		{
			break;
		}
	} while (*str++);
	return (str);
}

/**
 * str_duplicate - Duplic a string
 * @src: String to duplicate
 * Return: Pointer to the duplicated string or NULL on failure
 */
char *str_duplicate(char *src)
{
	size_t src_len, index = 0;
	char *str_copy;

	src_len = str_lenght(src);
	str_copy = malloc(sizeof(char) * (src_len + 1));
	if (!str_copy)
	{
		return (NULL);
	}
	while (index <= src_len)
	{
		str_copy[index] = src[index];
		index++;
	}
	return (str_copy);
}

/**
 * str_concat - Concatenate two strings.
 * @destination: Pointer to the destination string.
 * @source: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *str_concat(char *destination, char *source)
{
	char *result = destination;

	for (; *destination != '\0'; destination++)
	{
	}
	for (; *source != '\0'; destination++, source++)
	{
		*destination = *source;
	}
	*destination = '\0';
	return (result);
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
