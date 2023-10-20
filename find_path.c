#include "main.h"

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
			return (126);
		}
		return (0);
	}
	/* Return an errno code if the file does not exist. */
	errno = 127;
	return (127);
}

/**
 * find_program - Find a program in the PATH environment variable.
 * @data: A pointer to the program's data.
 * Return: Return 0 if successful, an error code otherwise.
 */
int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/* Check if it's a full path or an executable in the same path. */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Tokenize the PATH environment variable into directories.
 * @data: A pointer to the program's data.
 * Return: An array of path directories.
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int num_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Get the value of the PATH environment variable. */
	PATH = env_get_key("PATH", data);

	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/* Return NULL if the PATH is not found. */
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			num_directories++;
	}

	tokens = malloc(sizeof(char *) * num_directories);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));

	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}
