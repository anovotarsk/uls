#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *c1 = (char*) s1;
    char *c2 = (char*) s2;
    size_t i;

    for (i = 0; i < n; i++) {
        if (*c1 - *c2 != 0)
            return *c1 - *c2;
        c1++;
        c2++;
    }
    return 0;
}
