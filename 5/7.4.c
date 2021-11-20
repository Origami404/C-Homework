// 7.4
#include <stdio.h>

// O(log n) 解法
// int gcd(int a, int b) { return a == 0 ? b : gcd(b % a, a); }
// int lcm(int a, int b) { return a*b / gcd(a, b); }

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int lcm = 1;
    while ((lcm % a != 0) || (lcm % b != 0))
        lcm += 1;
    
    printf("%d\n", lcm);
    return 0;
}