#include <stdint.h>
#include <stdio.h>

#include "test.h"
#include "chacha.h"

static void
check_streams(char const *const label, unsigned long long const count,
              uint8_t const *const observed, uint8_t const *const expected)
{
    for (unsigned long long i = 0; i < count; ++i) {
        if (observed[i] == expected[i]) {
            continue;
        }
        printf(vrr_observed("%s: [%llu] == 0x%02hhx"), label, i, observed[i]);
        printf(vrr_expected("%s: [%llu] == 0x%02hhx"), label, i, expected[i]);
    }
}

static void
test_rfc(void)
{
    // Test vectors from this draft RFC, with case 2 padded with observed values
    // https://datatracker.ietf.org/doc/html/draft-agl-tls-chacha20poly1305-04#section-7
    {
        struct vrr_chacha_key const key = {{0}};
        struct vrr_chacha_nonce const nonce = {{0}};
        uint8_t const expected[64] = {
            0x76, 0xb8, 0xe0, 0xad, 0xa0, 0xf1, 0x3d, 0x90, 0x40, 0x5d, 0x6a,
            0xe5, 0x53, 0x86, 0xbd, 0x28, 0xbd, 0xd2, 0x19, 0xb8, 0xa0, 0x8d,
            0xed, 0x1a, 0xa8, 0x36, 0xef, 0xcc, 0x8b, 0x77, 0x0d, 0xc7, 0xda,
            0x41, 0x59, 0x7c, 0x51, 0x57, 0x48, 0x8d, 0x77, 0x24, 0xe0, 0x3f,
            0xb8, 0xd8, 0x4a, 0x37, 0x6a, 0x43, 0xb8, 0xf4, 0x15, 0x18, 0xa1,
            0x1c, 0xc3, 0x87, 0xb6, 0x69, 0xb2, 0xee, 0x65, 0x86};
        uint8_t observed[sizeof(expected)];
        vrr_chacha_stream(key, nonce, sizeof(expected), observed);
        check_streams("0", sizeof(expected), observed, expected);
    }
    {
        struct vrr_chacha_key const key = {{[31] = 1}};
        struct vrr_chacha_nonce const nonce = {{0}};
        uint8_t const expected[64] = {
            0x45, 0x40, 0xf0, 0x5a, 0x9f, 0x1f, 0xb2, 0x96, 0xd7, 0x73, 0x6e,
            0x7b, 0x20, 0x8e, 0x3c, 0x96, 0xeb, 0x4f, 0xe1, 0x83, 0x46, 0x88,
            0xd2, 0x60, 0x4f, 0x45, 0x09, 0x52, 0xed, 0x43, 0x2d, 0x41, 0xbb,
            0xe2, 0xa0, 0xb6, 0xea, 0x75, 0x66, 0xd2, 0xa5, 0xd1, 0xe7, 0xe2,
            0x0d, 0x42, 0xaf, 0x2c, 0x53, 0xd7, 0x92, 0xb1, 0xc4, 0x3f, 0xea,
            0x81, 0x7e, 0x9a, 0xd2, 0x75, 0xae, 0x54, 0x69, 0x63};
        uint8_t observed[sizeof(expected)];
        vrr_chacha_stream(key, nonce, sizeof(expected), observed);
        check_streams("1", sizeof(expected), observed, expected);
    }
    {
        struct vrr_chacha_key const key = {{0}};
        struct vrr_chacha_nonce const nonce = {{[7] = 1}};
        uint8_t const expected[64] = {
            0xde, 0x9c, 0xba, 0x7b, 0xf3, 0xd6, 0x9e, 0xf5, 0xe7, 0x86, 0xdc,
            0x63, 0x97, 0x3f, 0x65, 0x3a, 0x0b, 0x49, 0xe0, 0x15, 0xad, 0xbf,
            0xf7, 0x13, 0x4f, 0xcb, 0x7d, 0xf1, 0x37, 0x82, 0x10, 0x31, 0xe8,
            0x5a, 0x05, 0x02, 0x78, 0xa7, 0x08, 0x45, 0x27, 0x21, 0x4f, 0x73,
            0xef, 0xc7, 0xfa, 0x5b, 0x52, 0x77, 0x06, 0x2e, 0xb7, 0xa0, 0x43,
            0x3e, 0x44, 0x5f, 0x41, 0xe3, 0x1a, 0xfa, 0xb7, 0x57};
        uint8_t observed[sizeof(expected)];
        vrr_chacha_stream(key, nonce, sizeof(expected), observed);
        check_streams("2", sizeof(expected), observed, expected);
    }
    {
        struct vrr_chacha_key const key = {{0}};
        struct vrr_chacha_nonce const nonce = {{1}};
        uint8_t const expected[64] = {
            0xef, 0x3f, 0xdf, 0xd6, 0xc6, 0x15, 0x78, 0xfb, 0xf5, 0xcf, 0x35,
            0xbd, 0x3d, 0xd3, 0x3b, 0x80, 0x09, 0x63, 0x16, 0x34, 0xd2, 0x1e,
            0x42, 0xac, 0x33, 0x96, 0x0b, 0xd1, 0x38, 0xe5, 0x0d, 0x32, 0x11,
            0x1e, 0x4c, 0xaf, 0x23, 0x7e, 0xe5, 0x3c, 0xa8, 0xad, 0x64, 0x26,
            0x19, 0x4a, 0x88, 0x54, 0x5d, 0xdc, 0x49, 0x7a, 0x0b, 0x46, 0x6e,
            0x7d, 0x6b, 0xbd, 0xb0, 0x04, 0x1b, 0x2f, 0x58, 0x6b};
        uint8_t observed[sizeof(expected)];
        vrr_chacha_stream(key, nonce, sizeof(expected), observed);
        check_streams("3", sizeof(expected), observed, expected);
    }
}

static void
test_prefixes(void)
{
    struct vrr_chacha_key const key = {{[3] = 0xab, [31] = 0xba}};
    struct vrr_chacha_nonce const nonce = {{3, 1, 4, 1, 5, 9, 2, 6}};
    uint8_t full[256];
    vrr_chacha_stream(key, nonce, sizeof(full), full);
    uint8_t partial[sizeof(full)];
    unsigned long long checks[] = {0, 1, 2, 3, 4, 45, 63, 64, 65, 255, 256};
    for (unsigned long long i = 0; i < sizeof(checks) / sizeof(*checks); ++i) {
        unsigned long long count = checks[i];
        vrr_chacha_stream(key, nonce, count, partial);
        check_streams("prefix", count, partial, full);
    }
}

unsigned long long
vrr_checksum(unsigned long long const count, uint8_t const *const data)
{
    // Approximate tabulation hashing with tables defined by SplitMix64
    uint64_t acc = 0;
    for (uint64_t i = 0; i < count; ++i) {
        uint64_t x = (i << 8) | data[i];
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        x ^= x >> 31;
        acc += x;
    }
    return acc;
}

static void
test_checksum(void)
{
    struct vrr_chacha_key key = {{0}};
    struct vrr_chacha_nonce nonce = {{0}};
    for (int i = 0; i < 32; ++i) {
        key.x[i] = (uint8_t)i;
    }
    for (int i = 0; i < 8; ++i) {
        nonce.x[i] = (uint8_t)i;
    }
    uint8_t stream[1000 * 1000];
    vrr_chacha_stream(key, nonce, sizeof(stream), stream);
    {
        uint64_t observed = vrr_checksum(sizeof(stream), stream);
        uint64_t expected = 0x31793600d4477bfc;
        if (observed != expected) {
            printf(vrr_observed("checksum 0x%016lx"), observed);
            printf(vrr_expected("checksum 0x%016lx"), expected);
        }
    }
}

int
main(void)
{
    test_rfc();
    test_prefixes();
    test_checksum();
}
