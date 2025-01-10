#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "chrono.h"

void simple_loop(void);
void no_op(void);

int
main(void)
{
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
}

void
no_op(void)
{
}

void
simple_loop(void)
{
    int acc = 0;
    for (long i = 0; i < 10000; ++i) {
        acc += 1;
        acc -= 1;
    }
    (void)acc;  // dismiss unused warnings
}
