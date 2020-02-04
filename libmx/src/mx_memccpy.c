#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src,
                 int c, size_t n) {
    char *d = (char*) dst;
    char *s = (char*) src;
    size_t i;
    bool flag = true;

    for (i = 0; i < n && flag; i++) {
        if (*s == c)
            flag = false;
        *d++ = *s++;
    }
    if (flag)
        return NULL;
    return d;
}
