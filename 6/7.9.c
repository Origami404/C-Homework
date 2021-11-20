// 7.9
#include <stdio.h>

int get_age(int idx) {
    return idx == 1 ? 10 : (2 + get_age(idx - 1));
}

int main() {
    printf("%d\n", get_age(5));
    return 0;
}