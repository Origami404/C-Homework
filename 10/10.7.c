#include <stdio.h>
#include <string.h>

void my_strrev_arr(char dst[], char const src[]) {
    size_t const len = strlen(src);
    for (int i = len - 1; i >= 0; i--) {
        dst[len - 1 - i] = src[i];
    }
    dst[len] = '\0';
}

void my_strrev_ptr(char *dst, char const *src) {
    char const * const beg = src;
    while (*src != '\0')
        src++;
    src -= 1; // 此时 src 指向 \0, 往后缩一位
    
    while (src >= beg)
        *dst++ = *src--;
    *dst = '\0';
}

int main() {
    char const test[] = "abcdefg";
    char buf[16]; 

    memset(buf, 0, sizeof(buf));
    my_strrev_arr(buf, test);
    puts(buf);

    memset(buf, 0, sizeof(buf));
    my_strrev_ptr(buf, test);
    puts(buf);

    return 0;
}