#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "vrr.h"
#include "chacha.h"

int
main(void)
{
    // It must match https://datatracker.ietf.org/doc/html/rfc7539 page 9.
    struct vrr_u32x4x4 const x = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,  // first row
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,  // second row
        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
        0x00000001, 0x09000000, 0x4a000000, 0x00000000,
    };
    struct vrr_u32x4x4 const y = {
        0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3,  // first row
        0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3,  // second row
        0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9,
        0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2,
    };
    struct vrr_u32x4x4 const s = vrr_chacha20(x);

    if (s.aa != y.aa || s.ab != y.ab || s.ac != y.ac || s.ad != y.ad) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.aa, s.ab, s.ac, s.ad);
        printf(vrr_expected("%08x %08x %08x %08x"), y.aa, y.ab, y.ac, y.ad);
    }
    if (s.ba != y.ba || s.bb != y.bb || s.bc != y.bc || s.bd != y.bd) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.ba, s.bb, s.bc, s.bd);
        printf(vrr_expected("%08x %08x %08x %08x"), y.ba, y.bb, y.bc, y.bd);
    }
    if (s.ca != y.ca || s.cb != y.cb || s.cc != y.cc || s.cd != y.cd) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.ca, s.cb, s.cc, s.cd);
        printf(vrr_expected("%08x %08x %08x %08x"), y.ca, y.cb, y.cc, y.cd);
    }
    if (s.da != y.da || s.db != y.db || s.dc != y.dc || s.dd != y.dd) {
        printf(vrr_observed("%08x %08x %08x %08x"), s.da, s.db, s.dc, s.dd);
        printf(vrr_expected("%08x %08x %08x %08x"), y.da, y.db, y.dc, y.dd);
    }
}
