#include "iva.h"
#include <ctype.h>

// 字符
// 值在 int8_t 范围之内: -128 -- 127
// 0 成功, 1 正常失败(用户乱来), -1 其他错误(如EOF)
int accept_i8_impl(int8_t *result, struct InputSpec spec) {
    char *prompt = spec.prompt ? spec.prompt : "";
    char *at_fail = spec.at_fail ? spec.at_fail : "";
    FILE *file = spec.file ? spec.file : stdin;

    int c = EOF;

    do {
        c = getchar();
        if (c == EOF) 
            return -1;
    } while (isspace(c));

    if (c == '+')
        c = getchar();
    else if (c == '-')


}