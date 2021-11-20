#ifndef HEADER_IVA_H__
#define HEADER_IVA_H__

#include <stdint.h>
#include <stdio.h>

struct InputSpec {
    char *prompt;
    char *at_fail;
    FILE *file;
};

int accept_i8_impl(int8_t *result, struct InputSpec spec);
int8_t accept_i8_relentless_impl(struct InputSpec spec);

#define accept_i8(result, ...) accept_i8_impl(result, (struct InputSpec) { __VA_ARGS__ })
#define accept_i8_relentless(...) accept_i8_relentless_impl((struct InputSpec) { __VA_ARGS__ }) 


#define accept(var, ...) \
    _Generic(var, \
        int8_t* : accept_i8(var, __VA_ARGS__))


#endif // HEADER_IVA_H__
