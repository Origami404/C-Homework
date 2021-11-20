#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    int c[2][n + 1];
    memset(c, 0, sizeof(int) * 2 * (n + 1));

    c[0][0] = 1;
    printf("    1\n");

    for (int i = 1; i <= n; i++) {
        int const now = (i & 1);
        
        c[now][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[now][j] = c[now^1][j] + c[now^1][j-1];
        }

        for (int j = 0; j <= i; j++)
            printf("%5d", c[now][j]);
        printf("\n");
    }

    return 0;
}