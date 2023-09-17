#include "shell.h"

/**
 * c_memcopy - Copies a specified number of bytes from
 * source to destination.
 * @new_dest: Pointer to the destination buffer.
 * @new_src: Pointer to the source buffer.
 * @length: The number of bytes to copy.
 * Return: Pointer to the destination buffer.
 */
char *c_memcopy(char *new_dest, char *new_src, unsigned int length)
{
	unsigned int ind = 0;

	while (ind < length)
	{
		new_dest[ind] = new_src[ind];
		ind++;
	}
	return (new_dest);
}

/**
 * arr_fill - Fill an array with a constant byte.
 * @dest: Pointer to the memory to be filled.
 * @byte: The byte value to fill.
 * @length: The number of bytes to be filled.
 * Return: Pointer to the filled memory area.
 */
void *arr_fill(void *dest, int byte, unsigned int length)
{
	char *ptr = dest;
	unsigned int ind;

	for (ind = 0; ind < length; ind++)
	{
		*ptr = byte;
		ptr++;
	}
	return (dest);
}

/**
 * envir_free - Frees the memory allocated for an array
 * of environment variables.
 * @environment: The array of environment variables to free.
 *
 * Return: void
 */
void envir_free(char **environment)
{
	int index = 0;

	while (environment[index])
	{
		free(environment[index]);
		index++;
	}
}
