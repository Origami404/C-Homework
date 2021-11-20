#include <stdio.h>

static inline void swap(int *a, int *b) {
    int const t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort(int a[], int n) {
    int has_changed; // flag

    do {
        has_changed = 0;

        for (int i = 1; i < n; i++) {
            if (a[i-1] > a[i]) {
                swap(a + i - 1, a + i);
                has_changed = 1;
            }
        }
    } while (has_changed);
}

// ==== test ====
int main() {
    int a[7] = { 3, 1, 5, 4, 3, 6, 7 };

    bubble_sort(a, 7);

    for (int i = 0; i < 7; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}