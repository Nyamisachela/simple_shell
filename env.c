#include "main.h"

/**
 * builtin_env - Display the environment where the shell is running.
 * @data: The struct for the program's data.
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int builtin_env(ProgramInfo *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->arguments[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->arguments[1][i]; i++)
		{
			if (data->arguments[1][i] == '=')
			{
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->arguments[1] + i + 1, data);

				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					_print(data->arguments[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->arguments[1][i];
		}
		errno = 2;
		perror(data->currentCommand);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - Set or modify an environment variable.
 * @data: The struct for the program's data.
 * Return: 0 if successful, or an error code if specified in the arguments.
 */
int builtin_set_env(ProgramInfo *data)
{
	if (data->arguments[1] == NULL || data->arguments[2] == NULL)
		return (0);
	if (data->arguments[3] != NULL)
	{
		errno = E2BIG;
		perror(data->currentCommand);
		return (5);
	}

	env_set_key(data->arguments[1], data->arguments[2], data);

	return (0);
}

/**
 * builtin_unset_env - Delete an environment variable.
 * @data: The struct for the program's data.
 * Return: 0.
 */
int builtin_unset_env(ProgramInfo *data)
{
	if (data->arguments[1] == NULL)
		return (0);
	if (data->arguments[2] != NULL)
	{
		errno = E2BIG;
		perror(data->currentCommand);
		return (5);
	}
	env_remove_key(data->arguments[1], data);

	return (0);
}

