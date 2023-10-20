#include "shell.h"

/**
 * _strtok - Splits a string into tokens based on delimiters.
 *
 * @line: The input string to be tokenized.
 * @delim: The set of delimiter characters to split the string.
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copystr;

	/* If 'line' is not NULL, initialize 'str' to 'line' */
	if (line != NULL)
		str = line;

	/* Find the beginning of the next token */
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
	}

	copystr = str;

	/* If the current character is the end of the string, return NULL */
	if (*copystr == '\0')
		return (NULL);

	/* Find the end of the current token and null-terminate it */
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}

	/* If no more tokens are found, return the last token */
	return (copystr);
}
