#include "../inc/uls.h"

int mx_dirlen(char *dir) {
    DIR *dd = opendir(dir);
    int len = 0;
    struct dirent *entry;

    if (dd == NULL)
        return -1;
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

    if (len == -1) {
        free(arr);
        return NULL; // error
    }
    for (i = 0; (entry = readdir(dd)) != NULL; i++) {
        arr[i] = entry->d_name;
    }
    arr[i] = NULL;
    closedir(dd);
    return arr;
}
