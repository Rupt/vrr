
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

static inline uint64_t
mix(uint64_t a, uint64_t b)
{
    // Constants taken from:
    //  http://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
    b += a;
    b ^= b >> 31;
    b *= 0x7fb5d329728ea185;
    a += b;
    a ^= a >> 27;
    a *= 0x81dadef4bc2dd44d;
    b += a;
    b ^= b >> 33;
    b *= 0x62a9d9ed799705f5;
    a += b;
    a ^= a >> 28;
    return a;
}

uint64_t
vrr_checksum(uint64_t count, uint8_t const *const bytes)
{
    // Tabulation hashing with implicit tables
    uint64_t const increment = 0x9e3779b97f4a7c15;
    uint64_t sum = 0;
    for (uint64_t i = 0, xi = 0; i < count; ++i, xi += increment) {
        sum += mix(xi + increment, bytes[i]);
    }
    return sum;
}
