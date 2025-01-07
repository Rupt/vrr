#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "vrr.h"

static void test_u32_to_from_u8x4_little_endian(uint32_t x);

int
main()
{
    // A known case must hold.
    struct vrr_u8x4 const example = {0x0a, 0x1b, 0x2c, 0x3d};
    uint32_t const reference = 0x3d2c1b0a;
    uint32_t const check = vrr_u32_from_u8x4_little_endian(example);
    if (check != reference) {
        printf(vrr_observed("0x%08x"), check);
        printf(vrr_expected("0x%08x"), reference);
    }
    test_u32_to_from_u8x4_little_endian(reference);

    // Pseudo-random other cases must hold.
    uint32_t const increment = 0xcba98765;
    for (uint32_t i = 0; i != increment * 256; i += increment) {
        test_u32_to_from_u8x4_little_endian(0x456789ab * (i ^ (i >> 17)));
    }
}

static void
test_u32_to_from_u8x4_little_endian(uint32_t const x)
{
    struct vrr_u8x4 const bytes = vrr_bytes_from_u32_little_endian(x);

    // Our little-endian bytes form must match a reference implementation.
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
    uint32_t const check = vrr_u32_from_u8x4_little_endian(bytes);
    if (check != x) {
        printf(vrr_observed("0x%08x"), check);
        printf(vrr_expected("0x%08x"), x);
    };
}
