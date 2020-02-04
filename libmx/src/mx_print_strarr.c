#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    int len_arr = 0;
    int i;

    if (!arr || !delim)
        return;
    while (arr[len_arr] != NULL)
        len_arr++;
    if (len_arr == 0)
        return;
    for (i = 0; i < len_arr; i++) {
        mx_printstr(arr[i]);
        if (i < len_arr - 1)
            mx_printstr(delim);
    }
    mx_printstr("\n");
}
