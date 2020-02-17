#include "../inc/uls.h"

static void type_of_file(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & S_IFMT) == S_IFSOCK)
        *str = mx_strcat(tmp, "s");
    if ((file.st_mode & S_IFMT) == S_IFLNK)
        *str = mx_strcat(tmp, "l");
    if ((file.st_mode & S_IFMT) == S_IFREG)
        *str = mx_strcat(tmp, "-");
    if ((file.st_mode & S_IFMT) == S_IFBLK)
        *str = mx_strcat(tmp, "b");
    if ((file.st_mode & S_IFMT) == S_IFDIR)
        *str = mx_strcat(tmp, "d");
    if ((file.st_mode & S_IFMT) == S_IFCHR)
        *str = mx_strcat(tmp, "c");
    if ((file.st_mode & S_IFMT) == S_IFIFO)
        *str = mx_strcat(tmp, "p");
    mx_strdel(&tmp);
}

static void owner_permissions(struct stat file, char **str) {
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
    tmp = *str;
    if ((file.st_mode & S_IXUSR) == S_IXUSR)
        *str = mx_strcat(tmp, "x");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
}

static void group_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & S_IRGRP) == S_IRGRP)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & S_IWGRP) == S_IWGRP)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & S_IXGRP) == S_IXGRP)
        *str = mx_strcat(tmp, "x");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
}

static void other_permissions(struct stat file, char **str) {
    char *tmp = *str;

    if ((file.st_mode & S_IROTH) == S_IROTH)
        *str = mx_strcat(tmp, "r");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & S_IWOTH) == S_IWOTH)
        *str = mx_strcat(tmp, "w");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
    tmp = *str;
    if ((file.st_mode & S_IXOTH) == S_IXOTH)
        *str = mx_strcat(tmp, "x");
    else
        *str = mx_strcat(tmp, "-");
    mx_strdel(&tmp);
}

char * mx_permissions(struct stat file) {
    char * permissions = mx_strnew(0);

    type_of_file(file, &permissions);
    owner_permissions(file, &permissions);
    group_permissions(file, &permissions);
    other_permissions(file, &permissions);
    return permissions;
}
