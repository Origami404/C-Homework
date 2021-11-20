// 6.3
#include <stdio.h>

int main() {
    int x = 1, find = 0;

    while (!find) { // (1) while 后面的分号要删去

        // (2) if 的条件里将 == 误用为 =
        if (x%2 == 1 && x%3 == 2 && x%5 == 4 && x%6 == 5 && x%7 == 0) {
            printf("x = %d\n", x);
            find = 1;
        }
        // (3) 就算 x 不符合题意也要去寻找下一个 x
        x++;
    }
    // (4) 可以使用 break 以消除对 find 变量的不必要的使用

    return 0;
}