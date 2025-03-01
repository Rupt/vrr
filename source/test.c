
#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint64_t, uint8_t
#include "test.h"
#endif

uint64_t
vrr_checksum(unsigned long long const count, uint8_t const *const data)
{
    // Tabulation hashing with implicit tables from SplitMix64
    uint64_t sum = 0;
    for (uint64_t i = 0; i < count; ++i) {
        uint64_t x = (i << 8) | data[i];
        x *= 0x9e3779b97f4a7c15;
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        x ^= x >> 31;
        // Accumulation with xor would make the last xor-shift redundant.
        sum += x;
    }
    return sum;
}
