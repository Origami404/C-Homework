#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>", argv[0]);
        return 1;
    }

    FILE * const file = fopen(argv[1], "r");
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
        putchar(c);

    return 0;
}