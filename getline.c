#include "shell.h"

/**
 * input_buffer - buffers chained commands for processing.
 * @info: Parameter struct.
 * @buffer: Address of the buffer.
 * @length: Address of the length variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytes_read = 0;
    size_t new_length = 0;

    if (!*length) { /* If nothing left in the buffer, fill it. */
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigint_handler);
        bytes_read = get_input_line(info, buffer, &new_length);

        if (bytes_read > 0) {
            if ((*buffer)[bytes_read - 1] == '\n') {
                (*buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline. */
                bytes_read--;
            }
            info->linecount_flags = 1;
            remove_comment(*buffer);
            build_history_list(info, *buffer, info->histcount++);
            *length = bytes_read;
            info->cmd_buffer = buffer;
        }
    }
    return bytes_read;
}

/**
 * get_input_line - retrieves an input line without the newline character.
 * @info: Parameter struct.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input_line(info_t *info)
{
    static char *buffer; /* The ';' command chain buffer. */
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buf_p = &(info->arg), *pp;

    putchar(BUF_FLUSH);
    bytes_read = input_buffer(info, &buffer, &length);

    if (bytes_read == -1) { /* EOF */
        return -1;
    }

    if (length) { /* Commands left in the chain buffer. */
        j = i; /* Initialize a new iterator to the current buffer position. */
        pp = buffer + i; /* Get a pointer for return. */

        check_command_chain(info, buffer, &j, i, length);
        while (j < length) { /* Iterate to semicolon or end. */
            if (is_command_chain(info, buffer, &j)) {
                break;
            }
            j++;
        }

