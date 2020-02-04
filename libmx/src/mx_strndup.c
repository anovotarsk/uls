#include "libmx.h"

char *mx_strndup(const char *s1, size_t  n) {
    int len;
    char *str = NULL;
    size_t i;

    if (s1 == NULL)
        return NULL;
    len = mx_strlen(s1);
    str = mx_strnew((size_t)len > n ? n : len);
    if (str == NULL)
        return NULL;
    for (i = 0; i < n && s1[i] != '\0'; i++)
        str[i] = s1[i];
    return str;
}
