#include <stdio.h>

int peach_cnt_recu(int day_left) {
    if (day_left == 1) return 1;
    return 2 * (peach_cnt_recu(day_left - 1) + 1);
}

int peach_cnt_iter(int day_left) {
    int result = 1;
    while (day_left --> 1)
        result = 2 * (result + 1);
    return result;
}

int main() {
    int day;

    printf("Please input the day: ");
    scanf("%d", &day);

    printf("Result by recursion: %d\n", peach_cnt_recu(day));
    printf("Result by iteration: %d\n", peach_cnt_iter(day));

    return 0;
}



