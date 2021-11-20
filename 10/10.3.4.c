int MyStrlen(char s[], char t[]) {
    int i;
    for (i = 0; s[i] == t[i]; i++) {
        if (s[i] == '\0') // (1) '\0'
            return 0;
    }
    // 同样防止 char 是无符号的
    return ((int)s[i] - (int)t[i]); // (2) ((int)s[i] - (int)t[i]) 
}