#include "Shell.h"
/**
*execute - runs the commands parsed
*@argv: null terminated array of commands
*/
void execute(char **argv)
{
	char *cmd = NULL, *processed_cmd = NULL;

	if (argv)
	{
		cmd  = argv[0];
		processed_cmd = get_path(cmd);
		if (execve(processed_cmd, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
