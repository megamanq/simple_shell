#include "shell.h"
/**
 * c_exit - Exit Shell with Status Code
 * @args: Parsed Arguments
 * @user_input: User Input
 * @program_name: Name of the Shell Program
 * @cmd_cnt: Command Execution Count
 * Return: Void
 */
void c_exit(char **args, char *user_input, char **program_name, int cmd_cnt)
{
	int status, i = 0;

	if (args[1] == NULL)
	{
		free(user_input);
		free(args);
		exit(EXIT_SUCCESS);
	}

	for (i = 0; args[1][i]; i++)
	{
		if (c_isalpha(args[1][i]) != 0)
		{
			p_error(program_name, cmd_cnt, args);
			break;
		}
		else
		{
			status = c_atoi(args[1]);
			free(user_input);
			free(args);
			exit(status);
		}
	}
}


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
		perror("change_directory");
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
 * env_disp - Display Environment Variables.
 * @cmd_args: Parsed Command (unused).
 * @status: Status of the Last Command Executed (unused).
 * Return: Always 0.
 */

int env_disp(char **cmd_args, int status)
{
	(void)cmd_args;
	(void)status;
	size_t index = 0;
	int length;

	while (environ[index] != NULL)
	{
		length = str_lenght(environ[index]);
		write(1, environ[index], length);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	return (0);
}

/**
 * show_help - Display help information for a built-in command.
 * @command: Parsed command arguments, including the help file path.
 * @status: Status of the last executed command (unused).
 * Return: 0 on success, -1 on failure.
 */
int show_help(char **command, __attribute__((unused)) int status)
{
	int file_descriptor, file_write, read_result = 1;
	char character;

	file_descriptor = open(command[1], O_RDONLY);
	if (file_descriptor < 0)
	{
		perror("Error");
		return (0);
	}
	for (; read_result > 0;)
	{
		read_result = read(file_descriptor, &character, 1);
		file_write = write(STDOUT_FILENO, &character, read_result);
		if (file_write < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}


/**
 * echo_builtin - Handle various Echo cases.
 * @cmd_args: Parsed Command and Arguments.
 * @last_cmd_statu: Status of the Last Executed Command.
 * Return: Always 0, or execute normal Echo.
 */

int echo_builtin(char **cmd_args, int last_cmd_statu)
{
	char *path;
	unsigned int parent_pid = getppid();

	if (c_strncmp(cmd_args[1], "$?", 2) == 0)
	{
		print_integer(last_cmd_statu);
		PRINTER("\n");
	}
	else if (c_strncmp(cmd_args[1], "$$", 2) == 0)
	{
		print_uns_num(parent_pid);
		PRINTER("\n");
	}
	else if (c_strncmp(cmd_args[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);
	}
	else
	{
		return (execute_echo(cmd_args));
	}

	return (1);
}
