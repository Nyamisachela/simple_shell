#include "shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: pointer to the information struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->to_readfd <= 2);
}

/**
 * is_delimiter - checks whether a character is a delimiter
 * @c: the character to check
 * @delim_str: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delim_str)
{
    while (*delim_str) {
        if (*delim_str++ == c)
            return 1;
    }
    return 0;
}

/**
 * is_alpha - checks if a character is alphabetic
 * @c: The character to check
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise
 */
int is_alpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if there are no numbers in the string, the converted number otherwise
 */
int str_to_int(char *s)
{
    int i, sign = 1, flags = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flags != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flags = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flags == 1)
            flags = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return output;
}

