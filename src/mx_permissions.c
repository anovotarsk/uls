#include "../inc/uls.h"

static void type_of_file_1(struct stat file, char **str) {
    char *tmp = *str;

    switch (file.st_mode & MX_IFMT) {
        case MX_IFCHR:
            *str = mx_strcat(tmp, "c");
            break;
        case MX_IFIFO:
            *str = mx_strcat(tmp, "p");
            break;
        default:
            *str = mx_strcat(tmp, "-");
            break;
    }
}

static void type_of_file(struct stat file, char **str) {
    char *tmp = *str;

    switch (file.st_mode & MX_IFMT) {
        case MX_IFSOCK:
            *str = mx_strcat(tmp, "s");
            break;
        case MX_IFLNK:
            *str = mx_strcat(tmp, "l");
            break;
        case MX_IFBLK:
            *str = mx_strcat(tmp, "b");
            break;
        case MX_IFDIR:
            *str = mx_strcat(tmp, "d");
            break;
        default:
            type_of_file_1(file, str);
            break;
        }
    mx_strdel(&tmp);
}

// static void type_of_file(struct stat file, char **str) {
//     char *tmp = *str;

//     if ((file.st_mode & MX_IFMT) == MX_IFSOCK)
//         *str = mx_strcat(tmp, "s");
//     if ((file.st_mode & MX_IFMT) == MX_IFLNK)
//         *str = mx_strcat(tmp, "l");
//     if ((file.st_mode & MX_IFMT) == MX_IFREG)
//         *str = mx_strcat(tmp, "-");
//     if ((file.st_mode & MX_IFMT) == MX_IFBLK)
//         *str = mx_strcat(tmp, "b");
//     if ((file.st_mode & MX_IFMT) == MX_IFDIR)
//         *str = mx_strcat(tmp, "d");
//     if ((file.st_mode & MX_IFMT) == MX_IFCHR)
//         *str = mx_strcat(tmp, "c");
//     if ((file.st_mode & MX_IFMT) == MX_IFIFO)
//         *str = mx_strcat(tmp, "p");
//     mx_strdel(&tmp);
// }

char * mx_permissions(char *f) {
    char * permissions = mx_strnew(0);
    struct stat file;

    lstat(f, &file);
    type_of_file(file, &permissions);
    mx_owner_permissions(file, &permissions);
    mx_group_permissions(file, &permissions);
    mx_other_permissions(file, &permissions);
    mx_attr_or_acl(f, &permissions);
    return permissions;
}
