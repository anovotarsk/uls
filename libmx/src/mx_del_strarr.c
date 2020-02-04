#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char **box = *arr;

    while(*box != NULL) {
        mx_strdel(box);
        box++;
    }
    mx_strdel(box);
    free(*arr);
    *arr = NULL; 
}
