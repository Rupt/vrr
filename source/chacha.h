#ifdef VRR_INCLUDE_GUARD
#undef VRR_INCLUDE_GUARD
#include <stdint.h>
#endif

void vrr_chacha_stream(
    // TODO(rupt): use key and nonce structures
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    uint8_t const key[static 32], uint8_t const nonce[static 8],
    unsigned long long n, uint8_t *out);
