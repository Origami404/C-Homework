#include <stdio.h>

/**
 * @brief 获得某年某月的天数, 考虑闰年
 *
 * @param year 年份
 * @param month 月份
 * @return int 该月的天数
 */
int get_day(int year, int month);

/**
 * @brief 输出表头
 * 表头即每月份开头的 yyyy-mm 提示及星期
 * @param year 年份
 * @param month 月份
 */
void print_header(int year, int month);

/**
 * @brief 打印表体
 * 表体即表的内部, 也就是日期部分
 * @param year 年份
 * @param month 月份
 * @param weekday 该月第一天的星期数 (0-7 对应 Sun-Sat)
 */
void print_table(int year, int month, int weekday);

int main() {
    int year, weekday;

    // 输入年份并做一定的错误检查
    do {
        printf("Please input year: ");
        if (scanf("%d", &year) != 1) scanf("%*[^\n]");
    } while (year < 1900);

    // 获得该年第一天对应的星期数
    weekday = (year + (year - 1) / 400 + (year - 1) / 4 - (year - 1) / 100) % 7;
    for (int month = 1; month <= 12; month++) {
        print_header(year, month);
        print_table(year, month, weekday);
        printf("\n\n");

        weekday = (weekday + get_day(year, month)) % 7;
    }

    return 0;
}

/**
 * @brief 打印一定数量的空白
 *
 * @param cnt 要打印的空格的数量
 */
void print_blank(int cnt) {
    while (cnt --> 0)
        putchar(' ');
}

/**
 * @brief 计算一个整数 n 的十进制表示的长度
 *
 * @param n 待计算的整数
 * @return int 其十进制表示长度
 */
int calc_digit_length(int n) {
    int c = 0;
    while (n) {
        n /= 10;
        c += 1;
    }
    return c;
}

int get_day(int year, int month) {
    static int const day_in_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};

    // 判断闰年
    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
        return 29;
    return day_in_month[month - 1];
}

void print_header(int year, int month) {
    int const line_length = 49;

    // 为了让表头的年月份居中显示, 必需手动计算其长度并调整
    int const year_length  = calc_digit_length(year);
    int const month_length = calc_digit_length(month);
    int const word_length  = year_length + 1 + month_length;

    // 因为 year 是一个 int, 所以 space_before 永远不会小于 0
    int const space_before = (line_length - word_length) / 2;

    print_blank(space_before);
    printf("%d-%d\n", year, month);

    // 打印星期
    printf("    Sun    Mon   Tues    Wed   Thur    Fri    Sat\n");
}

void print_table(int year, int month, int weekday) {
    int const day_in_month = get_day(year, month);

    // 打印空白来跳过月份开头不存在的星期的天数
    print_blank(weekday * 7);
    for (int day = 1; day <= day_in_month; day++) {
        printf("%7d", day);

        weekday += 1;
        if (weekday == 7) {
            printf("\n");
            weekday = 0;
        }
    }
}