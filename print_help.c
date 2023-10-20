#include "main.h"

/**
 * _print - Write an array of characters to standard output.
 *
 * @string: The pointer to the character array.
 * Return: The number of bytes written. On error, -1 is returned, and
 * errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * _printe - Write an array of characters to standard error.
 *
 * @string: The pointer to the character array.
 * Return: The number of bytes written. On error, -1 is returned, and
 * errno is set appropriately.
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - Write an array of characters to standard error with error details.
 *
 * @errorcode: The error code to print.
 * @data: The pointer to the program's data.
 * Return: The number of bytes written. On error, -1 is returned, and
 * errno is set appropriately.
 */
int _print_error(int errorcode, ProgramInfo *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->executionCount, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->arguments[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": Can't change directory to ");
		_printe(data->arguments[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->currentCommand);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->currentCommand);
		_printe(": Permission denied\n");
	}
	return (0);
}
