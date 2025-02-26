#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u32x4 {
    uint32_t a, b, c, d;
};

struct vrr_u32x4x4 {
    struct vrr_u32x4 a, b, c, d;
};

struct vrr_u8x4 {
    uint8_t a, b, c, d;
};

static inline uint32_t
vrr_u32_from_u8x4(struct vrr_u8x4 const x)
{
    return x.a | (uint32_t)x.b << 8 | (uint32_t)x.c << 16 | (uint32_t)x.d << 24;
}

static inline struct vrr_u8x4
vrr_u8x4_from_u32(uint32_t const x)
{
    return (struct vrr_u8x4){(uint8_t)x, (uint8_t)(x >> 8), (uint8_t)(x >> 16),
                             (uint8_t)(x >> 24)};
}

static inline uint32_t
vrr_u32(uint8_t const a, uint8_t const b, uint8_t const c, uint8_t const d)
{
    // TODO(rupt): delete?
    return vrr_u32_from_u8x4((struct vrr_u8x4){a, b, c, d});
}

static inline void
vrr_u32_to_bytes(uint32_t const x, uint8_t out[static const 4])
{
    struct vrr_u8x4 split = vrr_u8x4_from_u32(x);
    out[0] = split.a;
    out[1] = split.b;
    out[2] = split.c;
    out[3] = split.d;
}

static inline void
vrr_u32x4_to_bytes(struct vrr_u32x4 const x, uint8_t out[static const 16])
{
    vrr_u32_to_bytes(x.a, &out[0]);
    vrr_u32_to_bytes(x.b, &out[4]);
    vrr_u32_to_bytes(x.c, &out[8]);
    vrr_u32_to_bytes(x.d, &out[12]);
}

static inline void
vrr_u32x4x4_to_bytes(struct vrr_u32x4x4 const x, uint8_t out[static const 64])
{
    vrr_u32x4_to_bytes(x.a, &out[0]);
    vrr_u32x4_to_bytes(x.b, &out[16]);
    vrr_u32x4_to_bytes(x.c, &out[32]);
    vrr_u32x4_to_bytes(x.d, &out[48]);
}

static inline uint32_t
vrr_rotate_left_u32(uint32_t const x, int const n)
{
    // WARNING: defined only for `1 <= n && n <= 31`.
    return (x << n) | (x >> (32 - n));
}
