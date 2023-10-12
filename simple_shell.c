#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * read_user_input - Read user input and remove newline character.
 *
 * @input: Buffer to store user input.
 * @max_size: Maximum input size.
 * @read_chars: Number of characters read from input.
 */
void read_user_input(char *input, size_t max_size, ssize_t *read_chars)
{
	*read_chars = read(0, input, max_size);
	if (*read_chars == -1)
	{
		perror("read");
		exit(1);
	}
	input[*read_chars - 1] = '\0';
}

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

/**
 * main - Entry point of the simple shell program.
 *
 * Description: This function implements a basic Unix shell.
 * It prompts user for a command, executes it, and displays prompt again.
 * If the command is not found, it prints an error message.
 *
 * Return: Always 0 to indicate successful execution.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	ssize_t read_chars;

	while (1)
	{
		display_prompt();
		read_user_input(input, MAX_INPUT_SIZE, &read_chars);

		if (read_chars == 0)
		{
			printf("\n");
			break;
		}

		execute_command(input);
	}
	return (0);
}

