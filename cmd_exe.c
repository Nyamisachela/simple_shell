#include "Shell.h"

/**
 * execute - runs the commands parsed
 * @argv: null-terminated array of commands
 */
void execute(char **argv)
{
	/* Declare variables */
	char *cmd = NULL, *processed_cmd = NULL;
	pid_t child_pid;
	int status;

	if (argv)
	{
		cmd = argv[0];
		processed_cmd = get_path(cmd);
		/* Check for the "env" command to print the environment */
		if (strcmp(cmd, "env") == 0)
		{
			print_env();
			return;
		}

		/* Fork a child process */
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Fork failed");
		}
		else if (child_pid == 0)
		{
			/* This code runs in the child process */
			if (execve(processed_cmd, argv, NULL) == -1)
			{
				perror("Error:");
				exit(1); /* Terminate the child proces*/
			}
		}
		else
		{
			/* This code runs in the parent process */
			waitpid(child_pid, &status, 0); 
			/* Wait for the child to finish */
		}
	}
}
