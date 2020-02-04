#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    int len1 = mx_strlen_null(s1);
    int len2 = mx_strlen_null(s2);
    int len = (len1 != 0 && len2 == 0) ? len1 : 0;
    char *str = mx_strnew(len);
    int i = 0;

    if (len1 == 0 && len2 == 0)
        return NULL;
    len = (len1 == 0 && len2 != 0) ? len2 : len1 + len2 + 1;
    while (i < len1) {
        str[i] = s1[i];
        i++;
    }
    if (len1 != 0 && len2 != 0)
        str[i] = ' ';
    while (i < len && len2 > 0) {
        str[i] = s2[i - len1];
        i++;
    }
    return str;
}
