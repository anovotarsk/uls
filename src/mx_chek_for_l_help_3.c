#include "../inc/uls.h"

void mx_add_time_help(char **mas_for_print, int count_of_row,
                      char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(space, help_arr[i]);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, " ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    mx_del_strarr(&help_arr);
    return;
}

void mx_add_time(char **mas_for_print, int count_of_row,
                 char **files, t_flags *flags) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_time(file, flags);
    }
    help_arr[count_of_row] = NULL;
    mx_add_time_help(mas_for_print, count_of_row, help_arr);
    return;
}

static void add_name_help(char **mas_for_print, char **name,
                          char *link, int i) {
    char *help_v;
    char *help_v_1;

    if (link != NULL) {
        help_v = mx_strcat(name[i], link);
        help_v_1 = mx_strcat(mas_for_print[i], help_v);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = help_v_1;
    }
    else {
        help_v = mx_strcat(mas_for_print[i] ,name[i]);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v);
    }
    mx_strdel(&help_v);
}

void mx_add_name(char **mas_for_print, int count_of_row, char **name,
                 char **files) {
    char *link;

    for (int i = 0; i < count_of_row; i++) {
        link = mx_link(files[i]);
        add_name_help(mas_for_print, name, link, i);
        mx_strdel(&link);
    }
}
