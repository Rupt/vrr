#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // for vrr.h
#include "vrr.h"  // struct vrr_u32x4x4, struct vrr_u32x4, vrr_rotate_left_u32
#endif

void vrr_chacha_stream(
    // TODO(rupt): use key and nonce structures
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    uint8_t const key[static 32], uint8_t const nonce[static 8],
    unsigned long long n, uint8_t *out);

struct vrr_u32x4x4 vrr_chacha20(struct vrr_u32x4x4 x);
