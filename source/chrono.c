#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <time.h>    // struct timespec, clock_gettime, CLOCK_MONOTONIC_RAW
#include <limits.h>  // LLONG_MAX
#include "chrono.h"
#endif

long long
vrr_time_ns_best_of_50(void (*const fn)(void))
{
    long long best = LLONG_MAX;
    for (int i = 0; i < 50; ++i) {
        struct timespec start;
        int const error_start = clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        fn();
        struct timespec end;
        int const error_end = clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        if (error_start || error_end) {
            continue;
        }
        long long const duration_ns =
            end.tv_nsec - start.tv_nsec +
            (end.tv_sec - start.tv_sec) * 1000000000LL;
        if (duration_ns < best) {
            best = duration_ns;
        }
    }
    return best;
}
