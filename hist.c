#include "shell.h"

/**
 * get_history_file - Retrieves the path of the history file.
 * @info: Pointer to the info_t structure.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
    char *buffer, *direction;

    direction = getenv("HOME");
    if (!direction)
        return NULL;

    buffer = malloc(sizeof(char) * (strlen(direction) + strlen(HIST_FILE) + 2));
    if (!buffer)
        return NULL;

    buffer[0] = '\0';
    strcpy(buffer, direction);
    strcat(buffer, "/");
    strcat(buffer, HIST_FILE);

    return buffer;
}

/**
 * write_history - Writes the history to a file, creating or overwriting it.
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *nodes = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (nodes = info->_history; nodes; nodes = nodes->to_next)
    {
        to_putsfd(nodes->strr, fd);
        to_putfd('\n', fd);
    }

    to_putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * read_history - Reads the command history from a file.
 * @info: Pointer to the info_t structure.
 *
 * Return: The number of history lines read, or 0 on failure.
 */
int read_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buffer = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buffer = malloc(sizeof(char) * (fsize + 1));
    if (!buffer)
        return 0;

    rdlen = read(fd, buffer, fsize);
    buffer[fsize] = '\0;

    if (rdlen <= 0)
        return free(buffer), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            to_build_history_list(info, buffer + last, line_count++);
            last = i + 1;
        }
    }

    if (last != i)
        to_build_history_list(info, buffer + last, line_count++);

    free(buffer);
    info->line_count = line_count;

    while (info->line_count-- >= HIST_MAX)
        to_delete_node_at_ind(&(info->_history), 0);

    to_renumber_history(info);

    return info->line_count;
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Pointer to the info_t structure.
 * @buffer: The command to add to the history.
 * @line_count: The history line count.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
    list_t *nodes = NULL;

    if (info->_history)
        nodes = info->_history;

    to_add_node_end(&nodes, buffer, line_count);

    if (!info->_history)
        info->_history = nodes;

    return 0;
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Pointer to the info_t structure.
 *
 * Return: The new history line count.
 */
int renumber_history(info_t *info)
{
    list_t *nodes = info->_history;
    int i = 0;

    while (nodes)
    {
        nodes->number = i++;
        nodes = nodes->to_next;
    }

    return (info->line_count = i);
}

