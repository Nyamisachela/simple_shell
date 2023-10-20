#include "shell.h"

/**
 * main - Initializes program variables and begins execution.
 *
 * @argc: Number of values received from the command line.
 * @argv: Values received from the command line.
 * @env: Environment variables.
 * Return: Returns 0 on success.
 */
int main(int argc, char *argv[], char *env[])
{
	ProgramInfo data_struct = {NULL};
	ProgramInfo *data = &data_struct;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, _ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	_prompt(prompt, data);
	return (0);
}

/**
 * _ctrl_c - Handles the SIGINT (Ctrl+C) signal 
 * by printing the prompt in a new line.
 *
 * @opr: Unused parameter.
 */
void _ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - Initializes the program data structure.
 *
 * @data: Pointer to the data structure.
 * @argv: Array of program arguments.
 * @env: Environment variables.
 * @argc: Number of values received from the command line.
 */
void init_data(ProgramInfo *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->name = argv[0];
	data->input = NULL;
	data->currentCommand = NULL;
	data->executionCount = 0;

	if (argc == 1)
		data->fd = STDIN_FILENO;
	else
	{
		data->fd = open(argv[1], O_RDONLY);
		if (data->fd == -1)
		{
			_printe(data->name);
			_printe(": Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}

	data->arguments = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = _strdup(env[i]);
		}
	}
	data->env[i] = NULL;

	data->aliases = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->aliases[i] = NULL;
	}
}

/**
 * _prompt - Starts an infinite loop 
 * that displays the prompt and handles user input.
 *
 * @prompt: The prompt to print.
 * @data: Pointer to program data.
 */
void _prompt(char *prompt, ProgramInfo *data)
{
	int error_code = 0, strings_len = 0;

	while (++(data->executionCount))
	{
		_print(prompt);
		error_code = strings_len = _getline(data);

		if (error_code == EOF)
		{
			free_data(data);
			exit(errno);
		}
		if (strings_len >= 1)
		{
			expand_alias(data);
			concat_variables(data);
			tokenize(data);
			if (data->arguments[0])
			{
				error_code = cmd_execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

