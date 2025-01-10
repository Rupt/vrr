#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u8abcd {
    uint8_t a, b, c, d;
};

static inline uint32_t
vrr_u32_from_u8abcd(struct vrr_u8abcd x)
{
    return x.a | (uint32_t)x.b << 8 | (uint32_t)x.c << 16 | (uint32_t)x.d << 24;
}

static inline struct vrr_u8abcd
vrr_u8abcd_from_u32(uint32_t x)
{
    return (struct vrr_u8abcd){x, x >> 8, x >> 16, x >> 24};
}
