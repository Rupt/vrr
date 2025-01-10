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
        x.aa + v.aa, x.ba + v.ba, x.ca + v.ca, x.da + v.da,
        x.ab + v.ab, x.bb + v.bb, x.cb + v.cb, x.db + v.db,
        x.ac + v.ac, x.bc + v.bc, x.cc + v.cc, x.dc + v.dc,
        x.ad + v.ad, x.bd + v.bd, x.cd + v.cd, x.dd + v.dd,
    };
}

static inline struct vrr_u32x4x4
vrr_chacha_double_round(struct vrr_u32x4x4 const x)
{
    // TODO(rupt): tidy names
    // Even rounds go down columns.
    struct vrr_u32x4 ta = vrr_chacha_quarter_round(x.aa, x.ab, x.ac, x.ad);
    struct vrr_u32x4 tb = vrr_chacha_quarter_round(x.ba, x.bb, x.bc, x.bd);
    struct vrr_u32x4 tc = vrr_chacha_quarter_round(x.ca, x.cb, x.cc, x.cd);
    struct vrr_u32x4 td = vrr_chacha_quarter_round(x.da, x.db, x.dc, x.dd);
    // Odd rounds go down diagonals.
    struct vrr_u32x4 t5 = vrr_chacha_quarter_round(ta.a, tb.b, tc.c, td.d);
    struct vrr_u32x4 t6 = vrr_chacha_quarter_round(tb.a, tc.b, td.c, ta.d);
    struct vrr_u32x4 t7 = vrr_chacha_quarter_round(tc.a, td.b, ta.c, tb.d);
    struct vrr_u32x4 t8 = vrr_chacha_quarter_round(td.a, ta.b, tb.c, tc.d);
    return (struct vrr_u32x4x4){
        t5.a, t6.a, t7.a, t8.a, t8.b, t5.b, t6.b, t7.b,
        t7.c, t8.c, t5.c, t6.c, t6.d, t7.d, t8.d, t5.d,
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
