// 6.2 (3)
#include <stdio.h>

int main() {
    long term, sum = 0; // (1) term
    int a, n;

    printf("Input a,n:");
    scanf("%d,%d", &a, &n);

    for (int i = 1; i <= n; i++) {
        term = term*10 + a; // (2) term*10 + a
        sum = sum + term;
    }

    printf("sum = %ld\n", sum);
    return 0;
}