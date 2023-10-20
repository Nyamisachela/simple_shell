#include "main.h"

/**
 * expand_variables - Expand variables in the input line.
 * @data: A pointer to the program's data struct.
 * Return: This function does not return a value but sets error if necessary.
 */
void expand_variables(ProgramInfo *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input == NULL)
		return;

	buffer_add(line, data->input);

	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = env_get_key(expansion, data);
			line[i] = '\0';
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	}

	if (!str_compare(data->input, line, 0))
	{
		free(data->input);
		data->input = str_duplicate(line);
	}
}

/**
 * expand_alias - Expand aliases in the input line.
 * @data: A pointer to the program's data struct.
 * Return: This function does not return a value but sets error if necessary.
 */
void expand_alias(ProgramInfo *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input == NULL)
		return;

	buffer_add(line, data->input);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}

	if (was_expanded)
	{
		free(data->input);
		data->input = str_duplicate(line);
	}
}

/**
 * buffer_add - Append a string at the end of a buffer.
 * @buffer: The buffer to be filled.
 * @str_to_add: The string to be copied into the buffer.
 * Return: The function returns the new length of the buffer.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, i;

	length = str_length(buffer);

	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}

	buffer[length + i] = '\0';
	return (length + i);
}
