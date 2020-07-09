#include "../inc/uls.h"

int mx_dirlen(char *dir) {
    DIR *dd;
    int len = 0;
    struct dirent *entry;

    dd = opendir(dir);
    if (dd == NULL && errno == 20)
        return -1;
    if (dd == NULL)
        return -2;
    while ((entry = readdir(dd)) != NULL)
        len++;
    closedir(dd);
    return len;
}

void mx_flag_sort(char **arr, t_flags *flags) {
    if (mx_flag_search('r', flags))
        mx_bubble_sort_r(arr, mx_arr_size(arr));
    else
        mx_bubble_sort(arr, mx_arr_size(arr));
}

void unprint_symbols(char **arr) {
    int i = 0;
    int j;

    if (isatty(1) != 0) {
        while (arr[i] != NULL) {
            for (j = 0; j < mx_strlen(arr[i]); j++) {
                if (arr[i][j] > 0 && arr[i][j] < 32)
                    arr[i][j] = '?';
            }
            i++;
        }
    }
}

char **mx_dir_to_matrix(char *dir, t_flags *flags) {
    DIR *dd = opendir(dir);
    int len = mx_dirlen(dir);
    struct dirent *entry;
    char **arr = (char**)malloc(sizeof(char*) * (len + 1));
    int i = 0;

    for (i = 0; (entry = readdir(dd)) != NULL;) {
        if (mx_flag_search('a', flags) || *(entry->d_name) != '.')
            arr[i++] = mx_strdup(entry->d_name);
        else
            if (mx_flag_search('A', flags)
                && mx_strcmp(entry->d_name, ".") != 0
                && (entry->d_name)[1] != '.')
                arr[i++] = mx_strdup(entry->d_name);
    }
    arr[i] = NULL;
    closedir(dd);
    mx_flag_sort(arr, flags);
    return arr;
}
