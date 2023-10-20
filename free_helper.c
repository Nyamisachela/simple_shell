#include "main.h"

/**
 * free_recurrent_data - Free the fields needed for each loop iteration.
 * @data: A pointer to the program's data.
 * Return: This function has no return value.
 */
void free_recurrent_data(ProgramInfo *data)
{
	if (data->arguments)
		free_array_of_pointers(data->arguments);
	if (data->input)
		free(data->input);
	if (data->currentCommand)
		free(data->currentCommand);

	data->input = NULL;
	data->currentCommand = NULL;
	data->arguments = NULL;
}

/**
 * free_data - Free all fields of the data structure.
 * @data: A pointer to the program's data.
 * Return: This function has no return value.
 */
void free_data(ProgramInfo *data)
{
	if (data->fd != 0)
	{
		if (close(data->fd))
			perror(data->name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->aliases);
}

/**
 * free_array_of_pointers - Free each pointer in an array of pointers and the array itself.
 * @array: The array of pointers to be freed.
 * Return: This function has no return value.
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}

