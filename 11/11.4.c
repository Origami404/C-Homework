#include <stdio.h>

void Swap(int *a, int *b) {
    int const t = *a;
    *a = *b;
    *b = t;
}

#define N 10

void transpose_1(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            Swap(&(a[i][j]), &(a[j][i]));
        }
    }
}

void transpose_2(int (*a)[N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            Swap(&(a[i][j]), &(a[j][i]));
        }
    }
}

void transpose_3(int *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            Swap(a + n*i + j, a + n*j + i);
        }
    }
}

void input(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &(a[i][j]));
        }
    }
}

void output(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int a[10][10], n;

    scanf("%d", &n);
    input(a, n);

    transpose_1(a, n);
    output(a, n);

    transpose_2(a, n);
    output(a, n);

    transpose_3((int*)a, n);
    output(a, n);
    
    return 0;
}