#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct candidate {
    char *name;
    int count;
};

int main() {
    struct candidate candidates[] = {
        { "zhang", 0 },
        { "li",    0 },
        { "wang",  0 }
    };
    size_t const cand_cnt = sizeof(candidates) / sizeof(struct candidate);

    char input[64];
    while (1) {
        printf("Please input a candidate's name: ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        
        for (char *p = input; *p; p++) {
            *p = tolower(*p);
        }

        for (size_t i = 0; i < cand_cnt; i++) {
            if (strcmp(input, candidates[i].name) == 0)
                candidates[i].count += 1;
        }
   }

    size_t max_pos = 0;
    for (size_t i = 0; i < cand_cnt; i++) {
        if (candidates[i].count > candidates[max_pos].count)
            max_pos = i;
    }

    printf("\n\n");
    printf("The winner: %s\n", candidates[max_pos].name);

    return 0;
}