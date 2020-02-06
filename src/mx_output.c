#include "../inc/uls.h"

char **mx_arr_of_files(char **argv) {
    int len = mx_arr_size(argv);
    int count_files = 0;
    int i;
    int j = 0;
    char **files;

    if (len == 0)
        return NULL;
    for (i = 0; i < len; i++)
        if (mx_dirlen(argv[i]) == -1)
            count_files++;
    files = (char**)malloc(sizeof(char*) * count_files + 1);
    files[count_files] = NULL;
    for (i = 0; i < len; i++)
        if (mx_dirlen(argv[i]) == -1) {
            files[j] = argv[i];
            j++;
        }
    return files;
}

void mx_dir_or_error(char *dir) {
    char *str;
    char **files_in_dir;

    mx_printstr(dir);
    mx_printstr(":\n");
    if (mx_dirlen(dir) < 0) {
        str = mx_strcat("uls: ", dir);
        perror(str);
        mx_strdel(&str);
        return;
    }
    files_in_dir = mx_dir_to_matrix(dir);
    mx_print_strarr(files_in_dir, " "); //допілити функцію прінта
    mx_del_strarr(&files_in_dir);
}

void mx_start_printing(char **argv) {
    char **files = mx_arr_of_files(argv);
    int i;
    bool was_out = false;

    mx_print_strarr(files, " "); //допілити функцію прінта
    if (files[0] != NULL)
        was_out = true;
    if (mx_arr_size(files) == mx_arr_size(argv)) {
        mx_del_strarr(&files);
        return;
    }
    mx_del_strarr(&files);
    for (i = 0; i < mx_arr_size(argv); i++) {
        errno = 0;
        if (mx_dirlen(argv[i]) != -1 && errno != 2) {
            if (was_out++)
                mx_printchar('\n');
            mx_dir_or_error(argv[i]);//допілити функцію прінта директоії
        }
    }
}
