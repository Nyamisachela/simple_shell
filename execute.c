#include "shell.h"

/**
 * execute_command - Execute the specified command.
 *
 * @input: User input containing the command.
 */
void execute_command(char *input)
{
	char *argv[2];
	pid_t child_pid;
	int status;

	if (access(input, X_OK) == 0)
	{
		argv[0] = input;
		argv[1] = NULL;

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(1);
		}

		if (child_pid == 0)
		{
			if (execve(input, argv, NULL) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	else
	{
		fprintf(stderr, "%s: No such file or directory\n", input);
	}
}

