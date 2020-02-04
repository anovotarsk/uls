#include "libmx.h"

static int loop(int len1, int len2, char *s, const char *sub) {
    bool flag;
    int i;
    int n = 0;

    while (len1 > 0) {
        flag = true;
        for (i = 0; i < len2 && flag; i++) {
            if (s[i] != sub[i])
                flag = false;
        }
        if (flag)
            return n;
        s++;
        n++;
        len1--;
    }
    return -1;
}

int mx_get_substr_index(const char *str, const char *sub) {
    int len1 = mx_strlen(str);
    int len2 = mx_strlen(sub);
    char *s = mx_strnew(len1);
    int i;

    if (str == NULL || sub == NULL || mx_strlen(sub) == 0)
        return -2;
    for (i = 0; i < len1; i++)
        s[i] = str[i];
    return loop(len1, len2, s, sub);
}
