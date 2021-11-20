// 7.11
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand01() { return rand() & 1; }

int play_computer(int top) {
    int result = top + (30 - top) % 3;
    if (result == top) {
        result += 1 + rand01();
    }

    return result;
}

int play_human(int top) {
    int a = -1;
    printf("Now the number is: %d\n", top);
    
    do {
        printf("Please input your number: ");
        scanf("%d", &a);
        // 做一定的输入错误处理
    } while (a <= top || (top + 2) < a || 30 < a);
    
    return a;
}

// 函数指针的数组
int (*play_func[2])(int) = { play_computer, play_human };

int main() {
    // 此游戏有先手必胜策略
    // 对于先手, 他首先面对 1, 此时其要出 3, 
    // 并且在后续保持自己取到的总是 3 的倍数即可

    srand(time(0));

    int top = 1;
    // role 只会取0, 1, 因为 0^1 == 1, 1^1 == 0, 每一次循环 role 都从 0 变到 1
    for (int role = rand01(); 1; role ^= 1) {
        if ((top = play_func[role](top)) == 30) {
            printf("%s win.\n", role ? "Human" : "Computer");
            break;
        } 
    }

    return 0;
}