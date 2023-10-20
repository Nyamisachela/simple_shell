#include "shell.h"

/**
 * check_file - Check if file exists, is not a dir,has execute permissions.
 * @full_path: The pointer to the full file name.
 * Return: Return 0 on success, errno code otherwise
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (errno);
		}
		return (0);
	}
	/* Return an errno code if the file does not exist. */
	errno = 127;
	return (errno);
}

/**
 * find_program - Find a program in the PATH environment variable.
 * @data: A pointer to the program's data.
 * Return: Return 0 if successful, an error code otherwise.
 */
int find_program(ProgramInfo *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->currentCommand)
		return (2);

	/* Check if it's a full path or an executable in the same path. */
	if (data->currentCommand[0] == '/' || data->currentCommand[0] == '.')
		return (check_file(data->currentCommand));

	free(data->arguments[0]);
	data->arguments[0] = _strcat(_strdup("/"), data->currentCommand);
	if (!data->arguments[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		directories[i] = _strcat(directories[i], data->arguments[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->arguments[0]);
			data->arguments[0] = _strdup(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->arguments[0]);
	data->arguments[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Tokenize the PATH environment variable into directories.
 * @data: A pointer to the program's data.
 * Return: An array of path directories.
 */
char **tokenize_path(ProgramInfo *data)
{
	int i = 0;
	int num_directories = 2;
	char **arguments = NULL;
	char *PATH;

	/* Get the value of the PATH environment variable. */
	PATH = env_get_key("PATH", data);

	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/* Return NULL if the PATH is not found. */
		return (NULL);
	}

	PATH = _strdup(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			num_directories++;
	}

	arguments = malloc(sizeof(char *) * num_directories);

	i = 0;
	arguments[i] = _strdup(_strtok(PATH, ":"));

	while (arguments[i++])
	{
		arguments[i] = _strdup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (arguments);
}
