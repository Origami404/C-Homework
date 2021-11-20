#include <stdio.h>

int main() {
    int a, b, c, d;

    printf("Input a/b,c/d: ");
    scanf("%d/%d,%d/%d", &a, &b, &c, &d);

    // 在不考虑负数的时候, a/b < c/d 等价于 a*d - b*c < 0
    // 如果要考虑负数, 那么就应该把 bd 乘上去再判断正负
    int const delta = b * d * (a*d - b*c);
    char const op   = (delta < 0 ? '<' :
                      (delta > 0 ? '>' : '='));

    printf("%d/%d %c %d/%d\n", a, b, op, c, d);
    return 0;
}