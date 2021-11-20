// ====== 5.7 ======
#include <stdio.h>
#include <ctype.h>

int main() {
    
    char const c = getchar(); // ignore EOF

    if (isupper(c)) {
        printf("%c %d\n", tolower(c), (int)c); // 不定参数会整型提升, 其实不打(int)也没问题
    } else if (islower(c)) {
        printf("%c %d\n", toupper(c), (int)c);
    } else {
        printf("%d\n", (int)c);
    }

    return 0;
}