#include "main.h"

/**
 * execute - Execute a command with its complete path variables.
 * @data: A pointer to the program's data.
 * Return: Returns 0 on success, or -1 on failure.
 */
int cmd_execute(ProgramInfo *data)
{
	int retval = 0, status;
	pid_t child_pid;

	/* Check if the program is a built-in command. */
	retval = builtins_list(data);
	if (retval != -1)
	{
		/* The program was found among built-ins. */
		return retval;
	}

	/* Check for the program in the file system. */
	retval = find_program(data);
	if (retval)
	{
		/* The program was not found. */
		return retval;
	}
	else
	{
		/* The program was found, create a child process. */
		child_pid = fork();
		if (child_pid == -1)
		{
			/* Fork call failed, print an error message. */
			perror(data->currentCommand);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			/* Child process: execute the program. */
			retval = execve(data->arguments[0], data->arguments, data->env);
			if (retval == -1)
			{
				/* Error occurred during execve, print an error message. */
				perror(data->currentCommand);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process: wait for the child and check its exit status. */
			wait(&status);
			if (WIFEXITED(status))
			{
				errno = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				errno = 128 + WTERMSIG(status);
			}
		}
	}
	return 0;
}
