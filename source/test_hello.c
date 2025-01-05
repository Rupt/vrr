#include <stdio.h>

#include "hello.h"

int main() {
    int a = 1;
    int b = plus_one(a);
    if (b != a + 1) {
        printf(
            "{"
            "\"file\": \"%s\", "
            "\"line\": \"%d\", "
            "\"expected\": \"%d\", "
            "\"observed\": \"%d\"}\n",
            __FILE__,
            __LINE__,
            b,
            a + 1
        );
    }
}
