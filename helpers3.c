#include "shell.h"

/**
 * parse_comand - Parse a Line of Input into Tokens
 * @line: User input to be parsed
 * Return: An array of character pointers containing
 * parsed tokens for a Simple Shell
 */

char **parse_comand(char *line)
{
	char **parsed_tokens;
	char *current_token;
	int token_count, buffer_size = BUFFSIZ;

	if (line == NULL)
		return (NULL);
	parsed_tokens = malloc(sizeof(char *) * buffer_size);
	if (!parsed_tokens)
	{
		perror("hsh");
		return (NULL);
	}
	current_token = c_strtok(line, "\n ");
	token_count = 0;
	while (current_token)
	{
		parsed_tokens[token_count] = current_token;
		current_token = c_strtok(NULL, "\n ");
		token_count++;
	}
	parsed_tokens[token_count] = NULL;
	return (parsed_tokens);
}

/**
 * excmd_path - Search for an Executable Command in the $PATH
 * @command: Parsed Input
 * Return: 1 for Failure, 0 for Success
 */

int excmd_path(char **command)
{
	char *srch_pth, *val, *ex_pth;
	struct stat buffer;

	srch_pth = c_getenv("PATH");
	for (val = c_strtok(srch_pth, ":"); val != NULL; val = c_strtok(NULL, ":"))
	{
		ex_pth = build_path(*command, val);
		if (stat(ex_pth, &buffer) == 0)
		{
			*command = str_duplicate(ex_pth);
			free(ex_pth);
			free(srch_pth);
			return (0);
		}
		free(ex_pth);
	}
	free(srch_pth);
	return (1);
}

/**
 * handle_signal - Signal handler function for handling SIGINT
 * @signal: The signal received
 */

void handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		LOG("\n$ ");
	}
}
