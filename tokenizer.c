#include "main.h"

/**
 * tokenize - Splits the input string into tokens using specified delimiters.
 *
 * @data: A pointer to the program's data structure.
 *
 * This function tokenizes the input line and stores the tokens in the 'data->tokens' array.
 * The 'data->command_name' is set to the first token.
 *
 * Return: No return value; the tokens are stored in 'data->tokens'.
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	/* Remove the newline character if present at the end of the input line */
	length = str_length(data->input_line);
	if (length > 0 && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';

	/* Count the number of tokens in the input line */
	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				counter++;
		}
	}

	/* Allocate memory for the tokens array */
	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiter));

	/* Set the command name to the first token */
	data->command_name = str_duplicate(data->tokens[0]);

	/* Tokenize the rest of the input line */
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}
