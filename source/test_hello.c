#include <stdio.h>

#include "hello.h"
#include "test.h"

int
main(void)
{
    int a = 1;
    int b = plus_one(/*x=*/a);
    if (b != a + 1) {
        printf(vrr_observed("plus_one(%d) == %d"), a, b);
        printf(vrr_expected("plus_one(%d) == %d"), a, a + 1);
    }
}
