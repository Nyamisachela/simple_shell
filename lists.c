#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of a linked list.
 * @header: Pointer to the head node of the list.
 * @strr: The string field of the new node.
 * @number: The index used in history.
 *
 * Return: The size of the list.
 */
list_t *add_node(list_t **header, const char *strr, int number)
{
    list_t *new_node;

    if (!header)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    memset((void *)new_node, 0, sizeof(list_t));
    new_node->number = number;

    if (strr)
    {
        new_node->strr = strdup(strr);
        if (!new_node->strr)
        {
            free(new_node);
            return NULL;
        }
    }

    new_node->to_next = *header;
    *header = new_node;

    return new_node;
}

/**
 * add_node_end - Adds a new node to the end of a linked list.
 * @header: Pointer to the head node of the list.
 * @strr: The string field of the new node.
 * @number: The index used in history.
 *
 * Return: The size of the list.
 */
list_t *add_node_end(list_t **header, const char *strr, int number)
{
    list_t *new_node, *nodes;

    if (!header)
        return NULL;

    nodes = *header;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    memset((void *)new_node, 0, sizeof(list_t));
    new_node->number = number;

    if (strr)
    {
        new_node->strr = strdup(strr);
        if (!new_node->strr)
        {
            free(new_node);
            return NULL;
        }
    }

    if (nodes)
    {
        while (nodes->to_next)
            nodes = nodes->to_next;
        nodes->to_next = new_node;
    }
    else
        *header = new_node;

    return new_node;
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @hh: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *hh)
{
    size_t i = 0;

    while (hh)
    {
        to_puts(hh->strr ? hh->strr : "(nil)");
        to_puts("\n");
        hh = hh->to_next;
        i++;
    }

    return i;
}

/**
 * delete_node_at_index - Deletes a node at the given index.
 * @header: Pointer to the first node of the list.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **header, unsigned int index)
{
    list_t *nodes, *prev_nodes;
    unsigned int i = 0;

    if (!header || !*header)
        return 0;

    if (!index)
    {
        nodes = *header;
        *header = (*header)->to_next;
        free(nodes->strr);
        free(nodes);
        return 1;
    }

    nodes = *header;
    while (nodes)
    {
        if (i == index)
        {
            prev_nodes->to_next = nodes->to_next;
            free(nodes->strr);
            free(nodes);
            return 1;
        }
        i++;
        prev_nodes = nodes;
        nodes = nodes->to_next;
    }

    return 0;
}

/**
 * free_list - Frees all nodes in a linked list.
 * @header_ptr: Pointer to the head node of the list.
 *
 * Return: Void.
 */
void free_list(list_t **header_ptr)
{
    list_t *nodes, *next_nodes, *header;

    if (!header_ptr || !*header_ptr)
        return;

    header = *header_ptr;
    nodes = header;

    while (nodes)
    {
        next_nodes = nodes->to_next;
        free(nodes->strr);
        free(nodes);
        nodes = next_nodes;
    }

    *header_ptr = NULL;
}

