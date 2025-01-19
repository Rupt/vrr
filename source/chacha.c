#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // for vrr.h
#include "vrr.h"  // struct vrr_u32x4x4, struct vrr_u32x4, vrr_rotate_left_u32
#include "chacha.h"
#endif

static inline struct vrr_u32x4x4 vrr_chacha_double(struct vrr_u32x4x4 x);
static inline struct vrr_u32x4 vrr_chacha_quarter(uint32_t a, uint32_t b,
                                                  uint32_t c, uint32_t d);

// TODO(rupt): only publicly expose the bytestream api.
void
vrr_chacha_stream(
    // TODO(rupt): use key and nonce structures
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    uint8_t const key[static const 32], uint8_t const nonce[static const 8],
    unsigned long long const n, uint8_t *out)
{
    // TODO(rupt): avoid mutating state
    struct vrr_u32x4x4 state = {
        // first row: constant
        0x61707865,
        0x3320646e,
        0x79622d32,
        0x6b206574,
        // second row: key part 1
        vrr_u32(key[0], key[1], key[2], key[3]),
        vrr_u32(key[4], key[5], key[6], key[7]),
        vrr_u32(key[8], key[9], key[10], key[11]),
        vrr_u32(key[12], key[13], key[14], key[15]),
        // third row: key part 2
        vrr_u32(key[16], key[17], key[18], key[19]),
        vrr_u32(key[20], key[21], key[22], key[23]),
        vrr_u32(key[24], key[25], key[26], key[27]),
        vrr_u32(key[28], key[29], key[30], key[31]),
        // fourth row: nonce | counter
        vrr_u32(nonce[0], nonce[1], nonce[2], nonce[3]),
        vrr_u32(nonce[4], nonce[5], nonce[6], nonce[7]),
        0x00000000,
        0x00000000,
    };
    for (uint64_t i = 0; i < n / 64; ++i) {
        // TODO(rupt): a function to assign the counter?
        state.cd = (uint32_t)(i >> 32);
        state.dd = (uint32_t)i;
        struct vrr_u32x4x4 v = vrr_chacha20(state);
        vrr_u32x4x4_to_bytes(v, &out[64 * i]);
    }
    // TODO(rupt): condense this? Move to branch within the main loop?
    unsigned long remainder = n % 64;
    if (remainder == 0) {
        return;
    }
    state.dd = (uint32_t)(n / 64);
    uint8_t tmp[64];
    struct vrr_u32x4x4 v = vrr_chacha20(state);
    vrr_u32x4x4_to_bytes(v, tmp);
    for (unsigned long i = 0; i < remainder; ++i) {
        out[n / 64 * 64 + i] = tmp[i];
    }
}

struct vrr_u32x4x4
vrr_chacha20(struct vrr_u32x4x4 const x)
{
    struct vrr_u32x4x4 v = x;
    for (int i = 0; i < 10; ++i) {
        v = vrr_chacha_double(v);
    }
    return (struct vrr_u32x4x4){
        x.aa + v.aa, x.ba + v.ba, x.ca + v.ca, x.da + v.da,
        x.ab + v.ab, x.bb + v.bb, x.cb + v.cb, x.db + v.db,
        x.ac + v.ac, x.bc + v.bc, x.cc + v.cc, x.dc + v.dc,
        x.ad + v.ad, x.bd + v.bd, x.cd + v.cd, x.dd + v.dd,
    };
}

static inline struct vrr_u32x4x4
vrr_chacha_double(struct vrr_u32x4x4 const x)
{
    // Even rounds go down columns.
    struct vrr_u32x4 const a = vrr_chacha_quarter(x.aa, x.ab, x.ac, x.ad);
    struct vrr_u32x4 const b = vrr_chacha_quarter(x.ba, x.bb, x.bc, x.bd);
    struct vrr_u32x4 const c = vrr_chacha_quarter(x.ca, x.cb, x.cc, x.cd);
    struct vrr_u32x4 const d = vrr_chacha_quarter(x.da, x.db, x.dc, x.dd);
    // Odd rounds go down diagonals.
    struct vrr_u32x4 const v1 = vrr_chacha_quarter(a.a, b.b, c.c, d.d);
    struct vrr_u32x4 const v2 = vrr_chacha_quarter(b.a, c.b, d.c, a.d);
    struct vrr_u32x4 const v3 = vrr_chacha_quarter(c.a, d.b, a.c, b.d);
    struct vrr_u32x4 const v4 = vrr_chacha_quarter(d.a, a.b, b.c, c.d);
    return (struct vrr_u32x4x4){
        v1.a, v2.a, v3.a, v4.a,  // format first row
        v4.b, v1.b, v2.b, v3.b,  // format second row
        v3.c, v4.c, v1.c, v2.c,  // format third row
        v2.d, v3.d, v4.d, v1.d,
    };
}

static inline struct vrr_u32x4
vrr_chacha_quarter(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    a += b;
    d = vrr_rotate_left_u32(d ^ a, 16);
    c += d;
    b = vrr_rotate_left_u32(b ^ c, 12);
    a += b;
    d = vrr_rotate_left_u32(d ^ a, 8);
    c += d;
    b = vrr_rotate_left_u32(b ^ c, 7);
    return (struct vrr_u32x4){a, b, c, d};
}
