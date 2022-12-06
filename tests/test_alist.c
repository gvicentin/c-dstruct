#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"
#include "alist.c"

//  Definitions
//
#define FAIL_MSG_LEN 512

//  Globals variables
//
int g_tests_run = 0;

//  Global functions
// 
void tests_setup(void);
void tests_teardown(void);

//  Members variables
//
static char m_fail_msg[FAIL_MSG_LEN];
static alist m_list;
static char *m_initial_state[] = {
    "1", "2", "fizz", "4", "buzz", "fizz", 
    "7", "8", "fizz", "buzz", "11", "fizz"
};

//  Members forward declaration
//
static char * test_alist_create(void);
static char * test_alist_expand(void);
static char * test_alist_add(void);
static char * test_alist_get(void);
static char * test_alist_pop(void);
static char * all_tests(void);

//  Entrypoint
//
int main(int argc, char **argv) {
    char *result = all_tests();

    if (result != NULL) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", g_tests_run);

    return result != NULL;
}

//  Test setup
//
void tests_setup(void) {
    // initialize list
    alist_init(&m_list);

    // fill list
    size_t arr_len = sizeof(m_initial_state)/sizeof(char *);
    for (uint8_t i = 0; i < arr_len; ++i) {
        alist_add(&m_list, (void *)m_initial_state[i]);
    }
}

void tests_teardown(void) {
    // deinitializate list
    alist_destroy(&m_list);
}

//  Tests implementation
//
static char * test_alist_create(void) {
    alist empty_list;
    alist_init(&empty_list);

    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_create] Expected size (%u), got (%zu)", 0, empty_list.size);
    mu_assert(m_fail_msg, empty_list.size == 0);

    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_create] Expected capacity (%u), got (%zu)", INITIAL_CAPACITY, empty_list.capacity);
    mu_assert(m_fail_msg, empty_list.capacity == INITIAL_CAPACITY);

    mu_assert("[list_create] Array buffer can't be NULL",
              empty_list.data_array != NULL);

    alist_destroy(&empty_list);

    return NULL;
}

static char * test_alist_expand(void) {
    size_t new_capacity = 100, prev_capacity;

    alist_expand(&m_list, new_capacity);

    // test expand capacity
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             new_capacity, m_list.capacity);
    mu_assert(m_fail_msg, m_list.capacity == new_capacity);

    // test when not to expand
    prev_capacity = new_capacity;
    new_capacity = 50;
    alist_expand(&m_list, new_capacity);
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             prev_capacity, m_list.capacity);
    mu_assert(m_fail_msg, m_list.capacity == prev_capacity);

    return NULL;
}

static char * test_alist_add(void) {
    char *add[] = { 
        "13", "14", "fizz buzz", "16", "17", "fizz"
    };
    char *result[] = {
        "1", "2", "fizz", "4", "buzz", "fizz", 
        "7", "8", "fizz", "buzz", "11", "fizz",
        "13", "14", "fizz buzz", "16", "17", "fizz"
    };
    size_t add_count = sizeof(add)/sizeof(char *);
    size_t result_count = sizeof(result)/sizeof(char *);

    for (uint8_t i = 0; i < add_count; ++i) {
        alist_add(&m_list, (char *)add[i]); 
    }

    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_add] Expected size (%zu), got (%zu)",
             result_count, m_list.size);
    mu_assert(m_fail_msg, m_list.size == result_count);

    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_add] Expected capacity greater than (%zu), got (%zu)",
             result_count, m_list.capacity);
    mu_assert(m_fail_msg, m_list.capacity >= result_count);

    return NULL;
}

static char * test_alist_get(void) {
    char *expected_arr[] = {
        "1", "2", "fizz", "4", "buzz", "fizz", 
        "7", "8", "fizz", "buzz", "11", "fizz",
    };
    size_t expected_count = sizeof(expected_arr)/sizeof(char *);

    for (uint8_t i = 0; i < expected_count; ++i) {
        char *expected = expected_arr[i];
        char *got = (char *) alist_get(&m_list, i);

        snprintf(m_fail_msg, FAIL_MSG_LEN,
                 "[list_get] Expected (%s), got (%s)",
                 expected, got);
        mu_assert(m_fail_msg, strcmp(expected, got) == 0);
    }

    return NULL;
}

static char * test_alist_pop(void) {
    char *result[] = {
        "1", "2", "fizz", "4", "buzz",
        "fizz", "7", "8", "fizz"
    };
    char *pop[] = { "fizz", "11", "buzz" };
    size_t result_count = sizeof(result)/sizeof(char *);
    size_t pop_count = sizeof(pop)/sizeof(char *);

    for (uint8_t i = 0; i < pop_count; ++i) {
        char *expected = pop[i];
        char *got = (char *)alist_pop(&m_list);

        snprintf(m_fail_msg, FAIL_MSG_LEN,
                 "[list_pop] Expected (%s), got (%s)",
                 expected, got);
        mu_assert(m_fail_msg, strcmp(expected, got) == 0);
    }

    for (uint8_t i = 0; i < result_count; ++i) {
        char *expected = result[i];
        char *got = (char *) alist_get(&m_list, i);

        snprintf(m_fail_msg, FAIL_MSG_LEN,
                 "[list_pop] Expected (%s), got (%s)",
                 expected, got);
        mu_assert(m_fail_msg, strcmp(expected, got) == 0);
    }

    return NULL;
}

static char * all_tests() {
    // run all tests
    mu_run_test(test_alist_create);
    mu_run_test(test_alist_expand);
    mu_run_test(test_alist_add);
    mu_run_test(test_alist_get);
    mu_run_test(test_alist_pop);

    return NULL;
}
