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

void mx_dir_or_error(char **dirs, int i, t_flags *flags) {
    char *str;
    char **files_in_dir;
    
    if ((mx_strcmp(dirs[0], ".") != 0 || dirs[1] != NULL) && mx_arr_size(dirs) > 1) {
        mx_printstr(dirs[i]);
        mx_printstr(":\n");
    }
    if (mx_dirlen(dirs[i]) < 0) {
        str = mx_strcat("uls: ", dirs[i]);
        perror(str);
        mx_strdel(&str);
        return;
    }
    files_in_dir = mx_dir_to_matrix(dirs[i], flags);
    mx_ulsprint(files_in_dir);
    mx_del_strarr(&files_in_dir);
}

void mx_start_printing(char **argv, t_flags *flags) {
    char **files = mx_arr_of_files(argv);
    int i;
    bool was_out = false;

    mx_ulsprint(files);
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
            mx_dir_or_error(argv, i, flags);
        }
    }
}
