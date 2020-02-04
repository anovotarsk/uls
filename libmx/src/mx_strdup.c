#include "libmx.h"

char *mx_strdup(const char *str) {
    int len = mx_strlen(str);
    char *s = mx_strnew(len);

    mx_strcpy(s, str);
    return s;
}
