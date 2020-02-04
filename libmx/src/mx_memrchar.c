#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *str = (char*) s;
    char *str1 = (char*) s;
    bool flag = false;
    size_t i;

    for (i = 0; i < n; i++) {
        if (*str == c) {
            str1 = str;
            flag = true;
        }
        str++;
    }
    if (flag)
        return str1;
    return NULL;
}
