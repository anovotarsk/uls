#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int n;
    int i;

    if (src == NULL || dst == NULL)
        return NULL;
    n = mx_strlen(src);
    for (i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    if (n < len) {
        for (i = n; i < len; i++) {
            dst[i] = '\0';
        }
    }
    return dst;
}
