#include <stdio.h>
#include <stdlib.h>

void my_strdel_arr(char dst[], char const src[], char x) {
    int pos = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] != x)
            dst[pos++] = src[i];
    }
    dst[pos] = '\0';
}

void my_strdel_ptr(char *dst, char const *src, char x) {
    while (*src != '\0') {
        if ((*dst = *src++) != x)
            *dst++;
    }
    *dst = '\0';
}

int main() {
    char buf[20];
    char test[] = "aabbccaabbcc";

    my_strdel_arr(buf, test, 'a');
    printf("%s\n", buf);
    
    my_strdel_arr(buf, test, 'b');
    printf("%s\n", buf);
    
    my_strdel_arr(buf, test, 'c');
    printf("%s\n", buf);
    

    my_strdel_ptr(buf, test, 'a');
    printf("%s\n", buf);
    
    my_strdel_ptr(buf, test, 'b');
    printf("%s\n", buf);
    
    my_strdel_ptr(buf, test, 'c');
    printf("%s\n", buf);

    return 0;
}