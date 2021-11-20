// 7.8
#include <stdio.h>

int test(int init) {
    int now = init;
    // 只需要做 n - 1 次, 因为最后一次不需要除以四并且也不需要判断是否能整除四
    for (int i = 1; i < 5; i++) {
        now = now * 5 + 1;
        if (now % 4 != 0) 
            return -1;
        now /= 4;
    }
    
    return now * 5 + 1;
}   

int main() {
    int init = 1;
    while (1) {
        int const result = test(init++);
        if (result > 0) {
            printf("%d\n", result);
            break;
        }
    }
    return 0;
}
