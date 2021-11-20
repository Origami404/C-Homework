#include <stdio.h>

#include <stdio.h>

void Swap(int *a, int *b) {
    int const t = *a;
    *a = *b;
    *b = t;
}

#define N 10
#define M 10

void transpose_1(int a[][N], int at[][M], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            at[j][i] = a[i][j];
        }
    }
}

void transpose_2(int (*a)[N], int (*at)[M], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            at[j][i] = a[i][j];
        }
    }
}

void transpose_3(int *a, int *at, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            *(at + j*M + i) = *(a + i*N + j);
        }
    }
}

void input(int a[][N], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(a[i][j]));
        }
    }
}

void output(int a[][M], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int a[M][N], at[M][N], m, n;

    scanf("%d %d", &m, &n);
    input(a, m, n);

    transpose_1(a, at, m, n);
    output(at, n, m);

    transpose_2(a, at, m, n);
    output(at, n, m);

    transpose_3((int*)a, (int*)at, m, n);
    output(at, n, m);
    
    return 0;
}
