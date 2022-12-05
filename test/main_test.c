#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../list.h"

static void clean_int(void *data)
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

static void print_my_int(void *data)
{
    int *my_int;

    my_int = (int *)data;
    printf("%d", *my_int);
}

static bool is_my_int_equal(void *left, void *right)
{
    int *int_left;
    int *int_right;

    int_left = (int *)left;
    int_right = (int *)right;
    return (*int_left == *int_right);
}

static void initialize(t_list *root)
{
    t_list element1 = new_int_element(0);
    t_list element2 = new_int_element(10);
    t_list element3 = new_int_element(20);
    t_list element4 = new_int_element(30);
    t_list element5 = new_int_element(40);

    push_element(root, element1);
    push_element(root, element2);
    push_element(root, element3);
    push_element(root, element4);
    push_element(root, element5);
}

void test_new_element(void)
{
    t_list element = new_int_element(5);
    int *data;

    CU_ASSERT(element->next == NULL);
    CU_ASSERT(element->previous == NULL);
    data = (int *)element->data;
    CU_ASSERT_EQUAL(*data, 5);
    free_element(element);
}

void test_three_element(void)
{
    t_list element1 = new_int_element(0);
    t_list element2 = new_int_element(10);
    t_list element3 = new_int_element(20);
    t_list root = NULL;
    t_list head;
    int *data;

    push_element(&root, element1);
    push_element(&root, element2);
    push_element(&root, element3);
    head = root;

    data = (int *)head->data;
    CU_ASSERT(head == element1);
    CU_ASSERT(*data == 0);

    head = head->next;
    data = (int *)head->data;
    CU_ASSERT(head == element2);
    CU_ASSERT_EQUAL(*data, 10);
    CU_ASSERT(head->previous == element1);

    head = head->next;
    data = (int *)head->data;
    CU_ASSERT(head == element3);
    CU_ASSERT_EQUAL(*data, 20);
    CU_ASSERT(head->previous == element2);
    CU_ASSERT(head->next == NULL);

    clean_list(&root);
}

void test_pop_element(void)
{
    t_list root = NULL;
    t_list last;

    initialize(&root);
    last = root;

    while (last->next)
        last = last->next;
    CU_ASSERT(len_list(root) == 5);

    last = last->previous;
    pop_element(&root);
    CU_ASSERT(last->next == NULL);
    CU_ASSERT(len_list(root) == 4);

    last = last->previous;
    pop_element(&root);
    CU_ASSERT(last->next == NULL);
    CU_ASSERT(len_list(root) == 3);

    clean_list(&root);
}

void test_len_list(void)
{
    t_list root = NULL;

    initialize(&root);

    CU_ASSERT(len_list(root) == 5);
    push_element(&root, new_int_element(50));
    push_element(&root, new_int_element(60));
    CU_ASSERT(len_list(root) == 7);

    clean_list(&root);
}

void test_add_element_at_index(void)
{
    t_list root = NULL;
    t_list element1 = new_int_element(5);
    t_list element2 = new_int_element(-5);

    initialize(&root);

    add_element_at_index(&root, element1, 1);
    CU_ASSERT(root->next == element1);
    add_element_at_index(&root, element2, 0);
    CU_ASSERT(root == element2);

    clean_list(&root);
}

void test_add_element_before(void)
{
    t_list root = NULL;
    t_list new = new_int_element(5);
    t_list current;
    int find_me = 10;

    initialize(&root);
    current = search_element(root, &find_me, is_my_int_equal);

    printf("BEFORE ADD ELEMENT BEFORE: %d\n", 10);
    print_list(root, print_my_int);
    add_element_before(&root, new, current);
    printf("AFTER: \n");
    print_list(root, print_my_int);
    CU_ASSERT(current->previous == new);
    CU_ASSERT(new->next == current);

    clean_list(&root);
}

void test_add_element_after(void)
{
    t_list root = NULL;
    t_list new = new_int_element(25);
    t_list current;
    int find_me = 20;

    initialize(&root);
    current = search_element(root, &find_me, is_my_int_equal);

    printf("BEFORE ADD ELEMENT AFTER: %d\n", 20);
    print_list(root, print_my_int);
    add_element_after(new, current);
    printf("AFTER: \n");
    print_list(root, print_my_int);
    CU_ASSERT(current->next == new);
    CU_ASSERT(new->previous == current);

    clean_list(&root);
}

void test_search_element(void)
{
    t_list root = NULL;
    t_list current;
    int find_me = 0;

    initialize(&root);
    current = search_element(root, &find_me, is_my_int_equal);

    CU_ASSERT(current == root);
    find_me = 99;
    current = search_element(root, &find_me, is_my_int_equal);
    CU_ASSERT(current == NULL);

    clean_list(&root);
}

void test_revert_list(void)
{
    t_list root = NULL;
    t_list last;
    t_list first;
    int find_me = 40;

    initialize(&root);
    first = root;
    last = search_element(root, &find_me, is_my_int_equal);

    CU_ASSERT(last->next == NULL);
    CU_ASSERT(first->previous == NULL);
    printf("BEFORE REVERT LIST\n");
    print_list(root, print_my_int);
    revert_list(&root);
    printf("AFTER: \n");
    print_list(root, print_my_int);
    CU_ASSERT(last == root);
    CU_ASSERT(last->previous == NULL)
    CU_ASSERT(first->next == NULL);

    clean_list(&root);
}

void test_simple_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 30;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 10;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == cpy_element1.next);
    CU_ASSERT(element1->previous == cpy_element2.previous);
    CU_ASSERT(element2->previous == cpy_element1.previous);

    clean_list(&root);
}

void test_consecutive_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 20;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 30;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == element1);
    CU_ASSERT(element1->previous == element2);
    CU_ASSERT(element2->previous == cpy_element1.previous);

    clean_list(&root);
}

void test_head_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 0;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 30;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == cpy_element1.next);
    CU_ASSERT(element1->previous == cpy_element2.previous);
    CU_ASSERT(element2->previous == cpy_element1.previous);
    CU_ASSERT(element2 == root);

    clean_list(&root);
}

void test_head_consecutive_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 0;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 10;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == element1);
    CU_ASSERT(element1->previous == element2);
    CU_ASSERT(element2->previous == cpy_element1.previous);
    CU_ASSERT(element2 == root);

    clean_list(&root);
}

void test_end_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 20;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 40;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == cpy_element1.next);
    CU_ASSERT(element1->previous == cpy_element2.previous);
    CU_ASSERT(element2->previous == cpy_element1.previous);

    clean_list(&root);
}

void test_end_consecutive_swap_element(void)
{
    t_list root = NULL;
    t_list element1;
    t_list element2;
    struct s_list cpy_element1;
    struct s_list cpy_element2;
    int find_me;

    initialize(&root);
    find_me = 30;
    element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 40;
    element2 = search_element(root, &find_me, is_my_int_equal);

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == element1);
    CU_ASSERT(element1->previous == element2);
    CU_ASSERT(element2->previous == cpy_element1.previous);

    clean_list(&root);
}

void test_remove_element(void)
{
    t_list root = NULL;
    int find_me = 2;
    int *data;
    t_list element1;
    t_list element2;

    initialize(&root);
    element1 = root;

    for (int i = 1; i < 2; i++)
        element1 = element1->next;
    element2 = element1->next;
    data = (int *)element2->data;
    CU_ASSERT_EQUAL(*data, 20);

    remove_element(&root, &find_me, INDEX, is_my_int_equal);
    element2 = element1->next;
    data = (int *)element2->data;
    CU_ASSERT_EQUAL(*data, 30);

    clean_list(&root);
}

void test_clean_list(void)
{
    t_list root = NULL;

    initialize(&root);
    clean_list(&root);
    CU_ASSERT(root == NULL);
}

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main(void)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite 1", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (
        NULL == CU_add_test(pSuite, "of test_new_element()", test_new_element) ||
        NULL == CU_add_test(pSuite, "of test_three_element()", test_three_element) ||
        NULL == CU_add_test(pSuite, "of test_pop_element()", test_pop_element) ||
        NULL == CU_add_test(pSuite, "of test_len_list()", test_len_list) ||
        NULL == CU_add_test(pSuite, "of test_add_element_at_index()", test_add_element_at_index) ||
        NULL == CU_add_test(pSuite, "of test_add_element_before()", test_add_element_before) ||
        NULL == CU_add_test(pSuite, "of test_add_element_after()", test_add_element_after) ||
        NULL == CU_add_test(pSuite, "of test_search_element()", test_search_element) ||
        NULL == CU_add_test(pSuite, "of test_revert_list()", test_revert_list) ||
        NULL == CU_add_test(pSuite, "of test_swap_element()", test_simple_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_consecutive_swap_element()", test_consecutive_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_head_swap_element()", test_head_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_head_consecutive_swap_element()", test_head_consecutive_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_end_swap_element()", test_end_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_end_consecutive_swap_element()", test_end_consecutive_swap_element) ||
        NULL == CU_add_test(pSuite, "of test_remove_element()", test_remove_element) ||
        NULL == CU_add_test(pSuite, "of test_clean_list()", test_clean_list))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}