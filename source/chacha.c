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
    unsigned long long const n, uint8_t out[static const n])
{
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
    for (unsigned long long i = 0; i + 64 < n; i += 64) {
        // TODO(rupt): a function to assign the counter?
        state.cd = (uint32_t)(i >> 32);
        state.dd = (uint32_t)i;
        struct vrr_u32x4x4 v = vrr_chacha20(state);
        // TODO(rupt): a function for extracting bytes in the right order
        struct vrr_u8x4 xaa = vrr_u8x4_from_u32(v.aa);
        out[i + 0] = xaa.a;
        out[i + 1] = xaa.b;
        out[i + 2] = xaa.c;
        out[i + 3] = xaa.d;
        struct vrr_u8x4 xba = vrr_u8x4_from_u32(v.ba);
        out[i + 4] = xba.a;
        out[i + 5] = xba.b;
        out[i + 6] = xba.c;
        out[i + 7] = xba.d;
        struct vrr_u8x4 xca = vrr_u8x4_from_u32(v.ca);
        out[i + 8] = xca.a;
        out[i + 9] = xca.b;
        out[i + 10] = xca.c;
        out[i + 11] = xca.d;
        struct vrr_u8x4 xda = vrr_u8x4_from_u32(v.da);
        out[i + 12] = xda.a;
        out[i + 13] = xda.b;
        out[i + 14] = xda.c;
        out[i + 15] = xda.d;

        struct vrr_u8x4 xab = vrr_u8x4_from_u32(v.ab);
        out[i + 16] = xab.a;
        out[i + 17] = xab.b;
        out[i + 18] = xab.c;
        out[i + 19] = xab.d;
        struct vrr_u8x4 xbb = vrr_u8x4_from_u32(v.bb);
        out[i + 20] = xbb.a;
        out[i + 21] = xbb.b;
        out[i + 22] = xbb.c;
        out[i + 23] = xbb.d;
        struct vrr_u8x4 xcb = vrr_u8x4_from_u32(v.cb);
        out[i + 24] = xcb.a;
        out[i + 25] = xcb.b;
        out[i + 26] = xcb.c;
        out[i + 27] = xcb.d;
        struct vrr_u8x4 xdb = vrr_u8x4_from_u32(v.db);
        out[i + 28] = xdb.a;
        out[i + 29] = xdb.b;
        out[i + 30] = xdb.c;
        out[i + 31] = xdb.d;

        struct vrr_u8x4 xac = vrr_u8x4_from_u32(v.ac);
        out[i + 32] = xac.a;
        out[i + 33] = xac.b;
        out[i + 34] = xac.c;
        out[i + 35] = xac.d;
        struct vrr_u8x4 xbc = vrr_u8x4_from_u32(v.bc);
        out[i + 36] = xbc.a;
        out[i + 37] = xbc.b;
        out[i + 38] = xbc.c;
        out[i + 39] = xbc.d;
        struct vrr_u8x4 xcc = vrr_u8x4_from_u32(v.cc);
        out[i + 40] = xcc.a;
        out[i + 41] = xcc.b;
        out[i + 42] = xcc.c;
        out[i + 43] = xcc.d;
        struct vrr_u8x4 xdc = vrr_u8x4_from_u32(v.dc);
        out[i + 44] = xdc.a;
        out[i + 45] = xdc.b;
        out[i + 46] = xdc.c;
        out[i + 47] = xdc.d;

        struct vrr_u8x4 xad = vrr_u8x4_from_u32(v.ad);
        out[i + 48] = xad.a;
        out[i + 49] = xad.b;
        out[i + 50] = xad.c;
        out[i + 51] = xad.d;
        struct vrr_u8x4 xbd = vrr_u8x4_from_u32(v.bd);
        out[i + 52] = xbd.a;
        out[i + 53] = xbd.b;
        out[i + 54] = xbd.c;
        out[i + 55] = xbd.d;
        struct vrr_u8x4 xcd = vrr_u8x4_from_u32(v.cd);
        out[i + 56] = xcd.a;
        out[i + 57] = xcd.b;
        out[i + 58] = xcd.c;
        out[i + 59] = xcd.d;
        struct vrr_u8x4 xdd = vrr_u8x4_from_u32(v.dd);
        out[i + 60] = xdd.a;
        out[i + 61] = xdd.b;
        out[i + 62] = xdd.c;
        out[i + 63] = xdd.d;
    }
    // TODO(rupt): support n not divisible by 64
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
