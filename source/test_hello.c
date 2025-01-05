
#include <stdio.h>

#include "hello.h"
#include "test.h"

int
main()
{
    int a = 1;
    int b = plus_one(/*x=*/a);
    if (b != a + 1) {
        printf(vrr_expected("%d"), b);
        printf(vrr_observed("%d"), a + 1);
    }
}
