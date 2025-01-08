#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u8x4 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
};

static inline uint32_t
vrr_u32_from_u8x4_little_endian(struct vrr_u8x4 x)
{
    return x.a | (uint32_t)x.b << 8 | (uint32_t)x.c << 16 | (uint32_t)x.d << 24;
}

static inline struct vrr_u8x4
vrr_u8x4_from_u32_little_endian(uint32_t x)
{
    return (struct vrr_u8x4){x, x >> 8, x >> 16, x >> 24};
}
