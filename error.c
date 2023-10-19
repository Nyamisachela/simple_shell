#include "shell.h"

/**
 * print_error_string - prints a string to standard error.
 * @str: The string to be printed.
 *
 * Return: Nothing
 */
void print_error_string(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        print_error_character(str[i]);
        i++;
    }
}

/**
 * print_error_character - writes a character to the standard error.
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int print_error_character(char c)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(2, buffer, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buffer[i++] = c;
    return 1;
}

/**
 * write_character_to_fd - writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int write_character_to_fd(char c, int fd)
{
    static int i;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(fd, buffer, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buffer[i++] = c;
    return 1;
}

/**
 * write_string_to_fd - writes a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int write_string_to_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;
    while (*str)
    {
        i += write_character_to_fd(*str++, fd);
    }
    return i;
}

