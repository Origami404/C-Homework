// 8.9
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(a[i][j]));
        }
    }

    int main_diagonal = 0;
    for (int i = 0; i < n; i++) {
        main_diagonal += a[i][i];
    }

    int antidiagonal = 0;
    for (int i = 0; i < n; i++) {
        antidiagonal += a[n - i - 1][i];
    }

    printf("%d %d\n", main_diagonal, antidiagonal);
    return 0;
}