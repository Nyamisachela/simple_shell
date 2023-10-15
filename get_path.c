#include "Shell.h"

/**
*get_path - gets the environment variables
*@cmd: argv[0]
*Return: pointer to buffer containing the path
*/
char *get_path(char *cmd)
{
	char *path, *path_cpy, *path_token, *file_path;
	int cmd_length, dir_len;
	struct stat buffer;

	path = getenv("PATH");/* gets the path from the env variables */
	if (path)
	{
		path_cpy = strdup(path);/* copy of path to use with tokenization */
		cmd_length = strlen(cmd);/* will be used for allocating memory */
		path_token = strtok(path_cpy, ":");/* path is separated by : */
		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			file_path = malloc(cmd_length + dir_len + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_cpy);
				return (file_path);
			}
			else
			{/*if the file path is invalid, check next path */
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (stat(cmd, &buffer) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}
