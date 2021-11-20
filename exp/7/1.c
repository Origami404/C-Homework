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

typedef int16_t digit_t;

typedef struct {
    size_t len;
    digit_t *digit;
} BigNum;

#define DIGIT_LEN sizeof(digit_t)

static inline BigNum* bn_alloc(void) {
    BigNum *p = checked_malloc(sizeof(BigNum));
    memset(p, 0, sizeof(BigNum));
    return p;
}

// static inline void bn_init(BigNum *num, size_t len) {
//     num->digit = checked_malloc(len * DIGIT_LEN);
//     memset(num->digit, 0, len);
//     num->len = len;
// }

// static inline BigNum* bn_new(size_t len) {
//     BigNum *p = bn_alloc();
//     bn_init(p, len);
//     return p;
// }

static inline void bn_del(BigNum *num) {
    free(num->digit);
    free(num);
}

static inline digit_t* bn_ref(BigNum *num, size_t i) {
    return num->digit + i;
}

static inline digit_t bn_get(BigNum *num, size_t i) {
    return i < num->len ? num->digit[i] : 0;
} 

static inline void bn_resize(BigNum *num, size_t new_len) {
    if (new_len > num->len) {
        num->digit = realloc(num->digit, new_len * DIGIT_LEN);
        memset(num->digit + num->len, 0, (new_len - num->len) * DIGIT_LEN);
    }
    num->len = new_len;
}

static inline void bn_normalize(BigNum *num) {
    while (num->digit[num->len - 1] == 0)
        num->len -= 1;
}

void bn_add(BigNum *res, BigNum *a, BigNum *b) {
    size_t const rlen = max(a->len, b->len) + 1;
    bn_resize(res, rlen);

    for (size_t i = 0; i < rlen; i++) {
        *bn_ref(res, i) += bn_get(a, i) + bn_get(b, i);
        if (bn_get(res, i) > 10) {
            // 在加法的情况下, 进位不会超过二十
            *bn_ref(res, i + 1) += 1;
            *bn_ref(res, i) -= 10;
        }
    }

    // 并且最后一位不会进位

    bn_normalize(res);
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

void bn_assign_digit(BigNum *num, char const *str) {
    size_t const len = strlen(str);
    if (len == 0)
        return;

    bn_resize(num, len);

    for (size_t i = 0; i < len; i++) {
        num->digit[len - i - 1] = str[i] - '0';
    }

    bn_normalize(num);
}

void bn_print(FILE *f, BigNum *num) {
    if (num->len == 0)
        return;

    for (size_t i = num->len; i --> 0; ) {
        fprintf(f, "%d", num->digit[i]);
    }
}

int main() {
    BigNum * const a = bn_alloc();
    BigNum * const b = bn_alloc();
    BigNum * const c = bn_alloc();

    char buf[128];

    scanf("%s", buf);
    bn_assign_digit(a, buf);

    scanf("%s", buf);
    bn_assign_digit(b, buf);

    bn_add(c, a, b);
    
    bn_print(stdout, c);
    printf("\n");

    bn_del(a);
    bn_del(b);
    bn_del(c);
    return 0;
}