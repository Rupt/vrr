#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>  // uint8_t
#endif

struct vrr_chacha_key {
    uint8_t x[32];
};

struct vrr_chacha_nonce {
    uint8_t x[8];
};

void vrr_chacha_stream(struct vrr_chacha_key key, struct vrr_chacha_nonce nonce,
                       unsigned long long n, uint8_t *out);
