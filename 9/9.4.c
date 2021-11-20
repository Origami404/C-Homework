#include <stdio.h>

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int const N = 10;
int main() {
    int a[N];
    for (int i = 0; i < N; i++)
        scanf("%d", a + i);

    int max_val = a[0], min_val = a[0];
    int max_pos = 0, min_pos = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
            max_pos = i;
        }

        if (a[i] < min_val) {
            min_val = a[i];
            min_pos = i;
        }
    }

    Swap(a + min_pos, a + max_pos);
    printf("Max: %d\nMin: %d\n", max_val, min_val);

    return 0;
}