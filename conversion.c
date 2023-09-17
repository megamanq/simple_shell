#include "shell.h"

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
 * c_itoa - Convert Integer To Char
 * @num: Int To Convert
 *
 * Return: Char Pointer
 */
char *c_itoa(unsigned int num)
{
	char *result;
	int length = 0, i = 0;

	length = int_length(num);
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	*result = '\0';
	for (; num / 10; i++)
	{
		result[i] = (num % 10) + '0';
		num /= 10;
	}
	result[i] = (num % 10) + '0';
	rev_arr(result, length);
	result[i + 1] = '\0';
	return (result);
}

/**
 * c_isalpha - Check if a Character is Alphabetic
 * @ch: Character to check
 * Return: 1 if it's an alphabetic character, 0 if not
 */
int c_isalpha(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * rev_arr - Reverses an Array of Characters
 * @inputArray: Pointer to the Array to be Reversed
 * @arrayLength: Length of the Array
 * Return: void
 */
void rev_arr(char *inputArray, int arrayLength)
{
	int index = 0;
	char temporary;

	while (index < (arrayLength / 2))
	{
		temporary = inputArray[index];
		inputArray[index] = inputArray[(arrayLength - 1) - index];
		inputArray[(arrayLength - 1) - index] = temporary;
		index++;
	}
}
