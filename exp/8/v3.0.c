#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Record {
    char id[5 + 1];
    char name[10 + 1];
    int income;
    int expenses;
} Record;

Record *record_list = 0;
size_t record_cnt = 0;

void exit_program(void);
void input_record(void);
void print_records_in_name_asc(void);
void print_records_by_name(void);
void print_avg_income_and_expenses(void);
void print_expenses_above_avg(void);
void print_records_in_id_asc(void);

void (*functions[])(void) = {
    exit_program,
    input_record,
    print_records_in_name_asc,
    print_records_by_name,
    print_avg_income_and_expenses,
    print_expenses_above_avg,
    print_records_in_id_asc,
};

int main() {
    while (true) {
        puts("1. Input record");
        puts("2. Sort and list records in alphabetical order by user name");
        puts("3. Search records by user name");
        puts("4. Calculate and list per capita income and expenses");
        puts("5. List records which have more expenses than per capita expenses");
        puts("6. List all records");
        puts("0. Exit");
        
        int choice = -1;
        do {
            printf("Please enter your choice: ");
        } while (scanf("%d", &choice) != 1 || !(0 <= choice && choice <= 6));

        functions[choice]();
    }

    return 0;
}

/**
 * @brief 判断整个字符串的所有字符是否都满足谓词 cond
 * (用于输入校验)
 * @param p 字符串
 * @param cond 谓词
 * @return true 如果字符串内所有字符都满足谓词
 * @return false 如果字符串内存在不满足谓词的字符
 */
bool str_all(char const *p, int (*cond)(int)) {
    size_t const len = strlen(p);
    for (size_t i = 0; i < len; i++) {
        if (!cond(p[i]))
            return false;
    }
    return true;
}

// ============ 比较函数, 遵循 <field>_[asc/des]_cmp 命名 ================
int name_asc_cmp(void const *a, void const *b) {
    return strcmp(((Record const *)a)->name, ((Record const *)b)->name);
}
int id_asc_cmp(void const *a, void const *b) {
    return strcmp(((Record const *)a)->id, ((Record const *)b)->id);
}

// ============ 无类型数据处理工具 ==============
typedef unsigned char byte;

/**
 * @brief 二分搜索, 有多个重复元素时返回首个元素
 * 
 * @param key 目标元素
 * @param ptr 已排序的待查找数组(按 comp 降序)
 * @param count 数组中元素的个数
 * @param size 元素的大小
 * @param comp 比较函数, 遵循 qsort 的约定
 * @return void* 找到的元素的指针, 若元素不存在则返回空指针
 */
void* binary_search_first_appear(void const *key, void const *ptr, size_t count, size_t size, int (*comp)(void const *, void const *)) {
    byte const *left = ptr;
    byte const *right = left + count*size;

    // keep element in [left, right) < key
    while (left != right) {
        byte const * const mid = left + (right - left) / size / 2 * size;
        int const res = comp(mid, key);

        if (res < 0) {
            left = mid + size;
        } else if (res == 0) {
            right = mid;
        } else {
            right = mid;
        }
    }

    return comp(right, key) == 0 ? (void*)right : 0;
}

// ============ 小工具 ====================
/**
 * @brief 打印输出 Record 之前的表头 */
void print_records_header(void) {
    printf("%10s%12s%10s%10s\n", "ID", "Name", "Income", "expenses");
    printf("  --------" "  ----------" "  --------" "  --------" "\n");
}

/**
 * @brief 打印 Record p
 * @param p 待打印的 Record */
void print_record(Record const *p) {
    printf("%10s%12s%10d%10d\n", p->id, p->name, p->income, p->expenses);
}

// ============== 由下为各个功能 ========================
void input_record(void) {
    printf("Please input the amount of records: ");
    scanf("%zu", &record_cnt);
    record_list = calloc(record_cnt, sizeof(Record));

    puts("Please input records in the format of \"ddddd <username> <income> <expenses>\"");
    for (Record *now = record_list; now < record_list + record_cnt; now++) {
        do {
            if (scanf("%5s", now->id) != 1 || !str_all(now->id, isdigit))
                continue;

            if (scanf("%10s", now->name) != 1 || !str_all(now->name, isalnum))
                continue;   

            if (scanf("%d %d", &(now->income), &(now->expenses)) != 2)
                continue;

            break;
        } while (1);
    }
}

void print_records_all(void) {
    print_records_header();
    for (size_t i = 0; i < record_cnt; i++) {
        print_record(record_list + i);
    }
}

void print_records_in_name_asc(void) {
    qsort(record_list, record_cnt, sizeof(Record), name_asc_cmp);
    print_records_all();
}

void print_records_by_name(void) {
    Record key = {0};

    do {
        scanf("%*[^\n]");
        printf("Please input name:");
    } while (scanf("%10s", key.name) != 1 && !str_all(key.id, isalnum));

    qsort(record_list, record_cnt, sizeof(Record), name_asc_cmp);
    Record *p = binary_search_first_appear(&key, record_list, record_cnt, sizeof(Record), name_asc_cmp);

    if (!p) {
        puts("Name not found, go back to menu.");
        return;
    }

    print_records_header();
    do {
        print_record(p++);
    } while (strcmp(p->name, key.name) == 0);
} 

void print_avg_income_and_expenses(void) {
    if (record_cnt == 0) {
        puts("Avg income: 0");
        puts("Avg expenses: 0");
        return;
    }

    int income_sum = 0;
    int expenses_sum = 0;

    for (size_t i = 0; i < record_cnt; i++) {
        income_sum += record_list[i].income;
        expenses_sum += record_list[i].expenses;
    }

    printf("Per capita income: %.2f\n", 1.0 * income_sum / record_cnt);
    printf("Per capita expenses: %.2f\n", 1.0 * expenses_sum / record_cnt);
}

void print_expenses_above_avg(void) {
    if (record_cnt == 0) 
        return;

    int expenses_sum = 0;
    for (size_t i = 0; i < record_cnt; i++) {
        expenses_sum += record_list[i].expenses;
    }

    double const avg_expenses = 1.0 * expenses_sum / record_cnt;

    for (size_t i = 0; i < record_cnt; i++) {
        if (record_list[i].expenses > avg_expenses) 
            print_record(record_list + i);
    }
}

void print_records_in_id_asc(void) {
    qsort(record_list, record_cnt, sizeof(Record), id_asc_cmp);
    print_records_all();
}

void exit_program(void) {
    exit(0);
}