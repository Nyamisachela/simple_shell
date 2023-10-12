#include "shell.h"
/**
 * read_user_input - Read user input and remove newline character.
 *
 * @input: Buffer to store user input.
 * @max_size: Maximum input size.
 * @read_chars: Number of characters read from input.
 */
void read_user_input(char *input, size_t max_size, ssize_t *read_chars)
{
	*read_chars = read(0, input, max_size);
	if (*read_chars == -1)
	{
		perror("read");
		exit(1);
	}
	input[*read_chars - 1] = '\0';
}
