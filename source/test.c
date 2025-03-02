
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(unsigned long long const count, uint8_t const *const bytes)
{
    // Tabulation hashing with implicit tables from SplitMix64
    uint64_t sum = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from one distinguishes zero bytes from one zero-valued byte.
    for (uint64_t i = 0, xi = 1 << 8; i < count; ++i, xi += 1 << 8) {
        uint64_t x = xi | bytes[i];
        x *= 0x9e3779b97f4a7c15;
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        // Xor accumulation makes the final xor-shift redundant.
        sum ^= x;
    }
    return sum;
}
