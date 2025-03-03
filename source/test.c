
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(unsigned long long const count, uint8_t const *const bytes)
{
    uint64_t const c0 = 0x79b97f4a7c150000;
    // Tabulation hashing with implicit tables from SplitMix64
    uint64_t sum = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from one distinguishes zero bytes from one zero-valued byte.
    uint64_t i = 0;
    uint64_t xi = 0;
    for (; i + 2 <= count; i += 2) {
        xi += 2 * c0;
        uint64_t x = xi ^ bytes[i] ^ ((uint64_t)bytes[i + 1] << 8);
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        x ^= x >> 31;
        // Xor accumulation would make the final xor-shift redundant.
        sum += x;
    }
    for (; i < count; ++i) {
        xi += c0;
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
