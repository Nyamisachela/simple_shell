#include "shell.h"

/**
 * _strlen - Get the length of a string.
 *
 * @string: Pointer to the string.
 * Return: Length of the string.
 */
int _strlen(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * _strdup - Duplicate a string.
 *
 * @string: String to be duplicated.
 * Return: Pointer to the duplicated string.
 */
char *_strdup(char *string)
{
	char *result;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = _strlen(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Memory Allocation Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * _strcmp - Compare two strings.
 *
 * @string3: String one, or the shorter one.
 * @string4: String two, or the longer one.
 * @number: The number of characters to be compared, 0 for infinite.
 * Return: 1 if the strings are equal, 0 if they are different.
 */
int _strcmp(char *string3, char *string4, int number)
{
	int iterator;

	if (string3 == NULL && string4 == NULL)
		return (1);

	if (string3 == NULL || string4 == NULL)
		return (0);

	if (number == 0) /* Infinite length */
	{
		if (_strlen(string3) != _strlen(string4))
			return (0);
		for (iterator = 0; string3[iterator]; iterator++)
		{
			if (string3[iterator] != string4[iterator])
				return (0);
		}
		return (1);
	}
	else /* If a number of characters to be compared is specified */
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string3[iterator] != string4[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * _strcat - Concatenate two strings.
 *
 * @string3: String to be concatenated.
 * @string4: String to be concatenated.
 *
 * Return: Pointer to the concatenated string.
 */
char *_strcat(char *string3, char *string4)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string3 == NULL)
		string3 = "";
	length1 = _strlen(string3);

	if (string4 == NULL)
		string4 = "";
	length2 = _strlen(string4);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Memory Allocation Error");
		return (NULL);
	}

	/* Copy string3 */
	for (length1 = 0; string3[length1] != '\0'; length1++)
		result[length1] = string3[length1];
	free(string3);

	/* Copy string4 */
	for (length2 = 0; string4[length2] != '\0'; length2++)
	{
		result[length1] = string4[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * revstring - Reverse a string.
 *
 * @string: Pointer to the string.
 * Return: Void.
 */
void revstring(char *string)
{
	int i = 0, length = _strlen(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}

