#include "shell.h"

/**
 * shell_exit_file - Exit the shell in case of a file input
 * @line: Line from a file
 * @args: Parsed command
 * @file_desc: File descriptor
 * Return: Exit status based on the command in the file line
 */
void shell_exit_file(char **args, char *line, FILE *file_desc)
{
	int exit_status, index;

	if (args[1] == NULL)
	{
		free(line);
		free(args);
		fclose(file_desc);
		exit(errno);
	}
	for (index = 0; args[1][index]; index++)
	{
		if (c_isalpha(args[1][index]) < 0)
		{
			perror("illegal number");
		}
	}
	exit_status = c_atoi(args[1]);
	free(line);
	free(args);
	fclose(file_desc);
	exit(exit_status);
}

/**
 * handle_file - Process, Verify, Fork, Wait, and Execute
 * a Line from a File
 * @line: A line read from a file
 * @er_cnt: Counter for encountered errors
 * @f_desc: File descriptor for the file being processed
 * @prog_name: The name of the program
 * Return: This function does not return a value (void).
 */

void handle_file(char *line, int er_cnt, FILE *f_desc, char **prog_name)
{
	char **command;
	int status = 0;

	command = parse_comand(line);
	if (c_strncmp(command[0], "exit", 4) == 0)
	{
		shell_exit_file(command, line, f_desc);
	}
	else if (bultn_check(command) == 0)
	{
		status = ex_bltn(command, status);
		free(command);
	}
	else
	{
		status = verif_cmnd(command, line, er_cnt, prog_name);
		free(command);
	}
}

/**
 * c_getenv - Retrieves the value of an environment variable by name
 * @var_name: Name of the environment variable
 * Return: The value of the environment variable, or NULL if not found
 */

char *c_getenv(char *var_name)
{
	size_t name_len, val_len;
	char *val_ptr;
	int ind, char_ind, val_ind;

	name_len = str_lenght(var_name);
	ind = 0;
	while (environ[ind])
	{
		if (c_strncmp(var_name, environ[ind], name_len) == 0)
		{
			val_len = str_lenght(environ[ind]) - name_len;
			val_ptr = malloc(sizeof(char) * val_len);
			if (!val_ptr)
			{
				free(val_ptr);
				perror("unable to alloc");
				return (NULL);
			}
			val_ind = 0;
			char_ind = name_len + 1;
			while (environ[ind][char_ind])
			{
				val_ptr[val_ind] = environ[ind][char_ind];
				char_ind++;
				val_ind++;
			}
			val_ptr[val_ind] = '\0';
			return (val_ptr);
		}
		ind++;
	}
	return (NULL);
}

/**
 * c_getline - Read User Input from Standard Input
 * Return: Input String
 */
char *c_getline()
{
	int ind, buffer_size = BUFFSIZ, read_bytes;
	char curr_char = 0;
	char *inp_buffer = malloc(buffer_size);

	if (inp_buffer == NULL)
	{
		free(inp_buffer);
		return (NULL);
	}
	ind = 0;
	while (curr_char != EOF && curr_char != '\n')
	{
		fflush(stdin);
		read_bytes = read(STDIN_FILENO, &curr_char, 1);
		if (read_bytes == 0)
		{
			free(inp_buffer);
			exit(EXIT_SUCCESS);
		}
		inp_buffer[ind] = curr_char;
		if (inp_buffer[0] == '\n')
		{
			free(inp_buffer);
			return ("\0");
		}
		if (ind >= buffer_size)
		{
			inp_buffer = c_realloc(inp_buffer, buffer_size, buffer_size + 1);
			if (inp_buffer == NULL)
			{
				return (NULL);
			}
		}
		ind++;
	}
	inp_buffer[ind] = '\0';
	handle_sharp(inp_buffer);
	return (inp_buffer);
}

/**
 * file_scan - Read and process a file line by line.
 * @filename: The name of the file to read.
 * @argv: The command line arguments.
 * Return: void
 */
void file_scan(char *filename, char **argv)
{
	FILE *file_ptr;
	char *buffer = NULL;
	size_t length = 0;
	int count = 0;

	file_ptr = fopen(filename, "r");
	if (file_ptr == NULL)
	{
		fprintf(stderr, "Can't open %s\n", filename);
		exit(127);
	}
	for (; getline(&buffer, &length, file_ptr) != -1; count++)
	{
		handle_file(buffer, count, file_ptr, argv);
	}
	if (buffer)
		free(buffer);
	fclose(file_ptr);
	exit(0);
}
