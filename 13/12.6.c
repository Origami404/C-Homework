#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static inline _Noreturn void panic(char const *message) {
    fputs(message, stderr);
    exit(1);
}

static inline void* checked_malloc(size_t s) {
    void *p = malloc(s);
    if (!p) panic("Malloc failed.");
    return p;
}

typedef struct Node {
    enum NodeType {
        INT, DOUBLE
    } type;

    union {
        int ival;
        double dval;
    };
} Node;

double const eps = 1e-5;
static inline bool fzero(double x) {
    return fabs(x) < eps;
}

Node *node_new_int(int ival) {
    Node *p = checked_malloc(sizeof(*p));
    p->type = INT;
    p->ival = ival;
    return p;
}

Node *node_new_double(double dval) {
    Node *p = checked_malloc(sizeof(*p));
    p->type = DOUBLE;
    p->dval = dval;
    return p;
}

Node *node_new_from_str(char const *str) {
    double const res = atof(str);
    if (fzero(res - round(res))) {
        return node_new_int((int)lround(res));
    } else {
        return node_new_double(res);
    }
}


int calc_int(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (b == 0) 
                panic("Divided by zero. (int)"); 
            else return a / b;
        }   
        default: panic("Unknown op.");
    }
}

double calc_double(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (fzero(b)) 
                panic("Divided by zero. (double)"); 
            else return a / b;
        }   
        default: panic("Unknown op.");
    }
}

typedef struct List {
    void *car;
    struct List *cdr;
} List;

List *cons(void *car, List *cdr) {
    List *p = checked_malloc(sizeof(*p));
    p->car = car;
    p->cdr = cdr;
    return p;
}

typedef List *Stack;

Stack *st_new() {
    Stack *p = checked_malloc(sizeof(*p)); 
    *p = 0;
    return p;
}

void st_push(Stack *s, void *data) { *s = cons(data, *s); }

bool st_empty(Stack *s) { return !*s; }
void* st_pop(Stack *s) {
    if (st_empty(s))
        panic("Pop from an empty stack");
    List *p = *s;

    void * const data = p->car;
    *s = p->cdr;

    free(p);
    return data;
}

void* st_top(Stack *s) { return (*s)->car; }

// void debug_print_stack(Stack *s) {
//     printf("DEBUG(stack): ");
//     for (List *l = *s; l; l = l->cdr) {
//         Node const * const n = l->car;
//         // printf("(%s, ", n->type == INT ? "int" : "double");
//         if (n->type == INT) {
//             printf("(int, %d) ", n->ival);
//         } else {
//             printf("(double, %f) ", n->dval);
//         }
//     }
//     printf("\n");
// }

int main() {
    char buf[64];
    Stack *s = st_new();

    while (scanf("%s", buf) == 1 && strcmp(buf, "#")) {
        // debug_print_stack(s);
        char const first = buf[0];
        // printf("DEBUG: %c\n", first);
        if (isdigit(first)) {
            st_push(s, node_new_from_str(buf));
        } else {
            Node * const b = st_pop(s);
            Node * const a = st_pop(s);

            if (a->type == DOUBLE || b->type == DOUBLE) {
                double const a_num = a->type == DOUBLE ? a->dval : a->ival;
                double const b_num = b->type == DOUBLE ? b->dval : b->ival;
                st_push(s, node_new_double(calc_double(first, a_num, b_num)));
            } else {
                st_push(s, node_new_int(calc_int(first, a->ival, b->ival)));
            }

            free(a);
            free(b);
        }
    }

    Node *res = st_pop(s);
    if (res->type == DOUBLE) {
        printf("%f\n", res->dval);
    } else {
        printf("%d\n", res->ival);
    }

    free(res);
    free(s);

    return 0;
}