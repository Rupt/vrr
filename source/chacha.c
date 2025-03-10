#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>
#include "chacha.h"
#endif

struct u8x4 {
    uint8_t a, b, c, d;
};

struct u32x4 {
    uint32_t a, b, c, d;
};

struct u32x4x4 {
    struct u32x4 a, b, c, d;
};

static inline uint32_t
u32_from_u8(uint8_t const a, uint8_t const b, uint8_t const c, uint8_t const d)
{
    return a | (uint32_t)b << 8 | (uint32_t)c << 16 | (uint32_t)d << 24;
}

static inline void
u32_to_bytes(uint32_t const x, uint8_t out[static const 4])
{
    out[0] = (uint8_t)x;
    out[1] = (uint8_t)(x >> 8);
    out[2] = (uint8_t)(x >> 16);
    out[3] = (uint8_t)(x >> 24);
}

static inline void
u32x4_to_bytes(struct u32x4 const x, uint8_t out[static const 16])
{
    u32_to_bytes(x.a, &out[0]);
    u32_to_bytes(x.b, &out[4]);
    u32_to_bytes(x.c, &out[8]);
    u32_to_bytes(x.d, &out[12]);
}

static inline void
u32x4x4_to_bytes(struct u32x4x4 const x, uint8_t out[static const 64])
{
    u32x4_to_bytes(x.a, &out[0]);
    u32x4_to_bytes(x.b, &out[16]);
    u32x4_to_bytes(x.c, &out[32]);
    u32x4_to_bytes(x.d, &out[48]);
}

static inline struct u32x4
chacha_quarter(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    a += b;
    d ^= a;
    d = (d << 16) | (d >> 16);
    c += d;
    b ^= c;
    b = (b << 12) | (b >> 20);
    a += b;
    d ^= a;
    d = (d << 8) | (d >> 24);
    c += d;
    b ^= c;
    b = (b << 7) | (b >> 25);
    return (struct u32x4){a, b, c, d};
}

static inline struct u32x4x4
chacha_double(struct u32x4x4 const x)
{
    // Even rounds go down columns.
    struct u32x4 const a = chacha_quarter(x.a.a, x.b.a, x.c.a, x.d.a);
    struct u32x4 const b = chacha_quarter(x.a.b, x.b.b, x.c.b, x.d.b);
    struct u32x4 const c = chacha_quarter(x.a.c, x.b.c, x.c.c, x.d.c);
    struct u32x4 const d = chacha_quarter(x.a.d, x.b.d, x.c.d, x.d.d);
    // Odd rounds go down diagonals.
    struct u32x4 const v1 = chacha_quarter(a.a, b.b, c.c, d.d);
    struct u32x4 const v2 = chacha_quarter(b.a, c.b, d.c, a.d);
    struct u32x4 const v3 = chacha_quarter(c.a, d.b, a.c, b.d);
    struct u32x4 const v4 = chacha_quarter(d.a, a.b, b.c, c.d);
    return (struct u32x4x4){
        {v1.a, v2.a, v3.a, v4.a},
        {v4.b, v1.b, v2.b, v3.b},
        {v3.c, v4.c, v1.c, v2.c},
        {v2.d, v3.d, v4.d, v1.d},
    };
}

static inline struct u32x4x4
chacha20(struct u32x4x4 const x)
{
    struct u32x4x4 v = x;
    for (int i = 0; i < 10; ++i) {
        v = chacha_double(v);
    }
    return (struct u32x4x4){
        {x.a.a + v.a.a, x.a.b + v.a.b, x.a.c + v.a.c, x.a.d + v.a.d},
        {x.b.a + v.b.a, x.b.b + v.b.b, x.b.c + v.b.c, x.b.d + v.b.d},
        {x.c.a + v.c.a, x.c.b + v.c.b, x.c.c + v.c.c, x.c.d + v.c.d},
        {x.d.a + v.d.a, x.d.b + v.d.b, x.d.c + v.d.c, x.d.d + v.d.d},
    };
}

void
vrr_chacha_stream(struct vrr_chacha_key const key,
                  struct vrr_chacha_nonce const nonce,
                  unsigned long long const n, uint8_t *out)
{
    // TODO(rupt): avoid mutating state
    struct u32x4x4 state = {
        // first row: constant
        {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574},
        // second row: key part 1
        {u32_from_u8(key.x[0], key.x[1], key.x[2], key.x[3]),
         u32_from_u8(key.x[4], key.x[5], key.x[6], key.x[7]),
         u32_from_u8(key.x[8], key.x[9], key.x[10], key.x[11]),
         u32_from_u8(key.x[12], key.x[13], key.x[14], key.x[15])},
        // third row: key part 2
        {u32_from_u8(key.x[16], key.x[17], key.x[18], key.x[19]),
         u32_from_u8(key.x[20], key.x[21], key.x[22], key.x[23]),
         u32_from_u8(key.x[24], key.x[25], key.x[26], key.x[27]),
         u32_from_u8(key.x[28], key.x[29], key.x[30], key.x[31])},
        // fourth row: {counter, nonce}
        {0x00000000, 0x00000000,
         u32_from_u8(nonce.x[0], nonce.x[1], nonce.x[2], nonce.x[3]),
         u32_from_u8(nonce.x[4], nonce.x[5], nonce.x[6], nonce.x[7])},
    };
    for (uint64_t i = 0; i < n / 64; ++i) {
        // TODO(rupt): a function to assign the counter?
        state.d.a = (uint32_t)i;
        state.d.b = (uint32_t)(i >> 32);
        struct u32x4x4 v = chacha20(state);
        u32x4x4_to_bytes(v, &out[64 * i]);
    }
    // TODO(rupt): condense this? Move to branch within the main loop?
    unsigned long remainder = n % 64;
    if (remainder == 0) {
        return;
    }
    // TODO(rupt): a function to assign the counter?
    uint64_t i_remainder = (uint32_t)(n / 64);
    state.d.a = (uint32_t)i_remainder;
    state.d.b = (uint32_t)(i_remainder >> 32);
    uint8_t tmp[64];
    struct u32x4x4 v = chacha20(state);
    u32x4x4_to_bytes(v, tmp);
    for (unsigned long i = 0; i < remainder; ++i) {
        out[i_remainder * 64 + i] = tmp[i];
    }
}
