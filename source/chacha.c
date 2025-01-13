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
    uint8_t const key[static const 32], uint8_t const nonce[static const 12],
    unsigned long long const n, uint8_t *out)
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
        vrr_u32(nonce[8], nonce[9], nonce[10], nonce[11]),
        0x00000000,
    };
    for (unsigned long i = 0; i < n / 64; ++i) {
        // TODO(rupt): a function to assign the counter?
        state.dd = (uint32_t)i;
        struct vrr_u32x4x4 v = vrr_chacha20(state);
        // TODO(rupt): a function for extracting bytes in the right order
        uint8_t *out_i = &out[i * 64];
        struct vrr_u8x4 xaa = vrr_u8x4_from_u32(v.aa);
        out_i[0] = xaa.a;
        out_i[1] = xaa.b;
        out_i[2] = xaa.c;
        out_i[3] = xaa.d;
        struct vrr_u8x4 xba = vrr_u8x4_from_u32(v.ba);
        out_i[4] = xba.a;
        out_i[5] = xba.b;
        out_i[6] = xba.c;
        out_i[7] = xba.d;
        struct vrr_u8x4 xca = vrr_u8x4_from_u32(v.ca);
        out_i[8] = xca.a;
        out_i[9] = xca.b;
        out_i[10] = xca.c;
        out_i[11] = xca.d;
        struct vrr_u8x4 xda = vrr_u8x4_from_u32(v.da);
        out_i[12] = xda.a;
        out_i[13] = xda.b;
        out_i[14] = xda.c;
        out_i[15] = xda.d;

        struct vrr_u8x4 xab = vrr_u8x4_from_u32(v.ab);
        out_i[16] = xab.a;
        out_i[17] = xab.b;
        out_i[18] = xab.c;
        out_i[19] = xab.d;
        struct vrr_u8x4 xbb = vrr_u8x4_from_u32(v.bb);
        out_i[20] = xbb.a;
        out_i[21] = xbb.b;
        out_i[22] = xbb.c;
        out_i[23] = xbb.d;
        struct vrr_u8x4 xcb = vrr_u8x4_from_u32(v.cb);
        out_i[24] = xcb.a;
        out_i[25] = xcb.b;
        out_i[26] = xcb.c;
        out_i[27] = xcb.d;
        struct vrr_u8x4 xdb = vrr_u8x4_from_u32(v.db);
        out_i[28] = xdb.a;
        out_i[29] = xdb.b;
        out_i[30] = xdb.c;
        out_i[31] = xdb.d;

        struct vrr_u8x4 xac = vrr_u8x4_from_u32(v.ac);
        out_i[32] = xac.a;
        out_i[33] = xac.b;
        out_i[34] = xac.c;
        out_i[35] = xac.d;
        struct vrr_u8x4 xbc = vrr_u8x4_from_u32(v.bc);
        out_i[36] = xbc.a;
        out_i[37] = xbc.b;
        out_i[38] = xbc.c;
        out_i[39] = xbc.d;
        struct vrr_u8x4 xcc = vrr_u8x4_from_u32(v.cc);
        out_i[40] = xcc.a;
        out_i[41] = xcc.b;
        out_i[42] = xcc.c;
        out_i[43] = xcc.d;
        struct vrr_u8x4 xdc = vrr_u8x4_from_u32(v.dc);
        out_i[44] = xdc.a;
        out_i[45] = xdc.b;
        out_i[46] = xdc.c;
        out_i[47] = xdc.d;

        struct vrr_u8x4 xad = vrr_u8x4_from_u32(v.ad);
        out_i[48] = xad.a;
        out_i[49] = xad.b;
        out_i[50] = xad.c;
        out_i[51] = xad.d;
        struct vrr_u8x4 xbd = vrr_u8x4_from_u32(v.bd);
        out_i[52] = xbd.a;
        out_i[53] = xbd.b;
        out_i[54] = xbd.c;
        out_i[55] = xbd.d;
        struct vrr_u8x4 xcd = vrr_u8x4_from_u32(v.cd);
        out_i[56] = xcd.a;
        out_i[57] = xcd.b;
        out_i[58] = xcd.c;
        out_i[59] = xcd.d;
        struct vrr_u8x4 xdd = vrr_u8x4_from_u32(v.dd);
        out_i[60] = xdd.a;
        out_i[61] = xdd.b;
        out_i[62] = xdd.c;
        out_i[63] = xdd.d;
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
