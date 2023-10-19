#include "Shell.h"
/**
*_strcat - concatenates string 2 to string 1
*@dest: string 1
*@src: string 2
*Return: *dest pointer to string 1
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
	char temp;

	while (dest[i] != '\0')
		i++;
	temp = dest[i];
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = temp;
	return (dest);
}
