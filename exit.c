#include "shell.h"

/**
 * copy_string_with_limit - copies a string up to a specified limit.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @limit: The maximum number of characters to copy.
 *
 * Return: The concatenated string.
 */
char *copy_string_with_limit(char *destination, char *source, int limit)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < limit - 1)
    {
        destination[i] = source[i];
        i++;
    }
    if (i < limit)
    {
        j = i;
        while (j < limit)
        {
            destination[j] = '\0';
            j++;
        }
    }
    return result;
}

/**
 * concatenate_strings_with_limit - concatenates two strings up to a specified limit.
 * @destination: The first string.
 * @source: The second string.
 * @limit: The maximum number of bytes to be used.
 *
 * Return: The concatenated string.
 */
char *concatenate_strings_with_limit(char *destination, char *source, int limit)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;
    while (source[j] != '\0' && j < limit)
    {
        destination[i] = source[j];
        i++;
        j++;
    }
    if (j < limit)
        destination[i] = '\0';
    return result;
}

/**
 * find_character_in_string - locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area containing the character, or NULL if not found.
 */
char *find_character_in_string(char *s, char c)
{
    do {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}

