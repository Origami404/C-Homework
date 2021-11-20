unsigned int MyStrlen(char s[]) {
    char *p = s;
    while (*p != '\0') // (1) '\0'
        p++;
    return p - s; // (2) p - s
}