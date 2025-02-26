#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>
#endif

struct vrr_chacha_key {
    uint8_t key[32];
};

struct vrr_chacha_nonce {
    uint8_t nonce[8];
};

void vrr_chacha_stream(struct vrr_chacha_key key1,
                       struct vrr_chacha_nonce nonce1, unsigned long long n,
                       uint8_t *out);
