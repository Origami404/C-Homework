#include <stdio.h>

int main() {
    int a[10], n, max, min, maxPos, minPos;

    for (n = 0; n < 10; n++)
        scanf("%d", a + n);

    max = min = a[0];
    maxPos = minPos = 0; // (1) 0
    for (n = 0; n < 10; n++) {
        if (a[n] > max) { // (2) a[n] > max
            max = a[n];
            maxPos = n; // (3) n
        } else if (a[n] < min) { // (4) a[n] < min
            min = a[n];
            minPos = n; // (5) n
        }
    }

    printf("max = %d, pos = %d\n", max, maxPos);
    printf("min = %d, pos = %d\n", min, minPos);
    return 0;
}