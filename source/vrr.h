#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u32x4x4 {
    uint32_t aa, ab, ac, ad;
    uint32_t ba, bb, bc, bd;
    uint32_t ca, cb, cc, cd;
    uint32_t da, db, dc, dd;
};

struct vrr_u32x4 {
    uint32_t a, b, c, d;
};

struct vrr_u8x4 {
    uint8_t a, b, c, d;
};

static inline uint32_t
vrr_u32_from_u8x4(struct vrr_u8x4 x)
{
    return x.a | (uint32_t)x.b << 8 | (uint32_t)x.c << 16 | (uint32_t)x.d << 24;
}

static inline struct vrr_u8x4
vrr_u8x4_from_u32(uint32_t x)
{
    return (struct vrr_u8x4){(uint8_t)x, (uint8_t)(x >> 8), (uint8_t)(x >> 16),
                             (uint8_t)(x >> 24)};
}

static inline uint32_t
vrr_rotate_left_u32(uint32_t x, int n)
{
    return (x << n) | (x >> (32 - n));
}
