#include "libmx.h"

void mx_str_reverse(char *s) {
    int len;
    int i = 0;

    if (s == NULL)
        return;
    len = mx_strlen(s) - 1;
    while (len != i && len > i) {
        mx_swap_char(&s[i], &s[len]);
        i++;
        len--;
    }
}
