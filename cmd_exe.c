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
<<<<<<< HEAD
	char *string_literal;
=======
>>>>>>> 4f2d09324313f9f5f1bf8b52339e46e3996552ed

	string_literal = "env";
	if (argv)
	{
		cmd = argv[0];
		processed_cmd = get_path(cmd);
		/* Fork a child process */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork failed");
		}
		else if (child_pid == 0)
		{
			/* This code runs in the child process */
<<<<<<< HEAD
			if (strcmp(*argv, string_literal) == 0)
			{
				print_env();
				return;
			}
			else if (execve(processed_cmd, argv, NULL) == -1)
=======
			if (execve(processed_cmd, argv, NULL) == -1)
>>>>>>> 4f2d09324313f9f5f1bf8b52339e46e3996552ed
			{
				perror("Error:");
				exit(1);
				/* Terminate the child process if execve fails */
			}
		}
		else
		{/* This code runs in the parent process */
		waitpid(child_pid, &status, 0);
		/* Wait for the child to finish */
		}
	}
}
