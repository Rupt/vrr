#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "vrr.h"
#include "chacha.h"

int
main(void)
{
    // It must match https://datatracker.ietf.org/doc/html/rfc7539 page 9.
    struct vrr_u32x4x4 const y = {
        0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3,  // format first row
        0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3,  // format second row
        0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9,
        0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2,
    };

    uint32_t key32[8] = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                         0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
    uint32_t nonce32[3] = {0x00000001, 0x09000000, 0x4a000000};

    uint8_t key[32];
    for (int i = 0; i < 8; ++i) {
        struct vrr_u8x4 k = vrr_u8x4_from_u32(key32[i]);
        key[4 * i + 0] = k.a;
        key[4 * i + 1] = k.b;
        key[4 * i + 2] = k.c;
        key[4 * i + 3] = k.d;
    }
    uint8_t nonce[12];
    for (int i = 0; i < 3; ++i) {
        struct vrr_u8x4 k = vrr_u8x4_from_u32(nonce32[i]);
        nonce[4 * i + 0] = k.a;
        nonce[4 * i + 1] = k.b;
        nonce[4 * i + 2] = k.c;
        nonce[4 * i + 3] = k.d;
    }

    uint8_t stream[64];
    vrr_chacha_stream(key, nonce, 64, stream);

    struct vrr_u32x4x4 const s = {
        vrr_u32(stream[0], stream[1], stream[2], stream[3]),
        vrr_u32(stream[4], stream[5], stream[6], stream[7]),
        vrr_u32(stream[8], stream[9], stream[10], stream[11]),
        vrr_u32(stream[12], stream[13], stream[14], stream[15]),
        vrr_u32(stream[16], stream[17], stream[18], stream[19]),
        vrr_u32(stream[20], stream[21], stream[22], stream[23]),
        vrr_u32(stream[24], stream[25], stream[26], stream[27]),
        vrr_u32(stream[28], stream[29], stream[30], stream[31]),
        vrr_u32(stream[32], stream[33], stream[34], stream[35]),
        vrr_u32(stream[36], stream[37], stream[38], stream[39]),
        vrr_u32(stream[40], stream[41], stream[42], stream[43]),
        vrr_u32(stream[44], stream[45], stream[46], stream[47]),
        vrr_u32(stream[48], stream[49], stream[50], stream[51]),
        vrr_u32(stream[52], stream[53], stream[54], stream[55]),
        vrr_u32(stream[56], stream[57], stream[58], stream[59]),
        vrr_u32(stream[60], stream[61], stream[62], stream[63]),
    };

    if (s.aa != y.aa || s.ba != y.ba || s.ca != y.ca || s.da != y.da) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.aa, s.ba, s.ca, s.da);
        printf(vrr_expected("%08x %08x %08x %08x"), y.aa, y.ba, y.ca, y.da);
    }
    if (s.ab != y.ab || s.bb != y.bb || s.cb != y.cb || s.db != y.db) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.ab, s.bb, s.cb, s.db);
        printf(vrr_expected("%08x %08x %08x %08x"), y.ab, y.bb, y.cb, y.db);
    }
    if (s.ac != y.ac || s.bc != y.bc || s.cc != y.cc || s.dc != y.dc) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.ac, s.bc, s.cc, s.dc);
        printf(vrr_expected("%08x %08x %08x %08x"), y.ac, y.bc, y.cc, y.dc);
    }
    if (s.ad != y.ad || s.bd != y.bd || s.cd != y.cd || s.dd != y.dd) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.ad, s.bd, s.cd, s.dd);
        printf(vrr_expected("%08x %08x %08x %08x"), y.ad, y.bd, y.cd, y.dd);
    }
}
