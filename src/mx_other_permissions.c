#include "../inc/uls.h"  

static void S_x_s(struct stat file, char **str) {
    char *tmp;

    tmp = *str;
    if ((file.st_mode & MX_IXOTH) == MX_IXOTH) {
        if ((file.st_mode & MX_ISTXT) == MX_ISTXT)
            *str = mx_strcat(tmp, "t");
        else
            *str = mx_strcat(tmp, "x");
    }
    else {
        if ((file.st_mode & MX_ISTXT) == MX_ISTXT)
            *str = mx_strcat(tmp, "T");
        else
            *str = mx_strcat(tmp, "-");
    }
    mx_strdel(&tmp);
}

void mx_other_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & MX_IROTH) == MX_IROTH)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & MX_IWOTH) == MX_IWOTH)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    S_x_s(file, str);
}
