#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

static inline void* checked_malloc(size_t s) {
    void *p = malloc(s);
    if (!p) {
        fprintf(stderr, "Malloc fail.\n");
        exit(-1);
    }
    return p;
}

typedef struct {
    size_t len;
    int16_t *digit;
} BigNum;

#define DIGIT_LEN sizeof(((BigNum*) 0)->digit[0])

BigNum* bn_alloc(void) {
    BigNum *p = checked_malloc(sizeof(BigNum));
    memset(p, 0, sizeof(BigNum));
    return p;
}

void bn_init(BigNum *num, size_t len) {
    num->digit = checked_malloc(len * DIGIT_LEN);
    memset(num->digit, 0, len);
    num->len = len;
}

BigNum* bn_new(size_t len) {
    BigNum *p = bn_alloc();
    bn_init(p, len);
    return p;
}

void bn_del(BigNum *num) {
    free(num->digit);
    free(num);
}

void bn_resize(BigNum *num, size_t new_len) {
    if (new_len > num->len) {
        num->digit = realloc(num->digit, new_len * DIGIT_LEN);
        memset(num->digit + num->len, 0, (new_len - num->len) * DIGIT_LEN);
    }
    num->len = new_len;
}

void bn_mul_to_i8(BigNum *res, int8_t x) {
    size_t const orig_len = res->len;
    size_t const rlen = res->len + 3; // a int8_t variable has at most 3 digits
    bn_resize(res, rlen);

    for (size_t i = 0; i < orig_len; i++) {
        res->digit[i] *= x;
    }

    for (size_t i = 0; i < rlen - 1; i++) {
        if (res->digit[i] > 9) {
            res->digit[i + 1] += (res->digit[i] / 10);
            res->digit[i] %= 10;
        }
    }

    // remove leading zero
    while (res->digit[res->len - 1] == 0) 
        res->len -= 1;
}

void bn_assign_i64(BigNum *num, int64_t x) {
    int digit_len = 0, xx = x, pos = 0;
    while (xx) {
        digit_len += 1;
        xx /= 10;
    }


    bn_resize(num, digit_len);
    while (x) {
        num->digit[pos++] = (int16_t) (x % 10);
        x /= 10;
    }
}

void bn_print(FILE *f, BigNum *num) {
    if (num->len == 0)
        return;

    for (size_t i = num->len - 1; i != 0; i--) {
        fprintf(f, "%d", num->digit[i]);
    }
    fprintf(f, "%d", num->digit[0]);
}

int main() {
    BigNum *r = bn_alloc();

    bn_assign_i64(r, 1);

    for (int8_t i = 1; i <= 40; i++) {
        bn_mul_to_i8(r, i);

        printf("%d! = ", i);
        bn_print(stdout, r);
        printf("\n");
    }

    bn_del(r);
    return 0;
}