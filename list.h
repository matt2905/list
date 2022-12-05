#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct s_list *t_list;

typedef bool (*t_is_equal)(void *, void *);
typedef void (*t_print)(void *);
typedef void (*t_clean)(void *);

struct s_list
{
    void *data;
    t_clean clean_up;
    t_list previous;
    t_list next;
};

typedef enum e_remove_type
{
    FIRST,
    ALL,
    INDEX
} t_remove_type;

t_list new_element(void *data, t_clean clean_up);
void free_element(t_list element);
void push_element(t_list *root, t_list element);
void pop_element(t_list *root);
int len_list(t_list root);
void clean_list(t_list *root);
void print_list(t_list root, t_print print);

void add_element_at_index(t_list *root, t_list element, int index);
void add_element_before(t_list *root, t_list new, t_list current);
void add_element_after(t_list new, t_list current);
t_list search_element(t_list root, void *find_me, t_is_equal is_equal);
void swap_element(t_list *root, t_list left, t_list right);
void revert_list(t_list *root);
void remove_element(t_list *root, void *find_me, t_remove_type remove_type, t_is_equal is_equal);

#endif