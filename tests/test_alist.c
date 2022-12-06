#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "minunit.h"
#include "alist.c"

#define FAIL_MSG_LEN 512

int g_tests_run = 0;

static char m_fail_msg[FAIL_MSG_LEN];

// Test functions
static char * test_alist_create(void);
static char * test_alist_expand(void);
static char * test_alist_add(void);
static char * test_alist_get(void);
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

static char * test_alist_create(void) {
    alist tlist;

    alist_init(&tlist);

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

    alist_destroy(&tlist);

    return NULL;
}

static char * test_alist_expand(void) {
    alist tlist;
    size_t new_capacity = 100, prev_capacity;

    alist_init(&tlist);
    alist_expand(&tlist, new_capacity);

    // test expand capacity
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             new_capacity, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity == new_capacity);

    // test when not to expand
    prev_capacity = new_capacity;
    new_capacity = 50;
    alist_expand(&tlist, new_capacity);
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_expand] Expected capacity (%zu), got (%zu)",
             prev_capacity, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity == prev_capacity);

    alist_destroy(&tlist);

    return NULL;
}

static char * test_alist_add(void) {
    alist tlist;
    char *tstr = "foobar";
    uint8_t count = 50;

    alist_init(&tlist);

    for (uint8_t i = 0; i < count; ++i) {
        alist_add(&tlist, (void *) tstr);
    }

    // size
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_add] Expected size (%u), got (%zu)",
             count, tlist.size);
    mu_assert(m_fail_msg, tlist.size == count);

    // capacity
    snprintf(m_fail_msg, FAIL_MSG_LEN,
             "[list_add] Expected capacity greater than (%u), got (%zu)",
             count, tlist.capacity);
    mu_assert(m_fail_msg, tlist.capacity >= count);

    alist_destroy(&tlist);

    return NULL;
}

static char * test_alist_get(void) {
    alist tlist;
    char *tarray[] = { "foo", "bar", "foobar" };

    alist_init(&tlist);
    alist_add(&tlist, (void *) tarray[0]);
    alist_add(&tlist, (void *) tarray[1]);
    alist_add(&tlist, (void *) tarray[2]);

    for (uint8_t i = 0; i < 3; ++i) {
        char *expected = tarray[i];
        char *got = (char *) alist_get(&tlist, i);

        snprintf(m_fail_msg, FAIL_MSG_LEN,
                 "[list_get] Expected (%s), got (%s)",
                 expected, got);
        mu_assert(m_fail_msg, expected == got);
    }

    alist_destroy(&tlist);

    return NULL;
}

static char * all_tests() {
    // run all tests
    mu_run_test(test_alist_create);
    mu_run_test(test_alist_expand);
    mu_run_test(test_alist_add);
    mu_run_test(test_alist_get);

    return NULL;
}
