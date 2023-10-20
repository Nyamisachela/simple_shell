#include "main.h"

/**
 * tokenize - Splits the input string into arguments using specified delimiters.
 *
 * @data: A pointer to the program's data structure.
 *
 * This function tokenizes the input line and stores the arguments in the 'data->arguments' array.
 * The 'data->currentCommand' is set to the first token.
 *
 * Return: No return value; the arguments are stored in 'data->arguments'.
 */
void tokenize(ProgramInfo *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	/* Remove the newline character if present at the end of the input line */
	length = _strlen(data->input);
	if (length > 0 && data->input[length - 1] == '\n')
		data->input[length - 1] = '\0';

	/* Count the number of arguments in the input line */
	for (i = 0; data->input[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input[i] == delimiter[j])
				counter++;
		}
	}

	/* Allocate memory for the arguments array */
	data->arguments = malloc(counter * sizeof(char *));
	if (data->arguments == NULL)
	{
		perror(data->name);
		exit(errno);
	}

	i = 0;
	data->arguments[i] = _strdup(_strtok(data->input, delimiter));

	/* Set the command name to the first token */
	data->currentCommand = _strdup(data->arguments[0]);

	/* Tokenize the rest of the input line */
	while (data->arguments[i++])
	{
		data->arguments[i] = _strdup(_strtok(NULL, delimiter));
	}
}
