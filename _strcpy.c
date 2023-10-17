#include "Shell.h"
/**
*_strcpy - copies source to a destination
*and returns pointer to destination
*@src: source array
*@dest: dstination array
*Return: pointer to array
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0, i = 0;

	while (src[x] != '\0')
		x++;
	for (i = 0; i <= x; i++)
		*(dest + i) = *(src + i);
	return (dest);
}
