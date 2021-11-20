// ====== 5.4 ======
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double get_rate(int const year) {
    switch (year) {
        case 1: return 2.25;
        case 2: return 2.43;
        case 3: return 2.70;
        case 5: return 2.88;
        case 8: return 3.00;
        default: exit(1);
    }
}

int main() {
    int year;
    double capital;

    scanf("%lf %d", &capital, &year);
    printf("%f", capital * pow(1 + get_rate(year) / 100, year));

    return 0;
}