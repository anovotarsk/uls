#include "../inc/uls.h"

int mx_arr_size(char **arr) {
    int size = 0;

    if (arr == NULL)
        return 0;
    while (arr[size] != NULL)
        size++;
    return size;
}

static char **no_dirs() {
    char **arr = (char**)malloc(sizeof(char*) * 2);

    arr[0] = mx_strdup(".");
    arr[1] = NULL;
    return arr;
}

static char **list_to_arr(t_dirs *list) {
    int len = 0;
    char **arr;
    t_dirs *l = list;
    int i;

    while (list != NULL) {
        len++;
        list = list->next;
    }
    if (len == 0)
        return no_dirs();
    arr = (char**)malloc(sizeof(char*) * (len + 1));
    for (i = 0; i < len; i++) {
        arr[i] = l->dir;
        l = l->next;
    }
    arr[len] = NULL;
    mx_bubble_sort(arr, len);
    return arr;
}

//сортирует и выводит ошибку о несуществующем файле
char **mx_check_arguments(t_dirs *list) {
    char *str;
    char **arr = list_to_arr(list);
    int len = mx_arr_size(arr);
    int i;

    for (i = 0; i < len; i++) {
        mx_dirlen(arr[i]);
        if (errno == 2) {
            str = mx_strcat("uls: ", arr[i]);
            perror(str);
            mx_strdel(&str);
        }
    }
    return arr;
}