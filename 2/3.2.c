#include <stdio.h>

int main() {
    int x;

    scanf("%d", &x);
    x = (x < 0) ? -x : x;

    while (x) {
        printf("%d", x % 10);
        x /= 10;
    }

    return 0;
}