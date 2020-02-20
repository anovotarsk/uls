#include "../inc/uls.h"

char *mx_link(char *file) {
    char buf[1024];
    int len;
    char *link;
    int i;

    len = readlink(file, buf, 1024);
    if (len == -1)
        return NULL;
    link = mx_strnew(len);
    for (i = 0; i < len; i++)
        link[i] = buf[i];
    return link;
}
