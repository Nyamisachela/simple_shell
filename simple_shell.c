#include "shell.h"
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
