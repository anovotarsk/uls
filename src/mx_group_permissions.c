#include "../inc/uls.h" 

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXGRP) == MX_IXGRP) {
        if ((file.st_mode & MX_ISGID) == MX_ISGID)
            *str = mx_strcat(tmp, "s");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISGID) == MX_ISGID)
            *str = mx_strcat(tmp, "S");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_group_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IRGRP) == MX_IRGRP)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWGRP) == MX_IWGRP)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
