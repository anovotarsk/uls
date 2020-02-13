#include "../inc/uls.h"

static void mx_dir_or_error_R(char **dirs, int i, t_flags *flags, bool flag) {
    char *str;
    char **files_in_dir;

    if (mx_dirlen(dirs[i]) < 0 && flag)
        mx_printchar('\n');
    if (flag) {
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

static char **print_and_create(char **argv, int i, t_flags *flags, bool flag) {
    char **dir;
    char *help_v;

    mx_dir_or_error_R(argv, i, flags, flag);
    dir = mx_dir_to_matrix(argv[i], flags);
    for (int j = 0; j < mx_arr_size(dir); j++) {
        if (mx_strcmp(argv[i], "/") != 0)
            help_v = mx_strcat("/", dir[j]);
        else
            help_v = mx_strdup(dir[j]);
        mx_strdel(&dir[j]);
        dir[j] = mx_strcat(argv[i], help_v);
        mx_strdel(&help_v);
    }
    return dir;
}

void mx_uls_flag_R(char **argv, t_flags *flags, int chek, bool flag) {
    int cheker;
    char **dir;
    struct stat file;

    for (int i = 0; i < mx_arr_size(argv); i++) {
        cheker = mx_dirlen(argv[i]);
        lstat(argv[i], &file);
        if (S_IFLNK != (file.st_mode & S_IFMT) && mx_dirlen(argv[i]) != -1) {
            if (cheker != -2) {
                if (chek++ != 0)
                    mx_printchar('\n');
                chek = 1;
                dir = print_and_create(argv, i, flags, flag);
                mx_uls_flag_R(dir, flags, chek, true);
                mx_del_strarr(&dir);
            }
            else
                mx_dir_or_error_R(argv, i, flags, flag);
        }
    }
}
