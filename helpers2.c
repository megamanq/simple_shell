#include "shell.h"

/**
 * change_directory - Change the current working directory.
 * @cmd_args: Parsed command arguments, including the directory path.
 * @lst_cmd_stat: Status of the last executed command (unused).
 * Return: 0 on success, -1 on failure
 * (Always 0 in case of no old working directory).
 */
int change_directory(char **cmd_args, __attribute__((unused)) int lst_cmd_stat)
{
	int result = -1;
	char curr_dir[PATH_MAX];

	if (cmd_args[1] == NULL)
	{
		result = chdir(getenv("HOME"));
	}
	else if (str_cmp(cmd_args[1], "-") == 0)
	{
		result = chdir(getenv("OLDPWD"));
	}
	else
	{
		result = chdir(cmd_args[1]);
	}
	if (result == -1)
	{
		perror("hsh");
		return (-1);
	}
	else
	{
		getcwd(curr_dir, sizeof(curr_dir));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", curr_dir, 1);
	}
	return (0);
}

/**
 * history - Append User Input to a History File
 * @us_in: User Input to Append
 * Return: -1 on Failure, 0 on Success
 */
int history(char *us_in)
{
	char *filename = ".history_logfile";
	ssize_t file_desc, write_res;
	int input_len = 0;

	if (!filename)
		return (-1);
	file_desc = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (file_desc < 0)
		return (-1);
	if (us_in)
	{
		for (input_len = 0; us_in[input_len]; input_len++)
		{
		}
		write_res = write(file_desc, us_in, input_len);
		if (write_res < 0)
			return (-1);
	}
	return (0);
}

/**
 * build_path - Build a path by concatenating a directory and a token
 * @token: The token to append to the directory
 * @directory: The directory to append the token to
 *
 * Return: The concatenated path (directory + '/' + token)
 */
char *build_path(char *token, char *directory)
{
	char *path;
	size_t length;

	length = str_lenght(directory) + str_lenght(token) + 2;
	path = malloc(sizeof(char) * length);
	if (path == NULL)
	{
		return (NULL);
	}
	memset(path, 0, length);
	path = str_concat(path, directory);
	path = str_concat(path, "/");
	path = str_concat(path, token);
	return (path);
}

/**
 * bultn_check - Check if a command is a built-in
 * @command: The command to check
 * Return: 0 if built-in, -1 otherwise
 */

int bultn_check(char **command)
{
	int index;
	built_list builtins[] = {
		{"cd", NULL},
		{"help", NULL},
		{"echo", NULL},
		{"history", NULL},
		{NULL, NULL}
	};

	if (*command == NULL)
	{
		return (-1);
	}
	for (index = 0; (builtins + index)->command; index++)
	{
		if (str_cmp(command[0], (builtins + index)->command) == 0)
			return (0);
	}
	return (-1);
}

/**
 * create_environment - Creates a copy of the environment variables.
 * @env_copy: Pointer to the new environment variable array.
 */
void create_environment(char **env_copy)
{
	int index = 0;

	while (environ[index])
	{
		env_copy[index] = str_duplicate(environ[index]);
		index++;
	}
	env_copy[index] = NULL;
}
