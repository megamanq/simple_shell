#include "shell.h"

/**
 * all_free - Free memory for commands and input line
 * @commands: Parsed commands
 * @input_line: Input line
 *
 * This function frees memory allocated for parsed commands and the input line.
 */
void all_free(char **commands, char *input_line)
{
	free(commands);
	free(input_line);
	commands = NULL;
	input_line = NULL;
}

/**
 * c_calloc - Allocate memory for an array and
 * initialize it with zero
 * @size: Size of the memory block
 * Return: A pointer to the allocated memory,
 * or NULL if allocation fails
 */
void *c_calloc(unsigned int size)
{
	char *allocated_memory;
	unsigned int index;

	if (size == 0)
		return (NULL);
	allocated_memory = malloc(size);
	if (allocated_memory == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		allocated_memory[index] = '\0';
		index++;
	}
	return (allocated_memory);
}

/**
 * c_realloc - Reallocates a memory block using malloc and free
 * @old_ptr: Pointer to the old memory block
 * @old_siz: Size of the old memory block
 * @nw_siz: New size of the memory block
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure
 */
void *c_realloc(void *old_ptr, unsigned int old_siz, unsigned int nw_siz)
{
	void *new_ptr;

	if (nw_siz == old_siz)
		return (old_ptr);
	if (nw_siz == 0 && old_ptr)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = malloc(nw_siz);
	if (new_ptr == NULL)
		return (NULL);
	if (old_ptr == NULL)
	{
		arr_fill(new_ptr, '\0', nw_siz);
		free(old_ptr);
	}
	else
	{
		c_memcopy(new_ptr, old_ptr, old_siz);
		free(old_ptr);
	}
	return (new_ptr);
}
