#include "main.h"

/**
 * print_alias - Print, add, or remove aliases.
 * @data: The struct for the program's data.
 * @alias: The name of the alias to be printed.
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int print_alias(ProgramInfo *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->aliases)
	{
		alias_length = str_length(alias);
		for (i = 0; data->aliases[i]; i++)
		{
			if (!alias || (str_compare(data->aliases[i], alias, alias_length)
				&&	data->aliases[i][alias_length] == '='))
			{
				for (j = 0; data->aliases[i][j]; j++)
				{
					buffer[j] = data->aliases[i][j];
					if (data->aliases[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_to_buffer(buffer, "'");
				add_to_buffer(buffer, data->aliases[i] + j + 1);
				add_to_buffer(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - Get the value of an alias.
 * @data: The struct for the program's data.
 * @name: The name of the requested alias.
 * Return: The value of the alias if found, or NULL if not found.
 */
char *get_alias(ProgramInfo *data, char *name)
{
	int i, alias_length;

	if (name == NULL || data->aliases == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->aliases[i]; i++)
	{
		if (str_compare(name, data->aliases[i], alias_length) &&
			data->aliases[i][alias_length] == '=')
		{
			return (data->aliases[i] + alias_length + 1);
		}
	}

	return (NULL);
}

/**
 * set_alias - Add or override an alias.
 * @alias_string: The alias to be set in the form (name='value').
 * @data: The struct for the program's data.
 * Return: 0 if successful, or 1 if an error occurs.
 */
int set_alias(char *alias_string, ProgramInfo *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->aliases == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}
	}

	for (j = 0; data->aliases[j]; j++)
	{
		if (str_compare(buffer, data->aliases[j], i) &&
			data->aliases[j][i] == '=')
		{
			free(data->aliases[j]);
			break;
		}
	}

	if (temp)
	{
		add_to_buffer(buffer, "=");
		add_to_buffer(buffer, temp);
		data->aliases[j] = str_duplicate(buffer);
	}
	else
	{
		data->aliases[j] = str_duplicate(alias_string);
	}

	return (0);
}
