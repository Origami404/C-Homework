#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;

    scanf("%lf %lf %lf", &a, &b, &c);

    double const delta = b*b - 4*a*c;
    if (delta < 0) {
        return -1;
    }

    printf("x1 = %f\n", (-b + sqrt(delta)) / (2*a));
    printf("x2 = %f\n", (-b - sqrt(delta)) / (2*a));

    return 0;
}