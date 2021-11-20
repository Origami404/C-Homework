// 6.5
#include <stdio.h>

int main() {
    printf("   F --- C\n");
    for (int t = 0; t <= 300; t += 10) {
        printf("%4d --- %4.2f\n", t, 5.0 / 9 * (t - 32));
    }

    return 0;
}