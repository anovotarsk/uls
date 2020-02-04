#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int len1 = mx_strlen_null(s1);
    int len2 = mx_strlen_null(s2);
    char *str = mx_strnew(len1 + len2);
    int i;

    if (s1 == NULL) {
        mx_strdel(&str);
        return NULL;
    }
    if (s2 == NULL) {
        mx_strdel(&str);
        return s1;
    }
    for (i = 0; i < len1 + len2; i++) {
        if (i < len1)
            str[i] = s1[i];
        if (i > len1 -1)
            str[i] = s2[i - len1];
    }
    return str;
}
