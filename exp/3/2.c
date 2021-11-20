#include <stdio.h>

/**
 * @brief 输出方程的解  
 * 
 * @param x 解 x
 * @param y 解 y
 * @param z 解 z
 */
void output(int x, int y, int z) {
    printf("x = %d, y = %d, z = %d\n", x, y, z);
}

void method_1(void) {
    // O(1) 解法 / 数学方法
    printf("Method 1: \n");
    output(0, 25, 75); // 注意其实可以买 0 只鸡
    output(4, 18, 78);
    output(8, 11, 81);
    output(12, 4, 84);
} 

void method_2(void) {
    // 单重循环解法
    printf("Method 2: \n");
    // 变形, x = 4/3 * (z - 75), y = 1/3 * (600 - 7*z)
    // 要判断除法是否能够进行
    for (int z = 0; z <= 100; z++) {
        if (   (z - 75) >= 0    && (z - 75) % 3 == 0
            && (600 - 7*z) >= 0 && (600 - 7*z) % 3 == 0) {
            output(4 * (z - 75) / 3, (600 - 7*z) / 3, z);
        }
    }
}

void method_3(void) {
    // 双重循环解法
    printf("Method 3: \n");
    for (int y = 0; y <= 100; y++) {
        for (int z = 0; z <= 100; z++) {
            const int x = 100 - y - z;
            if (x >= 0 && z % 3 == 0 && 5*x + 3*y + z/3 == 100) {
                output(x, y, z);
            }
        }
    }
}

int main() {
    method_1();
    method_2();
    method_3();

    return 0;
}