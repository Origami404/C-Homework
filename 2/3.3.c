#include <stdio.h>
#include <math.h>

int main() {
    double const rate = 2.25 / 100;
    int n, capital;

    scanf("%d %d", &n, &capital);
    printf("%f\n", capital * pow(1 + rate, n));

    return 0;
}