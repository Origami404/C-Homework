#include <stdio.h>
#include <assert.h>

/**
 * @brief 根据年份获得该年每一个月有多少天, 考虑闰年
 * 
 * @param year 年份
 * @return int const* 一个长度为 13 的数组, 索引为 1 的位置是一月的天数, 索引为 0 的位置的值未定义
 */
int const * get_day_in_month(int year) {
    static int const day_in_month_normal[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static int const day_in_month_leap[13] = { -1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? day_in_month_leap : day_in_month_normal;
}

/**
 * @brief 获得给定的日期是该年的第几天
 * 
 * @param year 年份
 * @param month 月份
 * @param day 月中天数
 * @return int 给定日期是该年的第几天
 */
int DayOfYear(int year, int month, int day) {
    int const * const day_in_month = get_day_in_month(year);

    int result = day;
    for (int i = 1; i < month; i++) 
        result += day_in_month[i];
    return result;
}

/**
 * @brief 计算输入的天数是该年的第几月第几天
 * 
 * @param year 给定的年份
 * @param yearDay 给定的天数
 * @param pMonth 返回值, 返回第几个月
 * @param pDay 返回值, 返回该天是该月的第几天
 */
void MonthDay(int year, int yearDay, int *pMonth, int *pDay) {
    int const * const day_in_month = get_day_in_month(year);

    int month = 1;
    while (yearDay - day_in_month[month] > 0) {
        yearDay -= day_in_month[month];
        month += 1;
        assert(month <= 12);
    }
    
    *pMonth = month;
    *pDay = yearDay;
}

/**
 * @brief 从键盘接收一个数字直到真的接收到符合条件的数字
 */
#define input_int(prompt, var, cond) \
    do {                                                \
        do {                                            \
            printf(prompt);                             \
        } while (scanf("%d", &var) == 1 && !(cond));     \
    } while (0)

int main() {
    while (1) {
        puts("1. year/month/day -> yearDay");
        puts("2. yearDay -> year/month/day");
        puts("3. Exit");

        int op = -1;
        input_int("Please input your choice: ", op, 1 <= op && op <= 3);

        switch (op) {
            case 1: {
                int year = -1, month = -1, day = -1;
                input_int("Please input year: ", year, 0 < year);
                input_int("Please input month: ", month, 1 <= month && month <= 12);
                input_int("Please input day: ", day, 1 <= day && day <= 31);

                printf("The day of year is %d.\n", DayOfYear(year, month, day));
            } break;

            case 2: {
                int year = -1, yearDay = -1;
                input_int("Please input year: ", year, 0 < year);

                int const day_in_year = 365 + (get_day_in_month(year)[2] - 28);
                input_int("Please input yearDay: ", yearDay, 1 <= yearDay && yearDay <= day_in_year);

                int month, day;
                MonthDay(year, yearDay, &month, &day);
                printf("The day in the year is: %d/%d/%d.\n", year, month, day);
            } break;

            case 3: return 0;
            default: assert(0);
        }
    }
    return 0;
}