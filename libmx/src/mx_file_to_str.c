#include "libmx.h"

static bool file_len(const char *file, int *len) {
    int f = open(file, O_RDONLY);
    char c[1];

    *len = 0;
    if (f == -1)
        return false;
    while (read(f, &c, 1) > 0)
        len[0]++;
    close(f);
    return true;
}

char *mx_file_to_str(const char *file) {
    int f = open(file, O_RDONLY);
    int len = 0;
    char c[1];
    char *str = NULL;
    int i;

    if (f == -1 || file_len(file, &len) == false || len == 0)
        return NULL;
    str = mx_strnew(len);
    for (i = 0; i < len; i++) {
        read(f, &c, 1);
        str[i] = c[0];
    }
    close(f);
    return str;
}
