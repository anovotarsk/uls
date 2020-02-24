#include "../inc/uls.h"

int mx_max_strlen(char **arr) {
    int len = 0;
    int i = 0;

    while (arr[i] != NULL) {
        if (mx_strlen(arr[i]) > len)
            len = mx_strlen(arr[i]);
        i++;
    }
    return len;
}
