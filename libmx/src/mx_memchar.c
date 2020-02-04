#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *str = (char*) s;
    size_t i;

    for (i = 0; i < n; i++) {
        if (*str == c)
            return str;
        str++;
    }
    return NULL;
}
