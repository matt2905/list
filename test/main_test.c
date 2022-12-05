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

static t_list root = NULL;

void test_three_element(void)
{
    t_list element1 = new_int_element(0);
    t_list element2 = new_int_element(10);
    t_list element3 = new_int_element(20);
    int *data;
    t_list head;

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
}

void test_pop_element(void)
{
    t_list last = root;

    while (last->next)
        last = last->next;
    CU_ASSERT(len_list(root) == 3);

    last = last->previous;
    pop_element(&root);
    CU_ASSERT(last->next == NULL);
    CU_ASSERT(len_list(root) == 2);

    last = last->previous;
    pop_element(&root);
    CU_ASSERT(last->next == NULL);
    CU_ASSERT(len_list(root) == 1);
}

void test_len_list(void)
{
    CU_ASSERT(len_list(root) == 1);
    push_element(&root, new_int_element(10));
    push_element(&root, new_int_element(20));
    CU_ASSERT(len_list(root) == 3);
}

void test_add_element_at_index(void)
{
    t_list element1 = new_int_element(3);
    t_list element2 = new_int_element(-3);

    add_element_at_index(&root, element1, 1);
    CU_ASSERT(root->next == element1);
    add_element_at_index(&root, element2, 0);
    CU_ASSERT(root == element2);
}

void test_add_element_before_this(void)
{
    t_list new = new_int_element(5);
    int find_me = 10;
    t_list this = search_element(root, &find_me, is_my_int_equal);

    printf("BEFORE ADD ELEMENT BEFORE THIS: %d\n", 10);
    print_list(root, print_my_int);
    add_element_before_this(&root, new, this);
    printf("AFTER: \n");
    print_list(root, print_my_int);
    CU_ASSERT(this->previous == new);
    CU_ASSERT(new->next == this);
}

void test_add_element_after_this(void)
{
    t_list new = new_int_element(51);
    int find_me = 20;
    t_list this = search_element(root, &find_me, is_my_int_equal);

    printf("BEFORE ADD ELEMENT AFTER THIS: %d\n", 20);
    print_list(root, print_my_int);
    add_element_after_this(new, this);
    printf("AFTER: \n");
    print_list(root, print_my_int);
    CU_ASSERT(this->next == new);
    CU_ASSERT(new->previous == this);
}

void test_search_element(void)
{
    int find_me = -3;
    t_list this = search_element(root, &find_me, is_my_int_equal);
    CU_ASSERT(this == root);

    find_me = 99;
    this = search_element(root, &find_me, is_my_int_equal);
    CU_ASSERT(this == NULL);
}

void test_revert_list(void)
{
    int find_me = 51;
    t_list last = search_element(root, &find_me, is_my_int_equal);
    t_list first = root;

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
}

void test_swap_element(void)
{
    int find_me = 20;
    t_list element1 = search_element(root, &find_me, is_my_int_equal);
    find_me = 3;
    t_list element2 = search_element(root, &find_me, is_my_int_equal);
    struct s_list cpy_element1;
    struct s_list cpy_element2;

    cpy_element1.next = element1->next;
    cpy_element1.previous = element1->previous;
    cpy_element2.next = element2->next;
    cpy_element2.previous = element2->previous;

    swap_element(&root, element1, element2);
    CU_ASSERT(element1->next == cpy_element2.next);
    CU_ASSERT(element2->next == cpy_element1.next);
    CU_ASSERT(element1->previous == cpy_element2.previous);
    CU_ASSERT(element2->previous == cpy_element1.previous);
}

void test_remove_element(void)
{
    int find_me = 2;
    int *data;
    t_list element1 = root;
    t_list element2;

    for (int i = 1; i < 2; i++)
        element1 = element1->next;
    element2 = element1->next;
    data = (int *)element2->data;
    CU_ASSERT_EQUAL(*data, 10);

    remove_element(&root, &find_me, INDEX, is_my_int_equal);
    element2 = element1->next;
    data = (int *)element2->data;
    CU_ASSERT_EQUAL(*data, 5);
}

void test_clean_list(void)
{
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
        NULL == CU_add_test(pSuite, "of test_add_element_before_this()", test_add_element_before_this) ||
        NULL == CU_add_test(pSuite, "of test_add_element_after_this()", test_add_element_after_this) ||
        NULL == CU_add_test(pSuite, "of test_search_element()", test_search_element) ||
        NULL == CU_add_test(pSuite, "of test_revert_list()", test_revert_list) ||
        NULL == CU_add_test(pSuite, "of test_swap_element()", test_swap_element) ||
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