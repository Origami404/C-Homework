#include <stdio.h>

void input_array(int *p, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", p + i*n + j);
        }
    }
}

int find_max(int *p, int m, int n, int *pRow, int *pCol) {
    int pr = 0, pc = 0, max = *p;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int const num = *(p + i*n + j);
            if (num > max) {
                max = num;
                pr = i;
                pc = j;
            }
        }
    }

    *pRow = pr;
    *pCol = pc;
    return max;
}

int main() {
    int m, n;
    
    scanf("%d %d", &m, &n); 
    int a[m][n];

    input_array((int*)a, m, n);

    int row, col;
    int const max_num = find_max((int*)a, m, n, &row, &col);
    printf("The max num is %d at (%d, %d)\n", max_num, row, col);

    return 0;
}