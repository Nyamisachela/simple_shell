#include "shell.h"

/**
 * list_length - Determines the length of a linked list.
 * @hh: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_length(const list_t *hh)
{
    size_t i = 0;

    while (hh)
    {
        hh = hh->to_next;
        i++;
    }
    return i;
}

/**
 * list_to_string - Returns an array of strings from the list's 'str' field.
 * @header: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_string(list_t *header)
{
    list_t *nodes = header;
    size_t i = list_length(header), j;
    char **strs;
    char *strr;

    if (!header || !i)
        return NULL;

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return NULL;

    for (i = 0; nodes; nodes = nodes->to_next, i++)
    {
        strr = malloc(strlen(nodes->strr) + 1);
        if (!strr)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }

        strcpy(strr, nodes->strr);
        strs[i] = strr;
    }
    strs[i] = NULL;
    return strs;
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @hh: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *hh)
{
    size_t i = 0;

    while (hh)
    {
        to_puts(to_convert_number(hh->number, 10, 0));
        to_putchar(':');
        to_putchar(' ');
        to_puts(hh->strr ? hh->strr : "(nil)");
        to_puts("\n");
        hh = hh->to_next;
        i++;
    }
    return i;
}

/**
 * node_start_with - Returns the node whose string starts with a given prefix.
 * @nodes: Pointer to the list head.
 * @pref: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *node_start_with(list_t *nodes, char *pref, char c)
{
    char *pp = NULL;

    while (nodes)
    {
        pp = to_start_with(nodes->strr, pref);
        if (pp && ((c == -1) || (*pp == c)))
            return nodes;
        nodes = nodes->to_next;
    }
    return NULL;
}

/**
 * get_node_index - Gets the index of a node in the list.
 * @header: Pointer to the list head.
 * @nodes: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *header, list_t *nodes)
{
    size_t i = 0;

    while (header)
    {
        if (header == nodes)
            return i;
        header = header->to_next;
        i++;
    }
    return -1;
}

