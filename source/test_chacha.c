#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "vrr.h"
#include "chacha.h"

// TODO(rupt): test non-multiples of 64 bytes
// TODO(rupt): test more than 64 bytes

static void test_chacha_64(
    int label,
    // TODO(rupt): use key and nonce structures
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    uint8_t const key[static 32], uint8_t const nonce[static 8],
    uint8_t const expected[static 64]);

struct mynonce {
    uint8_t value[8];
};

int
main(void)
{
    // Test vectors from this early RFC before its update to 12-byte nonces:
    // https://datatracker.ietf.org/doc/html/draft-agl-tls-chacha20poly1305-04#section-7
    test_chacha_64(
        /*label=*/0,
        /*key=*/(uint8_t[32]){0}, /*nonce=*/(uint8_t[8]){0},
        /*expected=*/(uint8_t[64]){0x76, 0xb8, 0xe0, 0xad, 0xa0, 0xf1, 0x3d,
                                   0x90, 0x40, 0x5d, 0x6a, 0xe5, 0x53, 0x86,
                                   0xbd, 0x28, 0xbd, 0xd2, 0x19, 0xb8, 0xa0,
                                   0x8d, 0xed, 0x1a, 0xa8, 0x36, 0xef, 0xcc,
                                   0x8b, 0x77, 0x0d, 0xc7, 0xda, 0x41, 0x59,
                                   0x7c, 0x51, 0x57, 0x48, 0x8d, 0x77, 0x24,
                                   0xe0, 0x3f, 0xb8, 0xd8, 0x4a, 0x37, 0x6a,
                                   0x43, 0xb8, 0xf4, 0x15, 0x18, 0xa1, 0x1c,
                                   0xc3, 0x87, 0xb6, 0x69, 0xb2, 0xee, 0x65,
                                   0x86});
}

static void
test_chacha_64(int const label,
               // TODO(rupt): use key and nonce structures
               // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
               uint8_t const key[static const 32],
               // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
               uint8_t const nonce[static const 8],
               uint8_t const expected[static const 64])
{
    uint8_t stream[64];
    vrr_chacha_stream(key, nonce, 64, stream);
    for (int i = 0; i < 64; ++i) {
        if (stream[i] != expected[i]) {
            printf(vrr_observed("case %d: stream[%d] == 0x%02x"), label, i,
                   stream[i]);
            printf(vrr_expected("case %d: stream[%d] == 0x%02x"), label, i,
                   expected[i]);
        }
    }
}
