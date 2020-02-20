#include "../inc/uls.h"

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & S_IXUSR) == S_IXUSR) {
        if ((file.st_mode & S_ISUID) == S_ISUID)
            *str = mx_strcat(tmp, "s");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & S_ISUID) == S_ISUID)
            *str = mx_strcat(tmp, "S");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_owner_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & S_IRUSR) == S_IRUSR)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & S_IWUSR) == S_IWUSR)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
