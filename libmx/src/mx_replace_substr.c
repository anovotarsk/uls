#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    int str_len = mx_strlen_null(str);
    int s_len = 0;
    int point = mx_get_substr_index(str, sub);
    char *s = mx_strnew(str_len * mx_strlen_null(replace));
    int i;

    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;
    while (point > -1) {
        for (i = 0; i < point; i++)
            s[i + s_len] = str[i];
        str += point, s_len += point;
        for (i = 0; i < mx_strlen(replace); i++)
             s[i + s_len] = replace[i];
        str += mx_strlen(sub), s_len += mx_strlen(replace);
        point = mx_get_substr_index(str, sub);
    }
    for (i = 0; i < mx_strlen(str); i++)
        s[i + s_len] = str[i];
    return s;
}
