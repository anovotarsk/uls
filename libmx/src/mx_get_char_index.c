#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    int len = mx_strlen(str);
    int i;

    if (str == NULL) 
        return -2;
    for (i = 0; i < len; i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}
