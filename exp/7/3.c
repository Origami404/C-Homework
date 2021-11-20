#include <stdio.h>

void transpose(int m, int n, int res[n][m], int a[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[j][i] = a[i][j];
        }
    }
}


void input(int m, int n, int a[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(a[i][j]));
        }
    }
}

void output(int m, int n, int a[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int a[m][n], res[m][n];

    input(m, n, a);

    transpose(m, n, res, a);
    output(n, m, res);

    return 0;
}