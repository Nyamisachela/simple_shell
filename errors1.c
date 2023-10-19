#include "shell.h"

/**
 * string_to_integer - converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, 0 if no numbers in the string, and -1 on error.
 */
int string_to_integer(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return result;
}

/**
 * print_error_message - prints an error message.
 * @info: The parameter and return information struct.
 * @error_str: String containing the specified error type.
 *
 * Return: None
 */
void print_error_message(info_t *info, char *error_str)
{
    eputs(info->file_name);
    eputs(": ");
    print_decimal(info->line_count, STDERR_FILENO);
    eputs(": ");
    eputs(info->argv[0]);
    eputs(": ");
    eputs(error_str);
}

/**
 * print_decimal - function to print a decimal (integer) number (base 10).
 * @num: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int num, int fd)
{
    int (*write_character)(char) = putchar;
    int i, count = 0;
    unsigned int absolute_value, current;

    if (fd == STDERR_FILENO)
        write_character = eputchar;
    if (num < 0)
    {
        absolute_value = -num;
        write_character('-');
        count++;
    }
    else
        absolute_value = num;
    current = absolute_value;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute_value / i)
        {
            write_character('0' + current / i);
            count++;
        }
        current %= i;
    }
    write_character('0' + current);
    count++;
    return count;
}

/**
 * convert_number - converter function, a clone of itoa.
 * @number: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: A string representation of the number.
 */
char *convert_number(long int number, int base, int flags)
{
    static char *char_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = number;

    if (!(flags & CONVERT_UNSIGNED) && number < 0)
    {
        n = -number;
        sign = '-';
    }
    char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';
    do {
        *--ptr = char_array[n % base];
        n /= base;
    } while (n != 0);
    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_comment - function replaces the first instance of '#' with '\0'.
 * @buffer: The address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comment(char *buffer)
{
    int i;
    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
    }
}

