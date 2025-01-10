#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "vrr.h"

static void test_u32_to_from_u8x4();
static void test_u32_to_from_u8x4_case(uint32_t x);
static void test_rotate_left_u32();

int
main()
{
    test_u32_to_from_u8x4();
    test_rotate_left_u32();
}

static void
test_u32_to_from_u8x4()
{
    // A known case must hold.
    struct vrr_u8x4 const example = {0x0a, 0x1b, 0x2c, 0x3d};
    uint32_t const reference = 0x3d2c1b0a;
    uint32_t const check = vrr_u32_from_u8x4(example);
    if (check != reference) {
        printf(vrr_observed("0x%08x"), check);
        printf(vrr_expected("0x%08x"), reference);
    }
    test_u32_to_from_u8x4_case(reference);

    // Pseudo-random other cases must hold.
    test_u32_to_from_u8x4_case(0x243f6a88);
    test_u32_to_from_u8x4_case(0x85a308d3);
    test_u32_to_from_u8x4_case(0x13198a2e);
    test_u32_to_from_u8x4_case(0x03707344);
}

static void
test_u32_to_from_u8x4_case(uint32_t const x)
{
    struct vrr_u8x4 const bytes = vrr_u8x4_from_u32(x);

    // Our little-endian layout must match a reference implementation.
    struct vrr_u8x4 const ref = {(x >> 0) & 0xff, (x >> 8) & 0xff,
                                 (x >> 16) & 0xff, (x >> 24) & 0xff};
    if (bytes.a != ref.a || bytes.b != ref.b || bytes.c != ref.c ||
        bytes.d != ref.d) {
        printf(vrr_observed("{0x%02x, 0x%02x, 0x%02x, 0x%02x}"), bytes.a,
               bytes.b, bytes.c, bytes.d);
        printf(vrr_expected("{0x%02x, 0x%02x, 0x%02x, 0x%02x}"), ref.a, ref.b,
               ref.c, ref.d);
    }

    // Our inverse function must reconstruct the original.
    uint32_t const check = vrr_u32_from_u8x4(bytes);
    if (check != x) {
        printf(vrr_observed("0x%08x"), check);
        printf(vrr_expected("0x%08x"), x);
    };
}

static void
test_rotate_left_u32()
{
    uint32_t x_n_expected[4][3] = {
        {0x01020304, 4, 0x10203040},
        {0x01020304, 8, 0x02030401},
        {0x01020304, 8, 0x02030401},
        {0x24824824, 31, 0x12412412},
    };
    for (int i = 0; i < 4; ++i) {
        uint32_t x = x_n_expected[i][0];
        int n = (int)x_n_expected[i][1];
        uint32_t expected = x_n_expected[i][2];

        uint32_t observed = vrr_rotate_left_u32(x, n);
        if (observed != expected) {
            printf(vrr_observed("0x%08x"), observed);
            printf(vrr_expected("0x%08x"), expected);
        };
    }
}
