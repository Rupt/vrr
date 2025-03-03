
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(unsigned long long const count, uint8_t const *const bytes)
{
    // Tabulation hashing with implicit tables a MurmurHash3 finalizer variant
    // Constants from David Stafford's Mix01
    //  http://zimbry.blogspot.com/2011/09/better-bit-mixing-improving-on.html
    uint64_t sum = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from one distinguishes zero bytes from one zero-valued byte.
    for (uint64_t i = 0, xi = 256; i < count; ++i, xi += 256) {
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
