#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define feq(a, b) (fabs((a) - (b)) < 1e-5)

int main() {
    double a, b, c;

    scanf("%lf %lf %lf", &a, &b, &c);
    if (!(a + b > c && a + c > b && b + c > a)) {
        printf("不是三角形\n");
        return 0;
    }

    bool const is_equilateral = (feq(a, b) && feq(b, c));
    bool const is_isoceles    = (feq(a, b) || feq(b, c) || feq(a, c));
    bool const is_right       = (feq(a*a + b*b, c*c) || feq(a*a + c*c, b*b) || feq(b*b + c*c, a*a));
    
    if (is_equilateral) {
        printf("等边三角形\n");
    } else if (is_isoceles && is_right) {
        printf("等腰直角三角形\n");
    } else if (is_isoceles) {
        printf("等腰三角形\n");
    } else if (is_right) {
        printf("直角三角形\n");
    } else {
        printf("一般三角形\n");
    }

    double const p = (a + b + c) / 2;
    printf("S=%.2f\n", sqrt(p * (p-a) * (p-b) * (p-c)));

    return 0;
}