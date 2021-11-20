#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <src> <dst>", argv[0]);
        return 1;
    }

    char const * const src_filename = argv[1];
    char const * const dst_filename = argv[2];

    FILE * const src_file = fopen(src_filename, "r");
    FILE * const dst_file = fopen(dst_filename, "w");

    for (int c = fgetc(src_file); c != EOF; c = fgetc(src_file))
        fputc(c, dst_file);

    return 0;
}