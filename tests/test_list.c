#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "minunit.h"
#include "list.c"

#define FAIL_MSG_LEN 512

int g_tests_run = 0;

static char m_fail_msg[FAIL_MSG_LEN];

static char * test_list_create(void);
static char * test_list_expand(void);
static char * all_tests(void);

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

static char * test_list_create(void) {
    list tlist;

    list_create(&tlist);

    // size
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_create] Expected size (%u), got (%zu)", 0, tlist.size);
    mu_assert(m_fail_msg, tlist.size == 0);

    // capacity
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_create] Expected capacity (%u), got (%zu)", INITIAL_CAPACITY, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity == INITIAL_CAPACITY);

    // data array
    mu_assert("[list_create] Array buffer can't be NULL",
              tlist.data_array != NULL);

    list_destroy(&tlist);

    return NULL;
}

static char * test_list_expand(void) {
    list tlist;
    size_t new_capacity = 100, prev_capacity;

    list_create(&tlist);
    list_expand(&tlist, new_capacity);

    // test expand capacity
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             new_capacity, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity == new_capacity);

    // test when not to expand
    prev_capacity = new_capacity;
    new_capacity = 50;
    list_expand(&tlist, new_capacity);
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             prev_capacity, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity == prev_capacity);

    list_destroy(&tlist);

    return NULL;
}

static char * all_tests() {
    // run all tests
    mu_run_test(test_list_create);
    mu_run_test(test_list_expand);

    return NULL;
}
