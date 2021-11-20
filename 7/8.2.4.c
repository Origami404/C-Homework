#include <stdio.h>
#define ROW 2
#define COL 3

void MultiplyMatrix(int a[ROW][COL], int b [COL][ROW], int c[ROW][ROW]) { // (1) c[ROW][ROW]
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) {
            c[i][j] = 0; // (2) 0
            for (int k = 0; k < COL; k++) {
                c[i][j] += a[i][k] * b[k][j]; // (3) a[i][k] * b[k][j]
            }
        }
    }
}

void PrintMatrix(int a[ROW][ROW]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) 
            printf("%6d", a[i][j]);
        printf("\n"); // (4) printf("\n");
    }
}

int main() {
    int a[ROW][COL], b[COL][ROW], c[ROW][ROW];

    printf("Input 2*3 matrix a:\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
            scanf("%d", &(a[i][j])); // (5) &(a[i][j]) 
    }

    printf("Input 3*2 matrix a:\n");
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++)
            scanf("%d", &(b[i][j])); // (6) &(b[i][j]) 
    }

    MultiplyMatrix(a, b, c); // (7) a, b, c
    printf("Results: \n");
    PrintMatrix(c);
    return 0;
}