#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *c = (char*) dst;
    const char *s = (char*) src;
    size_t i;

    for (i = 0; i < n; ++i)
        *c++ = *s++;
    return dst;
}
