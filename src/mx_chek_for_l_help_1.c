#include "../inc/uls.h"

void mx_add_count_link_help(char **mas_for_print, int count_of_row,
                            char **links_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(links_arr, links_arr[i], count_of_row);
        help_v1 = mx_strcat(space, links_arr[i]);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, " ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_ownew_name_help(char **mas_for_print, int count_of_row,
                            char **help_arr) {
    int i;
    char *space;
    char *help_v1;
    char *help_v2;

    for (i = 0; i < count_of_row; i++) {
        space = neded_space(help_arr, help_arr[i], count_of_row);
        help_v1 = mx_strcat(help_arr[i], space);
        mx_strdel(&space);
        help_v2 = mx_strcat(help_v1, "  ");
        mx_strdel(&help_v1);
        help_v1 = mx_strcat(mas_for_print[i], help_v2);
        mx_strdel(&mas_for_print[i]);
        mas_for_print[i] = mx_strdup(help_v1);
        mx_strdel(&help_v1);
        mx_strdel(&help_v2);
    }
    return;
}

void mx_add_permissions(char **mas_to_print, int count_of_row, char **files) {
    int i;
    char *help_v;
    struct stat file;

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_v = mx_permissions(files[i]);
        mas_to_print[i] = mx_strcat(help_v, " ");
        mx_strdel(&help_v);
    }
}

void mx_add_count_link(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **links_arr = (char **)malloc(sizeof(char*) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        links_arr[i] = mx_count_links(file);
    }
    links_arr[count_of_row] = NULL;
    mx_add_count_link_help(mas_for_print, count_of_row, links_arr);
    mx_del_strarr(&links_arr);
    return;
}

void mx_add_ownew_name(char **mas_for_print, int count_of_row, char **files) {
    int i;
    struct stat file;
    char **help_arr = (char **)malloc(sizeof(char **) * count_of_row + 1);

    for (i = 0; i < count_of_row; i++) {
        lstat(files[i], &file);
        help_arr[i] = mx_owner_name(file);
    }
    help_arr[count_of_row] = NULL;
    mx_add_ownew_name_help(mas_for_print, count_of_row, help_arr);
    mx_del_strarr(&help_arr);
    return;
}
