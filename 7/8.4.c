#include <stdio.h>

int main() {
    int score[40], n = 0, now, sum = 0, cnt = 0;

    while (scanf("%d", &now) && now >= 0) {
        sum += (score[n++] = now);
    }

    int const avg = n == 0 ? sum / n : -1;
    for (int i = 0; i < n; i++)
        cnt += (score[i] > avg);
    printf("%d\n", cnt);

    return 0;
}