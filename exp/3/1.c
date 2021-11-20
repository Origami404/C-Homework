#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief 判断一个数是不是正素数  
 * 
 * @param x 待判断的数
 * @return true x是素数
 * @return false x不是素数
 */
bool is_prime(int x) {
    if (x <= 1)
        return false;

    // 小心浮点截断
    int const harf = (int)sqrt(x) + 1;
    for (int i = 2; i < harf; i++) {
        if (x % i == 0)
            return false;
    }

    return true;
}

int main() {
    int m; // 组数
    scanf("%d", &m);

    while (m --> 0) {
        int n, res = 0;
        scanf("%d", &n); // 该组有多少个数

        while (n --> 0) {
            int num;
            scanf("%d", &num);
            if (is_prime(num))
                res += num;
        }

        printf("%d\n", res);
    }
}