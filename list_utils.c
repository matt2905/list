#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/**
 * @brief allocate a new element.
 *
 * @param data
 * @return t_list
 */
t_list new_element(void *data, t_clean clean_up)
{
    t_list element;

    element = (t_list)malloc(sizeof(struct s_list));
    if (!element)
    {
        printf("Allocation error\n");
        exit(1);
    }
    element->data = data;
    element->previous = NULL;
    element->next = NULL;
    element->clean_up = clean_up;
    return element;
}

/**
 * @brief free an element given
 *
 * @param element
 */
void free_element(t_list element)
{
    if (element->next)
        element->next->previous = element->previous;
    if (element->previous)
        element->previous->next = element->next;
    element->next = NULL;
    element->previous = NULL;
    element->clean_up(element->data);
    free(element);
}

/**
 * @brief push a new element to the list;
 *
 * @param root
 * @param data
 */
void push_element(t_list *root, t_list element)
{
    t_list current;

    if (*root)
    {
        current = *root;
        while (current->next)
            current = current->next;
        current->next = element;
        element->previous = current;
    }
    else
        *root = element;
}

/**
 * @brief pop the last element of the list
 *
 * @param root
 */
void pop_element(t_list *root)
{
    t_list current;

    if (*root)
    {
        current = *root;
        while (current->next)
            current = current->next;
        free_element(current);
    }
}

/**
 * @brief get the lenght of the list
 *
 * @param root
 * @return int
 */
int len_list(t_list root)
{
    t_list current;
    int i;

    i = 0;
    if (root)
    {
        current = root;
        for (i = 1; current->next; i++)
            current = current->next;
    }
    return i;
}

/**
 * @brief free all element of the list
 *
 * @param root
 */
void clean_list(t_list *root)
{
    t_list previous;

    if (*root)
    {
        while ((*root)->next)
        {
            previous = *root;
            *root = (*root)->next;
            free_element(previous);
        }
        free_element(*root);
        *root = NULL;
    }
}

/**
 * @brief function to display the content and the index of the list
 *
 * @param root
 */
void print_list(t_list root, t_print print)
{
    t_list current;
    int i;

    i = 0;
    if (root)
    {
        current = root;
        for (i = 1; current->next; i++)
        {
            printf("index: [%d], value:(", i - 1);
            print(current->data);
            printf(")\n");
            current = current->next;
        }
        printf("index: [%d], value:(", i - 1);
        print(current->data);
        printf(")\n");
    }
}