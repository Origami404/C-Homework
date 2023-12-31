int MyStrcmp(char *p1, char *p2) {
    for (; *p1 == *p2; p1++, p2++) {
        if (*p1 == '\0') {
            // 注意不可以像下面一样写: 
            // return -*p2           char不一定是无符号的, 而且对于非ASCII字符可能给出错误结果
            // return -(int)*p2      同理, 如果char是有符号的, 那么就算转成int, 也只会做有符号整型提升, 对于非ASCII字符可能给出错误结果

            // 但是下面这样应该可以接受
            // return -(int)(unsigned)*p2 先提升为无符号整数, 再转换为有符号, 再取负

            return *p2 ? -1 : 0; // (1) *p2 ? -1 : 0
        }
    }

    // 不可以这样写, 当 *p1 是 CHAR_MIN 的时候有可能会溢出, 并且也无法保证 char 就是有符号的
    // return *p1 - *p2; 

    // 建议这样写, 对于 ASCII 内的总是正确的. 注意 C 里的条件运算符保证结果为 1/0 而不是其他值
    return (*p1 > *p2) - (*p1 < *p2);  // (2) (*p1 > *p2) - (*p1 < *p2)
}