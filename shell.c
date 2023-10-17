#include "Shell.h"
/**
*main - main entry point
*@argc: argument count
*@argv: null terminated array of string arguments
*Return: 0 upon success.
*/
int main(int argc, char **argv)
{
	char *prompt, *lineptr; /* lineptr = input from user */
	size_t n = 0; /* size of the buffer lineptr */
	ssize_t getline_return  = 0;/*could be no of xters or -1(failure)*/
	char *exit;

	exit = "exit";
	(void)argc;
	argv = malloc(sizeof(char *) * BUFFER_SIZE);
	prompt = ">- ";
	while (1)
	{
		printf("%s", prompt);
		getline_return = getline(&lineptr, &n, stdin);
		if (getline_return < 0)
		{/* Checks if getline failed or encountered EOF */
			printf("\n");
			return (-1);
		}
		else
		{
			argv = split_input(lineptr);
			argc = arg_count(argv);
		}
		if (_strcmp(*argv, exit) == 0)
		{
			break;
		}
		execute(argv);
	}
	free(lineptr);/* free the buffer */
	return (0);
}
