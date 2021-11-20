#include <stdio.h>

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief 交换两个等长数组里对应位置元素的值
 * 
 * @param a 待交换的数组 a
 * @param b 待交换的数组 b
 * @param n 数组长度
 */
void swap_array(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        Swap(a + i, b + i);
}

// ==== test ====
int main() {
    int a[] = { 1, 3, 5, 7, 9 };
    int b[] = { 2, 4, 6, 8, 10 };
    int const n = 5;

    swap_array(a, b, n);

    printf("a: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("b: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
    return 0;
}

