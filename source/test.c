
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(uint64_t count, uint8_t const *const bytes)
{
    // Tabulation hashing with implicit tables from David Stafford's Mix01
    //  http://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
    uint64_t sum = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from nonzero distinguishes zero bytes from one zero-valued byte.
    uint64_t const increment = 0x9e3779b97f4a7d00;
    for (uint64_t i = 0, xi = increment; i < count; ++i, xi += increment) {
        uint64_t x = xi ^ bytes[i];
        x ^= x >> 31;
        x *= 0x7fb5d329728ea185;
        x ^= x >> 27;
        x *= 0x81dadef4bc2dd44d;
        x ^= x >> 33;
        // Xor accumulation would make the final xor-shift redundant.
        sum += x;
    }
    return sum;
}
