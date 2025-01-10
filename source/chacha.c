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
vrr_chacha_double_round(struct vrr_u32x4x4 const x)
{
    // Even rounds go down columns.
    struct vrr_u32x4 ta = vrr_chacha_quarter_round(x.aa, x.ba, x.ca, x.da);
    struct vrr_u32x4 tb = vrr_chacha_quarter_round(x.ab, x.bb, x.cb, x.db);
    struct vrr_u32x4 tc = vrr_chacha_quarter_round(x.ac, x.bc, x.cc, x.dc);
    struct vrr_u32x4 td = vrr_chacha_quarter_round(x.ad, x.bd, x.cd, x.dd);
    // Odd rounds go down diagonals.
    struct vrr_u32x4 t5 = vrr_chacha_quarter_round(ta.a, tb.b, tc.c, td.d);
    struct vrr_u32x4 t6 = vrr_chacha_quarter_round(tb.a, tc.b, td.c, ta.d);
    struct vrr_u32x4 t7 = vrr_chacha_quarter_round(tc.a, td.b, ta.c, tb.d);
    struct vrr_u32x4 t8 = vrr_chacha_quarter_round(td.a, ta.b, tb.c, tc.d);
    return (struct vrr_u32x4x4){
        .aa = t5.a,
        .bb = t5.b,
        .cc = t5.c,
        .dd = t5.d,
        .ab = t6.a,
        .bc = t6.b,
        .cd = t6.c,
        .da = t6.d,
        .ac = t7.a,
        .bd = t7.b,
        .ca = t7.c,
        .db = t7.d,
        .ad = t8.a,
        .ba = t8.b,
        .cb = t8.c,
        .dc = t8.d,
    };
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
