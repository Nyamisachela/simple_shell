#include "main.h"

/**
 * builtins_list - Search for a matching built-in command and execute it.
 * @data: The struct for the program's data.
 * Return: The return value of the executed function if there is a match,
 *         otherwise, it returns -1.
 */
int builtins_list(ProgramInfo *data)
{
	int iterator;
	builtins options[] = {
		{"help", builtin_help},
		{"exit", builtin_exit},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/* Iterate through the structure to find a match. */
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		/* Check if there is a match between the given command and a built-in. */
		if (str_compare(options[iterator].builtin, data->currentCommand, 0))
		{
			/* Execute the function and return its return value. */
			return (options[iterator].function(data));
		}
	}

	/* Return -1 if there is no match. */
	return (-1);
}
