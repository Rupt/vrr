#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "chrono.h"
#include "chacha.h"

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
    (void)acc;  // unused
}

void
chacha(void)
{
    struct vrr_chacha_key const key = {{0}};
    struct vrr_chacha_nonce const nonce = {{0}};
    uint8_t stream[1024 * 1024];
    vrr_chacha_stream(key, nonce, sizeof(stream), stream);
    (void)stream;  // unused
}

int
main(void)
{
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("      no-op: %9lld ns\n", vrr_time_ns_best_of_50(no_op));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
    printf("simple loop: %9lld ns\n", vrr_time_ns_best_of_50(simple_loop));
    printf("     chacha: %9lld ns\n", vrr_time_ns_best_of_50(chacha));
    printf("     chacha: %9lld ns\n", vrr_time_ns_best_of_50(chacha));
    printf("     chacha: %9lld ns\n", vrr_time_ns_best_of_50(chacha));
}
