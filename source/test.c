
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

// TODO: document
// TODO: clarify names
// TODO: empirically test this mixing function

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
    uint64_t const c0 = 0x9e3779b97f4a7c15;
    uint64_t sum = 0;
    for (uint64_t i = 0, xi = 0; i < count / 8; ++i, xi += 8 * c0) {
        sum += mix(xi + 8 * c0, u64(bytes + 8 * i));
    }
    // TODO: explain the need for padding
    if (count & 7) {
        uint8_t pad[8] = {0};
        for (uint64_t j = 0; j < (count & 7); ++j) {
            pad[j] = bytes[count / 8 * 8 + j];
        }
        sum += mix(count * c0, u64(pad));
    }
    return sum;
}
