
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(unsigned long long const count, uint8_t const *const bytes)
{
    uint64_t const c0 = 0x9e3779b97f4a7d00;
    // Tabulation hashing with implicit tables from SplitMix64
    uint64_t sum = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from one distinguishes zero bytes from one zero-valued byte.
    for (uint64_t i = 0, xi = c0; i < count; ++i, xi += c0) {
        uint64_t x = xi ^ bytes[i];
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        x ^= x >> 31;
        // Xor accumulation would make the final xor-shift redundant.
        sum += x;
    }
    return sum;
}
