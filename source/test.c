
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
    uint64_t i = 0;
    uint64_t xi = 0;
    // Mixing with a counter encodes each byte position.
    // Counting from one distinguishes zero bytes from one zero-valued byte.
    for (; i + 8 <= count; i += 8) {
        xi += 8 * c0;
        uint64_t a = xi;
        uint64_t b = *(uint64_t const *)(bytes + i);

        b ^= (a << 34) | (a >> 30);
        b *= 0xbf58476d1ce4e5b9;
        a += b;
        b ^= (a << 37) | (a >> 27);
        b *= 0x94d049bb133111eb;
        a += b;
        b ^= (a << 33) | (a >> 31);
        b *= 0x7fb5d329728ea185;
        a += b;
        b ^= (a << 37) | (a >> 27);

        sum += b;
    }
    for (; i < count; ++i) {
        xi += c0;
        uint64_t a = xi;
        uint64_t b = bytes[i];

        b ^= (a << 34) | (a >> 30);
        b *= 0xbf58476d1ce4e5b9;
        a += b;
        b ^= (a << 37) | (a >> 27);
        b *= 0x94d049bb133111eb;
        a += b;
        b ^= (a << 33) | (a >> 31);
        b *= 0x7fb5d329728ea185;
        a += b;
        b ^= (a << 37) | (a >> 27);

        sum += b;
    }
    return sum;
}
