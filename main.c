#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void clean_int(void *data)
{
    free(data);
}

static t_list new_int_element(int value)
{
    t_list new;
    int *data;

    data = (int *)malloc(sizeof(int));
    *data = value;
    new = new_element((void *)data, clean_int);
    return new;
}

void print_my_int(void *data)
{
    int *my_int;

    my_int = (int *)data;
    printf("%d", *my_int);
}

bool is_my_int_equal(void *left, void *right)
{
    int *int_left;
    int *int_right;

    int_left = (int *)left;
    int_right = (int *)right;
    return (*int_left == *int_right);
}

static void swap(t_list *root)
{
    t_list left;
    t_list right;
    int find_me;

    find_me = 51;
    left = search_element(*root, &find_me, is_my_int_equal);
    find_me = 3;
    right = search_element(*root, &find_me, is_my_int_equal);
    swap_element(root, left, right);
}

int main(void)
{
    t_list root;
    t_list result;
    int i;
    int find_me;

    root = NULL;
    for (i = 0; i < 10; i++)
        push_element(&root, new_int_element(i));

    add_element_at_index(&root, new_int_element(3), 2);
    pop_element(&root);

    find_me = 3;
    result = search_element(root, &find_me, is_my_int_equal);
    add_element_before(&root, new_int_element(-3), result);

    find_me = 5;
    result = search_element(root, &find_me, is_my_int_equal);
    add_element_after(new_int_element(51), result);

    swap(&root);
    revert_list(&root);

    find_me = 2;
    remove_element(&root, &find_me, INDEX, is_my_int_equal);
    push_element(&root, new_int_element(51));

    find_me = 51;
    remove_element(&root, &find_me, FIRST, is_my_int_equal);
    push_element(&root, new_int_element(3));
    push_element(&root, new_int_element(3));

    find_me = 3;
    printf("before: \n");
    print_list(root, print_my_int);
    remove_element(&root, &find_me, ALL, is_my_int_equal);

    printf("after: \n");
    print_list(root, print_my_int);
    printf("len: %d\n", len_list(root));
    clean_list(&root);

    return (0);
}