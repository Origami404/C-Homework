// Chinese comments included
// Please open with UTF-8 encoding
// 8.15
#include <stdio.h>
#include <string.h>

/**
 * @brief 在一个升序列表中插入 x, 使得序列仍然保持升序
 * 
 * @param a 待插入的升序列表, 必须有 n + 1 这么长(即 a[n] 必须是可用的)
 * @param n a 中原有数据的长度
 * @param x 要插入的值 x
 */
void insert_in_ordered_array(int a[], int n, int x) {
    // 找到第一个大于 x 的位置, x 将插入这里
    int pos = 0;
    while (pos < n && x >= a[pos]) {
        pos += 1;
    }

    // move a[pos] --- a[n-1] to a[pos+1] --- a[n]
    memmove(a + pos + 1, a + pos, (n - pos) * sizeof(int));

    // 插入
    a[pos] = x;
} 

// ==== test/测试部分 ====
void print_array(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%3d", a[i]);
    printf("\n");
}

int main() {
    int a[10] = { 1, 3, 5, 7, 9 };

    // 普通测试
    insert_in_ordered_array(a, 5, 6);
    print_array(a, 10); // 1 3 5 6 7 9 0 0 0 0

    // 重复数据测试
    insert_in_ordered_array(a, 6, 7);
    print_array(a, 10); // 1 3 5 6 7 7 9 0 0 0

    // 末尾插入测试
    insert_in_ordered_array(a, 7, 10);
    print_array(a, 10); // 1 3 5 6 7 7 9 10 0 0

    return 0;
}