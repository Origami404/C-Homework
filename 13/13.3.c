#include <stdio.h>

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct Student {
    long id;
    char name[10];
    char sex;
    Date birthday;
    int score[4];
} Student;

int main() {
    Student students[] = {
        {100310121,   "WangGang", 'M', {1991,  5, 19}, {72, 83, 90, 82}},
        {100310122, "LiXiaoHong", 'M', {1992,  8, 20}, {88, 92, 78, 78}},
        {100310123, "WangLiHong", 'F', {1991,  9, 19}, {98, 72, 89, 66}},
        {100310124,  "ChengLiLI", 'F', {1992,  8, 20}, {87, 95, 78, 90}}
    };
    int const stu_cnt = sizeof(students) / sizeof(*students);

    FILE * const output = fopen("score.txt", "w");

    for (int i = 0; i < stu_cnt; i++) {
        int sum = 0;
        for (int j = 0; j < 4; j++)
            sum += students[i].score[j];
        
        fprintf(output, "%10ld%12s%c%6d/%02d/%02d%4d%4d%4d%4d%6.1f\n", 
            students[i].id, students[i].name, students[i].sex,
            students[i].birthday.year, students[i].birthday.month, students[i].birthday.day,
            students[i].score[0], students[i].score[1], students[i].score[2],students[i].score[3],
            sum / 4.0);
    }

    return 0;
}