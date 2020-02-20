#include "../inc/uls.h"

static void add_hours(char **date, char *hours) {
    char **arr = mx_strsplit(hours, ':');
    char *tmp = *date;

    *date = mx_strcat(tmp, " ");
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, arr[0]);
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, ":");
    mx_strdel(&tmp);
    tmp = *date;
    *date = mx_strcat(tmp, arr[1]);
    mx_strdel(&tmp);
    mx_del_strarr(&arr);
}

char *mx_time(struct stat file) {
    char *date = ctime(&file.st_mtimespec.tv_sec);
    char **date_arr = mx_strsplit(date, ' ');
    char *tmp;

    date = mx_strcat(date_arr[1], " ");
    tmp = date;
    date = mx_strcat(tmp, date_arr[2]);
    mx_strdel(&tmp);
    if (time(NULL) - MX_HALF_YEAR < file.st_mtimespec.tv_sec)
        add_hours(&date, date_arr[3]);
    else {
        tmp = date;
        date = mx_strcat(tmp, "  ");
        mx_strdel(&tmp);
        tmp = date;
        date = mx_strcat(tmp, date_arr[4]);
        mx_strdel(&tmp);
    }
    mx_del_strarr(&date_arr);
    return date;
}
