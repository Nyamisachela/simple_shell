#include "main.h"

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
	data_of_program data_struct = {NULL};
	data_of_program *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	our_prompt(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - Handles the SIGINT (Ctrl+C) signal 
 * by printing the prompt in a new line.
 *
 * @opr: Unused parameter.
 */
void handle_ctrl_c(int opr UNUSED)
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
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}

	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * our_prompt - Starts an infinite loop 
 * that displays the prompt and handles user input.
 *
 * @prompt: The prompt to print.
 * @data: Pointer to program data.
 */
void our_prompt(char *prompt, data_of_program *data)
{
	int error_code = 0, strings_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = strings_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (strings_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

