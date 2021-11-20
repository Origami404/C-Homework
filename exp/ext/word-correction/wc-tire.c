#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct TrieNode {
    bool is_end;
    struct TrieNode *next[26];
} TrieNode;

TrieNode* trie_node_new() {
    TrieNode *p = malloc(sizeof(*p));
    memset(p, 0, sizeof(*p));
    return p;
}

// will cost 1916136(~2M) byte
TrieNode *root;

void trie_add_word(char *s) {
    TrieNode *now = root;

    while (islower(*s)) {
        const int c = *s - 'a';

        if (now->next[c] == 0) 
            now->next[c] = trie_node_new();
        now = now->next[c];

        s++;
    }

    now->is_end = true;
}

void trie_init(FILE *voc_file) {
    root = trie_node_new();

    char word[64];
    while (fgets(word, sizeof(word), voc_file)) {
        trie_add_word(word);
    }
}

void trie_destory_impl(TrieNode *now) {
    for (int i = 0; i < 26; i++) {
        if (now->next[i])
            trie_destory_impl(now->next[i]);
    }

    free(now);
}

void trie_destory(void) {
    trie_destory_impl(root);
    root = 0;
}

size_t mem_count(TrieNode *now) {
    size_t mem = 0;
    for (int i = 0; i < 26; i++) {
        if (now->next[i])
            mem += mem_count(now->next[i]);
    }
    return mem + sizeof(TrieNode);
}

void trie_print(TrieNode *now, int level) {
    for (int i = 0; i < 26; i++) {
        if (now->next[i]) {
            for (int j = 0; j < level; j++)
                putchar(' ');
            putchar(i + 'a');
            putchar('\n');
            trie_print(now->next[i], level + 1);
        }
    }
}

TrieNode *succ[20];
size_t succ_cnt = 0;

int now_min_distance = INT_MAX;
void dfs(TrieNode *now, char *s, int distance) {
    if (distance > now_min_distance) {
        return;
    }
}


int main() {
    FILE *voc_file = fopen("vocabulary.txt", "r");

    trie_init(voc_file);

    printf("Memory usage: %zu (byte)\n", mem_count(root));
    // trie_print(root, 0);

    trie_destory();

    return 0;
}
