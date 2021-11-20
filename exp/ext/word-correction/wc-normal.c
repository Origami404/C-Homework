// This file is saved with UTF-8 encoding,
// and Chinese comments included.
// Please open with editor support UTF-8 to get the best experience.
/* Test result with i7-11700H on WSL2 Archlinux:
 *     $ clang -Wall -Wextra -std=c17 -Ofast wc-normal.c -o wc-norm-O2.tmpexc
 *     $ clang -Wall -Wextra -std=c17 wc-normal.c -o wc-norm.tmpexc 
 *     $ time ./wc-norm.tmpexc 
 *     ./wc-norm.tmpexc  1.22s user 0.02s system 99% cpu 1.245 total
 *     $ time ./wc-norm-O2.tmpexc 
 *     ./wc-norm-O2.tmpexc  0.26s user 0.01s system 99% cpu 0.275 total
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

static inline int min(int a, int b) { return a < b ? a : b; }

#define VOC_COUNT 3500
char *dict[VOC_COUNT];
size_t dict_cnt = 0;

/**
 * @brief 手动实现的 strdup, 返回一个字符串的副本, 进行内存分配
 * 
 * @param s 待复制的字符串
 * @return char* 复制出来的字符串副本, 在堆上
 */
char *strdup(char const *s) {
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

/**
 * @brief 比较两个字符串指针指针指向的字符串的大小, 遵循 qsort 约定
 * 
 * @param a 待比较字符串指针指针
 * @param b 待比较字符串指针指针
 * @return int 他们指向的字符串的相对大小
 */
int strp_cmp(void const *a, void const *b) { return strcmp(*(char **)a, *(char **)b); }

/**
 * @brief 从词典文件中解析出词典并排序
 * 
 * 限定单个单词最长长度为 64 个字符
 * 
 * @param voc_file 词典文件指针
 */
void dict_build(FILE *voc_file) {
    char buf[64];
    // 读取直到回车为止的字符, 并且把回车吃掉
    while (fscanf(voc_file, "%[^\n] ", buf) != -1) {
        dict[dict_cnt++] = strdup(buf); 
    }

    // 排序, 通过排序字符串指针指针来减小拷贝性能损耗
    qsort(dict, dict_cnt, sizeof(char *), strp_cmp);
}

/**
 * @brief 查找单词是否在词汇表内
 * 
 * @param word 待查找的单词
 * @return true 单词在词汇表内
 * @return false 单词不在词汇表内
 */
bool is_in_dict(char const *word) {
    return bsearch(&word, dict, dict_cnt, sizeof(char *), strp_cmp) != 0;
}

/**
 * @brief 类 strtok 实现的待改错文件的单词划分
 * 
 * 本函数不可重入 
 * 本函数会破坏 input 的内容
 * 以一个或多个非字母数字字符为分隔符
 * 返回的字符串指针是 input 的一部分, 不可 free
 * 
 * @param input (1) 当其非空时, 为待分词的字符串, 此字符串内容将会被破坏 
 *              (2) 当其为空时, 接着上一次返回的结果往后继续分词
 * @return char* 当下分出的字符串指针, 若再无词可被分出, 返回空指针
 */
char *cut_word(char *input) {
    // 保存目前解析进度
    static char *str;

    // 如果输入非空, 就进行一次重置
    if (input) { str = input; }

    // 往后推进忽略所有空白并检测空字符
    while (*str && !isalnum(*str)) 
        str += 1;
    if (!*str) return 0;

    // 保存待返回的结果
    char * const word = str;

    // 往后推进直到本词结束
    char *now = str;
    while (isalnum(*now)) 
        now += 1;
    *now = '\0';

    // 把 str 往后挪
    str = now + 1;

    return word;
}

/**
 * @brief 计算两字符串 A, B 之间的编辑距离
 * 
 * @param A 非空字符串 A
 * @param B 非空字符串 B
 * @return int 他们的编辑距离
 */
int calc_distance(char const A[static 1], char const B[static 1]) {
    size_t const la = strlen(A);
    size_t const lb = strlen(B);

    int distance[la + 1][lb + 1];

    for (size_t i = 0; i <= la; i++) {
        distance[i][0] = i;
    }

    for (size_t j = 0; j <= lb; j++) {
        distance[0][j] = j;
    }

    for (size_t i = 1; i <= la; i++) {
        for (size_t j = 1; j <= lb; j++) {
            distance[i][j] = INT_MAX;
            distance[i][j] = min(distance[i][j], distance[i-1][j-1] + (A[i-1] != B[j-1]));
            distance[i][j] = min(distance[i][j], distance[i-1][j] + 1);
            distance[i][j] = min(distance[i][j], distance[i][j-1] + 1);
        }
    }

    return distance[la][lb];
}

/**
 * @brief 改正词汇, 如果词汇在表内则原样返回, 否则返回词汇表内的一个词汇
 * 
 * @param word 待改正的词汇
 * @return char* 改正后的词汇
 */
char const *correct(char const *word) {
    // 若在表内则直接返回原单词
    if (is_in_dict(word)) 
        return word;

    // 否则遍历单词表计算编辑距离
    // 并返回编辑距离最小的单词

    int min_dis = INT_MAX;
    char *min_word = 0;

    for (size_t i = 0; i < dict_cnt; i++) {
        int const now_dis = calc_distance(dict[i], word);
        if (now_dis < min_dis) {
            min_dis = now_dis;
            min_word = dict[i];
        }
    }

    return min_word;
}


int main() {
    // 读取并构建单词表
    FILE *voc_file = fopen("vocabulary.txt", "r");
    dict_build(voc_file);

    // 打开输入输出文件
    FILE *input_file = fopen("words.txt", "r");
    FILE *output_file = fopen("word_correction.txt", "w");

    char buf[128];
    fgets(buf, 4, input_file); // eat the BOM

    // 逐行处理原文件
    while (fgets(buf, sizeof(buf), input_file)) {
        // 原样输出前四个数字字符
        buf[4] = '\0'; 
        fprintf(output_file, "%s ", buf);

        // 开始切词, 第一个词以空格跟其他的词分隔
        char *word = cut_word(buf + 5);
        fprintf(output_file, "%s ", correct(word));

        // 继续切词直到结束, 后面的词中间以斜杠分隔, 并且末尾不能出现斜杠
        bool is_first_slash = true;
        while ((word = cut_word(0))) {
            // 分隔用斜杠的处理
            if (is_first_slash) {
                is_first_slash = false;
            } else {
                fprintf(output_file, "/");
            }

            // 输出单词
            fprintf(output_file, "%s", correct(word));
        }

        // 该行结束 
        fprintf(output_file, "\n");
    }   

    // Clearup
    for (size_t i = 0; i < dict_cnt; i++) {
        free(dict[i]);
    }

    return 0;
}