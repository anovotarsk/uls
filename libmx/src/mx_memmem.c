#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len) {
    char *b = (char*) big;
    char *l = (char*) little;
    bool flag;
    size_t i;
    size_t j;

    if (little_len == 0)
        return NULL;
    for (i = 0; i < big_len; i++, b++) {
        flag = true;
        for (j = 0; j < little_len; j++) {
            if (b[j] != l[j])
                flag = false;
        }
        if (flag)
            return b;
    }
    return NULL;
}
