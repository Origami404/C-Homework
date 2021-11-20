// 6.2 (5)
#include <stdio.h>
#include <math.h>

int main() {
    int n = 1, count = 1;
    double x, sum, term;

    printf("Input x:");
    scanf("%lf", &x); // (1) &x

    sum = term = x;
    do {
        term = term * -1 * x*x / ((n+1)*(n+2)); // (2) term * -1 * x*x / ((n+1)*(n+2))
        sum += term;
        n += 2;
        count += 1; // (3) count += 1
    } while (fabs(term) >= 1e-5); // (4) fabs(term) >= 1e-5

    printf("sin(x) = %f, count = %d\n", sum, count);

    return 0;
}