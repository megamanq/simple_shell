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
 * verif_cmnd - Execute a command in the Simple Shell (Fork, Wait, Execute)
 *
 * @cmnd: Parsed command
 * @usr_in: User input
 * @err_c: Shell execution time case when the command is not found
 * @prog_name: Program name and arguments
 *
 * Return: 1 if the command is NULL, -1 on wrong command,
 * 0 on command execution
 */

int verif_cmnd(char **cmnd, char *usr_in, int err_c, char **prog_name)
{
	int status;
	pid_t child_pid;

	if (*cmnd == NULL)
	{
		return (-1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (c_strncmp(*cmnd, "./", 2) != 0 && c_strncmp(*cmnd, "/", 1) != 0)
		{
			excmd_path(cmnd);
		}
		if (execve(*cmnd, cmnd, environ) == -1)
		{
			print_err(cmnd[0], err_c, prog_name);
			free(usr_in);
			free(cmnd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
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
 * ex_bltn - Execute Built-In Commands
 * @command: Parsed Command
 * @error_status: Status of the previous execution
 * Return: -1 on failure, 0 on success (Execution of Built-In Commands)
 */

int ex_bltn(char **command, int error_status)
{
	built_list builtins[] = {
		{"cd", change_directory},
		{"env", env_disp},
		{"help", show_help},
		{"echo", echo_builtin},
		{"history", history_display},
		{NULL, NULL}
	};
	int index;

	for (index = 0; (builtins + index)->command; index++)
	{
		if (str_cmp(command[0], (builtins + index)->command) == 0)
		{
			return ((builtins + index)->funct(command, error_status));
		}
	}
	return (-1);
}

/**
 * history_display - Display the history of user input in Simple Shell
 * @cmd_args: Parsed Command (unused)
 * @status: Status of the last execution (unused)
 * Return: 0 on success, -1 on failure
 */

int history_display(char **cmd_args, int status)
{
	char *history_fn;
	FILE *file_ptr;
	char *curr_line = NULL;
	size_t line_length = 0;
	int line_count = 0;
	char *counter_string;

	(void)cmd_args;
	(void)status;

	history_fn = ".simple_shell_history";
	file_ptr = fopen(history_fn, "r");
	if (file_ptr == NULL)
	{
		return (-1);
	}
	for (; getline(&curr_line, &line_length, file_ptr) != -1;)
	{
		line_count++;
		counter_string = c_itoa(line_count);
		LOG(counter_string);
		free(counter_string);
		LOG(" ");
		LOG(curr_line);
	}
	if (curr_line)
		free(curr_line);
	fclose(file_ptr);
	return (0);
}
