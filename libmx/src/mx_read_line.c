#include "libmx.h"

char *mx_read_line(char delim, const int fd) {
    char buf;
    int status;
    char *s = mx_strnew(0);
    int len = 0;

    while (true) {
        status = read(fd, &buf, 1);
        if (status == -1 || status == 0) {
            mx_strdel(&s);
            return NULL;
        }
        if (buf == delim || status == 0) {
            s = mx_realloc(s, ++len);
            s[len - 1] = '\0';
            return s;
        }
        s = mx_realloc(s, ++len);
        s[len - 1] = buf;
    }
    return NULL;
}
