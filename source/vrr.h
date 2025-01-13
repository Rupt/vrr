#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u32x4x4 {
    uint32_t aa, ba, ca, da;
    uint32_t ab, bb, cb, db;
    uint32_t ac, bc, cc, dc;
    uint32_t ad, bd, cd, dd;
};

struct vrr_u32x4 {
    uint32_t a, b, c, d;
};

struct vrr_u8x4 {
    uint8_t a, b, c, d;
};

static inline uint32_t
vrr_u32_from_u8x4(struct vrr_u8x4 const x)
{
    return x.a | (uint32_t)x.b << 8 | (uint32_t)x.c << 16 | (uint32_t)x.d << 24;
}

static inline uint32_t
vrr_u32(uint8_t const a, uint8_t const b, uint8_t const c, uint8_t const d)
{
    return vrr_u32_from_u8x4((struct vrr_u8x4){a, b, c, d});
}

static inline struct vrr_u8x4
vrr_u8x4_from_u32(uint32_t const x)
{
    return (struct vrr_u8x4){(uint8_t)x, (uint8_t)(x >> 8), (uint8_t)(x >> 16),
                             (uint8_t)(x >> 24)};
}

static inline uint32_t
vrr_rotate_left_u32(uint32_t const x, int const n)
{
    // WARNING: defined only for `1 <= n && n <= 31`.
    return (x << n) | (x >> (32 - n));
}
