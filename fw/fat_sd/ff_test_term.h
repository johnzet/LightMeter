#ifndef FF_TEST_TERM_H_
#define FF_TEST_TERM_H_

#include <stdbool.h>

void ff_test_term_timerproc(void) __attribute__ ((section(".ramfunc")));
bool ff_test_term(void);

#endif

