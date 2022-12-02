#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "minunit.h"
#include "list.c"

#define MSG_LEN 512

int g_testsRun = 0;

static char m_errorMsg[MSG_LEN];
static const char *m_input[] = {
    "192.168.15.134/24",
    "172.16.65.23/20",
    "10.169.23.212/23",
    "81.215.25.74/18",
    "127.0.75.88/8"
};

static char * testGetBroadcast(void);
static char * allTests(void);

int main(int argc, char **argv) {
    char *result = allTests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", g_testsRun);

    return result != 0;
}

static char * testGetBroadcast(void) {
    // Cidr cidr;
    // uint32_t broadcast;
    // uint32_t expectedBroadcasts[] = {
    //     0xC0A80FFF,
    //     0xAC104FFF,
    //     0x0AA917FF,
    //     0x51D73FFF,
    //     0x7FFFFFFF
    // };

    // for (int i = 0; i < 5; ++i) {
    //     CidrCreate(&cidr, m_input[i]);
    //     broadcast = CidrGetBroadcast(&cidr);
    //     snprintf(
    //         m_errorMsg,
    //         MSG_LEN,
    //         "CidrGetBroadcast(%s), Expect: %X, Got %X",
    //         m_input[i], expectedBroadcasts[i], broadcast
    //     );
    //     mu_assert(m_errorMsg, broadcast == expectedBroadcasts[i]);
    // }
    return 0;
}

static char * allTests() {
    mu_run_test(testGetBroadcast);
    return 0;
}
