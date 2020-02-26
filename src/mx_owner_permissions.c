#include "../inc/uls.h"

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXUSR) == MX_IXUSR) {
        if ((file.st_mode & MX_ISUID) == MX_ISUID)
            *str = mx_strcat(tmp, "s");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISUID) == MX_ISUID)
            *str = mx_strcat(tmp, "S");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_owner_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IRUSR) == MX_IRUSR)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWUSR) == MX_IWUSR)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
