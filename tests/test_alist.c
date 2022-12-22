#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alist.c"
#include "elmnt.h"
#include "minunit.h"

//  Globals variables
//
int g_testsRun = 0;
int g_failMsgLen = 512;
char *g_failMsgBuff;

//  Global functions
//
void TestsSetup(void);
void TestsTeardown(void);

//  Members variables
//
static AList m_list;
static const char *m_initialState[] = {"1",    "2",    "fizz", "4",
                                       "buzz", "fizz", "7",    "8",
                                       "fizz", "buzz", "11",   "fizz"};

//  Members forward declaration
//
static char *test_AListCreate(void);
static char *test_AListExpand(void);
static char *test_AListAdd(void);
static char *test_AListAddAll(void);
static char *test_AListGet(void);
static char *test_AListSet(void);
static char *test_AListPop(void);
static char *test_AListInsert(void);
static char *test_AListInsertAll(void);
static char *test_AListRemove(void);
static char *test_AListRevert(void);
static char *allTests(void);

static char *matchExpected(const char *tag, char **expected, size_t count);

//  Entrypoint
//
int main(int argc, char **argv) {
    char *result;

    // setup fail msg
    g_failMsgBuff = (char *)calloc(g_failMsgLen, sizeof(char));

    result = allTests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", g_testsRun);

    // cleanup
    free(g_failMsgBuff);

    return result != NULL;
}

//  Test setup
//
void TestsSetup(void) {
    // initialize list
    AListInit(&m_list);

    // fill list
    size_t arr_len = sizeof(m_initialState) / sizeof(char *);
    for (uint8_t i = 0; i < arr_len; ++i) {
        AListAdd(&m_list, STRING_ELMNT(m_initialState[i]));
    }
}

void TestsTeardown(void) {
    // deinitializate list
    AListDestroy(&m_list);
}

//  Tests implementation
//
static char *test_AListCreate(void) {
    AList emptyList;
    AListInit(&emptyList);

    // test size
    MU_ASSERT_EXP("AListInit", 0, emptyList.size);

    // test capacity
    MU_ASSERT_EXP("AListInit", INITIAL_CAPACITY, emptyList.capacity);

    // check array allocation
    MU_ASSERT("AListInit", "Array buffer can't be NULL",
              emptyList.elmntArray != NULL);

    AListDestroy(&emptyList);

    return NULL;
}

static char *test_AListExpand(void) {
    size_t newCapacity = 100, prevCapacity;

    AListExpand(&m_list, newCapacity);

    // test expand capacity
    MU_ASSERT_EXP("AListExpand", newCapacity, m_list.capacity);

    // test when not to expand
    prevCapacity = newCapacity;
    newCapacity = 50;
    AListExpand(&m_list, newCapacity);
    MU_ASSERT_EXP("AListExpand", prevCapacity, m_list.capacity);

    return NULL;
}

static char *test_AListAdd(void) {
    char *add[] = {"13", "14", "fizz buzz", "16", "17", "fizz"};
    char *result[] = {"1",  "2",  "fizz",      "4",    "buzz", "fizz",
                      "7",  "8",  "fizz",      "buzz", "11",   "fizz",
                      "13", "14", "fizz buzz", "16",   "17",   "fizz"};
    size_t addCount = sizeof(add) / sizeof(char *);
    size_t resultCount = sizeof(result) / sizeof(char *);

    for (uint8_t i = 0; i < addCount; ++i) {
        AListAdd(&m_list, STRING_ELMNT(add[i]));
    }

    // test size
    MU_ASSERT_EXP("AListAdd", resultCount, m_list.size);

    // test capacity
    MU_ASSERT("AListAdd", "Expected capacity greater than result count",
              m_list.capacity >= resultCount);

    return matchExpected("AListAdd", result, resultCount);
}

static char *test_AListAddAll(void) {
    AList add;
    char *result[] = {"1",  "2",  "fizz",      "4",    "buzz", "fizz",
                      "7",  "8",  "fizz",      "buzz", "11",   "fizz",
                      "13", "14", "fizz buzz", "16",   "17",   "fizz"};
    size_t resultCount = sizeof(result) / sizeof(char *);

    AListInit(&add);
    AListAdd(&add, STRING_ELMNT("13"));
    AListAdd(&add, STRING_ELMNT("14"));
    AListAdd(&add, STRING_ELMNT("fizz buzz"));
    AListAdd(&add, STRING_ELMNT("16"));
    AListAdd(&add, STRING_ELMNT("17"));
    AListAdd(&add, STRING_ELMNT("fizz"));
    AListAddAll(&m_list, &add);

    // test size
    MU_ASSERT_EXP("AListAddAll", resultCount, m_list.size);

    // test capacity
    MU_ASSERT("AListAddAll", "Expected capacity greater than result count",
              m_list.capacity >= resultCount);

    // cleanup
    AListDestroy(&add);

    return matchExpected("AListAddAll", result, resultCount);
}

static char *test_AListGet(void) {
    char *expected[] = {"1", "2", "fizz", "4",    "buzz", "fizz",
                        "7", "8", "fizz", "buzz", "11",   "fizz"};
    size_t count = sizeof(expected) / sizeof(char *);

    // check if match expected list
    return matchExpected("AListGet", expected, count);
}

static char *test_AListSet(void) {
    char *expected[] = {"1", "2", "foo", "4",   "bar", "foo",
                        "7", "8", "foo", "bar", "11",  "foo"};
    size_t count = sizeof(expected) / sizeof(char *);

    AListSet(&m_list, 2, STRING_ELMNT("foo"));
    AListSet(&m_list, 4, STRING_ELMNT("bar"));
    AListSet(&m_list, 5, STRING_ELMNT("foo"));
    AListSet(&m_list, 8, STRING_ELMNT("foo"));
    AListSet(&m_list, 9, STRING_ELMNT("bar"));
    AListSet(&m_list, 11, STRING_ELMNT("foo"));

    // check if match expected list
    return matchExpected("AListSet", expected, count);
}

static char *test_AListPop(void) {
    char *result[] = {"1", "2", "fizz", "4", "buzz", "fizz", "7", "8", "fizz"};
    char *pop[] = {"fizz", "11", "buzz"};
    size_t resultCount = sizeof(result) / sizeof(char *);
    size_t popCount = sizeof(pop) / sizeof(char *);

    for (uint8_t i = 0; i < popCount; ++i) {
        // check if pop is returning elements in the right order
        char *expected = pop[i];
        const char *got = ELMNT_STRING(AListPop(&m_list));

        MU_ASSERT_EXP_STR("AListPop", expected, got);
    }

    // check if match expected list
    return matchExpected("AListPop", result, resultCount);
}

static char *test_AListInsert(void) {
    char *expected[] = {"1", "2",   "foo",  "fizz", "4",  "buzz", "fizz",  "7",
                        "8", "bar", "fizz", "buzz", "11", "fizz", "foobar"};
    size_t count = sizeof(expected) / sizeof(char *);

    AListInsert(&m_list, 2, STRING_ELMNT("foo"));
    AListInsert(&m_list, 9, STRING_ELMNT("bar"));
    AListInsert(&m_list, 14, STRING_ELMNT("foobar"));

    return matchExpected("AListInsert", expected, count);
}

static char *test_AListInsertAll(void) {
    AList insert;
    char *expected[] = {"1", "2",   "fizz", "4",      "buzz", "fizz",
                        "7", "foo", "bar",  "foobar", "1",    "2",
                        "3", "8",   "fizz", "buzz",   "11",   "fizz"};
    size_t count = sizeof(expected) / sizeof(char *);

    AListInit(&insert);
    AListAdd(&insert, STRING_ELMNT("foo"));
    AListAdd(&insert, STRING_ELMNT("bar"));
    AListAdd(&insert, STRING_ELMNT("foobar"));
    AListAdd(&insert, STRING_ELMNT("1"));
    AListAdd(&insert, STRING_ELMNT("2"));
    AListAdd(&insert, STRING_ELMNT("3"));

    AListInsertAll(&m_list, &insert, 7);

    // cleanup
    AListDestroy(&insert);

    return matchExpected("AListInsertAll", expected, count);
}

static char *test_AListRemove(void) {
    char *expected[] = {"1", "2", "4", "7", "8", "11"};
    size_t count = sizeof(expected) / sizeof(char *);

    AListRemove(&m_list, 11);
    AListRemove(&m_list, 9);
    AListRemove(&m_list, 8);
    AListRemove(&m_list, 5);
    AListRemove(&m_list, 4);
    AListRemove(&m_list, 2);

    return matchExpected("AListRemove", expected, count);
}

static char *test_AListRevert(void) {
    char *expected[] = {"fizz", "11",   "buzz", "fizz", "8", "7",
                        "fizz", "buzz", "4",    "fizz", "2", "1"};
    size_t count = sizeof(expected) / sizeof(char *);

    AListRevert(&m_list);

    return matchExpected("AListRevert", expected, count);
}

static char *allTests() {
    // run all tests
    MU_RUN_TEST(test_AListCreate);
    MU_RUN_TEST(test_AListExpand);
    MU_RUN_TEST(test_AListAdd);
    MU_RUN_TEST(test_AListAddAll);
    MU_RUN_TEST(test_AListGet);
    MU_RUN_TEST(test_AListSet);
    MU_RUN_TEST(test_AListPop);
    MU_RUN_TEST(test_AListInsert);
    MU_RUN_TEST(test_AListInsertAll);
    MU_RUN_TEST(test_AListRemove);
    MU_RUN_TEST(test_AListRevert);

    return NULL;
}

static char *matchExpected(const char *tag, char **expected, size_t count) {
    for (uint8_t i = 0; i < count; ++i) {
        char *e = expected[i];
        const char *got = ELMNT_STRING(AListGet(&m_list, i));

        MU_ASSERT_EXP_STR(tag, e, got);
    }

    return NULL;
}
