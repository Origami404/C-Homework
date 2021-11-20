// 6.18
#include <stdio.h>

void print_header(void) {
    // 表头
    for (int i = 1; i <= 9; i++) 
        printf("%2d ", i);
    printf("\n");

    // 分隔线
    for (int i = 1; i <= 9; i++) 
        printf(" - ");
    printf("\n");
}

int main() {
    // 第一种形式
    print_header();
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) 
            printf("%2d ", i * j);
        printf("\n");
    }

    printf("\n\n");

    // 第二种形式
    print_header();
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) 
            printf("%2d ", i * j);
        printf("\n");
    }

    printf("\n\n");

    // 第三种形式
    print_header();
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i - 1; j++)
            printf("   ");
        for (int j = i; j <= 9; j++) 
            printf("%2d ", i * j);
        printf("\n");
    }

    return 0;
}