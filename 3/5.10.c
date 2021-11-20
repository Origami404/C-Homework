// ====== 5.10 ======
#include <stdio.h>

// 连续的比较长的表为什么要用 switch ?
// switch 适合离散的(比如前面的年利率)或者短的
// 这种从 0/1 开始的数据数组不香吗
int month_day[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int is_leap(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int main() {
    int year, month;

    scanf("%d %d", &year, &month);
    if (month > 12) return 1;

    printf("%d\n", month_day[month] + (month == 2 ? is_leap(year) : 0));

    return 0;
}