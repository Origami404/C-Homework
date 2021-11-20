// 8.2 (1)
int PositiveNum(int a[], int n) {
    int i, count = 0; // (1) = 0
    for (i = 0; i < n; i++) {
        if (a[i] > 0)
            count += 1; // (2) count += 1
    }
    return count; // (3) count
}
