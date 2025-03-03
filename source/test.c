
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

static inline uint64_t
u64(uint8_t const *const bytes)
{
    return ((uint64_t)bytes[0] | ((uint64_t)bytes[1] << 8) |
            ((uint64_t)bytes[2] << 16) | ((uint64_t)bytes[3] << 24) |
            ((uint64_t)bytes[4] << 32) | ((uint64_t)bytes[5] << 40) |
            ((uint64_t)bytes[6] << 48) | ((uint64_t)bytes[7] << 56));
}

uint64_t
vrr_checksum(uint64_t count, uint8_t const *const bytes)
{
    // Tabulation hashing with implicit tables
    uint64_t const increment = 0x9e3779b97f4a7c15;
    uint64_t sum = 0;
    uint64_t i = 0;
    uint64_t xi = 0;
    for (; i + 8 <= count; i += 8, xi += 8 * increment) {
        sum += mix(xi + 8 * increment, u64(bytes + i));
    }
    uint64_t left = count & 7;
    uint64_t item = 0;
    switch (left) {
        case 7:
            item |= (uint64_t)bytes[i + 6] << 48;
            /* fallthrough */
        case 6:
            item |= (uint64_t)bytes[i + 5] << 40;
            /* fallthrough */
        case 5:
            item |= (uint64_t)bytes[i + 4] << 32;
            /* fallthrough */
        case 4:
            item |= (uint64_t)bytes[i + 3] << 24;
            /* fallthrough */
        case 3:
            item |= (uint64_t)bytes[i + 2] << 16;
            /* fallthrough */
        case 2:
            item |= (uint64_t)bytes[i + 1] << 8;
            /* fallthrough */
        case 1:
            item |= (uint64_t)bytes[i];
            sum += mix(xi + left * increment, item);
            /* fallthrough */
        default:
            return sum;
    }
}
