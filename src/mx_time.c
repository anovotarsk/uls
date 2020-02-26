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

static void add_day(char **date, char *day, char *year) {
    char *tmp = *date;
    char *day_tmp;

    year[4] = '\0';
    day = mx_strdup(day);
    while (mx_strlen(day) < 2) {
        day_tmp = day;
        day = mx_strcat(" ", day_tmp);
        mx_strdel(&day_tmp);
    }
    *date = mx_strcat(tmp, day);
    mx_strdel(&day);
    mx_strdel(&tmp);
}

static char *time_T_flag(char *str, char ***arr_to_del) {
    mx_del_strarr(arr_to_del);
    str++;
    str++;
    str++;
    str++;
    str[mx_strlen(str) - 1] = '\0';
    return mx_strdup(str);
}

static void hours_or_year(char **date, char **date_arr, struct stat file) {
    char *tmp;

    if (time(NULL) - MX_HALF_YEAR < file.st_mtimespec.tv_sec
        && file.st_mtimespec.tv_sec < time(NULL))
        add_hours(date, date_arr[3]);
    else {
        tmp = *date;
        *date = mx_strcat(tmp, "  ");
        mx_strdel(&tmp);
        tmp = *date;
        *date = mx_strcat(tmp, date_arr[4]);
        mx_strdel(&tmp);
    }
}

char *mx_time(struct stat file, t_flags *flags) {
    char *date = ctime(&file.st_mtimespec.tv_sec);
    char **date_arr = mx_strsplit(date, ' ');

    if (mx_flag_search('T', flags) == true)
        return time_T_flag(date, &date_arr);
    date = mx_strcat(date_arr[1], " ");
    add_day(&date, date_arr[2], date_arr[4]);
    hours_or_year(&date, date_arr, file);
    mx_del_strarr(&date_arr);
    return date;
}
