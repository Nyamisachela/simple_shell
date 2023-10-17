#include "Shell.h"
/**
*_strlen - returns lenght of a string
*@s: first character of a string
*Return: number of iterations
*/
int _strlen(char *s)
{
	int a = 0;

	while (*s != '\0')
	{
		a++;
		s++;
	}
	return (a++);
}
