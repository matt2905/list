#include <stdio.h>
#include "list.h"

/**
 * @brief add a new element to the list at index
 *
 * @param root
 * @param element
 * @param index
 */
void add_element_at_index(t_list *root, t_list element, int index)
{
    t_list current;
    int i;

    i = 0;
    if (*root)
    {
        current = *root;
        while (current->next && i < index)
        {
            current = current->next;
            i++;
        }
        if (i == index)
        {
            element->next = current;
            element->previous = current->previous;
            current->previous = element;
            if (index != 0)
                element->previous->next = element;
            else
                *root = element;
        }
        else
            printf("Index Error\n");
    }
}

/**
 * @brief add a new element to the list before current element
 *
 * @param root
 * @param new
 * @param current
 */
void add_element_before(t_list *root, t_list new, t_list current)
{
    new->next = current;
    if (current->previous)
    {
        new->previous = current->previous;
        current->previous->next = new;
        current->previous = new;
    }
    else
    {
        current->previous = new;
        *root = new;
    }
}

/**
 * @brief add a new element to the list after current element
 *
 * @param new
 * @param current
 */
void add_element_after(t_list new, t_list current)
{
    new->previous = current;
    if (current->next)
    {
        new->next = current->next;
        current->next->previous = new;
        current->next = new;
    }
    else
        current->next = new;
}

/**
 * @brief return an element of the list
 *
 * @param root
 * @param find_me data needed to be found
 * @param is_equal comparaison function
 * @return t_list
 */
t_list search_element(t_list root, void *find_me, t_is_equal is_equal)
{
    t_list current;

    current = root;
    while (current->next)
    {
        if (is_equal(current->data, find_me))
            return current;
        current = current->next;
    }
    if (is_equal(current->data, find_me))
        return current;
    return NULL;
}

/**
 * @brief swap two element of a list
 *
 * @param root
 * @param left
 * @param right
 */
void swap_element(t_list *root, t_list left, t_list right)
{
    struct s_list tmp;

    if (*root == left)
        *root = right;
    else if (*root == right)
        *root = left;

    tmp.next = left->next;
    tmp.previous = left->previous;
    left->next = right->next;
    if (right->next)
        right->next->previous = left;
    if (right->previous == left)
        left->previous = right;
    else
        left->previous = right->previous;
    if (left->previous)
        left->previous->next = left;
    if (right->next != left)
        right->next = tmp.next;
    if (right->next)
        right->next->previous = right;
    right->previous = tmp.previous;
    if (right->previous)
        right->previous->next = right;
}

/**
 * @brief reverse order of the list
 *
 * @param root
 */
void revert_list(t_list *root)
{
    t_list tmp;

    while ((*root)->next)
    {
        tmp = (*root)->next;
        (*root)->next = (*root)->previous;
        (*root)->previous = tmp;
        *root = tmp;
    }
    (*root)->next = (*root)->previous;
    (*root)->previous = NULL;
}

/**
 * @brief remove either an element at index, one or all element equal to value
 *
 * @param root
 * @param find_me data needed to be found
 * @param criteria
 */
void remove_element(t_list *root, void *find_me, t_remove_type remove_type, t_is_equal is_equal)
{
    t_list current;
    int i;
    int index;

    i = 0;
    current = *root;
    if (remove_type == INDEX)
    {
        index = *((int *)find_me);
        while (current->next && i < index)
        {
            current = current->next;
            i++;
        }
        if (i == index)
            free_element(current);
    }
    else
    {
        if (remove_type == ALL)
        {
            while ((current = search_element(*root, find_me, is_equal)))
                free_element(current);
        }
        else
        {
            current = search_element(*root, find_me, is_equal);
            free_element(current);
        }
    }
}