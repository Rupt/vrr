#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // for vrr.h
#include "vrr.h"  // struct vrr_u32x4x4, struct vrr_u32x4, vrr_rotate_left_u32
#endif

static inline struct vrr_u32x4x4
vrr_chacha_double_round(struct vrr_u32x4x4 x)
{
    return x;
}

static inline struct vrr_u32x4
vrr_chacha_quarter_round(struct vrr_u32x4 x)
{
    x.a += x.b;
    x.d = vrr_rotate_left_u32(x.d ^ x.a, 16);
    x.c += x.d;
    x.b = vrr_rotate_left_u32(x.b ^ x.c, 12);
    x.a += x.b;
    x.d = vrr_rotate_left_u32(x.d ^ x.a, 8);
    x.c += x.d;
    x.b = vrr_rotate_left_u32(x.b ^ x.c, 7);
    return x;
}
