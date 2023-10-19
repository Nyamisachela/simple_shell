#include "shell.h"

/**
 * main - Entry point of the program.
 * @agc: Argument count.
 * @agv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int agc, char **agv)
{
    // Initialize the info structure.
    info_t _infor[] = { INFO_INIT };

    // Initialize a file descriptor variable.
    int fdd = 2;

    // Inline assembly to perform arithmetic operations.
    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fdd)
        : "r" (fdd)
    );

    // Check if a specific command-line argument is provided.
    if (agc == 2)
    {
        // Try to open a file for reading.
        fdd = open(agv[1], O_RDONLY);
        if (fdd == -1)
        {
            // Handle different error cases, such as permission denied or file not found.
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                to_eputs(agv[0]);
                to_eputs(": 0: Can't open ");
                to_eputs(agv[1]);
                to_eputchar('\n');
                to_eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        // Set the read file descriptor in the info structure.
        _infor->to_readfd = fdd;
    }

    // Populate the environment list in the info structure.
    to_populate_env_list(_infor);

    // Read command history from a file.
    to_read_history(_infor);

    // Start the main shell logic.
    to_hsh(_infor, agv);

    return EXIT_SUCCESS;
}

