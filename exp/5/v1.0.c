#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define RECORD_MAX_CNT 1024

typedef struct Record {
    char id[5 + 1];
    int income;
    int expenses;
} Record;

Record record_list[RECORD_MAX_CNT];
size_t record_cnt = 0;

void exit_program(void);
void input_record(void);
void print_records_in_des_expenses(void);
void print_records_in_asc_expenses(void);
void print_records_in_asc_income(void);
void print_records_by_id(void);
void print_users_deficit(void);
void print_records_in_asc_id(void); 

void (*functions[10])(void) = {
    exit_program,
    input_record,
    print_records_in_des_expenses,
    print_records_in_asc_expenses,
    print_records_in_asc_income,
    print_records_by_id,
    print_users_deficit,
    print_records_in_asc_id, 
};

int main() {
    while (true) {
        puts("1. Input record");
        puts("2. Selection Sort in descending order by expenses");
        puts("3. Selection Sort in ascending order by expenses");
        puts("4. Bubble Sort in ascending order by income");
        puts("5. Search records by ID using Binary Search");
        puts("6. List records which have more expenses than income");
        puts("7. List all records");
        puts("0. Exit");
        
        int choice = -1;
        do {
            printf("Please enter your choice: ");
        } while (scanf("%d", &choice) != 1 || !(0 <= choice && choice <= 7));

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
int income_asc_cmp(void const *a, void const *b) {
    Record const * const pa = a;
    Record const * const pb = b;
    return (pa->income > pb->income) - (pa->income < pb->income);
}
int income_des_cmp(void const *a, void const *b) {
    return -income_asc_cmp(a, b);
}
int expenses_asc_cmp(void const *a, void const *b) {
    Record const * const pa = a;
    Record const * const pb = b;
    return (pa->expenses > pb->expenses) - (pa->expenses < pb->expenses);
}
int expenses_des_cmp(void const *a, void const *b) {
    return -expenses_asc_cmp(a, b);
}
int id_asc_cmp(void const *a, void const *b) {
    return strcmp(((Record const *)a)->id, ((Record const *)b)->id);
}
int id_des_cmp(void const *a, void const *b) {
    return -id_asc_cmp(a, b);
}

// ============ 无类型数据处理工具 ==============
typedef unsigned char byte;

/**
 * @brief 交换两块数据
 * 
 * @param a 待交换的数据的指针
 * @param b 待交换的数据的指针
 * @param size 要交换的字节数
 */
void mem_swap(void *a, void *b, size_t size) {
    byte tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

/**
 * @brief 冒泡排序
 * 
 * @param ptr 待排序的数组
 * @param count 数组中元素的个数
 * @param size 元素的大小
 * @param comp 比较函数, 遵循 qsort 的约定
 */
void bubble_sort(void *ptr, size_t count, size_t size, int (*comp)(void const *, void const *)) {
    bool has_changed;
    byte * const beg = ptr; 
    byte * const end = beg + count*size;

    do {
        has_changed = false;
        for (byte *p = (beg + size); p < end; p += size) {
            if (comp(p - size, p) > 0) {
                mem_swap(p - size, p, size);
                has_changed = true;
            }
        }
    } while (has_changed);
}

/**
 * @brief 选择排序
 *
 * @param ptr 待排序的数组
 * @param count 数组中元素的个数
 * @param size 元素的大小
 * @param comp 比较函数, 遵循 qsort 的约定
 */
void selection_sort(void *ptr, size_t count, size_t size, int (*comp)(void const *, void const *)) {
    byte * const beg = ptr;
    byte * const end = ptr + count*size;

    for (byte *first_unsort = beg; first_unsort < end; first_unsort += size) {
        byte *min_pos = first_unsort;
        for (byte *p = first_unsort + size; p < end; p += size) {
            if (comp(min_pos, p) > 0) {
                min_pos = p;
            }
        }
        mem_swap(min_pos, first_unsort, size);
    }
}

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

/**
 * @brief 打印输出 Record 之前的表头 */
void print_records_header(void) {
    printf("%10s%10s%10s\n", "ID", "Income", "expenses");
    printf("  --------" "  --------" "  --------" "\n");
}

/**
 * @brief 打印 Record p
 * @param p 待打印的 Record */
void print_record(Record const *p) {
    printf("%10s%10d%10d\n", p->id, p->income, p->expenses);
}

// ============== 由下依次为功能 1-7, 0 ========================

void input_record(void) {
    puts("Please input records in the format of \"ddddd,<income>,<expenses>\", use -1,-1,-1 as id to end.");
    while (1) {
        Record * const now = record_list + record_cnt;
        scanf("%5s", now->id);
        if (now->id[0] == '-') {
            scanf("%*[^\n]"); // clear up
            return;
        }
        if (!str_all(now->id, isdigit))
            continue;

        scanf(",%d,%d ", &(now->income), &(now->expenses));
        record_cnt += 1;
    }
}

void print_records_all(void) {
    print_records_header();
    for (size_t i = 0; i < record_cnt; i++) {
        print_record(record_list + i);
    }
}

void print_records_in_des_expenses(void) {
    selection_sort(record_list, record_cnt, sizeof(Record), expenses_des_cmp);
    print_records_all();
}

void print_records_in_asc_expenses(void) {
    selection_sort(record_list, record_cnt, sizeof(Record), expenses_asc_cmp);
    print_records_all();
}

void print_records_in_asc_income(void) {
    bubble_sort(record_list, record_cnt, sizeof(Record), income_asc_cmp);
    print_records_all();
}

void print_records_by_id(void) {
    Record key = {0};

    do {
        scanf("%*[^\n]");
        printf("Please input id:");
    } while (scanf("%5s", key.id) != 1 && !str_all(key.id, isdigit));

    qsort(record_list, record_cnt, sizeof(Record), id_des_cmp);
    Record *p = binary_search_first_appear(&key, record_list, record_cnt, sizeof(Record), id_des_cmp);

    if (!p) {
        puts("ID not found, go back to menu.");
        return;
    }

    print_records_header();
    do {
        print_record(p++);
    } while (strcmp(p->id, key.id) == 0);
}

void print_users_deficit(void) {
    print_records_header();
    for (size_t i = 0; i < record_cnt; i++) {
        if (record_list[i].income < record_list[i].expenses) 
            print_record(record_list + i); 
    }
}

void print_records_in_asc_id(void) {
    qsort(record_list, record_cnt, sizeof(Record), id_asc_cmp);
    print_records_all();
}

void exit_program(void) {
    exit(0);
}