#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <time.h>       // struct timespec, clock_gettime, CLOCK_MONOTONIC
#include <bits/time.h>  // FIXME(rupt): clang-tidy wants this
#include <limits.h>     // LLONG_MAX
#include "chrono.h"
#endif

long long
vrr_time_ns_best_of_50(void fn(void))
{
    long long best = LLONG_MAX;
    for (int i = 0; i < 50; ++i) {
        struct timespec start;
        int const error_start = clock_gettime(CLOCK_MONOTONIC, &start);
        fn();
        struct timespec end;
        int const error_end = clock_gettime(CLOCK_MONOTONIC, &end);
        if (error_start || error_end) {
            continue;
        }
        long long const duration = end.tv_nsec - start.tv_nsec +
                                   1000000000LL * (end.tv_sec - start.tv_sec);
        if (duration < best) {
            best = duration;
        }
    }
    return best;
}
