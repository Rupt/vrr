#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // for vrr.h
#include "vrr.h"  // struct vrr_u32x4x4, struct vrr_u32x4, vrr_rotate_left_u32
#include "chacha.h"
#endif

static inline struct vrr_u32x4x4 vrr_chacha_double_round(struct vrr_u32x4x4 x);
static inline struct vrr_u32x4 vrr_chacha_quarter_round(uint32_t a, uint32_t b,
                                                        uint32_t c, uint32_t d);

// TODO(rupt): only publicly expose the bytestream api.
struct vrr_u32x4x4
vrr_chacha20(struct vrr_u32x4x4 const x)
{
    struct vrr_u32x4x4 v = x;
    for (int i = 0; i < 10; ++i) {
        v = vrr_chacha_double_round(v);
    }
    return (struct vrr_u32x4x4){
        x.aa + v.aa, x.ab + v.ab, x.ac + v.ac, x.ad + v.ad,
        x.ba + v.ba, x.bb + v.bb, x.bc + v.bc, x.bd + v.bd,
        x.ca + v.ca, x.cb + v.cb, x.cc + v.cc, x.cd + v.cd,
        x.da + v.da, x.db + v.db, x.dc + v.dc, x.dd + v.dd,
    };
}

static inline struct vrr_u32x4x4
vrr_chacha_double_round(struct vrr_u32x4x4 x)
{
    struct vrr_u32x4 tmp;
    // Even rounds go down columns.
    tmp = vrr_chacha_quarter_round(x.aa, x.ba, x.ca, x.da);
    x.aa = tmp.a, x.ba = tmp.b, x.ca = tmp.c, x.da = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ab, x.bb, x.cb, x.db);
    x.ab = tmp.a, x.bb = tmp.b, x.cb = tmp.c, x.db = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ac, x.bc, x.cc, x.dc);
    x.ac = tmp.a, x.bc = tmp.b, x.cc = tmp.c, x.dc = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ad, x.bd, x.cd, x.dd);
    x.ad = tmp.a, x.bd = tmp.b, x.cd = tmp.c, x.dd = tmp.d;
    // Odd rounds go down diagonals.
    tmp = vrr_chacha_quarter_round(x.aa, x.bb, x.cc, x.dd);
    x.aa = tmp.a, x.bb = tmp.b, x.cc = tmp.c, x.dd = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ab, x.bc, x.cd, x.da);
    x.ab = tmp.a, x.bc = tmp.b, x.cd = tmp.c, x.da = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ac, x.bd, x.ca, x.db);
    x.ac = tmp.a, x.bd = tmp.b, x.ca = tmp.c, x.db = tmp.d;
    tmp = vrr_chacha_quarter_round(x.ad, x.ba, x.cb, x.dc);
    x.ad = tmp.a, x.ba = tmp.b, x.cb = tmp.c, x.dc = tmp.d;
    return x;
}

static inline struct vrr_u32x4
vrr_chacha_quarter_round(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
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
