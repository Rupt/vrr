#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint32_t, uint8_t
#endif

struct vrr_u32x4x4 {
    // TODO(rupt): contain 4 vrr_u32x4 structures?
    // TODO(rupt): reconsider transposed labelling
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
    vrr_u32_to_bytes(x.aa, &out[0]);
    vrr_u32_to_bytes(x.ba, &out[4]);
    vrr_u32_to_bytes(x.ca, &out[8]);
    vrr_u32_to_bytes(x.da, &out[12]);

    vrr_u32_to_bytes(x.ab, &out[16]);
    vrr_u32_to_bytes(x.bb, &out[20]);
    vrr_u32_to_bytes(x.cb, &out[24]);
    vrr_u32_to_bytes(x.db, &out[28]);

    vrr_u32_to_bytes(x.ac, &out[32]);
    vrr_u32_to_bytes(x.bc, &out[36]);
    vrr_u32_to_bytes(x.cc, &out[40]);
    vrr_u32_to_bytes(x.dc, &out[44]);

    vrr_u32_to_bytes(x.ad, &out[48]);
    vrr_u32_to_bytes(x.bd, &out[52]);
    vrr_u32_to_bytes(x.cd, &out[56]);
    vrr_u32_to_bytes(x.dd, &out[60]);
}

static inline uint32_t
vrr_rotate_left_u32(uint32_t const x, int const n)
{
    // WARNING: defined only for `1 <= n && n <= 31`.
    return (x << n) | (x >> (32 - n));
}
