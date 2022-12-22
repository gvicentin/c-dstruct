#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.c"
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

//  Members forward declaration
//
static char *test_HTableInit(void);
static char *allTests(void);

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
}

void TestsTeardown(void) {
}

//  Tests implementation
//
static char *test_HTableInit(void) {
    HTable emptyTable;
    HTableInit(&emptyTable);

    // test size
    MU_ASSERT_EXP("HTableInit", 0, emptyTable.size);

    // test capacity
    MU_ASSERT_EXP("HTableInit", INITIAL_CAPACITY, emptyTable.capacity);

    // check array allocation
    MU_ASSERT("HTableInit", "Array buffer can't be NULL",
              emptyTable.entriesArray != NULL);

    HTableDestroy(&emptyTable);

    return NULL;
}

static char *allTests() {
    // run all tests
    MU_RUN_TEST(test_HTableInit);

    return NULL;
}
