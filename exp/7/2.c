#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief 递归判断输入的字符串是否为回文字符串
 * 
 * @param s 字符串
 * @param l 目前判断到的区间左端点(闭)
 * @param r 目前判断到的区间右端点(开)
 * @return true s 的 [l, r) 范围的子字符串是回文字符串
 * @return false s 的 [l, r) 范围的子字符串不是回文字符串
 */
bool is_palindrome(char const *s, size_t l, size_t r) {
    // 利用短路特性, 先判终止, 再判相等, 然后才递归
    // 尾递归, 常见编译器都可以优化为迭代
    return r - l <= 1 || (s[l] == s[r - 1] && is_palindrome(s, l + 1, r - 1));
}

int main() {
    char buf[128];

    scanf("%[^\n]", buf);
    puts(is_palindrome(buf, 0, strlen(buf)) ? "true" : "false");

    return 0;
}