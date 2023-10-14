#include "Shell.h"
/**
*split_input - tokenize input
*@lineptr: input from stdin
*Return: argv
*/
char **split_input(char *lineptr)
{
	char *input_cpy;
	char *token, *delim;
	char **argv;
	int i;

	/* Allocate memory for input_cpy */
	input_cpy = malloc(BUFFER_SIZE);

	/* Allocate memory for an array of char pointers */
	argv = malloc(sizeof(char *) * BUFFER_SIZE);
	if (input_cpy == NULL || argv == NULL)
	{
		perror("Memory allocation error");
		exit(1);
	}
	strcpy(input_cpy, lineptr);
	delim = " \n";
	i = 0;
	token = strtok(input_cpy, delim);
	while (token != NULL)
	{
		/* Allocate memory for each token (+1 for null terminator) */
		argv[i] = malloc(strlen(token) + 1);
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL; /* Null-terminate the array */
	free(input_cpy);
	return (argv);
}
/**
*arg_count - count values in argv
*@argv: array of strings
*Return: count
*/
int arg_count(char **argv)
{
	int i;

	for (i = 0; argv[i] != NULL;)
	{
		i++;/* Count the number of strings in argv */
	}
	return (i);
}
