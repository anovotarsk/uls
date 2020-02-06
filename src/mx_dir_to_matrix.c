#include "../inc/uls.h"

int mx_dirlen(char *dir) {
    DIR *dd = opendir(dir);
    int len = 0;
    struct dirent *entry;

    if (dd == NULL && errno == 20)
        return -1;
    if (dd == NULL)
        return -2;
    while ((entry = readdir(dd)) != NULL)
        len++;
    closedir(dd);
    return len;
}

char **mx_dir_to_matrix(char *dir) {
    DIR *dd = opendir(dir);
    int len = mx_dirlen(dir);
    struct dirent *entry;
    char **arr = (char**)malloc(sizeof(char*) * (len + 1));
    int i = 0;

    if (len < 0) {
        free(arr);
        return NULL; // error
    }
    for (i = 0; (entry = readdir(dd)) != NULL; i++) {
        arr[i] = mx_strdup(entry->d_name);
    }
    arr[i] = NULL;
    closedir(dd);
    mx_bubble_sort(arr, mx_arr_size(arr));
    return arr;
}
