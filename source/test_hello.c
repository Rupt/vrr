
#include <stdio.h>

#include "hello.h"
#include "test.h"

int
main()
{
    int a = 1;
    int b = plus_one(/*x=*/a);
    if (b != a + 1) {
        vrr_log_open();
        vrr_log_expected("%d", b);
        vrr_log_observed("%d", a + 1);
        vrr_log_close();
    }
}
