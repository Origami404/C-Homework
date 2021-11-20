// 6.10
#include <stdio.h>

int main() {
    for (int now = 100; now < 1000; now++) {
        int const a = (now / 100) % 10;
        int const b = (now / 10) % 10;
        int const c = (now / 1) % 10;

        if (a*a*a + b*b*b + c*c*c == now) {
            printf("%d ", now);
        } 
    }

    return 0;
}