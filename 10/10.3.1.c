// 虽然但是, 应该是接受 char const *, 返回 size_t
unsigned int MyStrlen(char *p) {
    unsigned int len;

    len = 0;
    for (; *p != '\0'; p++) // (1) '\0'
        len += 1; // (2) += 1
    
    return len; // (3) len
}
