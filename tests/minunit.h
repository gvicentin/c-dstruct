#ifndef MINUNIT_H
#define MINUNIT_H

#define MU_ASSERT(tag, message, test)                                          \
    do {                                                                       \
        if (!(test)) {                                                         \
            snprintf(g_failMsgBuff, g_failMsgLen, "[%s] %s", tag, message);    \
            return g_failMsgBuff;                                              \
        }                                                                      \
    } while (0)

#define MU_ASSERT_EXP(tag, expected, got)                                      \
    do {                                                                       \
        if (!(expected == got)) {                                              \
            snprintf(g_failMsgBuff, g_failMsgLen,                              \
                     "[%s] Expected(%d), Got(%d)", tag, (int)expected,         \
                     (int)got);                                                \
            return g_failMsgBuff;                                              \
        }                                                                      \
    } while (0)

#define MU_ASSERT_EXP_STR(tag, expected, got)                                  \
    do {                                                                       \
        if (strcmp(expected, got) != 0) {                                      \
            snprintf(g_failMsgBuff, g_failMsgLen,                              \
                     "[%s] Expected(%s), Got(%s)", tag, expected, got);        \
            return g_failMsgBuff;                                              \
        }                                                                      \
    } while (0)

#define MU_RUN_TEST(test)                                                      \
    do {                                                                       \
        TestsSetup();                                                          \
        char *message = test();                                                \
        g_testsRun++;                                                         \
        if (message)                                                           \
            return message;                                                    \
        TestsTeardown();                                                       \
    } while (0)

extern int g_testsRun;
extern int g_failMsgLen;
extern char *g_failMsgBuff;

extern void TestsSetup(void);
extern void TestsTeardown(void);

#endif // MINUNIT_H
