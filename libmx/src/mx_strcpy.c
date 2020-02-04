#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int len = 0;

    while (src[len] != '\0') {
        dst[len] = src[len];
        len++;
    }
    dst[len] = '\0';
    return dst;
}
