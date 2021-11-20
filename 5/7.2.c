// 7.2
#include <stdio.h>

int hour, minute, second;

void Update() {
    second++;

    if (second == 60) {
        second = 0;  // (1) second = 0
        minute++;
    } 

    if (minute == 60) { // (2) minute == 60
        minute = 0;
        hour ++;
    }

    if (hour == 24) 
        hour = 0; // (3) hour = 0
}

void Display() {
    printf("%02d:%02d:%02d\n", hour, minute, second); // (4) %02d:%02d:%02d\n
}

void Delay() {
    // 建议用 windows.h 里的 Sleep
    // 这样写不符合节能减排
    for (int t = 0; t < 1e9; t++)
        ; // Do nothing here
}

int main() {
    // Objects with static storage duration are always initialized.
    // 不需要给 hour, minute, second 初始化
    // Do nothing here // (5) // Do nothing here

    for (int i = 0; i < 1e6; i++) {
        Update();
        Display();
        Delay();
    }

    return 0;
}
