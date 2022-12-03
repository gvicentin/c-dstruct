#ifndef MINUNIT_H
#define MINUNIT_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); g_tests_run++; \
                                if (message) return message; } while (0)
extern int g_tests_run;

# endif // MINUNIT_H
