#include <stdio.h>

#include "hello.h"

int main() {
    int a = 1;
    int b = plus_one(a);
    if (b != a + 1) {
        fprintf(stderr, "plus_one(%d) != %d\n", a, a + 1);
    }
}
