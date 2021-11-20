// 6.20
#include <stdio.h>
#include <math.h>

int main() {
    // 根据甲乙证言可知车牌号为 aabb 的形式, 枚举 a, b
    for (int a = 1; a <= 9; a++) {
        for (int b = 1; b <= 9; b++) {
            if (a == b)
                continue;

            // 计算出车牌号对应的数字以及它的平方
            int const num = a*1000 + a*100 + b*10 + b;
            double const sq = sqrt(num);

            // 如果 sq 距离其四舍五入后的数字非常接近
            // 那就意味着 num 的平方根是整数, 输出 num
            if (fabs(sq - (int)(sq + 0.5)) <= 1e-5) {
                printf("%d\n", num);
            }
        }
    }

    // 答案是 7744 == 88*88

    return 0;
}