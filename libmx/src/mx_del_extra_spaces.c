#include "libmx.h"

static void writer(char *s, char **s1, int len) {
    int i;
    int j;

    for (i = 0, j = 0; i <  mx_strlen(s) && j < len; i++) {
        if (mx_if_space(s[i]) && !mx_if_space(s[i + 1])) {
            s1[0][j] = ' ';
            j++;
        }
        if (!mx_if_space(s[i])) {
            s1[0][j] = s[i];
            j++;
        }
    }
}

char *mx_del_extra_spaces(const char *str) {
    char *s = NULL;
    char *s1 = NULL;
    int i;
    int len = 0;

    if (str == NULL)
        return NULL;
    s = mx_strtrim(str);
    for (i = 0; i < mx_strlen(s) - 1; i++)
        if (mx_if_space(s[i]) && !mx_if_space(s[i + 1]))
            len++;
    for (i = 0; i < mx_strlen(s); i++)
        if (!mx_if_space(s[i]))
            len++;
    s1 = (char*)malloc(len);
    writer(s, &s1, len);
    mx_strdel(&s);
    return s1;
}
